/*
 * Perf PMU sysfs events attributes for available CPU-measurement counters
 *
 */

#include <linux/slab.h>
#include <linux/perf_event.h>


/* BEGIN: CPUM_CF COUNTER DEFINITIONS =================================== */

CPUMF_EVENT_ATTR(cf_fvn1, CPU_CYCLES, 0x0000);
CPUMF_EVENT_ATTR(cf_fvn1, INSTRUCTIONS, 0x0001);
CPUMF_EVENT_ATTR(cf_fvn1, L1I_DIR_WRITES, 0x0002);
CPUMF_EVENT_ATTR(cf_fvn1, L1I_PENALTY_CYCLES, 0x0003);
CPUMF_EVENT_ATTR(cf_fvn1, PROBLEM_STATE_CPU_CYCLES, 0x0020);
CPUMF_EVENT_ATTR(cf_fvn1, PROBLEM_STATE_INSTRUCTIONS, 0x0021);
CPUMF_EVENT_ATTR(cf_fvn1, PROBLEM_STATE_L1I_DIR_WRITES, 0x0022);
CPUMF_EVENT_ATTR(cf_fvn1, PROBLEM_STATE_L1I_PENALTY_CYCLES, 0x0023);
CPUMF_EVENT_ATTR(cf_fvn1, PROBLEM_STATE_L1D_DIR_WRITES, 0x0024);
CPUMF_EVENT_ATTR(cf_fvn1, PROBLEM_STATE_L1D_PENALTY_CYCLES, 0x0025);
CPUMF_EVENT_ATTR(cf_fvn1, L1D_DIR_WRITES, 0x0004);
CPUMF_EVENT_ATTR(cf_fvn1, L1D_PENALTY_CYCLES, 0x0005);
CPUMF_EVENT_ATTR(cf_fvn3, CPU_CYCLES, 0x0000);
CPUMF_EVENT_ATTR(cf_fvn3, INSTRUCTIONS, 0x0001);
CPUMF_EVENT_ATTR(cf_fvn3, L1I_DIR_WRITES, 0x0002);
CPUMF_EVENT_ATTR(cf_fvn3, L1I_PENALTY_CYCLES, 0x0003);
CPUMF_EVENT_ATTR(cf_fvn3, PROBLEM_STATE_CPU_CYCLES, 0x0020);
CPUMF_EVENT_ATTR(cf_fvn3, PROBLEM_STATE_INSTRUCTIONS, 0x0021);
CPUMF_EVENT_ATTR(cf_fvn3, L1D_DIR_WRITES, 0x0004);
CPUMF_EVENT_ATTR(cf_fvn3, L1D_PENALTY_CYCLES, 0x0005);
CPUMF_EVENT_ATTR(cf_svn_12345, PRNG_FUNCTIONS, 0x0040);
CPUMF_EVENT_ATTR(cf_svn_12345, PRNG_CYCLES, 0x0041);
CPUMF_EVENT_ATTR(cf_svn_12345, PRNG_BLOCKED_FUNCTIONS, 0x0042);
CPUMF_EVENT_ATTR(cf_svn_12345, PRNG_BLOCKED_CYCLES, 0x0043);
CPUMF_EVENT_ATTR(cf_svn_12345, SHA_FUNCTIONS, 0x0044);
CPUMF_EVENT_ATTR(cf_svn_12345, SHA_CYCLES, 0x0045);
CPUMF_EVENT_ATTR(cf_svn_12345, SHA_BLOCKED_FUNCTIONS, 0x0046);
CPUMF_EVENT_ATTR(cf_svn_12345, SHA_BLOCKED_CYCLES, 0x0047);
CPUMF_EVENT_ATTR(cf_svn_12345, DEA_FUNCTIONS, 0x0048);
CPUMF_EVENT_ATTR(cf_svn_12345, DEA_CYCLES, 0x0049);
CPUMF_EVENT_ATTR(cf_svn_12345, DEA_BLOCKED_FUNCTIONS, 0x004a);
CPUMF_EVENT_ATTR(cf_svn_12345, DEA_BLOCKED_CYCLES, 0x004b);
CPUMF_EVENT_ATTR(cf_svn_12345, AES_FUNCTIONS, 0x004c);
CPUMF_EVENT_ATTR(cf_svn_12345, AES_CYCLES, 0x004d);
CPUMF_EVENT_ATTR(cf_svn_12345, AES_BLOCKED_FUNCTIONS, 0x004e);
CPUMF_EVENT_ATTR(cf_svn_12345, AES_BLOCKED_CYCLES, 0x004f);
CPUMF_EVENT_ATTR(cf_svn_6, ECC_FUNCTION_COUNT, 0x0050);
CPUMF_EVENT_ATTR(cf_svn_6, ECC_CYCLES_COUNT, 0x0051);
CPUMF_EVENT_ATTR(cf_svn_6, ECC_BLOCKED_FUNCTION_COUNT, 0x0052);
CPUMF_EVENT_ATTR(cf_svn_6, ECC_BLOCKED_CYCLES_COUNT, 0x0053);
CPUMF_EVENT_ATTR(cf_z10, L1I_L2_SOURCED_WRITES, 0x0080);
CPUMF_EVENT_ATTR(cf_z10, L1D_L2_SOURCED_WRITES, 0x0081);
CPUMF_EVENT_ATTR(cf_z10, L1I_L3_LOCAL_WRITES, 0x0082);
CPUMF_EVENT_ATTR(cf_z10, L1D_L3_LOCAL_WRITES, 0x0083);
CPUMF_EVENT_ATTR(cf_z10, L1I_L3_REMOTE_WRITES, 0x0084);
CPUMF_EVENT_ATTR(cf_z10, L1D_L3_REMOTE_WRITES, 0x0085);
CPUMF_EVENT_ATTR(cf_z10, L1D_LMEM_SOURCED_WRITES, 0x0086);
CPUMF_EVENT_ATTR(cf_z10, L1I_LMEM_SOURCED_WRITES, 0x0087);
CPUMF_EVENT_ATTR(cf_z10, L1D_RO_EXCL_WRITES, 0x0088);
CPUMF_EVENT_ATTR(cf_z10, L1I_CACHELINE_INVALIDATES, 0x0089);
CPUMF_EVENT_ATTR(cf_z10, ITLB1_WRITES, 0x008a);
CPUMF_EVENT_ATTR(cf_z10, DTLB1_WRITES, 0x008b);
CPUMF_EVENT_ATTR(cf_z10, TLB2_PTE_WRITES, 0x008c);
CPUMF_EVENT_ATTR(cf_z10, TLB2_CRSTE_WRITES, 0x008d);
CPUMF_EVENT_ATTR(cf_z10, TLB2_CRSTE_HPAGE_WRITES, 0x008e);
CPUMF_EVENT_ATTR(cf_z10, ITLB1_MISSES, 0x0091);
CPUMF_EVENT_ATTR(cf_z10, DTLB1_MISSES, 0x0092);
CPUMF_EVENT_ATTR(cf_z10, L2C_STORES_SENT, 0x0093);
CPUMF_EVENT_ATTR(cf_z196, L1D_L2_SOURCED_WRITES, 0x0080);
CPUMF_EVENT_ATTR(cf_z196, L1I_L2_SOURCED_WRITES, 0x0081);
CPUMF_EVENT_ATTR(cf_z196, DTLB1_MISSES, 0x0082);
CPUMF_EVENT_ATTR(cf_z196, ITLB1_MISSES, 0x0083);
CPUMF_EVENT_ATTR(cf_z196, L2C_STORES_SENT, 0x0085);
CPUMF_EVENT_ATTR(cf_z196, L1D_OFFBOOK_L3_SOURCED_WRITES, 0x0086);
CPUMF_EVENT_ATTR(cf_z196, L1D_ONBOOK_L4_SOURCED_WRITES, 0x0087);
CPUMF_EVENT_ATTR(cf_z196, L1I_ONBOOK_L4_SOURCED_WRITES, 0x0088);
CPUMF_EVENT_ATTR(cf_z196, L1D_RO_EXCL_WRITES, 0x0089);
CPUMF_EVENT_ATTR(cf_z196, L1D_OFFBOOK_L4_SOURCED_WRITES, 0x008a);
CPUMF_EVENT_ATTR(cf_z196, L1I_OFFBOOK_L4_SOURCED_WRITES, 0x008b);
CPUMF_EVENT_ATTR(cf_z196, DTLB1_HPAGE_WRITES, 0x008c);
CPUMF_EVENT_ATTR(cf_z196, L1D_LMEM_SOURCED_WRITES, 0x008d);
CPUMF_EVENT_ATTR(cf_z196, L1I_LMEM_SOURCED_WRITES, 0x008e);
CPUMF_EVENT_ATTR(cf_z196, L1I_OFFBOOK_L3_SOURCED_WRITES, 0x008f);
CPUMF_EVENT_ATTR(cf_z196, DTLB1_WRITES, 0x0090);
CPUMF_EVENT_ATTR(cf_z196, ITLB1_WRITES, 0x0091);
CPUMF_EVENT_ATTR(cf_z196, TLB2_PTE_WRITES, 0x0092);
CPUMF_EVENT_ATTR(cf_z196, TLB2_CRSTE_HPAGE_WRITES, 0x0093);
CPUMF_EVENT_ATTR(cf_z196, TLB2_CRSTE_WRITES, 0x0094);
CPUMF_EVENT_ATTR(cf_z196, L1D_ONCHIP_L3_SOURCED_WRITES, 0x0096);
CPUMF_EVENT_ATTR(cf_z196, L1D_OFFCHIP_L3_SOURCED_WRITES, 0x0098);
CPUMF_EVENT_ATTR(cf_z196, L1I_ONCHIP_L3_SOURCED_WRITES, 0x0099);
CPUMF_EVENT_ATTR(cf_z196, L1I_OFFCHIP_L3_SOURCED_WRITES, 0x009b);
CPUMF_EVENT_ATTR(cf_zec12, DTLB1_MISSES, 0x0080);
CPUMF_EVENT_ATTR(cf_zec12, ITLB1_MISSES, 0x0081);
CPUMF_EVENT_ATTR(cf_zec12, L1D_L2I_SOURCED_WRITES, 0x0082);
CPUMF_EVENT_ATTR(cf_zec12, L1I_L2I_SOURCED_WRITES, 0x0083);
CPUMF_EVENT_ATTR(cf_zec12, L1D_L2D_SOURCED_WRITES, 0x0084);
CPUMF_EVENT_ATTR(cf_zec12, DTLB1_WRITES, 0x0085);
CPUMF_EVENT_ATTR(cf_zec12, L1D_LMEM_SOURCED_WRITES, 0x0087);
CPUMF_EVENT_ATTR(cf_zec12, L1I_LMEM_SOURCED_WRITES, 0x0089);
CPUMF_EVENT_ATTR(cf_zec12, L1D_RO_EXCL_WRITES, 0x008a);
CPUMF_EVENT_ATTR(cf_zec12, DTLB1_HPAGE_WRITES, 0x008b);
CPUMF_EVENT_ATTR(cf_zec12, ITLB1_WRITES, 0x008c);
CPUMF_EVENT_ATTR(cf_zec12, TLB2_PTE_WRITES, 0x008d);
CPUMF_EVENT_ATTR(cf_zec12, TLB2_CRSTE_HPAGE_WRITES, 0x008e);
CPUMF_EVENT_ATTR(cf_zec12, TLB2_CRSTE_WRITES, 0x008f);
CPUMF_EVENT_ATTR(cf_zec12, L1D_ONCHIP_L3_SOURCED_WRITES, 0x0090);
CPUMF_EVENT_ATTR(cf_zec12, L1D_OFFCHIP_L3_SOURCED_WRITES, 0x0091);
CPUMF_EVENT_ATTR(cf_zec12, L1D_OFFBOOK_L3_SOURCED_WRITES, 0x0092);
CPUMF_EVENT_ATTR(cf_zec12, L1D_ONBOOK_L4_SOURCED_WRITES, 0x0093);
CPUMF_EVENT_ATTR(cf_zec12, L1D_OFFBOOK_L4_SOURCED_WRITES, 0x0094);
CPUMF_EVENT_ATTR(cf_zec12, TX_NC_TEND, 0x0095);
CPUMF_EVENT_ATTR(cf_zec12, L1D_ONCHIP_L3_SOURCED_WRITES_IV, 0x0096);
CPUMF_EVENT_ATTR(cf_zec12, L1D_OFFCHIP_L3_SOURCED_WRITES_IV, 0x0097);
CPUMF_EVENT_ATTR(cf_zec12, L1D_OFFBOOK_L3_SOURCED_WRITES_IV, 0x0098);
CPUMF_EVENT_ATTR(cf_zec12, L1I_ONCHIP_L3_SOURCED_WRITES, 0x0099);
CPUMF_EVENT_ATTR(cf_zec12, L1I_OFFCHIP_L3_SOURCED_WRITES, 0x009a);
CPUMF_EVENT_ATTR(cf_zec12, L1I_OFFBOOK_L3_SOURCED_WRITES, 0x009b);
CPUMF_EVENT_ATTR(cf_zec12, L1I_ONBOOK_L4_SOURCED_WRITES, 0x009c);
CPUMF_EVENT_ATTR(cf_zec12, L1I_OFFBOOK_L4_SOURCED_WRITES, 0x009d);
CPUMF_EVENT_ATTR(cf_zec12, TX_C_TEND, 0x009e);
CPUMF_EVENT_ATTR(cf_zec12, L1I_ONCHIP_L3_SOURCED_WRITES_IV, 0x009f);
CPUMF_EVENT_ATTR(cf_zec12, L1I_OFFCHIP_L3_SOURCED_WRITES_IV, 0x00a0);
CPUMF_EVENT_ATTR(cf_zec12, L1I_OFFBOOK_L3_SOURCED_WRITES_IV, 0x00a1);
CPUMF_EVENT_ATTR(cf_zec12, TX_NC_TABORT, 0x00b1);
CPUMF_EVENT_ATTR(cf_zec12, TX_C_TABORT_NO_SPECIAL, 0x00b2);
CPUMF_EVENT_ATTR(cf_zec12, TX_C_TABORT_SPECIAL, 0x00b3);
CPUMF_EVENT_ATTR(cf_z13, L1D_RO_EXCL_WRITES, 0x0080);
CPUMF_EVENT_ATTR(cf_z13, DTLB1_WRITES, 0x0081);
CPUMF_EVENT_ATTR(cf_z13, DTLB1_MISSES, 0x0082);
CPUMF_EVENT_ATTR(cf_z13, DTLB1_HPAGE_WRITES, 0x0083);
CPUMF_EVENT_ATTR(cf_z13, DTLB1_GPAGE_WRITES, 0x0084);
CPUMF_EVENT_ATTR(cf_z13, L1D_L2D_SOURCED_WRITES, 0x0085);
CPUMF_EVENT_ATTR(cf_z13, ITLB1_WRITES, 0x0086);
CPUMF_EVENT_ATTR(cf_z13, ITLB1_MISSES, 0x0087);
CPUMF_EVENT_ATTR(cf_z13, L1I_L2I_SOURCED_WRITES, 0x0088);
CPUMF_EVENT_ATTR(cf_z13, TLB2_PTE_WRITES, 0x0089);
CPUMF_EVENT_ATTR(cf_z13, TLB2_CRSTE_HPAGE_WRITES, 0x008a);
CPUMF_EVENT_ATTR(cf_z13, TLB2_CRSTE_WRITES, 0x008b);
CPUMF_EVENT_ATTR(cf_z13, TX_C_TEND, 0x008c);
CPUMF_EVENT_ATTR(cf_z13, TX_NC_TEND, 0x008d);
CPUMF_EVENT_ATTR(cf_z13, L1C_TLB1_MISSES, 0x008f);
CPUMF_EVENT_ATTR(cf_z13, L1D_ONCHIP_L3_SOURCED_WRITES, 0x0090);
CPUMF_EVENT_ATTR(cf_z13, L1D_ONCHIP_L3_SOURCED_WRITES_IV, 0x0091);
CPUMF_EVENT_ATTR(cf_z13, L1D_ONNODE_L4_SOURCED_WRITES, 0x0092);
CPUMF_EVENT_ATTR(cf_z13, L1D_ONNODE_L3_SOURCED_WRITES_IV, 0x0093);
CPUMF_EVENT_ATTR(cf_z13, L1D_ONNODE_L3_SOURCED_WRITES, 0x0094);
CPUMF_EVENT_ATTR(cf_z13, L1D_ONDRAWER_L4_SOURCED_WRITES, 0x0095);
CPUMF_EVENT_ATTR(cf_z13, L1D_ONDRAWER_L3_SOURCED_WRITES_IV, 0x0096);
CPUMF_EVENT_ATTR(cf_z13, L1D_ONDRAWER_L3_SOURCED_WRITES, 0x0097);
CPUMF_EVENT_ATTR(cf_z13, L1D_OFFDRAWER_SCOL_L4_SOURCED_WRITES, 0x0098);
CPUMF_EVENT_ATTR(cf_z13, L1D_OFFDRAWER_SCOL_L3_SOURCED_WRITES_IV, 0x0099);
CPUMF_EVENT_ATTR(cf_z13, L1D_OFFDRAWER_SCOL_L3_SOURCED_WRITES, 0x009a);
CPUMF_EVENT_ATTR(cf_z13, L1D_OFFDRAWER_FCOL_L4_SOURCED_WRITES, 0x009b);
CPUMF_EVENT_ATTR(cf_z13, L1D_OFFDRAWER_FCOL_L3_SOURCED_WRITES_IV, 0x009c);
CPUMF_EVENT_ATTR(cf_z13, L1D_OFFDRAWER_FCOL_L3_SOURCED_WRITES, 0x009d);
CPUMF_EVENT_ATTR(cf_z13, L1D_ONNODE_MEM_SOURCED_WRITES, 0x009e);
CPUMF_EVENT_ATTR(cf_z13, L1D_ONDRAWER_MEM_SOURCED_WRITES, 0x009f);
CPUMF_EVENT_ATTR(cf_z13, L1D_OFFDRAWER_MEM_SOURCED_WRITES, 0x00a0);
CPUMF_EVENT_ATTR(cf_z13, L1D_ONCHIP_MEM_SOURCED_WRITES, 0x00a1);
CPUMF_EVENT_ATTR(cf_z13, L1I_ONCHIP_L3_SOURCED_WRITES, 0x00a2);
CPUMF_EVENT_ATTR(cf_z13, L1I_ONCHIP_L3_SOURCED_WRITES_IV, 0x00a3);
CPUMF_EVENT_ATTR(cf_z13, L1I_ONNODE_L4_SOURCED_WRITES, 0x00a4);
CPUMF_EVENT_ATTR(cf_z13, L1I_ONNODE_L3_SOURCED_WRITES_IV, 0x00a5);
CPUMF_EVENT_ATTR(cf_z13, L1I_ONNODE_L3_SOURCED_WRITES, 0x00a6);
CPUMF_EVENT_ATTR(cf_z13, L1I_ONDRAWER_L4_SOURCED_WRITES, 0x00a7);
CPUMF_EVENT_ATTR(cf_z13, L1I_ONDRAWER_L3_SOURCED_WRITES_IV, 0x00a8);
CPUMF_EVENT_ATTR(cf_z13, L1I_ONDRAWER_L3_SOURCED_WRITES, 0x00a9);
CPUMF_EVENT_ATTR(cf_z13, L1I_OFFDRAWER_SCOL_L4_SOURCED_WRITES, 0x00aa);
CPUMF_EVENT_ATTR(cf_z13, L1I_OFFDRAWER_SCOL_L3_SOURCED_WRITES_IV, 0x00ab);
CPUMF_EVENT_ATTR(cf_z13, L1I_OFFDRAWER_SCOL_L3_SOURCED_WRITES, 0x00ac);
CPUMF_EVENT_ATTR(cf_z13, L1I_OFFDRAWER_FCOL_L4_SOURCED_WRITES, 0x00ad);
CPUMF_EVENT_ATTR(cf_z13, L1I_OFFDRAWER_FCOL_L3_SOURCED_WRITES_IV, 0x00ae);
CPUMF_EVENT_ATTR(cf_z13, L1I_OFFDRAWER_FCOL_L3_SOURCED_WRITES, 0x00af);
CPUMF_EVENT_ATTR(cf_z13, L1I_ONNODE_MEM_SOURCED_WRITES, 0x00b0);
CPUMF_EVENT_ATTR(cf_z13, L1I_ONDRAWER_MEM_SOURCED_WRITES, 0x00b1);
CPUMF_EVENT_ATTR(cf_z13, L1I_OFFDRAWER_MEM_SOURCED_WRITES, 0x00b2);
CPUMF_EVENT_ATTR(cf_z13, L1I_ONCHIP_MEM_SOURCED_WRITES, 0x00b3);
CPUMF_EVENT_ATTR(cf_z13, TX_NC_TABORT, 0x00da);
CPUMF_EVENT_ATTR(cf_z13, TX_C_TABORT_NO_SPECIAL, 0x00db);
CPUMF_EVENT_ATTR(cf_z13, TX_C_TABORT_SPECIAL, 0x00dc);
CPUMF_EVENT_ATTR(cf_z13, MT_DIAG_CYCLES_ONE_THR_ACTIVE, 0x01c0);
CPUMF_EVENT_ATTR(cf_z13, MT_DIAG_CYCLES_TWO_THR_ACTIVE, 0x01c1);
CPUMF_EVENT_ATTR(cf_z14, L1D_RO_EXCL_WRITES, 0x0080);
CPUMF_EVENT_ATTR(cf_z14, DTLB2_WRITES, 0x0081);
CPUMF_EVENT_ATTR(cf_z14, DTLB2_MISSES, 0x0082);
CPUMF_EVENT_ATTR(cf_z14, DTLB2_HPAGE_WRITES, 0x0083);
CPUMF_EVENT_ATTR(cf_z14, DTLB2_GPAGE_WRITES, 0x0084);
CPUMF_EVENT_ATTR(cf_z14, L1D_L2D_SOURCED_WRITES, 0x0085);
CPUMF_EVENT_ATTR(cf_z14, ITLB2_WRITES, 0x0086);
CPUMF_EVENT_ATTR(cf_z14, ITLB2_MISSES, 0x0087);
CPUMF_EVENT_ATTR(cf_z14, L1I_L2I_SOURCED_WRITES, 0x0088);
CPUMF_EVENT_ATTR(cf_z14, TLB2_PTE_WRITES, 0x0089);
CPUMF_EVENT_ATTR(cf_z14, TLB2_CRSTE_WRITES, 0x008a);
CPUMF_EVENT_ATTR(cf_z14, TLB2_ENGINES_BUSY, 0x008b);
CPUMF_EVENT_ATTR(cf_z14, TX_C_TEND, 0x008c);
CPUMF_EVENT_ATTR(cf_z14, TX_NC_TEND, 0x008d);
CPUMF_EVENT_ATTR(cf_z14, L1C_TLB2_MISSES, 0x008f);
CPUMF_EVENT_ATTR(cf_z14, L1D_ONCHIP_L3_SOURCED_WRITES, 0x0090);
CPUMF_EVENT_ATTR(cf_z14, L1D_ONCHIP_MEMORY_SOURCED_WRITES, 0x0091);
CPUMF_EVENT_ATTR(cf_z14, L1D_ONCHIP_L3_SOURCED_WRITES_IV, 0x0092);
CPUMF_EVENT_ATTR(cf_z14, L1D_ONCLUSTER_L3_SOURCED_WRITES, 0x0093);
CPUMF_EVENT_ATTR(cf_z14, L1D_ONCLUSTER_MEMORY_SOURCED_WRITES, 0x0094);
CPUMF_EVENT_ATTR(cf_z14, L1D_ONCLUSTER_L3_SOURCED_WRITES_IV, 0x0095);
CPUMF_EVENT_ATTR(cf_z14, L1D_OFFCLUSTER_L3_SOURCED_WRITES, 0x0096);
CPUMF_EVENT_ATTR(cf_z14, L1D_OFFCLUSTER_MEMORY_SOURCED_WRITES, 0x0097);
CPUMF_EVENT_ATTR(cf_z14, L1D_OFFCLUSTER_L3_SOURCED_WRITES_IV, 0x0098);
CPUMF_EVENT_ATTR(cf_z14, L1D_OFFDRAWER_L3_SOURCED_WRITES, 0x0099);
CPUMF_EVENT_ATTR(cf_z14, L1D_OFFDRAWER_MEMORY_SOURCED_WRITES, 0x009a);
CPUMF_EVENT_ATTR(cf_z14, L1D_OFFDRAWER_L3_SOURCED_WRITES_IV, 0x009b);
CPUMF_EVENT_ATTR(cf_z14, L1D_ONDRAWER_L4_SOURCED_WRITES, 0x009c);
CPUMF_EVENT_ATTR(cf_z14, L1D_OFFDRAWER_L4_SOURCED_WRITES, 0x009d);
CPUMF_EVENT_ATTR(cf_z14, L1D_ONCHIP_L3_SOURCED_WRITES_RO, 0x009e);
CPUMF_EVENT_ATTR(cf_z14, L1I_ONCHIP_L3_SOURCED_WRITES, 0x00a2);
CPUMF_EVENT_ATTR(cf_z14, L1I_ONCHIP_MEMORY_SOURCED_WRITES, 0x00a3);
CPUMF_EVENT_ATTR(cf_z14, L1I_ONCHIP_L3_SOURCED_WRITES_IV, 0x00a4);
CPUMF_EVENT_ATTR(cf_z14, L1I_ONCLUSTER_L3_SOURCED_WRITES, 0x00a5);
CPUMF_EVENT_ATTR(cf_z14, L1I_ONCLUSTER_MEMORY_SOURCED_WRITES, 0x00a6);
CPUMF_EVENT_ATTR(cf_z14, L1I_ONCLUSTER_L3_SOURCED_WRITES_IV, 0x00a7);
CPUMF_EVENT_ATTR(cf_z14, L1I_OFFCLUSTER_L3_SOURCED_WRITES, 0x00a8);
CPUMF_EVENT_ATTR(cf_z14, L1I_OFFCLUSTER_MEMORY_SOURCED_WRITES, 0x00a9);
CPUMF_EVENT_ATTR(cf_z14, L1I_OFFCLUSTER_L3_SOURCED_WRITES_IV, 0x00aa);
CPUMF_EVENT_ATTR(cf_z14, L1I_OFFDRAWER_L3_SOURCED_WRITES, 0x00ab);
CPUMF_EVENT_ATTR(cf_z14, L1I_OFFDRAWER_MEMORY_SOURCED_WRITES, 0x00ac);
CPUMF_EVENT_ATTR(cf_z14, L1I_OFFDRAWER_L3_SOURCED_WRITES_IV, 0x00ad);
CPUMF_EVENT_ATTR(cf_z14, L1I_ONDRAWER_L4_SOURCED_WRITES, 0x00ae);
CPUMF_EVENT_ATTR(cf_z14, L1I_OFFDRAWER_L4_SOURCED_WRITES, 0x00af);
CPUMF_EVENT_ATTR(cf_z14, BCD_DFP_EXECUTION_SLOTS, 0x00e0);
CPUMF_EVENT_ATTR(cf_z14, VX_BCD_EXECUTION_SLOTS, 0x00e1);
CPUMF_EVENT_ATTR(cf_z14, DECIMAL_INSTRUCTIONS, 0x00e2);
CPUMF_EVENT_ATTR(cf_z14, LAST_HOST_TRANSLATIONS, 0x00e8);
CPUMF_EVENT_ATTR(cf_z14, TX_NC_TABORT, 0x00f3);
CPUMF_EVENT_ATTR(cf_z14, TX_C_TABORT_NO_SPECIAL, 0x00f4);
CPUMF_EVENT_ATTR(cf_z14, TX_C_TABORT_SPECIAL, 0x00f5);
CPUMF_EVENT_ATTR(cf_z14, MT_DIAG_CYCLES_ONE_THR_ACTIVE, 0x01c0);
CPUMF_EVENT_ATTR(cf_z14, MT_DIAG_CYCLES_TWO_THR_ACTIVE, 0x01c1);

