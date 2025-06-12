#define _POSIX_C_SOURCE 200809L
#include "print_utils.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int is_color_supported(void) {
    // Check if stdout is a terminal and TERM is set
    if (!isatty(fileno(stdout))) {
        return 0;
    }
    const char *term = getenv("TERM");
    if (!term || strcmp(term, "dumb") == 0) {
        return 0;
    }
    return 1;
}

void print_version(void) {
    const int color = is_color_supported();
    if (color) {
        printf("%srpc%s %s1.0.0%s - Replica template manager\n", 
               BOLD CYAN, RESET, GREEN, RESET);
    } else {
        printf("rpc 1.0.0 - Replica template manager\n");
    }
}

void print_error(const char *format, ...) {
    const int color = is_color_supported();
    va_list args;
    va_start(args, format);
    
    if (color) {
        fprintf(stderr, "%s✗ Error:%s ", BOLD RED, RESET);
    } else {
        fprintf(stderr, "Error: ");
    }
    
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void print_success(const char *format, ...) {
    const int color = is_color_supported();
    va_list args;
    va_start(args, format);
    
    if (color) {
        printf("%s✓%s ", BOLD GREEN, RESET);
    } else {
        printf("✓ ");
    }
    
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

void print_info(const char *format, ...) {
    const int color = is_color_supported();
    va_list args;
    va_start(args, format);
    
    if (color) {
        printf("%sℹ%s ", BOLD BLUE, RESET);
    } else {
        printf("i ");
    }
    
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

void print_warning(const char *format, ...) {
    const int color = is_color_supported();
    va_list args;
    va_start(args, format);
    
    if (color) {
        printf("%s⚠%s ", BOLD YELLOW, RESET);
    } else {
        printf("! ");
    }
    
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

void print_progress(const char *message) {
    const int color = is_color_supported();
    if (color) {
        printf("%s▶%s %s\n", BOLD CYAN, RESET, message);
    } else {
        printf("> %s\n", message);
    }
    fflush(stdout);
}

void print_help(const char *prog) {
    const int color = is_color_supported();
    
    // Header
    if (color) {
        printf("%s%s%s - Replica template manager%s\n\n", BOLD CYAN, prog, CYAN, RESET);
        printf("%sUSAGE:%s\n", BOLD WHITE, RESET);
    } else {
        printf("%s - Replica template manager\n\n", prog);
        printf("USAGE:\n");
    }
    
    // Basic usage
    if (color) {
        printf("  %s%s%s %sinit%s [%sOPTIONS%s] %s<destination>%s\n", 
               BOLD, prog, RESET, GREEN, RESET, YELLOW, RESET, BLUE, RESET);
        printf("  %s%s%s [%s--help%s|%s--version%s]\n\n", 
               BOLD, prog, RESET, CYAN, RESET, CYAN, RESET);
    } else {
        printf("  %s init [OPTIONS] <destination>\n", prog);
        printf("  %s [--help|--version]\n\n", prog);
    }
    
    // Commands
    if (color) {
        printf("%sCOMMANDS:%s\n", BOLD WHITE, RESET);
        printf("  %sinit%s                   Initialize templates in destination directory\n", GREEN, RESET);
    } else {
        printf("COMMANDS:\n");
        printf("  init                   Initialize templates in destination directory\n");
    }
    
    printf("\n");
    
    // Template options
    if (color) {
        printf("%sTEMPLATE OPTIONS:%s\n", BOLD WHITE, RESET);
    } else {
        printf("TEMPLATE OPTIONS:\n");
    }
    
    const char templates[][2][50] = {
        {"--readme", "README generation templates"},
        {"--release-notes", "Release notes templates"},
        {"--post", "LinkedIn post templates"},
        {"--contributing", "Contributing guidelines templates"},
        {"--license", "License selection templates"},
        {"--security", "Security policy templates"},
        {"--code-of-conduct", "Code of conduct templates"},
        {"--issue-template", "Issue template prompts"},
        {"--pr-template", "Pull request template prompts"},
        {"--architecture", "Architecture documentation templates"},
        {"--roadmap", "Project roadmap templates"},
        {"--support", "Support documentation templates"},
        {"--install", "Installation guide templates"},
        {"--all", "Copy all available templates"}
    };
    
    for (int i = 0; i < 14; i++) {
        if (color) {
            printf("  %s%-18s%s %s%s%s\n", YELLOW, templates[i][0], RESET, GRAY, templates[i][1], RESET);
        } else {
            printf("  %-18s %s\n", templates[i][0], templates[i][1]);
        }
    }
    
    printf("\n");
    
    // Global options
    if (color) {
        printf("%sGLOBAL OPTIONS:%s\n", BOLD WHITE, RESET);
        printf("  %s-h, --help%s           Show this help message\n", CYAN, RESET);
        printf("  %s-V, --version%s        Show version information\n", CYAN, RESET);
        printf("  %s-v, --verbose%s        Enable verbose output\n", CYAN, RESET);
    } else {
        printf("GLOBAL OPTIONS:\n");
        printf("  -h, --help           Show this help message\n");
        printf("  -V, --version        Show version information\n");
        printf("  -v, --verbose        Enable verbose output\n");
    }
    
    printf("\n");
    
    // Examples
    if (color) {
        printf("%sEXAMPLES:%s\n", BOLD WHITE, RESET);
        printf("  %s%s init ./my-project%s           %s# Initialize with README and release notes%s\n", 
               BOLD, prog, RESET, GRAY, RESET);
        printf("  %s%s init --readme ./docs%s        %s# Copy only README templates%s\n", 
               BOLD, prog, RESET, GRAY, RESET);
        printf("  %s%s init --all ./new-project%s    %s# Copy all available templates%s\n", 
               BOLD, prog, RESET, GRAY, RESET);
    } else {
        printf("EXAMPLES:\n");
        printf("  %s init ./my-project           # Initialize with README and release notes\n", prog);
        printf("  %s init --readme ./docs        # Copy only README templates\n", prog);
        printf("  %s init --all ./new-project    # Copy all available templates\n", prog);
    }
}
