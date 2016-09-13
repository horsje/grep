#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

void eprintf(char *fmt, ...)
{
	va_list args;

	fflush(stdout);

}