static struct attribute *cpumcf_fvn1_pmu_event_attr[] __initdata = {
	CPUMF_EVENT_PTR(cf_fvn1, CPU_CYCLES),
	CPUMF_EVENT_PTR(cf_fvn1, INSTRUCTIONS),
	CPUMF_EVENT_PTR(cf_fvn1, L1I_DIR_WRITES),
	CPUMF_EVENT_PTR(cf_fvn1, L1I_PENALTY_CYCLES),
	CPUMF_EVENT_PTR(cf_fvn1, PROBLEM_STATE_CPU_CYCLES),
	CPUMF_EVENT_PTR(cf_fvn1, PROBLEM_STATE_INSTRUCTIONS),
	CPUMF_EVENT_PTR(cf_fvn1, PROBLEM_STATE_L1I_DIR_WRITES),
	CPUMF_EVENT_PTR(cf_fvn1, PROBLEM_STATE_L1I_PENALTY_CYCLES),
	CPUMF_EVENT_PTR(cf_fvn1, PROBLEM_STATE_L1D_DIR_WRITES),
	CPUMF_EVENT_PTR(cf_fvn1, PROBLEM_STATE_L1D_PENALTY_CYCLES),
	CPUMF_EVENT_PTR(cf_fvn1, L1D_DIR_WRITES),
	CPUMF_EVENT_PTR(cf_fvn1, L1D_PENALTY_CYCLES),
	NULL,
};

