#ifndef _CONFIG_H_
#define _CONFIG_H_

#define MACHINE_CONFIG "ARM-CORTEX-M4"

/* priority from 0 to MAX */
#define PRIO_MAX_CONFIG 63U
#define PRIO_CLK_CONFIG 15U

/* pid maximum */
#define PID_MAX_CONFIG  30000U

/* default idle and clk stack size */
#define IDLE_STACK_SIZE_CONFIG 1024U
#define CLK_STACK_SIZE_CONFIG  4096U

/* 0 means downward, 1 means upward */
#define STACK_GROWTH_CONFIG 0

#define SWITCH_FREQUENCY_CONFIG 1000U

#define LOCAL_STATUS_CONFIG 1 /* enable this by default */
#if (LOCAL_STATUS_CONFIG == 1)
#define LSR()          uint32_t lsr = (uint32_t) 0
#define INTR_DISABLE() do { lsr = lsr_save(); } while (0)
#define INTR_ENABLE()  do { lsr_load(lsr); } while (0)
#else
#define LSR()
#define INTR_DISABLE() interrupt_disable()
#define INTR_ENABLE()  interrupt_enable()
#endif

#endif
