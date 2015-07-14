#ifndef KERN_SYSCALL_H
#define KERN_SYSCALL_H

/* syscalls will have sys_ as its prefix, some of them will be fake. */
#define sys_none    0
#define	sys_exit    1
/* #define sys_fork    2 */
#define	sys_read    3
#define	sys_write   4
#define	sys_open    5
#define	sys_close   6
#define	sys_wait4   7
/* #define	sys_link    9 */
/* #define	sys_unlink  10 */
#define	sys_chdir   12
#define	sys_fchdir  13
#define	sys_mknod   14
#define	sys_chmod   15
/* #define	sys_chown   16 */
#define	sys_break   17
#define	sys_getfsstat   18
#define	sys_getpid  20
#define	sys_ptrace  26
#define	sys_recvmsg 27
#define	sys_sendmsg 28
#define	sys_recvfrom    29
#define	sys_accept  30
#define	sys_getpeername 31
#define	sys_getsockname 32
#define	sys_access  33
/* It seems no need to support file flags... */
/* #define	sys_chflags 34 */
/* #define	sys_fchflags    35 */
#define	sys_sync    36
#define	sys_kill    37
#define	sys_getppid 39
#define	sys_dup     41
#define	sys_pipe    42
#define	sys_profil  44
#define	sys_ktrace  45
#define	sys_sigaction   46
#define	sys_sigprocmask 48
#define	sys_acct    51
#define	sys_sigpending  52
#define	sys_sigaltstack 53
#define	sys_ioctl   54
#define	sys_reboot  55
#define	sys_revoke  56
/* And no symbolic links for simplicity. */
/* #define	sys_symlink 57 */
/* #define	sys_readlink    58 */
#define	sys_execve  59
#define	sys_umask   60
#define	sys_msync   65
#define	sys_sbrk	69
#define	sys_sstk	70
#define	sys_vadvise	72
#define	sys_munmap	73
#define	sys_mprotect	74
#define	sys_madvise	75
#define	sys_setitimer	83
#define	sys_swapon	85
#define	sys_getitimer	86
#define	sys_getdtablesize	89
#define	sys_dup2	90
#define sys_fcntl   92
#define	sys_select	93
#define	sys_setpriority	96
/* syscall on networking will be supported in uxxx_net module. */
#define	sys_socket	97
#define	sys_connect	98
#define	sys_getpriority	100
#define	sys_sigreturn	103
#define	sys_bind	104
#define	sys_setsockopt	105
#define	sys_listen	106
#define	sys_sigsuspend	111
#define	sys_vtrace	115
#define	sys_gettimeofday	116
#define	sys_getrusage	117
#define	sys_getsockopt	118
#define	sys_resuba	119
#define	sys_readv	120
#define	sys_writev	121
#define	sys_settimeofday	122
#define	sys_fchown	123
#define	sys_fchmod	124
#define	sys_rename	128
#define	sys_flock	131
#define	sys_mkfifo	132
#define	sys_sendto	133
#define	sys_socketpair	135
#define	sys_mkdir	136
#define	sys_rmdir	137
#define	sys_utimes	138
#define	sys_adjtime	140
#define	sys_setsid	147
#define	sys_quotactl	148
#define	sys_nfssvc	155
#define	sys_statfs	157
#define	sys_fstatfs	158
#define	sys_getfh	161
#define	sys_shmsys	171
#define	sys_stat	188
#define	sys_fstat	189
#define	sys_lstat	190
#define	sys_getdirentries	196
#define	sys_mmap	197
#define	sys_lseek	199
#define	sys_truncate	200
#define	sys_ftruncate	201

#endif
