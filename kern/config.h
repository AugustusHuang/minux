#ifndef KERN_CONFIG_H
#define KERN_CONFIG_H

#define MACHINE_CONFIG "ARM-CORTEX-M4"

#define ENDIAN_BIG     0
#define ENDIAN_LITTLE  1
#define ENDIAN_DEFAULT 1
#define ENDIAN_CONFIG  ENDIAN_DEFAULT

#define VERSION_CONFIG "0.0.1"

/* Here I assume 32-bit word size. */
#define WORDSIZE_CONFIG 32

/* priority from 0 to MAX */
#define PRIO_MAX_CONFIG 63U
#define PRIO_CLK_CONFIG 15U

/* pid maximum */
#define PID_MAX_CONFIG  30000U

/* default idle and clk stack size */
#define IDLE_STACK_SIZE_CONFIG 1024U
#define CLK_STACK_SIZE_CONFIG  4096U

/* 0 means downward, 1 means upward */
#define STACK_GROWTH_DOWNWARD 0
#define STACK_GROWTH_UPWARD   1
#define STACK_GROWTH_CONFIG   STACK_GROWTH_DOWNWARD

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

/* Memory buddy system minimal block size (b). */
#define MEMORY_BLOCK_SIZE_CONFIG 1024U

#endif
