#ifndef KERN_PARAM_H
#define KERN_PARAM_H

/* Change the config.h. */
#define MACHINE MACHINE_CONFIG

/* Operating System endianess. */
#define ENDIAN  ENDIAN_CONFIG

/* Operating System version. */
#define VERSION VERSION_CONFIG

/* System running level/state. */
#define SYS_THREAD       0x1
#define SYS_HANDLER      0x2
#define SYS_PRIVILEGED   0x4
#define SYS_UNPRIVILEGED 0x8

/* Process states. */
#define PROC_RUN   1U
#define PROC_WAIT  2U
#define PROC_SLEEP 3U

/* Process priority levels, the smaller the higher priority. */
#define PRIO_MIN 0U
#define PRIO_IDLE PRIO_MAX_CONFIG

/* Interrupt priority levels, the smaller the higher priority,
 * 0 means configurable. */
#define IPRIO_RESET -3
#define IPRIO_NMI   -2
#define IPRIO_HF    -1
#define IPRIO_MM    0
#define IPRIO_BF    0
#define IPRIO_UF    0
#define IPRIO_DM    0
#define IPRIO_SVC   0
#define IPRIO_INT   0

#endif
