/*
 * PowerNV setup code.
 *
 * Copyright 2011 IBM Corp.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#undef DEBUG

#include <linux/cpu.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/tty.h>
#include <linux/reboot.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <linux/seq_file.h>
#include <linux/of.h>
#include <linux/of_fdt.h>
#include <linux/interrupt.h>
#include <linux/bug.h>
#include <linux/pci.h>
#include <linux/cpufreq.h>
#include <linux/cpuidle.h>

#include <asm/machdep.h>
#include <asm/firmware.h>
#include <asm/xics.h>
#include <asm/opal.h>
#include <asm/kexec.h>
#include <asm/smp.h>
#include <asm/cputhreads.h>
#include <asm/cpuidle.h>
#include <asm/code-patching.h>
#include <asm/setup.h>
#include <asm/security_features.h>

#include "powernv.h"
#include "subcore.h"


static bool fw_feature_is(const char *state, const char *name,
			  struct device_node *fw_features)
{
	struct device_node *np;
	bool rc = false;

	np = of_get_child_by_name(fw_features, name);
	if (np) {
		rc = of_property_read_bool(np, state);
		of_node_put(np);
	}

	return rc;
}

static void init_fw_feat_flags(struct device_node *np)
{
	if (fw_feature_is("enabled", "inst-spec-barrier-ori31,31,0", np))
		security_ftr_set(SEC_FTR_SPEC_BAR_ORI31);

	if (fw_feature_is("enabled", "fw-bcctrl-serialized", np))
		security_ftr_set(SEC_FTR_BCCTRL_SERIALISED);

	if (fw_feature_is("enabled", "inst-l1d-flush-ori30,30,0", np))
		security_ftr_set(SEC_FTR_L1D_FLUSH_ORI30);

	if (fw_feature_is("enabled", "inst-l1d-flush-trig2", np))
		security_ftr_set(SEC_FTR_L1D_FLUSH_TRIG2);

	if (fw_feature_is("enabled", "fw-l1d-thread-split", np))
		security_ftr_set(SEC_FTR_L1D_THREAD_PRIV);

	if (fw_feature_is("enabled", "fw-count-cache-disabled", np))
		security_ftr_set(SEC_FTR_COUNT_CACHE_DISABLED);

	if (fw_feature_is("enabled", "fw-count-cache-flush-bcctr2,0,0", np))
		security_ftr_set(SEC_FTR_BCCTR_FLUSH_ASSIST);

	if (fw_feature_is("enabled", "needs-count-cache-flush-on-context-switch", np))
		security_ftr_set(SEC_FTR_FLUSH_COUNT_CACHE);

	/*
	 * The features below are enabled by default, so we instead look to see
	 * if firmware has *disabled* them, and clear them if so.
	 */
	if (fw_feature_is("disabled", "speculation-policy-favor-security", np))
		security_ftr_clear(SEC_FTR_FAVOUR_SECURITY);

	if (fw_feature_is("disabled", "needs-l1d-flush-msr-pr-0-to-1", np))
		security_ftr_clear(SEC_FTR_L1D_FLUSH_PR);

	if (fw_feature_is("disabled", "needs-l1d-flush-msr-hv-1-to-0", np))
		security_ftr_clear(SEC_FTR_L1D_FLUSH_HV);

	if (fw_feature_is("disabled", "needs-spec-barrier-for-bound-checks", np))
		security_ftr_clear(SEC_FTR_BNDS_CHK_SPEC_BAR);
}

static void pnv_setup_rfi_flush(void)
{
	struct device_node *np, *fw_features;
	enum l1d_flush_type type;
	bool enable;

	/* Default to fallback in case fw-features are not available */
	type = L1D_FLUSH_FALLBACK;

	np = of_find_node_by_name(NULL, "ibm,opal");
	fw_features = of_get_child_by_name(np, "fw-features");
	of_node_put(np);

	if (fw_features) {
		init_fw_feat_flags(fw_features);
		of_node_put(fw_features);

		if (security_ftr_enabled(SEC_FTR_L1D_FLUSH_TRIG2))
			type = L1D_FLUSH_MTTRIG;

		if (security_ftr_enabled(SEC_FTR_L1D_FLUSH_ORI30))
			type = L1D_FLUSH_ORI;
	}

	enable = security_ftr_enabled(SEC_FTR_FAVOUR_SECURITY) && \
		 (security_ftr_enabled(SEC_FTR_L1D_FLUSH_PR)   || \
		  security_ftr_enabled(SEC_FTR_L1D_FLUSH_HV));

	setup_rfi_flush(type, enable);
	setup_count_cache_flush();
}

