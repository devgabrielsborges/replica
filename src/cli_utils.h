#ifndef CLI_UTILS_H
#define CLI_UTILS_H

#include <stdbool.h>

// ANSI Color codes
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define DIM "\033[2m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"
#define REVERSE "\033[7m"
#define STRIKETHROUGH "\033[9m"

// Text colors
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// Bright colors
#define BRIGHT_BLACK "\033[90m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"

// Background colors
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

// Bright background colors
#define BG_BRIGHT_BLACK "\033[100m"
#define BG_BRIGHT_RED "\033[101m"
#define BG_BRIGHT_GREEN "\033[102m"
#define BG_BRIGHT_YELLOW "\033[103m"
#define BG_BRIGHT_BLUE "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN "\033[106m"
#define BG_BRIGHT_WHITE "\033[107m"

// Icons and symbols
#define ICON_SUCCESS "✅"
#define ICON_ERROR "❌"
#define ICON_WARNING "⚠️"
#define ICON_INFO "ℹ️"
#define ICON_ARROW "➤"
#define ICON_CHECK "✓"
#define ICON_CROSS "✗"
#define ICON_BULLET "•"
#define ICON_FOLDER "📁"
#define ICON_FILE "📄"
#define ICON_ROCKET "🚀"
#define ICON_STAR "⭐"
#define ICON_HEART "❤️"
#define ICON_FIRE "🔥"
#define ICON_GEAR "⚙️"
#define ICON_SPARKLES "✨"
#define ICON_PACKAGE "📦"
#define ICON_COMPUTER "💻"
#define ICON_HOURGLASS "⏳"
#define ICON_THUMBS_UP "👍"

// Box drawing characters
#define BOX_HORIZONTAL "─"
#define BOX_VERTICAL "│"
#define BOX_TOP_LEFT "┌"
#define BOX_TOP_RIGHT "┐"
#define BOX_BOTTOM_LEFT "└"
#define BOX_BOTTOM_RIGHT "┘"
#define BOX_CROSS "┼"
#define BOX_T_DOWN "┬"
#define BOX_T_UP "┴"
#define BOX_T_RIGHT "├"
#define BOX_T_LEFT "┤"
#define BOX_DOUBLE_HORIZONTAL "═"
#define BOX_DOUBLE_VERTICAL "║"
#define BOX_DOUBLE_TOP_LEFT "╔"
#define BOX_DOUBLE_TOP_RIGHT "╗"
#define BOX_DOUBLE_BOTTOM_LEFT "╚"
#define BOX_DOUBLE_BOTTOM_RIGHT "╝"

// Progress bar characters
#define PROGRESS_FULL "█"
#define PROGRESS_SEVEN_EIGHTHS "▉"
#define PROGRESS_THREE_QUARTERS "▊"
#define PROGRESS_FIVE_EIGHTHS "▋"
#define PROGRESS_HALF "▌"
#define PROGRESS_THREE_EIGHTHS "▍"
#define PROGRESS_QUARTER "▎"
#define PROGRESS_EIGHTH "▏"
#define PROGRESS_EMPTY "░"

// Spinner characters
#define SPINNER_CHARS "⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏"
#define SPINNER_DOT_CHARS "⠁⠂⠄⡀⢀⠠⠐⠈"

// CLI Theme colors (semantic)
#define THEME_PRIMARY BRIGHT_CYAN
#define THEME_SECONDARY BRIGHT_MAGENTA
#define THEME_SUCCESS BRIGHT_GREEN
#define THEME_ERROR BRIGHT_RED
#define THEME_WARNING BRIGHT_YELLOW
#define THEME_INFO BRIGHT_BLUE
#define THEME_MUTED DIM
#define THEME_ACCENT YELLOW
#define THEME_HIGHLIGHT BG_BRIGHT_BLUE

// Command structure for enhanced CLI
typedef struct {
    const char *name;
    const char *description;
    const char *usage;
    const char *examples[5];
    int example_count;
} cli_command_t;

typedef struct {
    const char *name;
    const char *description;
    const char *short_flag;
    const char *long_flag;
    bool required;
} cli_option_t;

// Function declarations
void cli_print_header(const char *title);
void cli_print_success(const char *message);
void cli_print_error(const char *message);
void cli_print_warning(const char *message);
void cli_print_info(const char *message);
void cli_print_step(const char *message);
void cli_print_box(const char *content);
void cli_print_separator(void);
void cli_print_template_category(const char *name, const char *description);
void cli_show_progress(const char *operation, int current, int total);
bool cli_supports_color(void);

// Enhanced CLI functions
void cli_print_banner(const char *title, const char *subtitle);
void cli_print_panel(const char *title, const char *content, const char *border_color);
void cli_print_table_header(const char *columns[], int column_count, int column_widths[]);
void cli_print_table_row(const char *columns[], int column_count, int column_widths[]);
void cli_print_table_separator(int column_widths[], int column_count);
void cli_print_command_help(const cli_command_t *command);
void cli_print_option_help(const cli_option_t *option);
void cli_show_spinner(const char *message, int duration_ms);
void cli_print_tree_item(const char *item, int depth, bool is_last);
void cli_print_status_bar(const char *left_text, const char *right_text);
void cli_print_gradient_text(const char *text, const char *start_color, const char *end_color);
void cli_print_badge(const char *text, const char *bg_color, const char *text_color);
void cli_clear_line(void);
void cli_move_cursor_up(int lines);
void cli_hide_cursor(void);
void cli_show_cursor(void);

#endif // CLI_UTILS_H
