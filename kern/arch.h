#ifndef _ARCH_H_
#define _ARCH_H_

/* TODO: Now we are building OS upon Cortex-M4, how about backward? */
/* reg_t numbers */
#define R0  0
#define R1  1
#define R2  2
#define R3  3
#define R4  4
#define R5  5
#define R6  6
#define R7  7
#define R8  8
#define R9  9
#define R10 10
#define R11 11
#define R12 12
#define R13 13
#define R14 14
#define R15 15
#define R16 16
#define SP  13
#define LR  14
#define PC  15
#define PSR 16

/* On-chip registers. */
#define ARCH_SCS_START   0xe000e000
#define ARCH_ICTR        0xe000e004 /* interrupt controller type register */
#define ARCH_ACTLR       0xe000e008 /* auxiliary control register */
#define ARCH_SYST_CSR    0xe000e010 /* systick control and status register */
#define ARCH_SYST_RVR    0xe000e014 /* systick reload value */
#define ARCH_SYST_CVR    0xe000e018 /* systick current value */
#define ARCH_SYST_CALIB  0xe000e01c /* systick calibration value */
#define ARCH_NVIC_ISER0  0xe000e100 /* irq 0 to 31 set-enable register */
#define ARCH_NVIC_ISER15 0xe000e13c /* irq 480 to 495 set-enable register */
#define ARCH_NVIC_ICER0  0xe000e180 /* irq 0 to 31 clear-enable register */
#define ARCH_NVIC_ICER15 0xe000e1bc /* irq 480 to 495 clear-enable register */
#define ARCH_NVIC_ISPR0  0xe000e200 /* irq 0 to 31 set-pending register */
#define ARCH_NVIC_ISPR15 0xe000e23c /* irq 480 to 495 set-pending register */
#define ARCH_NVIC_ICPR0  0xe000e280 /* irq 0 to 31 clear-pending register */
#define ARCH_NVIC_ICPR15 0xe000e2bc /* irq 480 to 495 clear-pending register */
#define ARCH_NVIC_IABR0  0xe000e300 /* irq 0 to 31 active bit register */
#define ARCH_NVIC_IABR15 0xe000e37c /* irq 480 to 495 active bit register */
#define ARCH_NVIC_IPR0   0xe000e400 /* irq 0 to 3 priority register */
#define ARCH_NVIC_IPR123 0xe000e7ec /* irq 492 to 495 priority register */
#define ARCH_CPUID       0xe000ed00 /* CPUID base register */
#define ARCH_ICSR        0xe000ed04 /* interrupt controller state register */
#define ARCH_VTOR        0xe000ed08 /* vector table offset register */
#define ARCH_AIRCR       0xe000ed0c /* application interrupt/reset control register */
#define ARCH_SCR         0xe000ed10 /* system control register */
#define ARCH_CCR         0xe000ed14 /* configuration control register */
#define ARCH_SHPR1       0xe000ed18 /* system handlers 4-7 priority register */
#define ARCH_SHPR2       0xe000ed1c /* system handlers 8-11 priority register */
#define ARCH_SHPR3       0xe000ed20 /* system handlers 12-15 priority register */
#define ARCH_SHCSR       0xe000ed24 /* system handler control and state register */
#define ARCH_CFSR        0xe000ed28 /* configurable fault status register */
#define ARCH_HFSR        0xe000ed2c /* hard fault status register */
#define ARCH_DFSR        0xe000ed30 /* debug fault status register */
#define ARCH_MMFAR       0xe000ed34 /* mem manage address register */
#define ARCH_BFAR        0xe000ed38 /* bus fault address register */
#define ARCH_AFSR        0xe000ed3c /* auxiliary fault status register */
#define ARCH_CPACR       0xe000ed88 /* coprocessor access control register */
#define ARCH_MPU_TYPE    0xe000ed90 /* MPU type register */
#define ARCH_MPU_CTRL    0xe000ed94 /* MPU control register */
#define ARCH_MPU_RNR     0xe000ed98 /* MPU region number register */
#define ARCH_MPU_RBAR    0xe000ed9c /* MPU region base address register */
#define ARCH_MPU_RASR    0xe000eda0 /* MPU region attribute and size register */
#define ARCH_MPU_RBAR_A1 0xe000eda4 /* MPU alias */
#define ARCH_MPU_RASR_A1 0xe000eda8
#define ARCH_MPU_RBAR_A2 0xe000edac
#define ARCH_MPU_RASR_A2 0xe000edb0
#define ARCH_MPU_RBAR_A3 0xe000edb4
#define ARCH_MPU_RASR_A3 0xe000edb8
#define ARCH_STIR        0xe000ef00 /* software trigger interrupt register */
#define ARCH_PID4        0xe000efd0 /* peripheral identification register */
#define ARCH_PID5        0xe000efd4
#define ARCH_PID6        0xe000efd8
#define ARCH_PID7        0xe000edfc
#define ARCH_PID0        0xe000efe0
#define ARCH_PID1        0xe000efe4
#define ARCH_PID2        0xe000efe8
#define ARCH_PID3        0xe000efec
#define ARCH_CID0        0xe000eff0 /* component identification register */
#define ARCH_CID1        0xe000eff4
#define ARCH_CID2        0xe000eff8
#define ARCH_CID3        0xe000effc
#define ARCH_SCS_END     0xe000efff
 
#endif
