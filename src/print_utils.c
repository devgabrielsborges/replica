#include "print_utils.h"
#include "cli_utils.h"
#include <stdio.h>
#include <string.h>

// Template data structure for beautiful display
typedef struct {
    const char *flag;
    const char *name;
    const char *description;
    const char *icon;
} template_info_t;

static const template_info_t templates[] = {
    {"--readme", "README Templates", "Professional README.md generation", "📝"},
    {"--release-notes", "Release Notes", "Comprehensive release documentation", "🚀"},
    {"--post", "Social Posts", "LinkedIn and social media content", "📱"},
    {"--contributing", "Contributing Guides", "Contributor guidelines and standards", "🤝"},
    {"--license", "License Templates", "Software license selection", "⚖️"},
    {"--security", "Security Policies", "Security guidelines and policies", "🔒"},
    {"--code-of-conduct", "Code of Conduct", "Community behavior standards", "📋"},
    {"--issue-template", "Issue Templates", "GitHub issue reporting templates", "🐛"},
    {"--pr-template", "PR Templates", "Pull request contribution templates", "🔀"},
    {"--architecture", "Architecture Docs", "Technical architecture documentation", "🏗️"},
    {"--roadmap", "Project Roadmaps", "Development planning and milestones", "🗺️"},
    {"--support", "Support Docs", "User help and troubleshooting guides", "🆘"},
    {"--install", "Installation Guides", "Setup and deployment instructions", "⚙️"},
    {"--all", "Complete Package", "All available templates and resources", "📦"}
};

static const int template_count = sizeof(templates) / sizeof(templates[0]);

void print_help(const char *prog) {
    // Beautiful banner
    cli_print_banner("Replica (rpc)", "Template Management Tool");
    
    // Description panel
    cli_print_panel("About", 
        "A modern CLI tool for managing project templates and prompts with style ✨", 
        THEME_INFO);
    printf("\n");
    
    // Usage section
    if (cli_supports_color()) {
        printf("%s%s%s USAGE%s\n", ICON_COMPUTER, BOLD, THEME_PRIMARY, RESET);
        printf("\n");
        
        // Command examples with beautiful formatting
        printf("  %s%s%s %sinit%s %s<destination>%s\n", 
               THEME_MUTED, prog, RESET, THEME_SUCCESS, RESET, THEME_ACCENT, RESET);
        printf("  %s%s%s %sinit%s %s--<template>%s %s<destination>%s\n", 
               THEME_MUTED, prog, RESET, THEME_SUCCESS, RESET, THEME_INFO, RESET, THEME_ACCENT, RESET);
        printf("  %s%s%s %shelp%s | %sversion%s\n\n", 
               THEME_MUTED, prog, RESET, THEME_SUCCESS, RESET, THEME_SUCCESS, RESET);
    } else {
        printf("USAGE:\n");
        printf("  %s init <destination>\n", prog);
        printf("  %s init --<template> <destination>\n", prog);
        printf("  %s help | version\n\n", prog);
    }
    
    // Examples section
    if (cli_supports_color()) {
        printf("%s%s%s EXAMPLES%s\n", ICON_SPARKLES, BOLD, THEME_WARNING, RESET);
        printf("\n");
        
        // Example 1
        printf("  %s%s# Quick start with default templates%s\n", THEME_MUTED, ITALIC, RESET);
        printf("  %s$ %s%s init %s./my-project%s\n\n", 
               THEME_MUTED, THEME_SUCCESS, prog, THEME_ACCENT, RESET);
        
        // Example 2  
        printf("  %s%s# Specific template installation%s\n", THEME_MUTED, ITALIC, RESET);
        printf("  %s$ %s%s init --readme %s./docs%s\n\n", 
               THEME_MUTED, THEME_SUCCESS, prog, THEME_ACCENT, RESET);
        
        // Example 3
        printf("  %s%s# Complete template package%s\n", THEME_MUTED, ITALIC, RESET);
        printf("  %s$ %s%s init --all %s./complete-project%s\n\n", 
               THEME_MUTED, THEME_SUCCESS, prog, THEME_ACCENT, RESET);
    } else {
        printf("EXAMPLES:\n");
        printf("  # Quick start with default templates\n");
        printf("  %s init ./my-project\n\n", prog);
        printf("  # Specific template installation\n");
        printf("  %s init --readme ./docs\n\n", prog);
        printf("  # Complete template package\n");
        printf("  %s init --all ./complete-project\n\n", prog);
    }
    
    // Templates table
    if (cli_supports_color()) {
        printf("%s%s%s AVAILABLE TEMPLATES%s\n", ICON_PACKAGE, BOLD, THEME_PRIMARY, RESET);
        printf("\n");
        
        // Create beautiful table
        const char *headers[] = {"Option", "Name", "Description"};
        int widths[] = {18, 20, 50};
        
        cli_print_table_header(headers, 3, widths);
        
        for (int i = 0; i < template_count; i++) {
            char option_with_icon[32];
            snprintf(option_with_icon, sizeof(option_with_icon), "%s %s", 
                    templates[i].icon, templates[i].flag);
            
            const char *row[] = {
                option_with_icon,
                templates[i].name,
                templates[i].description
            };
            
            cli_print_table_row(row, 3, widths);
        }
        
        cli_print_table_separator(widths, 3);
    } else {
        printf("AVAILABLE TEMPLATES:\n");
        for (int i = 0; i < template_count; i++) {
            printf("  %-18s %-20s %s\n", 
                   templates[i].flag,
                   templates[i].name, 
                   templates[i].description);
        }
    }
    
    printf("\n");
    
    // Options section
    if (cli_supports_color()) {
        printf("%s%s%s OPTIONS%s\n", ICON_GEAR, BOLD, THEME_INFO, RESET);
        printf("\n");
        
        cli_option_t help_option = {
            .short_flag = "-h",
            .long_flag = "--help",
            .description = "Show this help message and exit",
            .required = false
        };
        
        cli_option_t version_option = {
            .short_flag = "-v", 
            .long_flag = "--version",
            .description = "Show version information and exit",
            .required = false
        };
        
        cli_print_option_help(&help_option);
        cli_print_option_help(&version_option);
    } else {
        printf("OPTIONS:\n");
        printf("  -h, --help     Show this help message\n");
        printf("  -v, --version  Show version information\n");
    }
    
    printf("\n");
    
    // Footer with links
    if (cli_supports_color()) {
        cli_print_status_bar(
            "💡 Learn more at https://github.com/gsborgz/replica", 
            "Made with ❤️ by Gabriel Borges"
        );
    } else {
        printf("Learn more: https://github.com/gsborgz/replica\n");
        printf("Made with love by Gabriel Borges\n");
    }
}