static void __init pnv_setup_arch(void)
{
	set_arch_panic_timeout(10, ARCH_PANIC_TIMEOUT);

	pnv_setup_rfi_flush();
	setup_stf_barrier();

	/* Initialize SMP */
	pnv_smp_init();

	/* Setup PCI */
	pnv_pci_init();

	/* Setup RTC and NVRAM callbacks */
	if (firmware_has_feature(FW_FEATURE_OPAL))
		opal_nvram_init();

	/* Enable NAP mode */
	powersave_nap = 1;

	/* XXX PMCS */
}

static void __init pnv_init_early(void)
{
	/*
	 * Initialize the LPC bus now so that legacy serial
	 * ports can be found on it
	 */
	opal_lpc_init();

#ifdef CONFIG_HVC_OPAL
	if (firmware_has_feature(FW_FEATURE_OPAL))
		hvc_opal_init_early();
	else
#endif
		add_preferred_console("hvc", 0, NULL);
}

static void __init pnv_init_IRQ(void)
{
	xics_init();

	WARN_ON(!ppc_md.get_irq);
}

static void pnv_show_cpuinfo(struct seq_file *m)
{
	struct device_node *root;
	const char *model = "";

	root = of_find_node_by_path("/");
	if (root)
		model = of_get_property(root, "model", NULL);
	seq_printf(m, "machine\t\t: PowerNV %s\n", model);
	if (firmware_has_feature(FW_FEATURE_OPALv3))
		seq_printf(m, "firmware\t: OPAL v3\n");
	else if (firmware_has_feature(FW_FEATURE_OPALv2))
		seq_printf(m, "firmware\t: OPAL v2\n");
	else if (firmware_has_feature(FW_FEATURE_OPAL))
		seq_printf(m, "firmware\t: OPAL v1\n");
	else
		seq_printf(m, "firmware\t: BML\n");
	of_node_put(root);
}

static void pnv_prepare_going_down(void)
{
	/*
	 * Disable all notifiers from OPAL, we can't
	 * service interrupts anymore anyway
	 */
	opal_event_shutdown();

	/* Soft disable interrupts */
	local_irq_disable();

	/*
	 * Return secondary CPUs to firwmare if a flash update
	 * is pending otherwise we will get all sort of error
	 * messages about CPU being stuck etc.. This will also
	 * have the side effect of hard disabling interrupts so
	 * past this point, the kernel is effectively dead.
	 */
	opal_flash_term_callback();
}

static void  __noreturn pnv_restart(char *cmd)
{
	long rc = OPAL_BUSY;

	pnv_prepare_going_down();

	while (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) {
		rc = opal_cec_reboot();
		if (rc == OPAL_BUSY_EVENT)
			opal_poll_events(NULL);
		else
			mdelay(10);
	}
	for (;;)
		opal_poll_events(NULL);
}

static void __noreturn pnv_power_off(void)
{
	long rc = OPAL_BUSY;

	pnv_prepare_going_down();

	while (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) {
		rc = opal_cec_power_down(0);
		if (rc == OPAL_BUSY_EVENT)
			opal_poll_events(NULL);
		else
			mdelay(10);
	}
	for (;;)
		opal_poll_events(NULL);
}

static void __noreturn pnv_halt(void)
{
	pnv_power_off();
}

static void pnv_progress(char *s, unsigned short hex)
{
}

static u64 pnv_dma_get_required_mask(struct device *dev)
{
	if (dev_is_pci(dev))
		return pnv_pci_dma_get_required_mask(to_pci_dev(dev));

	return __dma_get_required_mask(dev);
}

static void pnv_shutdown(void)
{
	/* Let the PCI code clear up IODA tables */
	pnv_pci_shutdown();

	/*
	 * Stop OPAL activity: Unregister all OPAL interrupts so they
	 * don't fire up while we kexec and make sure all potentially
	 * DMA'ing ops are complete (such as dump retrieval).
	 */
	opal_shutdown();
}

#ifdef CONFIG_KEXEC
static void pnv_kexec_wait_secondaries_down(void)
{
	int my_cpu, i, notified = -1;

	my_cpu = get_cpu();

	for_each_online_cpu(i) {
		uint8_t status;
		int64_t rc;

		if (i == my_cpu)
			continue;

		for (;;) {
			rc = opal_query_cpu_status(get_hard_smp_processor_id(i),
						   &status);
			if (rc != OPAL_SUCCESS || status != OPAL_THREAD_STARTED)
				break;
			barrier();
			if (i != notified) {
				printk(KERN_INFO "kexec: waiting for cpu %d "
				       "(physical %d) to enter OPAL\n",
				       i, paca[i].hw_cpu_id);
				notified = i;
			}
		}
	}
}

