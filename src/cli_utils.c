// For usleep on some systems
#define _POSIX_C_SOURCE 200809L

#include "cli_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

static bool color_support_checked = false;
static bool supports_color_cache = false;

bool cli_supports_color(void) {
    if (color_support_checked) {
        return supports_color_cache;
    }
    
    color_support_checked = true;
    
    // Check if stdout is a terminal
    if (!isatty(STDOUT_FILENO)) {
        supports_color_cache = false;
        return false;
    }
    
    // Check environment variables
    const char *term = getenv("TERM");
    const char *colorterm = getenv("COLORTERM");
    
    if (term && (strstr(term, "color") || strstr(term, "xterm") || strstr(term, "screen"))) {
        supports_color_cache = true;
        return true;
    }
    
    if (colorterm) {
        supports_color_cache = true;
        return true;
    }
    
    supports_color_cache = false;
    return false;
}

static void print_with_color(const char *color, const char *icon, const char *message) {
    if (cli_supports_color()) {
        printf("%s%s%s %s%s\n", color, icon, RESET, message, RESET);
    } else {
        printf("%s %s\n", icon, message);
    }
}

void cli_print_header(const char *title) {
    if (!title) return;
    
    int title_len = strlen(title);
    int box_width = title_len + 4; // 2 spaces on each side
    
    if (cli_supports_color()) {
        printf("\n%s%s", BRIGHT_CYAN, BOLD);
        
        // Top border
        printf("%s", BOX_TOP_LEFT);
        for (int i = 0; i < box_width; i++) {
            printf("%s", BOX_HORIZONTAL);
        }
        printf("%s\n", BOX_TOP_RIGHT);
        
        // Title line
        printf("%s  %s  %s\n", BOX_VERTICAL, title, BOX_VERTICAL);
        
        // Bottom border
        printf("%s", BOX_BOTTOM_LEFT);
        for (int i = 0; i < box_width; i++) {
            printf("%s", BOX_HORIZONTAL);
        }
        printf("%s%s\n\n", BOX_BOTTOM_RIGHT, RESET);
    } else {
        printf("\n=== %s ===\n\n", title);
    }
}

void cli_print_success(const char *message) {
    print_with_color(BRIGHT_GREEN, ICON_SUCCESS, message);
}

void cli_print_error(const char *message) {
    print_with_color(BRIGHT_RED, ICON_ERROR, message);
}

void cli_print_warning(const char *message) {
    print_with_color(BRIGHT_YELLOW, ICON_WARNING, message);
}

void cli_print_info(const char *message) {
    print_with_color(BRIGHT_BLUE, ICON_INFO, message);
}

void cli_print_step(const char *message) {
    if (cli_supports_color()) {
        printf("  %s%s%s %s\n", CYAN, ICON_ARROW, RESET, message);
    } else {
        printf("  > %s\n", message);
    }
}

void cli_print_box(const char *content) {
    if (!content) return;
    
    int content_len = strlen(content);
    int box_width = content_len + 4; // 2 spaces on each side
    
    if (cli_supports_color()) {
        printf("%s", DIM);
        
        // Top border
        printf("%s", BOX_TOP_LEFT);
        for (int i = 0; i < box_width; i++) {
            printf("%s", BOX_HORIZONTAL);
        }
        printf("%s\n", BOX_TOP_RIGHT);
        
        // Content line
        printf("%s  %s  %s\n", BOX_VERTICAL, content, BOX_VERTICAL);
        
        // Bottom border
        printf("%s", BOX_BOTTOM_LEFT);
        for (int i = 0; i < box_width; i++) {
            printf("%s", BOX_HORIZONTAL);
        }
        printf("%s%s\n", BOX_BOTTOM_RIGHT, RESET);
    } else {
        printf("┌");
        for (int i = 0; i < box_width; i++) {
            printf("─");
        }
        printf("┐\n");
        printf("│  %s  │\n", content);
        printf("└");
        for (int i = 0; i < box_width; i++) {
            printf("─");
        }
        printf("┘\n");
    }
}

void cli_print_separator(void) {
    if (cli_supports_color()) {
        printf("%s%s", DIM, BOX_HORIZONTAL);
        for (int i = 1; i < 50; i++) {
            printf("%s", BOX_HORIZONTAL);
        }
        printf("%s\n", RESET);
    } else {
        for (int i = 0; i < 50; i++) {
            printf("-");
        }
        printf("\n");
    }
}