static struct attribute *cpumcf_fvn3_pmu_event_attr[] __initdata = {
	CPUMF_EVENT_PTR(cf_fvn3, CPU_CYCLES),
	CPUMF_EVENT_PTR(cf_fvn3, INSTRUCTIONS),
	CPUMF_EVENT_PTR(cf_fvn3, L1I_DIR_WRITES),
	CPUMF_EVENT_PTR(cf_fvn3, L1I_PENALTY_CYCLES),
	CPUMF_EVENT_PTR(cf_fvn3, PROBLEM_STATE_CPU_CYCLES),
	CPUMF_EVENT_PTR(cf_fvn3, PROBLEM_STATE_INSTRUCTIONS),
	CPUMF_EVENT_PTR(cf_fvn3, L1D_DIR_WRITES),
	CPUMF_EVENT_PTR(cf_fvn3, L1D_PENALTY_CYCLES),
	NULL,
};

static struct attribute *cpumcf_svn_12345_pmu_event_attr[] __initdata = {
	CPUMF_EVENT_PTR(cf_svn_12345, PRNG_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, PRNG_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, PRNG_BLOCKED_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, PRNG_BLOCKED_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, SHA_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, SHA_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, SHA_BLOCKED_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, SHA_BLOCKED_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, DEA_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, DEA_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, DEA_BLOCKED_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, DEA_BLOCKED_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, AES_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, AES_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, AES_BLOCKED_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, AES_BLOCKED_CYCLES),
	NULL,
};

