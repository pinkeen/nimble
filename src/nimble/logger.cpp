/**
 * \file logger.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#include "logger.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void __assert(const char *file, int line, const char *function, const char *expr, const char *fmt, ...)
{
	va_list args;
	char buf[512];

	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	fprintf(stderr, "Assertion '%s' failed in %s:%d:%s() - %s\n", expr, file, line, function, buf);

	abort();
}


void __warn(const char *file, int line, const char *function, const char *fmt, ...)
{
	va_list args;
	char buf[512];

	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	fprintf(stdout, "WW: %s\n", buf);
}


void __error(const char *file, int line, const char *function, const char *fmt, ...)
{
	va_list args;
	char buf[512];

	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	fprintf(stderr, "EE: %s:%d:%s - %s\n", file, line, function, buf);

	abort();
}

void __info(const char *file, int line, const char *function, const char *fmt, ...)
{
	va_list args;
	char buf[512];

	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	fprintf(stdout, "II: %s\n", buf);
}


void __debug(const char *file, int line, const char *function, const char *fmt, ...)
{
	va_list args;
	char buf[512];

	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	fprintf(stdout, "DD: %s:%d:%s - %s\n", file, line, function, buf);
}

