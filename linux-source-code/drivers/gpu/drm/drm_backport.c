#include <linux/mmu_notifier.h>
#include <linux/slab.h>

/* linux/mmu_notifier.h wrappers */

#ifdef CONFIG_MMU_NOTIFIER

/* Undefine the various wrappers from drm_backport.h so we can use both the
 * drm backport versions and the current RH kernel versions
 */
#undef mmu_notifier
#undef mmu_notifier_ops

#define to_rh_drm_mmu_notifier(mn) \
	container_of(mn, struct __rh_drm_mmu_notifier, base)

static void rh_drm_mmu_notifier_release(struct mmu_notifier *mn,
					struct mm_struct *mm)
{
	struct __rh_drm_mmu_notifier *drm_mn = to_rh_drm_mmu_notifier(mn);

	drm_mn->ops->release(drm_mn, mm);
}

static int rh_drm_mmu_notifier_clear_flush_young(struct mmu_notifier *mn,
						 struct mm_struct *mm,
						 unsigned long start,
						 unsigned long end)
{
	struct __rh_drm_mmu_notifier *drm_mn = to_rh_drm_mmu_notifier(mn);

	return drm_mn->ops->clear_flush_young(drm_mn, mm, start, end);
}

static int rh_drm_mmu_notifier_clear_young(struct mmu_notifier *mn,
					   struct mm_struct *mm,
					   unsigned long start,
					   unsigned long end)
{
	struct __rh_drm_mmu_notifier *drm_mn = to_rh_drm_mmu_notifier(mn);

	return drm_mn->ops->clear_young(drm_mn, mm, start, end);
}

static int rh_drm_mmu_notifier_test_young(struct mmu_notifier *mn,
					  struct mm_struct *mm,
					  unsigned long address)
{
	struct __rh_drm_mmu_notifier *drm_mn = to_rh_drm_mmu_notifier(mn);

	return drm_mn->ops->test_young(drm_mn, mm, address);
}

static void rh_drm_mmu_notifier_change_pte(struct mmu_notifier *mn,
					   struct mm_struct *mm,
					   unsigned long address,
					   pte_t pte)
{
	struct __rh_drm_mmu_notifier *drm_mn = to_rh_drm_mmu_notifier(mn);

	drm_mn->ops->change_pte(drm_mn, mm, address, pte);
}

static void
rh_drm_mmu_notifier_invalidate_range_start(struct mmu_notifier *mn,
					   struct mm_struct *mm,
					   unsigned long start,
					   unsigned long end)
{
	struct __rh_drm_mmu_notifier *drm_mn = to_rh_drm_mmu_notifier(mn);
	struct mmu_notifier_range range = {
		.mm = mm,
		.start = start,
		.end = end,
		.blockable = true,
	};

	drm_mn->ops->invalidate_range_start(drm_mn, &range);
}

static void rh_drm_mmu_notifier_invalidate_range_end(struct mmu_notifier *mn,
						     struct mm_struct *mm,
						     unsigned long start,
						     unsigned long end)
{
	struct __rh_drm_mmu_notifier *drm_mn = to_rh_drm_mmu_notifier(mn);
	struct mmu_notifier_range range = {
		.mm = mm, .start = start, .end = end
	};

	drm_mn->ops->invalidate_range_end(drm_mn, &range);
}

void rh_drm_mmu_notifier_invalidate_range(struct mmu_notifier *mn,
					  struct mm_struct *mm,
					  unsigned long start,
					  unsigned long end)
{
	struct __rh_drm_mmu_notifier *drm_mn = to_rh_drm_mmu_notifier(mn);

	drm_mn->ops->invalidate_range(drm_mn, mm, start, end);
}

int __rh_drm_mmu_notifier_register(struct __rh_drm_mmu_notifier *mn,
				   struct mm_struct *mm,
				   int (*orig_func)(struct mmu_notifier *,
						    struct mm_struct *))
{
	memset(&mn->base_ops, 0, sizeof(mn->base_ops));
	mn->base_ops.flags = mn->ops->flags;

#define C(callback) \
	if (mn->ops->callback) \
		mn->base_ops.callback = rh_drm_mmu_notifier_ ## callback

	C(release);
	C(clear_flush_young);
	C(clear_young);
	C(test_young);
	C(change_pte);
	C(invalidate_range);
	C(invalidate_range_start);
	C(invalidate_range_end);
#undef C

	mn->base.ops = &mn->base_ops;

	return orig_func(&mn->base, mm);
}
EXPORT_SYMBOL(__rh_drm_mmu_notifier_register);

#endif /* CONFIG_MMU_NOTIFIER */
