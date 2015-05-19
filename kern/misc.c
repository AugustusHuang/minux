#include "param.h"
#include "systm.h"
#include "process.h"
#include "errno.h"
#include "type.h"
#include "print.h"

void panic(const string str)
{
	panicstr[] = str;
}

void printf(const string fmt, ... )
{
}