void cli_print_template_category(const char *name, const char *description) {
    if (!name || !description) return;
    
    if (cli_supports_color()) {
        printf("  %s%s%-20s%s %s%s%s\n", 
               BRIGHT_CYAN, BOLD, name, RESET,
               DIM, description, RESET);
    } else {
        printf("  %-20s %s\n", name, description);
    }
}

void cli_show_progress(const char *operation, int current, int total) {
    if (!operation) return;
    
    int percentage = (current * 100) / total;
    int bar_width = 30;
    int filled = (current * bar_width) / total;
    
    if (cli_supports_color()) {
        printf("\r%s%s%s [", THEME_INFO, operation, RESET);
        
        // Use different characters for a smoother progress bar
        for (int i = 0; i < bar_width; i++) {
            if (i < filled) {
                printf("%s%s%s", THEME_SUCCESS, PROGRESS_FULL, RESET);
            } else {
                printf("%s%s%s", THEME_MUTED, PROGRESS_EMPTY, RESET);
            }
        }
        
        printf("] %s%s%d%%%s%s (%d/%d)", 
               BOLD, THEME_ACCENT, percentage, RESET, RESET, current, total);
        fflush(stdout);
        
        if (current == total) {
            printf("\n");
        }
    } else {
        printf("\r%s [", operation);
        
        for (int i = 0; i < bar_width; i++) {
            if (i < filled) {
                printf("#");
            } else {
                printf(".");
            }
        }
        
        printf("] %d%% (%d/%d)", percentage, current, total);
        fflush(stdout);
        
        if (current == total) {
            printf("\n");
        }
    }
}


void cli_print_banner(const char *title, const char *subtitle) {
    if (!title) return;
    
    int title_len = strlen(title);
    int subtitle_len = subtitle ? strlen(subtitle) : 0;
    int width = (title_len > subtitle_len ? title_len : subtitle_len) + 8;
    
    if (cli_supports_color()) {
        printf("\n");
        // Top border with gradient effect
        printf("%s%s%s", THEME_PRIMARY, BOLD, BOX_DOUBLE_TOP_LEFT);
        for (int i = 0; i < width; i++) {
            printf("%s", BOX_DOUBLE_HORIZONTAL);
        }
        printf("%s%s\n", BOX_DOUBLE_TOP_RIGHT, RESET);
        
        // Title line
        int title_padding = (width - title_len) / 2;
        printf("%s%s%s%s", THEME_PRIMARY, BOLD, BOX_DOUBLE_VERTICAL, RESET);
        for (int i = 0; i < title_padding; i++) printf(" ");
        printf("%s%s%s%s", BG_BRIGHT_BLUE, BRIGHT_WHITE, title, RESET);
        for (int i = 0; i < width - title_len - title_padding; i++) printf(" ");
        printf("%s%s%s%s\n", THEME_PRIMARY, BOLD, BOX_DOUBLE_VERTICAL, RESET);
        
        // Subtitle line if provided
        if (subtitle) {
            int subtitle_padding = (width - subtitle_len) / 2;
            printf("%s%s%s%s", THEME_PRIMARY, BOLD, BOX_DOUBLE_VERTICAL, RESET);
            for (int i = 0; i < subtitle_padding; i++) printf(" ");
            printf("%s%s%s", THEME_MUTED, subtitle, RESET);
            for (int i = 0; i < width - subtitle_len - subtitle_padding; i++) printf(" ");
            printf("%s%s%s%s\n", THEME_PRIMARY, BOLD, BOX_DOUBLE_VERTICAL, RESET);
        }
        
        // Bottom border
        printf("%s%s%s", THEME_PRIMARY, BOLD, BOX_DOUBLE_BOTTOM_LEFT);
        for (int i = 0; i < width; i++) {
            printf("%s", BOX_DOUBLE_HORIZONTAL);
        }
        printf("%s%s\n\n", BOX_DOUBLE_BOTTOM_RIGHT, RESET);
    } else {
        printf("\n=== %s ===\n", title);
        if (subtitle) printf("%s\n", subtitle);
        printf("\n");
    }
}