static struct attribute *cpumcf_svn_6_pmu_event_attr[] __initdata = {
	CPUMF_EVENT_PTR(cf_svn_12345, PRNG_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, PRNG_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, PRNG_BLOCKED_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, PRNG_BLOCKED_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, SHA_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, SHA_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, SHA_BLOCKED_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, SHA_BLOCKED_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, DEA_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, DEA_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, DEA_BLOCKED_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, DEA_BLOCKED_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, AES_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, AES_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_12345, AES_BLOCKED_FUNCTIONS),
	CPUMF_EVENT_PTR(cf_svn_12345, AES_BLOCKED_CYCLES),
	CPUMF_EVENT_PTR(cf_svn_6, ECC_FUNCTION_COUNT),
	CPUMF_EVENT_PTR(cf_svn_6, ECC_CYCLES_COUNT),
	CPUMF_EVENT_PTR(cf_svn_6, ECC_BLOCKED_FUNCTION_COUNT),
	CPUMF_EVENT_PTR(cf_svn_6, ECC_BLOCKED_CYCLES_COUNT),
	NULL,
};

static struct attribute *cpumcf_z10_pmu_event_attr[] __initdata = {
	CPUMF_EVENT_PTR(cf_z10, L1I_L2_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z10, L1D_L2_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z10, L1I_L3_LOCAL_WRITES),
	CPUMF_EVENT_PTR(cf_z10, L1D_L3_LOCAL_WRITES),
	CPUMF_EVENT_PTR(cf_z10, L1I_L3_REMOTE_WRITES),
	CPUMF_EVENT_PTR(cf_z10, L1D_L3_REMOTE_WRITES),
	CPUMF_EVENT_PTR(cf_z10, L1D_LMEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z10, L1I_LMEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z10, L1D_RO_EXCL_WRITES),
	CPUMF_EVENT_PTR(cf_z10, L1I_CACHELINE_INVALIDATES),
	CPUMF_EVENT_PTR(cf_z10, ITLB1_WRITES),
	CPUMF_EVENT_PTR(cf_z10, DTLB1_WRITES),
	CPUMF_EVENT_PTR(cf_z10, TLB2_PTE_WRITES),
	CPUMF_EVENT_PTR(cf_z10, TLB2_CRSTE_WRITES),
	CPUMF_EVENT_PTR(cf_z10, TLB2_CRSTE_HPAGE_WRITES),
	CPUMF_EVENT_PTR(cf_z10, ITLB1_MISSES),
	CPUMF_EVENT_PTR(cf_z10, DTLB1_MISSES),
	CPUMF_EVENT_PTR(cf_z10, L2C_STORES_SENT),
	NULL,
};

