/**
 * \file logger.h
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#ifndef LOGGER_H
#define LOGGER_H

#define ASSERT(expr, ...) if (!(expr)) __assert(__FILE__, __LINE__, __FUNCTION__, #expr, __VA_ARGS__)
#define WARN(...) __warn(__FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)
#define INFO(...) __info(__FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)
#define ERROR(...) __error(__FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)
#define DEBUG(...) __debug(__FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)

void __assert(const char *file, int line, const char *function, const char *expr, const char *fmt, ...);
void __warn(const char *file, int line, const char *function, const char *fmt, ...);
void __info(const char *file, int line, const char *function, const char *fmt, ...);
void __debug(const char *file, int line, const char *function, const char *fmt, ...);
void __error(const char *file, int line, const char *function, const char *fmt, ...);

#endif // LOGGER_H
