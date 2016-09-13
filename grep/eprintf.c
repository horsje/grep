#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include "eprintf.h"

static char *name = NULL; /*program name for messages*/

void eprintf(char *fmt, ...)
{
	va_list args;

	fflush(stdout);
	if (progname() != NULL)
		fprintf(stderr, "%s: ", progname());

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	if (fmt[0] != '\0' && fmt[strlen(fmt) - 1] == ':')
		fprintf(stderr, " %s", strerror(errno));
	fprintf(stderr, "\n");
	exit(2); /*failed execution*/
}

void weprintf(char *fmt, ...)
{
	va_list args;

	fflush(stdout);
	if (progname() != NULL)
		fprintf(stderr, "%s: ", progname());

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	if (fmt[0] != '\0' && fmt[strlen(fmt) - 1] == ':')
		fprintf(stderr, " %s", strerror(errno));
	fprintf(stderr, "\n");
}

char *estrdup(char *s)
{
	char *t;

	t = (char *)malloc(strlen(s) + 1);
	if (t == NULL)
		eprintf("estrdup(\"%.20s\") failed:", s);
	strcpy(t, s);
	return t;
}

void *emalloc(size_t n)
{
	void *p;

	p = malloc(n);
	if (n == NULL)
		eprintf("malloc of %u bytes failed:", n);
	return p;
}

void setprogname(char *str)
{
	name = estrdup(str);
}

char *progname(void)
{
	return name;
}