static void pnv_kexec_cpu_down(int crash_shutdown, int secondary)
{
	xics_kexec_teardown_cpu(secondary);

	/* On OPAL v3, we return all CPUs to firmware */

	if (!firmware_has_feature(FW_FEATURE_OPALv3))
		return;

	if (secondary) {
		/* Return secondary CPUs to firmware on OPAL v3 */
		mb();
		get_paca()->kexec_state = KEXEC_STATE_REAL_MODE;
		mb();

		/* Return the CPU to OPAL */
		opal_return_cpu();
	} else if (crash_shutdown) {
		/*
		 * On crash, we don't wait for secondaries to go
		 * down as they might be unreachable or hung, so
		 * instead we just wait a bit and move on.
		 */
		mdelay(1);
	} else {
		/* Primary waits for the secondaries to have reached OPAL */
		pnv_kexec_wait_secondaries_down();
	}
}
#endif /* CONFIG_KEXEC */

#ifdef CONFIG_MEMORY_HOTPLUG_SPARSE
static unsigned long pnv_memory_block_size(void)
{
	return 256UL * 1024 * 1024;
}
#endif

static void __init pnv_setup_machdep_opal(void)
{
	ppc_md.get_boot_time = opal_get_boot_time;
	ppc_md.restart = pnv_restart;
	ppc_md.power_off = pnv_power_off;
	ppc_md.halt = pnv_halt;
	ppc_md.machine_check_exception = opal_machine_check;
	ppc_md.mce_check_early_recovery = opal_mce_check_early_recovery;
	ppc_md.hmi_exception_early = opal_hmi_exception_early;
	ppc_md.handle_hmi_exception = opal_handle_hmi_exception;
}

static u32 supported_cpuidle_states;

int pnv_save_sprs_for_winkle(void)
{
	int cpu;
	int rc;

	/*
	 * hid0, hid1, hid4, hid5, hmeer and lpcr values are symmetric accross
	 * all cpus at boot. Get these reg values of current cpu and use the
	 * same accross all cpus.
	 */
	uint64_t lpcr_val = mfspr(SPRN_LPCR) & ~(u64)LPCR_PECE1;
	uint64_t hid0_val = mfspr(SPRN_HID0);
	uint64_t hid1_val = mfspr(SPRN_HID1);
	uint64_t hid4_val = mfspr(SPRN_HID4);
	uint64_t hid5_val = mfspr(SPRN_HID5);
	uint64_t hmeer_val = mfspr(SPRN_HMEER);

	for_each_possible_cpu(cpu) {
		uint64_t pir = get_hard_smp_processor_id(cpu);
		uint64_t hsprg0_val = (uint64_t)&paca[cpu];

		/*
		 * HSPRG0 is used to store the cpu's pointer to paca. Hence last
		 * 3 bits are guaranteed to be 0. Program slw to restore HSPRG0
		 * with 63rd bit set, so that when a thread wakes up at 0x100 we
		 * can use this bit to distinguish between fastsleep and
		 * deep winkle.
		 */
		hsprg0_val |= 1;

		rc = opal_slw_set_reg(pir, SPRN_HSPRG0, hsprg0_val);
		if (rc != 0)
			return rc;

		rc = opal_slw_set_reg(pir, SPRN_LPCR, lpcr_val);
		if (rc != 0)
			return rc;

		/* HIDs are per core registers */
		if (cpu_thread_in_core(cpu) == 0) {

			rc = opal_slw_set_reg(pir, SPRN_HMEER, hmeer_val);
			if (rc != 0)
				return rc;

			rc = opal_slw_set_reg(pir, SPRN_HID0, hid0_val);
			if (rc != 0)
				return rc;

			rc = opal_slw_set_reg(pir, SPRN_HID1, hid1_val);
			if (rc != 0)
				return rc;

			rc = opal_slw_set_reg(pir, SPRN_HID4, hid4_val);
			if (rc != 0)
				return rc;

			rc = opal_slw_set_reg(pir, SPRN_HID5, hid5_val);
			if (rc != 0)
				return rc;
		}
	}

	return 0;
}