void cli_print_panel(const char *title, const char *content, const char *border_color) {
    if (!content) return;
    
    const char *color = border_color ? border_color : THEME_INFO;
    int content_len = strlen(content);
    int title_len = title ? strlen(title) : 0;
    int width = (content_len > title_len ? content_len : title_len) + 4;
    
    if (cli_supports_color()) {
        // Top border with title
        printf("%s%s", color, BOX_TOP_LEFT);
        if (title) {
            printf("%s %s%s%s %s", BOX_HORIZONTAL, BOLD, title, RESET, color);
            for (int i = 0; i < width - title_len - 3; i++) {
                printf("%s", BOX_HORIZONTAL);
            }
        } else {
            for (int i = 0; i < width; i++) {
                printf("%s", BOX_HORIZONTAL);
            }
        }
        printf("%s%s\n", BOX_TOP_RIGHT, RESET);
        
        // Content line
        printf("%s%s%s  %s  %s%s%s\n", color, BOX_VERTICAL, RESET, content, color, BOX_VERTICAL, RESET);
        
        // Bottom border
        printf("%s%s", color, BOX_BOTTOM_LEFT);
        for (int i = 0; i < width; i++) {
            printf("%s", BOX_HORIZONTAL);
        }
        printf("%s%s\n", BOX_BOTTOM_RIGHT, RESET);
    } else {
        if (title) printf("[ %s ]\n", title);
        printf("%s\n", content);
    }
}

void cli_print_table_header(const char *columns[], int column_count, int column_widths[]) {
    if (!columns || column_count <= 0) return;
    
    if (cli_supports_color()) {
        // Top border
        printf("%s%s", THEME_INFO, BOX_TOP_LEFT);
        for (int i = 0; i < column_count; i++) {
            for (int j = 0; j < column_widths[i]; j++) {
                printf("%s", BOX_HORIZONTAL);
            }
            if (i < column_count - 1) {
                printf("%s", BOX_T_DOWN);
            }
        }
        printf("%s%s\n", BOX_TOP_RIGHT, RESET);
        
        // Header row
        printf("%s%s%s", THEME_INFO, BOX_VERTICAL, RESET);
        for (int i = 0; i < column_count; i++) {
            printf("%s%s%-*s%s", BOLD, BRIGHT_WHITE, column_widths[i], columns[i], RESET);
            if (i < column_count - 1) {
                printf("%s%s%s", THEME_INFO, BOX_VERTICAL, RESET);
            }
        }
        printf("%s%s%s\n", THEME_INFO, BOX_VERTICAL, RESET);
        
        // Separator
        printf("%s%s", THEME_INFO, BOX_T_RIGHT);
        for (int i = 0; i < column_count; i++) {
            for (int j = 0; j < column_widths[i]; j++) {
                printf("%s", BOX_HORIZONTAL);
            }
            if (i < column_count - 1) {
                printf("%s", BOX_CROSS);
            }
        }
        printf("%s%s\n", BOX_T_LEFT, RESET);
    } else {
        for (int i = 0; i < column_count; i++) {
            printf("%-*s", column_widths[i], columns[i]);
            if (i < column_count - 1) printf(" | ");
        }
        printf("\n");
        for (int i = 0; i < column_count; i++) {
            for (int j = 0; j < column_widths[i]; j++) printf("-");
            if (i < column_count - 1) printf("-+-");
        }
        printf("\n");
    }
}

void cli_print_table_row(const char *columns[], int column_count, int column_widths[]) {
    if (!columns || column_count <= 0) return;
    
    if (cli_supports_color()) {
        printf("%s%s%s", THEME_INFO, BOX_VERTICAL, RESET);
        for (int i = 0; i < column_count; i++) {
            printf("%-*s", column_widths[i], columns[i]);
            if (i < column_count - 1) {
                printf("%s%s%s", THEME_INFO, BOX_VERTICAL, RESET);
            }
        }
        printf("%s%s%s\n", THEME_INFO, BOX_VERTICAL, RESET);
    } else {
        for (int i = 0; i < column_count; i++) {
            printf("%-*s", column_widths[i], columns[i]);
            if (i < column_count - 1) printf(" | ");
        }
        printf("\n");
    }
}

void cli_print_table_separator(int column_widths[], int column_count) {
    if (cli_supports_color()) {
        printf("%s%s", THEME_INFO, BOX_BOTTOM_LEFT);
        for (int i = 0; i < column_count; i++) {
            for (int j = 0; j < column_widths[i]; j++) {
                printf("%s", BOX_HORIZONTAL);
            }
            if (i < column_count - 1) {
                printf("%s", BOX_T_UP);
            }
        }
        printf("%s%s\n", BOX_BOTTOM_RIGHT, RESET);
    }
}

void cli_print_command_help(const cli_command_t *command) {
    if (!command) return;
    
    if (cli_supports_color()) {
        printf("  %s%s%s%s %s%s%s\n", 
               THEME_PRIMARY, BOLD, command->name, RESET,
               THEME_MUTED, command->description, RESET);
        
        if (command->usage) {
            printf("    %sUsage:%s %s\n", THEME_INFO, RESET, command->usage);
        }
        
        if (command->example_count > 0) {
            printf("    %sExamples:%s\n", THEME_WARNING, RESET);
            for (int i = 0; i < command->example_count; i++) {
                printf("      %s%s%s\n", THEME_ACCENT, command->examples[i], RESET);
            }
        }
    } else {
        printf("  %s - %s\n", command->name, command->description);
        if (command->usage) {
            printf("    Usage: %s\n", command->usage);
        }
    }
    printf("\n");
}

