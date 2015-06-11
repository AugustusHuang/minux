#include "param.h"
#include "systm.h"
#include "syscall.h"

void none()
{
	/* do nothing */
}

int exit(int status)
{
}

/* TODO: Move to a static structure. */
void syscall_init()
{
	struct sysent sysent[] = {
		{ 0, none }, /* none */
		{ 1, exit }, /* exit */
		{ 0, none }, /* fork */
		{ 0, none }, /* read */
		{ 0, none }, /* write */
		{ 0, none }, /* open */
		{ 0, none }, /* close */
		{ 0, none }, /* wait4 */
		{ 0, none }, /* creat */
		{ 0, none }, /* link */
		{ 0, none }, /* unlink */
		{ 0, none }, /* execv */
		{ 0, none }, /* chdir */
		{ 0, none }, /* fchdir */
		{ 0, none }, /* mknod */
		/* et cetera */
		{ 0, none }  /* syscall 255 */
	};

	nsysent = sizeof(sysent) / sizeof(sysent[0]);
}