static void pnv_alloc_idle_core_states(void)
{
	int i, j;
	int nr_cores = cpu_nr_cores();
	u32 *core_idle_state;

	/*
	 * core_idle_state - First 8 bits track the idle state of each thread
	 * of the core. The 8th bit is the lock bit. Initially all thread bits
	 * are set. They are cleared when the thread enters deep idle state
	 * like sleep and winkle. Initially the lock bit is cleared.
	 * The lock bit has 2 purposes
	 * a. While the first thread is restoring core state, it prevents
	 * other threads in the core from switching to process context.
	 * b. While the last thread in the core is saving the core state, it
	 * prevents a different thread from waking up.
	 */
	for (i = 0; i < nr_cores; i++) {
		int first_cpu = i * threads_per_core;
		int node = cpu_to_node(first_cpu);

		core_idle_state = kmalloc_node(sizeof(u32), GFP_KERNEL, node);
		*core_idle_state = PNV_CORE_IDLE_THREAD_BITS;

		for (j = 0; j < threads_per_core; j++) {
			int cpu = first_cpu + j;

			paca[cpu].core_idle_state_ptr = core_idle_state;
			paca[cpu].thread_idle_state = PNV_THREAD_RUNNING;
			paca[cpu].thread_mask = 1 << j;
		}
	}

	update_subcore_sibling_mask();

	if (supported_cpuidle_states & OPAL_PM_WINKLE_ENABLED)
		pnv_save_sprs_for_winkle();
}

u32 pnv_get_supported_cpuidle_states(void)
{
	return supported_cpuidle_states;
}
EXPORT_SYMBOL_GPL(pnv_get_supported_cpuidle_states);

static int __init pnv_init_idle_states(void)
{
	struct device_node *power_mgt;
	int dt_idle_states;
	const __be32 *idle_state_flags;
	u32 len_flags, flags;
	int i;

	supported_cpuidle_states = 0;

	if (cpuidle_disable != IDLE_NO_OVERRIDE)
		return 0;

	if (!firmware_has_feature(FW_FEATURE_OPALv3))
		return 0;

	power_mgt = of_find_node_by_path("/ibm,opal/power-mgt");
	if (!power_mgt) {
		pr_warn("opal: PowerMgmt Node not found\n");
		return 0;
	}

	idle_state_flags = of_get_property(power_mgt,
			"ibm,cpu-idle-state-flags", &len_flags);
	if (!idle_state_flags) {
		pr_warn("DT-PowerMgmt: missing ibm,cpu-idle-state-flags\n");
		return 0;
	}

	dt_idle_states = len_flags / sizeof(u32);

	for (i = 0; i < dt_idle_states; i++) {
		flags = be32_to_cpu(idle_state_flags[i]);
		supported_cpuidle_states |= flags;
	}
	if (!(supported_cpuidle_states & OPAL_PM_SLEEP_ENABLED_ER1)) {
		patch_instruction(
			(unsigned int *)pnv_fastsleep_workaround_at_entry,
			PPC_INST_NOP);
		patch_instruction(
			(unsigned int *)pnv_fastsleep_workaround_at_exit,
			PPC_INST_NOP);
	}
	pnv_alloc_idle_core_states();
	return 0;
}

subsys_initcall(pnv_init_idle_states);

static int __init pnv_probe(void)
{
	unsigned long root = of_get_flat_dt_root();

	if (!of_flat_dt_is_compatible(root, "ibm,powernv"))
		return 0;

	hpte_init_native();

	if (firmware_has_feature(FW_FEATURE_OPAL))
		pnv_setup_machdep_opal();

	pr_debug("PowerNV detected !\n");

	return 1;
}

/*
 * Returns the cpu frequency for 'cpu' in Hz. This is used by
 * /proc/cpuinfo
 */
unsigned long pnv_get_proc_freq(unsigned int cpu)
{
	unsigned long ret_freq;

	ret_freq = cpufreq_quick_get(cpu) * 1000ul;

	/*
	 * If the backend cpufreq driver does not exist,
         * then fallback to old way of reporting the clockrate.
	 */
	if (!ret_freq)
		ret_freq = ppc_proc_freq;
	return ret_freq;
}

void powernv_idle(void)
{
	/* Hook to cpuidle framework if available, else
	 * call on default platform idle code
	 */
	if (cpuidle_idle_call()) {
		power7_idle();
	}
}

define_machine(powernv) {
	.name			= "PowerNV",
	.probe			= pnv_probe,
	.init_early		= pnv_init_early,
	.setup_arch		= pnv_setup_arch,
	.init_IRQ		= pnv_init_IRQ,
	.show_cpuinfo		= pnv_show_cpuinfo,
	.get_proc_freq          = pnv_get_proc_freq,
	.progress		= pnv_progress,
	.machine_shutdown	= pnv_shutdown,
	.power_save             = powernv_idle,
	.calibrate_decr		= generic_calibrate_decr,
	.dma_get_required_mask	= pnv_dma_get_required_mask,
#ifdef CONFIG_KEXEC
	.kexec_cpu_down		= pnv_kexec_cpu_down,
#endif
#ifdef CONFIG_MEMORY_HOTPLUG_SPARSE
	.memory_block_size	= pnv_memory_block_size,
#endif
};
