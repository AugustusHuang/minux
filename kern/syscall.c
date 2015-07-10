#include "param.h"
#include "systm.h"
#include "syscall.h"

static sysent sysent[] = {
	{ 0, none },
	{ 1, exit },
	{ 0, none }, /* syscall 255. */
};

nsysent = sizeof(sysent) / sizeof(sysent[0]);

void none()
{
	/* do nothing */
}

int exit(int status)
{
}
