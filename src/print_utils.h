#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

// ANSI color codes
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define GRAY    "\033[90m"

// Print functions
void print_version(void);
void print_help(const char *prog);
void print_error(const char *format, ...);
void print_success(const char *format, ...);
void print_info(const char *format, ...);
void print_warning(const char *format, ...);
void print_progress(const char *message);
int is_color_supported(void);

#endif // PRINT_UTILS_H