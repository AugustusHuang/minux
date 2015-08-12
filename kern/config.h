#ifndef KERN_CONFIG_H
#define KERN_CONFIG_H

/* debug message printing config */
#define CONFIG_DEBUG   0

/* For now only Cortex-M3 and Cortex-M4 are supported. */
#define CONFIG_MACHINE "ARM"

/* Endianness, default is little-endian. */
#define ENDIAN_BIG     0
#define ENDIAN_LITTLE  1
#define CONFIG_ENDIAN  ENDIAN_LITTLE

#define CONFIG_VERSION "0.0.1"

/* Here I assume 32-bit word size. */
#define CONFIG_WORDSIZE 32

/* priority ranged from 0 to MAX */
#define CONFIG_MAX_PRIO 31U
#define CONFIG_CLK_PRIO 0U

/* The maximum of pid, is a 32-bit unsigned integer. */
#define CONFIG_MAX_PID  30000U

/* default idle and clk stack size */
#define CONFIG_IDLE_STACK_SIZE 1024U
#define CONFIG_CLK_STACK_SIZE  4096U

/* clock frequency to do context switch */
#define CONFIG_SWITCH_FREQUENCY 1000U

/* Local status register, if enabled, allocate it right after function call,
 * i.e. the first local variable in the callee frame, if disabled, act like
 * normal interrupt disable routine, which ensure the surrounded instructions
 * atomic. */
#define CONFIG_LOCAL_STATUS 1

#ifdef CONFIG_LOCAL_STATUS
#define LSR()          uint32_t lsr = (uint32_t) 0
#define INTR_DISABLE() do { lsr = lsr_save(); } while (0)
#define INTR_ENABLE()  do { lsr_load(lsr); } while (0)
#else
#define LSR()
#define INTR_DISABLE() interrupt_disable()
#define INTR_ENABLE()  interrupt_enable()
#endif

/* memory system size in KB. 
 * TODO: Shall we move the job to memory linker script? */
#define CONFIG_MEMORY_SIZE 512U

/* Enable ipc feature or not. */
#define CONFIG_IPC  0
/* TODO: There should be a unified total-size. Let them be here now. */
/* message queue maximal bytes */
#define MSGQ_CONFIG 2048U
/* message queue message maximal bytes */
#define MSGS_CONFIG 512U
/* semaphore numbers */
#define SEMS_CONFIG 16U
/* shared memory pool size */
#define SHMS_CONFIG 16U

#endif
