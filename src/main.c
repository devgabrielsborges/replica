#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "copy.h"
#include "print_utils.h"
#include "cli_utils.h"

static void print_version(void) {
    cli_print_banner("Replica v1.0.0", "Template Management Tool");
    
    cli_print_panel("About", 
        "A modern, cross-platform CLI tool for managing project templates 🚀", 
        THEME_SUCCESS);
    printf("\n");
    
    if (cli_supports_color()) {
        // Information badges
        printf("  ");
        cli_print_badge("Author", BG_BRIGHT_CYAN, BRIGHT_WHITE);
        printf(" Gabriel Souza Borges\n");
        
        printf("  ");
        cli_print_badge("License", BG_BRIGHT_GREEN, BRIGHT_WHITE);
        printf(" MIT License\n");
        
        printf("  ");
        cli_print_badge("Website", BG_BRIGHT_MAGENTA, BRIGHT_WHITE);
        printf(" https://github.com/devgabrielsborges/replica\n");
        
        printf("  ");
        cli_print_badge("Platform", BG_BRIGHT_YELLOW, BLACK);
        printf(" Cross-platform (Linux, macOS, Windows)\n");
    } else {
        printf("Author:   Gabriel Souza Borges\n");
        printf("License:  MIT License\n");
        printf("Website:  https://github.com/devgabrielsborges/replica\n");
        printf("Platform: Cross-platform\n");
    }
    
    printf("\n");
    cli_print_info("Use 'rpc help' to see available commands and templates");
}

static int execute_template_operation(const char *template_name, const char *dest) {
    if (!template_name || !dest) return -1;
    
    // Enhanced operation feedback
    char header_msg[256];
    snprintf(header_msg, sizeof(header_msg), "Installing %s Templates", template_name);
    cli_print_header(header_msg);
    
    // Show destination with beautiful formatting
    if (cli_supports_color()) {
        printf("  %s%sTarget:%s %s%s%s\n\n", 
               ICON_FOLDER, THEME_INFO, RESET, THEME_ACCENT, dest, RESET);
    } else {
        printf("  Target: %s\n\n", dest);
    }
    
    int result = -1;
    const char *operation_name = "Unknown";
    const char *operation_icon = ICON_PACKAGE;
    
    // Enhanced template matching with icons and descriptions
    if (strcmp(template_name, "readme") == 0) {
        operation_name = "README Templates";
        operation_icon = "📝";
        cli_print_step("Generating professional README templates...");
        result = copy_readme(dest);
    } else if (strcmp(template_name, "release-notes") == 0) {
        operation_name = "Release Notes Templates";
        operation_icon = "🚀";
        cli_print_step("Creating release documentation templates...");
        result = copy_release_notes(dest);
    } else if (strcmp(template_name, "post") == 0) {
        operation_name = "Social Media Templates";
        operation_icon = "📱";
        cli_print_step("Setting up social media content templates...");
        result = copy_post(dest);
    } else if (strcmp(template_name, "contributing") == 0) {
        operation_name = "Contributing Guidelines";
        operation_icon = "🤝";
        cli_print_step("Installing contributor guidelines...");
        result = copy_contributing(dest);
    } else if (strcmp(template_name, "license") == 0) {
        operation_name = "License Templates";
        operation_icon = "⚖️";
        cli_print_step("Adding software license templates...");
        result = copy_license_template(dest);
    } else if (strcmp(template_name, "security") == 0) {
        operation_name = "Security Policy Templates";
        operation_icon = "🔒";
        cli_print_step("Installing security policy templates...");
        result = copy_security(dest);
    } else if (strcmp(template_name, "code-of-conduct") == 0) {
        operation_name = "Code of Conduct Templates";
        operation_icon = "📋";
        cli_print_step("Setting up community standards...");
        result = copy_code_of_conduct(dest);
    } else if (strcmp(template_name, "issue-template") == 0) {
        operation_name = "Issue Templates";
        operation_icon = "🐛";
        cli_print_step("Installing GitHub issue templates...");
        result = copy_issue_template(dest);
    } else if (strcmp(template_name, "pr-template") == 0) {
        operation_name = "Pull Request Templates";
        operation_icon = "🔀";
        cli_print_step("Setting up PR contribution templates...");
        result = copy_pr_template(dest);
    } else if (strcmp(template_name, "architecture") == 0) {
        operation_name = "Architecture Documentation";
        operation_icon = "🏗️";
        cli_print_step("Installing architecture documentation...");
        result = copy_architecture(dest);
    } else if (strcmp(template_name, "roadmap") == 0) {
        operation_name = "Project Roadmap Templates";
        operation_icon = "🗺️";
        cli_print_step("Creating project roadmap templates...");
        result = copy_roadmap(dest);
    } else if (strcmp(template_name, "support") == 0) {
        operation_name = "Support Documentation";
        operation_icon = "🆘";
        cli_print_step("Installing support documentation...");
        result = copy_support(dest);
    } else if (strcmp(template_name, "install") == 0) {
        operation_name = "Installation Guides";
        operation_icon = "⚙️";
        cli_print_step("Creating installation guide templates...");
        result = copy_install(dest);
    } else if (strcmp(template_name, "all") == 0) {
        operation_name = "Complete Template Package";
        operation_icon = "📦";
        cli_print_step("Installing all available templates...");
        result = copy_all_templates(dest);
    } else {
        return -1;
    }
    
    printf("\n");
    
    // Enhanced result reporting
    if (result == 0) {
        if (cli_supports_color()) {
            printf("  %s %s%sSuccess!%s %s installed to %s%s%s\n", 
                   operation_icon, THEME_SUCCESS, BOLD, RESET,
                   operation_name, THEME_ACCENT, dest, RESET);
        } else {
            printf("  Success! %s installed to %s\n", operation_name, dest);
        }
        
        // Helpful next steps
        printf("\n");
        cli_print_panel("Next Steps", 
            "📖 Review the installed templates and customize them for your project", 
            THEME_INFO);
    } else {
        if (cli_supports_color()) {
            printf("  %s %s%sFailed!%s Could not install %s to %s%s%s\n", 
                   ICON_ERROR, THEME_ERROR, BOLD, RESET,
                   operation_name, THEME_ACCENT, dest, RESET);
        } else {
            printf("  Failed! Could not install %s to %s\n", operation_name, dest);
        }
        
        printf("\n");
        cli_print_panel("Troubleshooting", 
            "🔧 Check directory permissions and ensure the destination path is valid", 
            THEME_WARNING);
    }
    
    return result;
}