static struct attribute *cpumcf_z196_pmu_event_attr[] __initdata = {
	CPUMF_EVENT_PTR(cf_z196, L1D_L2_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1I_L2_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, DTLB1_MISSES),
	CPUMF_EVENT_PTR(cf_z196, ITLB1_MISSES),
	CPUMF_EVENT_PTR(cf_z196, L2C_STORES_SENT),
	CPUMF_EVENT_PTR(cf_z196, L1D_OFFBOOK_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1D_ONBOOK_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1I_ONBOOK_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1D_RO_EXCL_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1D_OFFBOOK_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1I_OFFBOOK_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, DTLB1_HPAGE_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1D_LMEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1I_LMEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1I_OFFBOOK_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, DTLB1_WRITES),
	CPUMF_EVENT_PTR(cf_z196, ITLB1_WRITES),
	CPUMF_EVENT_PTR(cf_z196, TLB2_PTE_WRITES),
	CPUMF_EVENT_PTR(cf_z196, TLB2_CRSTE_HPAGE_WRITES),
	CPUMF_EVENT_PTR(cf_z196, TLB2_CRSTE_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1D_ONCHIP_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1D_OFFCHIP_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1I_ONCHIP_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z196, L1I_OFFCHIP_L3_SOURCED_WRITES),
	NULL,
};

