/*
 * Copyright (C) 2018-2024 Alibaba Group Holding Limited
 */

#ifdef CONFIG_SMP
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <csi_core.h>

#define XIAOHUI_SRESET_BASE              0x18030000
#define XIAOHUI_SRESET_ADDR_OFFSET       0x10

static struct xuantie_regs_struct {
	unsigned long pmpaddr0;
	unsigned long pmpaddr1;
	unsigned long pmpaddr2;
	unsigned long pmpaddr3;
	unsigned long pmpaddr4;
	unsigned long pmpaddr5;
	unsigned long pmpaddr6;
	unsigned long pmpaddr7;
	unsigned long pmpcfg0;
	unsigned long mcor;
	unsigned long mhcr;
	unsigned long mccr2;
	unsigned long mhint;
	unsigned long msmpr;
	unsigned long mie;
	unsigned long mstatus;
	unsigned long mxstatus;
	unsigned long mtvec;
	unsigned long plic_base_addr;
	unsigned long clint_base_addr;
} xuantie_regs;

static void xuantie_csr_copy(void)
{
	if (CONFIG_RV_BOOT_HART == __get_MHARTID()) {
		/* Load from boot core */
		xuantie_regs.pmpaddr0 = rv_csr_read(pmpaddr0);
		xuantie_regs.pmpaddr1 = rv_csr_read(pmpaddr1);
		xuantie_regs.pmpaddr2 = rv_csr_read(pmpaddr2);
		xuantie_regs.pmpaddr3 = rv_csr_read(pmpaddr3);
		xuantie_regs.pmpaddr4 = rv_csr_read(pmpaddr4);
		xuantie_regs.pmpaddr5 = rv_csr_read(pmpaddr5);
		xuantie_regs.pmpaddr6 = rv_csr_read(pmpaddr6);
		xuantie_regs.pmpaddr7 = rv_csr_read(pmpaddr7);
		xuantie_regs.pmpcfg0  = rv_csr_read(pmpcfg0);
		xuantie_regs.mcor     = rv_csr_read(mcor);
		xuantie_regs.msmpr    = rv_csr_read(msmpr);
		xuantie_regs.mhcr     = rv_csr_read(mhcr);
		xuantie_regs.mccr2    = rv_csr_read(mccr2);
		xuantie_regs.mhint    = rv_csr_read(mhint);
		xuantie_regs.mtvec    = rv_csr_read(mtvec);
		xuantie_regs.mie      = rv_csr_read(mie);
		xuantie_regs.mstatus  = rv_csr_read(mstatus);
		xuantie_regs.mxstatus = rv_csr_read(mxstatus);
	} else {
		/* Store to other core */
		//rv_csr_write(pmpaddr0, xuantie_regs.pmpaddr0);
		//rv_csr_write(pmpaddr1, xuantie_regs.pmpaddr1);
		//rv_csr_write(pmpaddr2, xuantie_regs.pmpaddr2);
		//rv_csr_write(pmpaddr3, xuantie_regs.pmpaddr3);
		//rv_csr_write(pmpaddr4, xuantie_regs.pmpaddr4);
		//rv_csr_write(pmpaddr5, xuantie_regs.pmpaddr5);
		//rv_csr_write(pmpaddr6, xuantie_regs.pmpaddr6);
		//rv_csr_write(pmpaddr7, xuantie_regs.pmpaddr7);
		//rv_csr_write(pmpcfg0,  xuantie_regs.pmpcfg0);
		rv_csr_write(mcor,     xuantie_regs.mcor);
		rv_csr_write(msmpr,    xuantie_regs.msmpr);
		rv_csr_write(mhcr,     xuantie_regs.mhcr);
		rv_csr_write(mhint,    xuantie_regs.mhint);
		//rv_csr_write(mtvec,    xuantie_regs.mtvec);
		//rv_csr_write(mie,      xuantie_regs.mie);
		rv_csr_write(mstatus,  xuantie_regs.mstatus);
		rv_csr_write(mxstatus, xuantie_regs.mxstatus);
	}
}

int pm_cpu_on(unsigned long cpuid, uintptr_t entry_point)
{
	uint32_t mrmr;
	int cpu_num = cpuid;

	xuantie_csr_copy();
	*(unsigned long *)((unsigned long)XIAOHUI_SRESET_BASE + XIAOHUI_SRESET_ADDR_OFFSET + ((cpu_num - 1) << 3)) = (unsigned long)entry_point;
	__ASM("sync");
	mrmr = *(uint32_t *)(XIAOHUI_SRESET_BASE);
	*(uint32_t *)(XIAOHUI_SRESET_BASE) = mrmr | (0x1 << (cpu_num - 1));
	__ASM("sync");

	return 0;
}

void riscv_soc_init_cpu(int cpu_num)
{
    xuantie_csr_copy();
}

#endif