int main(int argc, char *argv[]) {
    // Handle help and version commands
    if (argc < 2 || strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_help(argv[0]);
        return EXIT_SUCCESS;
    }
    
    if (strcmp(argv[1], "version") == 0 || strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        print_version();
        return EXIT_SUCCESS;
    }

    if (strcmp(argv[1], "init") == 0) {
        if (argc < 3) {
            cli_print_banner("Error", "Missing Required Argument");
            cli_print_panel("Problem", 
                "🚫 No destination directory specified", 
                THEME_ERROR);
            printf("\n");
            
            // Show helpful usage hint
            if (cli_supports_color()) {
                printf("  %s%sCorrect usage:%s\n", THEME_INFO, BOLD, RESET);
                printf("    %s%s init %s<destination>%s\n\n", 
                       THEME_SUCCESS, argv[0], THEME_ACCENT, RESET);
                printf("  %s%sExample:%s\n", THEME_WARNING, BOLD, RESET);
                printf("    %s%s init %s./my-project%s\n\n", 
                       THEME_SUCCESS, argv[0], THEME_ACCENT, RESET);
            } else {
                printf("Correct usage: %s init <destination>\n", argv[0]);
                printf("Example: %s init ./my-project\n\n", argv[0]);
            }
            
            cli_print_info("Use 'rpc help' to see all available commands and templates");
            return EXIT_FAILURE;
        }
        
        const char *dest = argv[argc - 1];
        
        // Enhanced destination validation
        struct stat st = {0};
        if (stat(dest, &st) == 0 && !S_ISDIR(st.st_mode)) {
            cli_print_banner("Error", "Invalid Destination");
            cli_print_panel("Problem", 
                "🚫 Destination exists but is not a directory", 
                THEME_ERROR);
            printf("\n");
            
            if (cli_supports_color()) {
                printf("  %s%sPath:%s %s%s%s\n", 
                       ICON_FOLDER, THEME_INFO, RESET, THEME_ACCENT, dest, RESET);
            } else {
                printf("  Path: %s\n", dest);
            }
            
            return EXIT_FAILURE;
        }
        
        // Beautiful initialization header
        cli_print_banner("Template Initialization", "Setting up your project");
        
        // Show target info with styling
        if (cli_supports_color()) {
            printf("  %s%sDestination:%s %s%s%s\n", 
                   ICON_FOLDER, THEME_INFO, RESET, THEME_ACCENT, dest, RESET);
            printf("  %s%sMode:%s ", ICON_GEAR, THEME_INFO, RESET);
        } else {
            printf("  Destination: %s\n", dest);
            printf("  Mode: ");
        }

        if (argc == 3) {
            // Default operation with enhanced feedback
            if (cli_supports_color()) {
                printf("%sQuick Start%s (README + Release Notes)\n\n", THEME_SUCCESS, RESET);
            } else {
                printf("Quick Start (README + Release Notes)\n\n");
            }
            
            cli_print_step("Installing essential templates...");
            
            // Show progress for default templates
            cli_show_progress("Installing README templates", 1, 2);
            int r1 = copy_readme(dest);
            
            cli_show_progress("Installing Release Notes templates", 2, 2);
            int r2 = copy_release_notes(dest);
            
            printf("\n");
            
            if (r1 == 0 && r2 == 0) {
                if (cli_supports_color()) {
                    printf("  %s %s%sSuccess!%s Essential templates installed successfully\n", 
                           ICON_THUMBS_UP, THEME_SUCCESS, BOLD, RESET);
                } else {
                    printf("  Success! Essential templates installed successfully\n");
                }
                
                printf("\n");
                cli_print_panel("Quick Tips", 
                    "💡 Use 'rpc init --all .' to install all available templates", 
                    THEME_INFO);
                
                // Show what was installed
                printf("\n");
                if (cli_supports_color()) {
                    printf("  %s%sInstalled:%s\n", ICON_PACKAGE, THEME_INFO, RESET);
                    cli_print_tree_item("📝 README.md templates", 1, false);
                    cli_print_tree_item("🚀 Release notes templates", 1, true);
                } else {
                    printf("  Installed:\n");
                    printf("    - README.md templates\n");
                    printf("    - Release notes templates\n");
                }
            } else {
                cli_print_panel("Installation Failed", 
                    "❌ Some templates could not be installed. Check permissions and try again.", 
                    THEME_ERROR);
            }
            
            return (r1 == 0 && r2 == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
        } else if (argc == 4) {
            // Specific template operation
            const char *option = argv[2];
            
            if (cli_supports_color()) {
                printf("%sSpecific Template%s (%s)\n\n", THEME_WARNING, RESET, option);
            } else {
                printf("Specific Template (%s)\n\n", option);
            }
            
            // Remove leading dashes
            const char *template_name = option;
            if (template_name[0] == '-' && template_name[1] == '-') {
                template_name += 2;
            } else if (template_name[0] == '-') {
                template_name += 1;
            }
            
            int result = execute_template_operation(template_name, dest);
            
            if (result != 0) {
                cli_print_banner("Error", "Unknown Template Option");
                cli_print_panel("Problem", 
                    "🚫 The specified template option is not recognized", 
                    THEME_ERROR);
                printf("\n");
                
                if (cli_supports_color()) {
                    printf("  %s%sUnknown option:%s %s%s%s\n", 
                           ICON_CROSS, THEME_ERROR, RESET, THEME_ACCENT, option, RESET);
                } else {
                    printf("  Unknown option: %s\n", option);
                }
                
                printf("\n");
                cli_print_info("Use 'rpc help' to see all available template options");
                return EXIT_FAILURE;
            }
            
            return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
        }
    }

    // Enhanced error for unknown commands
    cli_print_banner("Error", "Unknown Command");
    cli_print_panel("Problem", 
        "🚫 The command you entered is not recognized", 
        THEME_ERROR);
    printf("\n");
    
    if (cli_supports_color()) {
        printf("  %s%sYou entered:%s %s%s%s\n", 
               ICON_INFO, THEME_INFO, RESET, THEME_ACCENT, argv[1], RESET);
    } else {
        printf("  You entered: %s\n", argv[1]);
    }
    
    printf("\n");
    
    // Show available commands
    if (cli_supports_color()) {
        printf("  %s%sAvailable commands:%s\n", ICON_GEAR, THEME_SUCCESS, RESET);
        cli_print_tree_item("init - Initialize templates in a directory", 1, false);
        cli_print_tree_item("help - Show help information", 1, false);
        cli_print_tree_item("version - Show version information", 1, true);
    } else {
        printf("  Available commands:\n");
        printf("    - init     Initialize templates\n");
        printf("    - help     Show help information\n");
        printf("    - version  Show version information\n");
    }
    
    printf("\n");
    cli_print_info("Use 'rpc help' for detailed usage information");
    return EXIT_FAILURE;
}