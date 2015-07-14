#include "param.h"
#include "systm.h"
#include "config.h"
#include "syscall.h"

static sysent sysent[] = {
	{ 0, none },
	{ 1, exit },
	{ 0, none },
#ifdef UXXX_FS
	{ 3, read },
	{ 3, write },
	{ 3, open },
	{ 1, close },
#else
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
#endif
	{ 2, wait4 },
	{ 0, none }, /* syscall 8 not defined */
	{ 0, none }, /* link won't be supported here */
	{ 0, none }, /* so will unlink */
	{ 0, none }, /* syscall 11 not defined */
#ifdef UXXX_FS
	{ 1, chdir },
	{ 1, fchdir },
	{ 3, mknod },
	{ 2, chmod },
#else
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
#endif
	{ 0, none }, /* owner one and only */
	{ 1, breakf }, /* break is a bad name */
	{ 1, getfsstat },
	{ 0, none }, /* syscall 19 not defined */
	{ 0, getpid },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	/* seems like net part... */
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none }, /* file flags won't be supported */
	{ 0, none },
	{ 1, sync },
	{ 2, kill },
	{ 0, none }, /* syscall 38 not defined */
	{ 0, none },
	{ 0, none }, /* syscall 40 not defined */
	{ 0, none }, /* syscall 201 */
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none },
	{ 0, none }, /* syscall 255 */
};

nsysent = sizeof(sysent) / sizeof(sysent[0]);

void none()
{
	/* do nothing */
}

int exit(int status)
{
}

#ifdef UXXX_FS
void read(fd_t fd, string buf, uint32_t bytes)
{
	fs_read(fd, buf, bytes);
}

void write(fd_t fd, string buf, uint32_t bytes)
{
	fs_write(fd, buf, bytes);
}

/* flags is superfluous? */
fd_t open(string path, int32_t flags, int32_t mode)
{
	fs_open(path, flags, mode);
}

int close(fd_t fd)
{
	fs_close(fd);
}
#endif

void wait4()
{
}

#ifdef UXXX_FS
void chdir(string path)
{
	fs_chdir(path);
}

void fchdir(string path)
{
	fs_fchdir(path);
}

void mknod()
{
	fs_mknod();
}

void chmod()
{
	fs_chmod();
}
#endif

/* Break is a bad name. */
int breakf()
{
}

