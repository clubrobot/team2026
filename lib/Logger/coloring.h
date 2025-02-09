#ifndef COLOR_H
#define COLOR_H

#define NOBOLD 0
#define BOLD 1

// Reset all colors (foreground, background and bold)
#define COLOR_NORMAL "\e[m"

// Bold text
#define COLOR_BOLD "\e[1m"

// Font colors
#define COLOR_BLACK "\e[30m"
#define COLOR_RED "\e[31m"
#define COLOR_GREEN "\e[32m"
#define COLOR_YELLOW "\e[33m"
#define COLOR_BLUE "\e[34m"
#define COLOR_MAGENTA "\e[35m"
#define COLOR_CYAN "\e[36m"
#define COLOR_WHITE "\e[37m"

// Background colors
#define COLOR_BG_BLACK "\e[40m"
#define COLOR_BG_RED "\e[41m"
#define COLOR_BG_GREEN "\e[42m"
#define COLOR_BG_YELLOW "\e[43m"
#define COLOR_BG_BLUE "\e[44m"
#define COLOR_BG_MAGENTA "\e[45m"
#define COLOR_BG_CYAN "\e[46m"
#define COLOR_BG_WHITE "\e[47m"

#endif