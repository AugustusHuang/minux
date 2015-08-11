#ifndef KERN_CONFIG_H
#define KERN_CONFIG_H

/* For now only Cortex-M3 and Cortex-M4 are supported. */
#define MACHINE_CONFIG "ARM"

#define ENDIAN_BIG     0
#define ENDIAN_LITTLE  1
#define ENDIAN_DEFAULT 1
#define ENDIAN_CONFIG  ENDIAN_DEFAULT

#define VERSION_CONFIG "0.0.1"

/* Here I assume 32-bit word size. */
#define WORDSIZE_CONFIG 32

/* priority from 0 to MAX */
#define PRIO_MAX_CONFIG 31U
#define PRIO_CLK_CONFIG 15U

/* pid maximum */
#define PID_MAX_CONFIG  30000U

/* default idle and clk stack size */
#define IDLE_STACK_SIZE_CONFIG 1024U
#define CLK_STACK_SIZE_CONFIG  4096U

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

/* Memory system size (b). 
 * TODO: Shall we move the job to memory linker script? */
#define MEMORY_SIZE_CONFIG 512U

/* Enable ipc feature or not. */
#define IPC_CONFIG  0
/* TODO: There should be a unified total-size. Let them be here now. */
/* Message queue maximal bytes. */
#define MSGQ_CONFIG 2048U
/* Message queue message maximal bytes. */
#define MSGS_CONFIG 512U
/* Semaphore numbers. */
#define SEMS_CONFIG 16U
/* Shared memory pool size. */
#define SHMS_CONFIG 16U

#endif