static struct attribute *cpumcf_zec12_pmu_event_attr[] __initdata = {
	CPUMF_EVENT_PTR(cf_zec12, DTLB1_MISSES),
	CPUMF_EVENT_PTR(cf_zec12, ITLB1_MISSES),
	CPUMF_EVENT_PTR(cf_zec12, L1D_L2I_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1I_L2I_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1D_L2D_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, DTLB1_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1D_LMEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1I_LMEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1D_RO_EXCL_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, DTLB1_HPAGE_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, ITLB1_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, TLB2_PTE_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, TLB2_CRSTE_HPAGE_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, TLB2_CRSTE_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1D_ONCHIP_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1D_OFFCHIP_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1D_OFFBOOK_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1D_ONBOOK_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1D_OFFBOOK_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, TX_NC_TEND),
	CPUMF_EVENT_PTR(cf_zec12, L1D_ONCHIP_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_zec12, L1D_OFFCHIP_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_zec12, L1D_OFFBOOK_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_zec12, L1I_ONCHIP_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1I_OFFCHIP_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1I_OFFBOOK_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1I_ONBOOK_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, L1I_OFFBOOK_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_zec12, TX_C_TEND),
	CPUMF_EVENT_PTR(cf_zec12, L1I_ONCHIP_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_zec12, L1I_OFFCHIP_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_zec12, L1I_OFFBOOK_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_zec12, TX_NC_TABORT),
	CPUMF_EVENT_PTR(cf_zec12, TX_C_TABORT_NO_SPECIAL),
	CPUMF_EVENT_PTR(cf_zec12, TX_C_TABORT_SPECIAL),
	NULL,
};