void cli_print_option_help(const cli_option_t *option) {
    if (!option) return;
    
    if (cli_supports_color()) {
        printf("    %s%s%s", THEME_SUCCESS, option->short_flag ? option->short_flag : "", RESET);
        if (option->short_flag && option->long_flag) {
            printf("%s, %s", RESET, THEME_SUCCESS);
        }
        printf("%s%s%s", THEME_SUCCESS, option->long_flag ? option->long_flag : "", RESET);
        
        int flag_len = (option->short_flag ? strlen(option->short_flag) : 0) + 
                       (option->long_flag ? strlen(option->long_flag) : 0) + 
                       (option->short_flag && option->long_flag ? 2 : 0);
        
        for (int i = flag_len; i < 20; i++) printf(" ");
        
        printf("%s%s%s", THEME_MUTED, option->description, RESET);
        if (option->required) {
            printf(" %s%s(required)%s", THEME_ERROR, ITALIC, RESET);
        }
        printf("\n");
    } else {
        printf("    %s%s%s %s\n", 
               option->short_flag ? option->short_flag : "",
               (option->short_flag && option->long_flag) ? ", " : "",
               option->long_flag ? option->long_flag : "",
               option->description);
    }
}

void cli_show_spinner(const char *message, int duration_ms) {
    if (!message) return;
    
    const char *spinner = SPINNER_CHARS;
    int spinner_len = strlen(spinner) / 3; // Each spinner char is 3 bytes (UTF-8)
    int iterations = duration_ms / 100; // Update every 100ms
    
    struct timespec ts = {0, 100000000}; // 100ms in nanoseconds
    
    cli_hide_cursor();
    
    for (int i = 0; i < iterations; i++) {
        if (cli_supports_color()) {
            printf("\r%s%s%.*s%s %s", THEME_INFO, BOLD, 3, &spinner[(i % spinner_len) * 3], RESET, message);
        } else {
            printf("\r[%c] %s", "|/-\\"[i % 4], message);
        }
        fflush(stdout);
        nanosleep(&ts, NULL);
    }
    
    cli_show_cursor();
    printf("\n");
}

void cli_print_tree_item(const char *item, int depth, bool is_last) {
    if (!item) return;
    
    if (cli_supports_color()) {
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }
        printf("%s%s%s %s%s%s\n", 
               THEME_MUTED, is_last ? "└─" : "├─", RESET,
               THEME_INFO, item, RESET);
    } else {
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }
        printf("%s %s\n", is_last ? "└─" : "├─", item);
    }
}

void cli_print_status_bar(const char *left_text, const char *right_text) {
    int term_width = 80; // Default terminal width
    int left_len = left_text ? strlen(left_text) : 0;
    int right_len = right_text ? strlen(right_text) : 0;
    int padding = term_width - left_len - right_len;
    
    if (padding < 0) padding = 0;
    
    if (cli_supports_color()) {
        printf("%s%s%s%s", BG_BRIGHT_BLUE, BRIGHT_WHITE, left_text ? left_text : "", RESET);
        for (int i = 0; i < padding; i++) {
            printf("%s %s", BG_BRIGHT_BLUE, RESET);
        }
        printf("%s%s%s%s\n", BG_BRIGHT_BLUE, BRIGHT_WHITE, right_text ? right_text : "", RESET);
    } else {
        printf("%s", left_text ? left_text : "");
        for (int i = 0; i < padding; i++) printf(" ");
        printf("%s\n", right_text ? right_text : "");
    }
}

void cli_print_badge(const char *text, const char *bg_color, const char *text_color) {
    if (!text) return;
    
    const char *bg = bg_color ? bg_color : BG_BRIGHT_BLUE;
    const char *fg = text_color ? text_color : BRIGHT_WHITE;
    
    if (cli_supports_color()) {
        printf(" %s%s %s %s", bg, fg, text, RESET);
    } else {
        printf("[%s]", text);
    }
}

void cli_clear_line(void) {
    printf("\r\033[K");
}

void cli_move_cursor_up(int lines) {
    printf("\033[%dA", lines);
}

void cli_hide_cursor(void) {
    printf("\033[?25l");
}

void cli_show_cursor(void) {
    printf("\033[?25h");
}
