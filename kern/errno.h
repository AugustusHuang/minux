#ifndef _ERRNO_H_
#define _ERRNO_H_

extern int errno;

/* Signal/error will have prefix E_. */
#define	E_PERM		1		/* Operation not permitted */
#define	E_NOENT		2		/* No such file or directory */
#define	E_SRCH		3		/* No such process */
#define	E_INTR		4		/* Interrupted system call */
#define	E_IO		5		/* Input/output error */
#define	E_NXIO		6		/* Device not configured */
#define	E_2BIG		7		/* Argument list too long */
#define	E_NOEXEC		8		/* Exec format error */
#define	E_BADF		9		/* Bad file descriptor */
#define	E_CHILD		10		/* No child processes */
#define	E_DEADLK		11		/* Resource deadlock avoided */
#define	E_NOMEM		12		/* Cannot allocate memory */
#define	E_ACCES		13		/* Permission denied */
#define	E_FAULT		14		/* Bad address */
#define	E_NOTBLK		15		/* Block device required */
#define	E_BUSY		16		/* Device busy */
#define	E_EXIST		17		/* File exists */
#define	E_XDEV		18		/* Cross-device link */
#define	E_NODEV		19		/* Operation not supported by device */
#define	E_NOTDIR		20		/* Not a directory */
#define	E_ISDIR		21		/* Is a directory */
#define	E_INVAL		22		/* Invalid argument */
#define	E_NFILE		23		/* Too many open files in system */
#define	E_MFILE		24		/* Too many open files */
#define	E_NOTTY		25		/* Inappropriate ioctl for device */
#define	E_TXTBSY		26		/* Text file busy */
#define	E_FBIG		27		/* File too large */
#define	E_NOSPC		28		/* No space left on device */
#define	E_SPIPE		29		/* Illegal seek */
#define	E_ROFS		30		/* Read-only file system */
#define	E_MLINK		31		/* Too many links */
#define	E_PIPE		32		/* Broken pipe */
#define	E_DOM		33		/* Numerical argument out of domain */
#define	E_RANGE		34		/* Result too large */
/* non-blocking and interrupt i/o */
#define	E_AGAIN		35		/* Resource temporarily unavailable */
#define	E_WOULDBLOCK	EAGAIN		/* Operation would block */
#define	E_INPROGRESS	36		/* Operation now in progress */
#define	E_ALREADY	37		/* Operation already in progress */
/* ipc/network software -- argument errors */
#define	E_NOTSOCK	38		/* Socket operation on non-socket */
#define	E_DESTADDRREQ	39		/* Destination address required */
#define	E_MSGSIZE	40		/* Message too long */
#define	E_PROTOTYPE	41		/* Protocol wrong type for socket */
#define	E_NOPROTOOPT	42		/* Protocol not available */
#define	E_PROTONOSUPPORT	43		/* Protocol not supported */
#define	E_SOCKTNOSUPPORT	44		/* Socket type not supported */
#define	E_OPNOTSUPP	45		/* Operation not supported */
#define	E_PFNOSUPPORT	46		/* Protocol family not supported */
#define	E_AFNOSUPPORT	47		/* Address family not supported by protocol family */
#define	E_ADDRINUSE	48		/* Address already in use */
#define	E_ADDRNOTAVAIL	49		/* Can't assign requested address */
/* ipc/network software -- operational errors */
#define	E_NETDOWN	50		/* Network is down */
#define	E_NETUNREACH	51		/* Network is unreachable */
#define	E_NETRESET	52		/* Network dropped connection on reset */
#define	E_CONNABORTED	53		/* Software caused connection abort */
#define	E_CONNRESET	54		/* Connection reset by peer */
#define	E_NOBUFS		55		/* No buffer space available */
#define	E_ISCONN		56		/* Socket is already connected */
#define	E_NOTCONN	57		/* Socket is not connected */
#define	E_SHUTDOWN	58		/* Can't send after socket shutdown */
#define	E_TOOMANYREFS	59		/* Too many references: can't splice */
#define	E_TIMEDOUT	60		/* Operation timed out */
#define	E_CONNREFUSED	61		/* Connection refused */
#define	E_LOOP		62		/* Too many levels of symbolic links */
#define	E_NAMETOOLONG	63		/* File name too long */
/* should be rearranged */
#define	E_HOSTDOWN	64		/* Host is down */
#define	E_HOSTUNREACH	65		/* No route to host */
#define	E_NOTEMPTY	66		/* Directory not empty */
/* quotas & mush */
#define	E_PROCLIM	67		/* Too many processes */
#define	E_DQUOT		69		/* Disc quota exceeded */
#define	E_NOLCK		77		/* No locks available */
#define	E_NOSYS		78		/* Function not implemented */
#define	E_FTYPE		79		/* Inappropriate file type or format */
#define	E_AUTH		80		/* Authentication error */
#define	E_NEEDAUTH	81		/* Need authenticator */
#define	E_LAST		81		/* Must be equal largest errno */

void panic(const string);

#endif