static struct attribute *cpumcf_z13_pmu_event_attr[] __initdata = {
	CPUMF_EVENT_PTR(cf_z13, L1D_RO_EXCL_WRITES),
	CPUMF_EVENT_PTR(cf_z13, DTLB1_WRITES),
	CPUMF_EVENT_PTR(cf_z13, DTLB1_MISSES),
	CPUMF_EVENT_PTR(cf_z13, DTLB1_HPAGE_WRITES),
	CPUMF_EVENT_PTR(cf_z13, DTLB1_GPAGE_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_L2D_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, ITLB1_WRITES),
	CPUMF_EVENT_PTR(cf_z13, ITLB1_MISSES),
	CPUMF_EVENT_PTR(cf_z13, L1I_L2I_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, TLB2_PTE_WRITES),
	CPUMF_EVENT_PTR(cf_z13, TLB2_CRSTE_HPAGE_WRITES),
	CPUMF_EVENT_PTR(cf_z13, TLB2_CRSTE_WRITES),
	CPUMF_EVENT_PTR(cf_z13, TX_C_TEND),
	CPUMF_EVENT_PTR(cf_z13, TX_NC_TEND),
	CPUMF_EVENT_PTR(cf_z13, L1C_TLB1_MISSES),
	CPUMF_EVENT_PTR(cf_z13, L1D_ONCHIP_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_ONCHIP_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z13, L1D_ONNODE_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_ONNODE_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z13, L1D_ONNODE_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_ONDRAWER_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_ONDRAWER_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z13, L1D_ONDRAWER_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_OFFDRAWER_SCOL_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_OFFDRAWER_SCOL_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z13, L1D_OFFDRAWER_SCOL_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_OFFDRAWER_FCOL_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_OFFDRAWER_FCOL_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z13, L1D_OFFDRAWER_FCOL_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_ONNODE_MEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_ONDRAWER_MEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_OFFDRAWER_MEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1D_ONCHIP_MEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_ONCHIP_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_ONCHIP_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z13, L1I_ONNODE_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_ONNODE_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z13, L1I_ONNODE_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_ONDRAWER_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_ONDRAWER_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z13, L1I_ONDRAWER_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_OFFDRAWER_SCOL_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_OFFDRAWER_SCOL_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z13, L1I_OFFDRAWER_SCOL_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_OFFDRAWER_FCOL_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_OFFDRAWER_FCOL_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z13, L1I_OFFDRAWER_FCOL_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_ONNODE_MEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_ONDRAWER_MEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_OFFDRAWER_MEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, L1I_ONCHIP_MEM_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z13, TX_NC_TABORT),
	CPUMF_EVENT_PTR(cf_z13, TX_C_TABORT_NO_SPECIAL),
	CPUMF_EVENT_PTR(cf_z13, TX_C_TABORT_SPECIAL),
	CPUMF_EVENT_PTR(cf_z13, MT_DIAG_CYCLES_ONE_THR_ACTIVE),
	CPUMF_EVENT_PTR(cf_z13, MT_DIAG_CYCLES_TWO_THR_ACTIVE),
	NULL,
};

