#include <stdarg.h>

#define LOG_COLOR_NONE                          "\033[m"
#define LOG_COLOR_REDi              "\033[0;32;31m"
#define LOG_COLOR_LIGHT_RED         "\033[1;31m"
#define LOG_COLOR_GREEN             "\033[0;32;32m"
#define LOG_COLOR_LIGHT_GREEN           "\033[1;32m"
#define LOG_COLOR_BLUE                          "\033[0;32;34m"
#define LOG_COLOR_LIGHT_BLUE            "\033[1;34m"
#define LOG_COLOR_DARY_GRAY             "\033[1;30m"
#define LOG_COLOR_CYAN                          "\033[0;36m"
#define LOG_COLOR_LIGHT_CYAN            "\033[1;36m"
#define LOG_COLOR_PURPLE                        "\033[0;35m"
#define LOG_COLOR_LIGHT_PURPLE          "\033[1;35m"
#define LOG_COLOR_BROWN                         "\033[0;33m"
#define LOG_COLOR_YELLOW                        "\033[1;33m"
#define LOG_COLOR_LIGHT_GRAY            "\033[0;37m"
#define LOG_COLOR_WHITE                         "\033[1;37m"

#define LOG_COLOR_L1                LOG_COLOR_LIGHT_RED
#define LOG_COLOR_L2                LOG_COLOR_LIGHT_BLUE
#define LOG_COLOR_L3                LOG_COLOR_LIGHT_GREEN

// ##### stdio printf micro
#define printf1(fmt, args...)           printf(fmt, ##args)
#define printf0(fmt, args...)

#define L0(fmt, args...)
#define L1(fmt, args...)                log_print(LOG_COLOR_L1, fmt, ## args)
#define L2(fmt, args...)                log_print(LOG_COLOR_L2, fmt, ## args)
#define L3(fmt, args...)                log_print(LOG_COLOR_L3, fmt, ## args)

extern void log_print(const char *color, char *fmt, ...);
