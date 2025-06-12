#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include "copy.h"
#include "print_utils.h"

// Global verbose flag - definition
bool verbose = false;

typedef struct {
    const char *name;
    const char *description;
    int (*func)(const char *dest);
} template_option;

// Template mapping table
static const template_option templates[] = {
    {"--readme", "README generation templates", copy_readme},
    {"--release-notes", "Release notes templates", copy_release_notes},
    {"--post", "LinkedIn post templates", copy_post},
    {"--contributing", "Contributing guidelines templates", copy_contributing},
    {"--license", "License selection templates", copy_license_template},
    {"--security", "Security policy templates", copy_security},
    {"--code-of-conduct", "Code of conduct templates", copy_code_of_conduct},
    {"--issue-template", "Issue template prompts", copy_issue_template},
    {"--pr-template", "Pull request template prompts", copy_pr_template},
    {"--architecture", "Architecture documentation templates", copy_architecture},
    {"--roadmap", "Project roadmap templates", copy_roadmap},
    {"--support", "Support documentation templates", copy_support},
    {"--install", "Installation guide templates", copy_install},
    {"--all", "All available templates", copy_all_templates},
    {NULL, NULL, NULL} // Sentinel
};

static int show_help(const char *prog) {
    print_help(prog);
    return EXIT_SUCCESS;
}

static int show_version(void) {
    print_version();
    return EXIT_SUCCESS;
}

static bool is_help_flag(const char *arg) {
    return strcmp(arg, "help") == 0 || 
           strcmp(arg, "-h") == 0 || 
           strcmp(arg, "--help") == 0;
}

static bool is_version_flag(const char *arg) {
    return strcmp(arg, "-V") == 0 || 
           strcmp(arg, "--version") == 0;
}

static bool is_verbose_flag(const char *arg) {
    return strcmp(arg, "-v") == 0 || 
           strcmp(arg, "--verbose") == 0;
}

static const template_option* find_template(const char *name) {
    for (const template_option *tmpl = templates; tmpl->name != NULL; tmpl++) {
        if (strcmp(name, tmpl->name) == 0) {
            return tmpl;
        }
    }
    return NULL;
}

static int validate_destination(const char *dest) {
    if (!dest || strlen(dest) == 0) {
        print_error("Destination path cannot be empty");
        return -1;
    }
    
    // Check if destination is too long
    if (strlen(dest) > 4096) {
        print_error("Destination path is too long (max 4096 characters)");
        return -1;
    }
    
    if (verbose) {
        print_info("Validating destination: %s", dest);
    }
    
    return 0;
}

static int execute_template_copy(const template_option *tmpl, const char *dest) {
    if (verbose) {
        char message[256];
        snprintf(message, sizeof(message), "Copying %s to %s", tmpl->description, dest);
        print_progress(message);
    }
    
    int result = tmpl->func(dest);
    
    if (result == 0) {
        print_success("Successfully copied %s", tmpl->description);
    } else {
        print_error("Failed to copy %s", tmpl->description);
    }
    
    return result;
}

static int handle_init_command(int argc, char *argv[]) {
    if (argc < 3) {
        print_error("Missing destination directory");
        print_info("Use '%s --help' for usage information", argv[0]);
        return EXIT_FAILURE;
    }
    
    const char *dest = argv[argc - 1];
    
    if (validate_destination(dest) != 0) {
        return EXIT_FAILURE;
    }
    
    // Handle simple init (no template specified)
    if (argc == 3) {
        if (verbose) {
            print_info("No specific template requested, copying default templates");
        }
        
        int r1 = execute_template_copy(&templates[0], dest); // README
        int r2 = execute_template_copy(&templates[1], dest); // Release notes
        
        return (r1 == 0 && r2 == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    
    // Handle specific template
    if (argc == 4) {
        const char *template_arg = argv[2];
        const template_option *tmpl = find_template(template_arg);
        
        if (tmpl == NULL) {
            print_error("Unknown template option: %s", template_arg);
            print_info("Use '%s --help' to see available templates", argv[0]);
            return EXIT_FAILURE;
        }
        
        return execute_template_copy(tmpl, dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    
    // Too many arguments
    print_error("Too many arguments for init command");
    print_info("Use '%s --help' for usage information", argv[0]);
    return EXIT_FAILURE;
}

int main(int argc, char *argv[]) {
    // Handle no arguments or help
    if (argc < 2) {
        return show_help(argv[0]);
    }
    
    // Check for global flags first
    for (int i = 1; i < argc; i++) {
        if (is_help_flag(argv[i])) {
            return show_help(argv[0]);
        }
        if (is_version_flag(argv[i])) {
            return show_version();
        }
        if (is_verbose_flag(argv[i])) {
            verbose = true;
            // Remove verbose flag from argv for further processing
            for (int j = i; j < argc - 1; j++) {
                argv[j] = argv[j + 1];
            }
            argc--;
            i--; // Adjust index after removal
        }
    }
    
    // Re-check argc after potential argument removal
    if (argc < 2) {
        return show_help(argv[0]);
    }
    
    // Handle commands
    if (strcmp(argv[1], "init") == 0) {
        return handle_init_command(argc, argv);
    }
    
    // Unknown command
    print_error("Unknown command: %s", argv[1]);
    print_info("Use '%s --help' for usage information", argv[0]);
    return EXIT_FAILURE;
}