static struct attribute *cpumcf_z14_pmu_event_attr[] __initdata = {
	CPUMF_EVENT_PTR(cf_z14, L1D_RO_EXCL_WRITES),
	CPUMF_EVENT_PTR(cf_z14, DTLB2_WRITES),
	CPUMF_EVENT_PTR(cf_z14, DTLB2_MISSES),
	CPUMF_EVENT_PTR(cf_z14, DTLB2_HPAGE_WRITES),
	CPUMF_EVENT_PTR(cf_z14, DTLB2_GPAGE_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1D_L2D_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, ITLB2_WRITES),
	CPUMF_EVENT_PTR(cf_z14, ITLB2_MISSES),
	CPUMF_EVENT_PTR(cf_z14, L1I_L2I_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, TLB2_PTE_WRITES),
	CPUMF_EVENT_PTR(cf_z14, TLB2_CRSTE_WRITES),
	CPUMF_EVENT_PTR(cf_z14, TLB2_ENGINES_BUSY),
	CPUMF_EVENT_PTR(cf_z14, TX_C_TEND),
	CPUMF_EVENT_PTR(cf_z14, TX_NC_TEND),
	CPUMF_EVENT_PTR(cf_z14, L1C_TLB2_MISSES),
	CPUMF_EVENT_PTR(cf_z14, L1D_ONCHIP_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1D_ONCHIP_MEMORY_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1D_ONCHIP_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z14, L1D_ONCLUSTER_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1D_ONCLUSTER_MEMORY_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1D_ONCLUSTER_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z14, L1D_OFFCLUSTER_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1D_OFFCLUSTER_MEMORY_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1D_OFFCLUSTER_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z14, L1D_OFFDRAWER_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1D_OFFDRAWER_MEMORY_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1D_OFFDRAWER_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z14, L1D_ONDRAWER_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1D_OFFDRAWER_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1D_ONCHIP_L3_SOURCED_WRITES_RO),
	CPUMF_EVENT_PTR(cf_z14, L1I_ONCHIP_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1I_ONCHIP_MEMORY_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1I_ONCHIP_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z14, L1I_ONCLUSTER_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1I_ONCLUSTER_MEMORY_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1I_ONCLUSTER_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z14, L1I_OFFCLUSTER_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1I_OFFCLUSTER_MEMORY_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1I_OFFCLUSTER_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z14, L1I_OFFDRAWER_L3_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1I_OFFDRAWER_MEMORY_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1I_OFFDRAWER_L3_SOURCED_WRITES_IV),
	CPUMF_EVENT_PTR(cf_z14, L1I_ONDRAWER_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, L1I_OFFDRAWER_L4_SOURCED_WRITES),
	CPUMF_EVENT_PTR(cf_z14, BCD_DFP_EXECUTION_SLOTS),
	CPUMF_EVENT_PTR(cf_z14, VX_BCD_EXECUTION_SLOTS),
	CPUMF_EVENT_PTR(cf_z14, DECIMAL_INSTRUCTIONS),
	CPUMF_EVENT_PTR(cf_z14, LAST_HOST_TRANSLATIONS),
	CPUMF_EVENT_PTR(cf_z14, TX_NC_TABORT),
	CPUMF_EVENT_PTR(cf_z14, TX_C_TABORT_NO_SPECIAL),
	CPUMF_EVENT_PTR(cf_z14, TX_C_TABORT_SPECIAL),
	CPUMF_EVENT_PTR(cf_z14, MT_DIAG_CYCLES_ONE_THR_ACTIVE),
	CPUMF_EVENT_PTR(cf_z14, MT_DIAG_CYCLES_TWO_THR_ACTIVE),
	NULL,
};

/* END: CPUM_CF COUNTER DEFINITIONS ===================================== */

static struct attribute_group cpumcf_pmu_events_group = {
	.name = "events",
};

PMU_FORMAT_ATTR(event, "config:0-63");

static struct attribute *cpumcf_pmu_format_attr[] = {
	&format_attr_event.attr,
	NULL,
};

static struct attribute_group cpumcf_pmu_format_group = {
	.name = "format",
	.attrs = cpumcf_pmu_format_attr,
};

static const struct attribute_group *cpumcf_pmu_attr_groups[] = {
	&cpumcf_pmu_events_group,
	&cpumcf_pmu_format_group,
	NULL,
};


static __init struct attribute **merge_attr(struct attribute **a,
					    struct attribute **b,
					    struct attribute **c)
{
	struct attribute **new;
	int j, i;

	for (j = 0; a[j]; j++)
		;
	for (i = 0; b[i]; i++)
		j++;
	for (i = 0; c[i]; i++)
		j++;
	j++;

	new = kmalloc(sizeof(struct attribute *) * j, GFP_KERNEL);
	if (!new)
		return NULL;
	j = 0;
	for (i = 0; a[i]; i++)
		new[j++] = a[i];
	for (i = 0; b[i]; i++)
		new[j++] = b[i];
	for (i = 0; c[i]; i++)
		new[j++] = c[i];
	new[j] = NULL;

	return new;
}

__init const struct attribute_group **cpumf_cf_event_group(void)
{
	struct attribute **combined, **model, **cfvn, **csvn;
	struct attribute *none[] = { NULL };
	struct cpumf_ctr_info ci;
	struct cpuid cpu_id;

	/* Determine generic counters set(s) */
	qctri(&ci);
	switch (ci.cfvn) {
	case 1:
		cfvn = cpumcf_fvn1_pmu_event_attr;
		break;
	case 3:
		cfvn = cpumcf_fvn3_pmu_event_attr;
		break;
	default:
		cfvn = none;
	}

	/* Determine version specific crypto set */
	switch (ci.csvn) {
	case 1 ... 5:
		csvn = cpumcf_svn_12345_pmu_event_attr;
		break;
	case 6:
		csvn = cpumcf_svn_6_pmu_event_attr;
		break;
	default:
		csvn = none;
	}

	/* Determine model-specific counter set(s) */
	get_cpu_id(&cpu_id);
	switch (cpu_id.machine) {
	case 0x2097:
	case 0x2098:
		model = cpumcf_z10_pmu_event_attr;
		break;
	case 0x2817:
	case 0x2818:
		model = cpumcf_z196_pmu_event_attr;
		break;
	case 0x2827:
	case 0x2828:
		model = cpumcf_zec12_pmu_event_attr;
		break;
	case 0x2964:
	case 0x2965:
		model = cpumcf_z13_pmu_event_attr;
		break;
	case 0x3906:
	case 0x3907:
	case 0x8561:
	case 0x8562:
		model = cpumcf_z14_pmu_event_attr;
		break;
	default:
		model = none;
		break;
	};

	combined = merge_attr(cfvn, csvn, model);
	if (combined)
		cpumcf_pmu_events_group.attrs = combined;
	return cpumcf_pmu_attr_groups;
}
