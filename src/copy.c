#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "copy.h"

#ifndef REPLICA_DATADIR
#warning "REPLICA_DATADIR is not defined. Using a default relative path for local development."
#define REPLICA_DATADIR "." // Fallback for local development (assumes running from project root)
#endif

static void construct_source_path(char *path_buffer, size_t buffer_size, const char *sub_path) {
    snprintf(path_buffer, buffer_size, "%s%s", REPLICA_DATADIR, sub_path);
}

int copy_file(const char *src_full_path, const char *dest_dir) {
    struct stat st = {0};
    if (stat(dest_dir, &st) == -1) {
        if (mkdir(dest_dir, 0755) != 0) {
            perror("Error creating destination directory");
            return -1;
        }
    }

    const char *filename_ptr = strrchr(src_full_path, '/');
    if (filename_ptr != NULL) {
        filename_ptr++;
    } else {
        filename_ptr = src_full_path; // No '/' found, so src_full_path is just the filename
    }

    char dest_full_path[1024];
    // Ensure dest_dir is not empty and handle potential trailing slash if necessary
    if (dest_dir == NULL || dest_dir[0] == '\0') {
        snprintf(dest_full_path, sizeof(dest_full_path), "%s", filename_ptr);
    } else {
        snprintf(dest_full_path, sizeof(dest_full_path), "%s/%s", dest_dir, filename_ptr);
    }


    FILE *source = fopen(src_full_path, "rb");
    if (!source) {
        perror("Error opening source file (fopen)");
        fprintf(stderr, "Failed to open: %s\n", src_full_path);
        return -1;
    }

    FILE *destination_file = fopen(dest_full_path, "wb");
    if (!destination_file) {
        perror("Error opening destination file (fopen)");
        fprintf(stderr, "Failed to open for writing: %s\n", dest_full_path);
        fclose(source);
        return -1;
    }

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytes_read, destination_file) != bytes_read) {
            perror("Error writing to destination file (fwrite)");
            fclose(source);
            fclose(destination_file);
            return -1;
        }
    }

    if (ferror(source)) {
        perror("Error reading from source file (ferror)");
        fclose(source);
        fclose(destination_file);
        return -1; // Indicate read error
    }

    fclose(source);
    fclose(destination_file);
    printf("Copied '%s' to '%s'\n", src_full_path, dest_full_path);
    return 0;
}

int copy_directory(const char *src, const char *dest) {
    DIR *dir = opendir(src);
    if (!dir) {
        perror("Error opening source directory");
        return -1;
    }

    struct stat st_dest = {0};
    if (stat(dest, &st_dest) == -1) {
        if (mkdir(dest, 0755) != 0 && errno != EEXIST) { // Create it, ignore if it already exists
            perror("Error creating destination directory");
            closedir(dir);
            return -1;
        }
    }


    struct dirent *entry;
    int result = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char src_path_item[1024];
            char dest_path_item[1024];
            snprintf(src_path_item, sizeof(src_path_item), "%s/%s", src, entry->d_name);
            snprintf(dest_path_item, sizeof(dest_path_item), "%s/%s", dest, entry->d_name);

            struct stat entry_stat;
            if (stat(src_path_item, &entry_stat) == 0) {
                if (S_ISDIR(entry_stat.st_mode)) {
                    if (copy_directory(src_path_item, dest_path_item) != 0)
                        result = -1; // Propagate error
                } else {
                    if (copy_file(src_path_item, dest) != 0) { // Pass 'dest' as the target directory
                        result = -1; // Propagate error
                    }
                }
            } else {
                perror("Error getting stat for source item");
                result = -1; // Error stating item
            }
        }
    }

    closedir(dir);
    return result;
}


static int create_directories(const char *path) {
    char temp_path[1024];
    char *p = NULL;
    size_t len;

    snprintf(temp_path, sizeof(temp_path), "%s", path);
    len = strlen(temp_path);
    if (temp_path[len - 1] == '/') {
        temp_path[len - 1] = 0;
    }

    for (p = temp_path + 1; *p; p++) {
        if (*p == '/') {
            *p = 0;
            if (mkdir(temp_path, 0755) != 0 && errno != EEXIST) {
                return -1;
            }
            *p = '/';
        }
    }
    if (mkdir(temp_path, 0755) != 0 && errno != EEXIST) {
        return -1;
    }
    return 0;
}

int copy_readme(const char *dest) {
    // Create .github/prompts/ directory
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    // Create .github/instructions/ directory  
    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files to their respective directories
    char src_path[1024];
    char dest_path[1024];
    
    // Copy prompt file
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/generate-readme.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/generate-readme.prompt.md", dest);
    
    int r1 = copy_file_to_file(src_path, dest_path);
    
    // Copy instructions file
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/readme.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/readme.instructions.md", dest);
    
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_release_notes(const char *dest) {
    // Create directories
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files
    char src_path[1024];
    char dest_path[1024];
    
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/generate-release-notes.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/generate-release-notes.prompt.md", dest);
    int r1 = copy_file_to_file(src_path, dest_path);
    
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/release-notes.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/release-notes.instructions.md", dest);
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_post(const char *dest) {
    // Create directories
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files
    char src_path[1024];
    char dest_path[1024];
    
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/generate-linkedin.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/generate-linkedin.prompt.md", dest);
    int r1 = copy_file_to_file(src_path, dest_path);
    
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/linkedin.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/linkedin.instructions.md", dest);
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_contributing(const char *dest) {
    // Create directories
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files
    char src_path[1024];
    char dest_path[1024];
    
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/CONTRIBUTING.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/CONTRIBUTING.prompt.md", dest);
    int r1 = copy_file_to_file(src_path, dest_path);
    
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/CONTRIBUTING.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/CONTRIBUTING.instructions.md", dest);
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_license_template(const char *dest) {
    // Create directories
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files
    char src_path[1024];
    char dest_path[1024];
    
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/LICENSE.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/LICENSE.prompt.md", dest);
    int r1 = copy_file_to_file(src_path, dest_path);
    
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/LICENSE.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/LICENSE.instructions.md", dest);
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_security(const char *dest) {
    // Create directories
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files
    char src_path[1024];
    char dest_path[1024];
    
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/SECURITY.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/SECURITY.prompt.md", dest);
    int r1 = copy_file_to_file(src_path, dest_path);
    
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/SECURITY.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/SECURITY.instructions.md", dest);
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_code_of_conduct(const char *dest) {
    // Create directories
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files
    char src_path[1024];
    char dest_path[1024];
    
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/CODE_OF_CONDUCT.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/CODE_OF_CONDUCT.prompt.md", dest);
    int r1 = copy_file_to_file(src_path, dest_path);
    
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/CODE_OF_CONDUCT.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/CODE_OF_CONDUCT.instructions.md", dest);
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_issue_template(const char *dest) {
    // Create directories
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files
    char src_path[1024];
    char dest_path[1024];
    
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/ISSUE_TEMPLATE.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/ISSUE_TEMPLATE.prompt.md", dest);
    int r1 = copy_file_to_file(src_path, dest_path);
    
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/ISSUE_TEMPLATE.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/ISSUE_TEMPLATE.instructions.md", dest);
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_pr_template(const char *dest) {
    // Create directories
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files
    char src_path[1024];
    char dest_path[1024];
    
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/PULL_REQUEST_TEMPLATE.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/PULL_REQUEST_TEMPLATE.prompt.md", dest);
    int r1 = copy_file_to_file(src_path, dest_path);
    
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/PULL_REQUEST_TEMPLATE.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/PULL_REQUEST_TEMPLATE.instructions.md", dest);
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_architecture(const char *dest) {
    // Create directories
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files
    char src_path[1024];
    char dest_path[1024];
    
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/ARCHITECTURE.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/ARCHITECTURE.prompt.md", dest);
    int r1 = copy_file_to_file(src_path, dest_path);
    
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/ARCHITECTURE.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/ARCHITECTURE.instructions.md", dest);
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_roadmap(const char *dest) {
    // Create directories
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files
    char src_path[1024];
    char dest_path[1024];
    
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/ROADMAP.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/ROADMAP.prompt.md", dest);
    int r1 = copy_file_to_file(src_path, dest_path);
    
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/ROADMAP.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/ROADMAP.instructions.md", dest);
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_support(const char *dest) {
    // Create directories
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files
    char src_path[1024];
    char dest_path[1024];
    
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/SUPPORT.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/SUPPORT.prompt.md", dest);
    int r1 = copy_file_to_file(src_path, dest_path);
    
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/SUPPORT.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/SUPPORT.instructions.md", dest);
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_install(const char *dest) {
    // Create directories
    char prompts_dir[1024];
    snprintf(prompts_dir, sizeof(prompts_dir), "%s/.github/prompts", dest);
    if (create_directories(prompts_dir) != 0) {
        perror("Error creating prompts directory");
        return -1;
    }

    char instructions_dir[1024];
    snprintf(instructions_dir, sizeof(instructions_dir), "%s/.github/instructions", dest);
    if (create_directories(instructions_dir) != 0) {
        perror("Error creating instructions directory");
        return -1;
    }

    // Copy files
    char src_path[1024];
    char dest_path[1024];
    
    construct_source_path(src_path, sizeof(src_path), "/.github/prompts/INSTALL.prompt.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/prompts/INSTALL.prompt.md", dest);
    int r1 = copy_file_to_file(src_path, dest_path);
    
    construct_source_path(src_path, sizeof(src_path), "/.github/instructions/INSTALL.instructions.md");
    snprintf(dest_path, sizeof(dest_path), "%s/.github/instructions/INSTALL.instructions.md", dest);
    int r2 = copy_file_to_file(src_path, dest_path);
    
    return (r1 == 0 && r2 == 0) ? 0 : -1;
}

int copy_all_templates(const char *dest) {
    // Copy all available templates
    int results[13];
    
    results[0] = copy_readme(dest);
    results[1] = copy_release_notes(dest);
    results[2] = copy_post(dest);
    results[3] = copy_contributing(dest);
    results[4] = copy_license_template(dest);
    results[5] = copy_security(dest);
    results[6] = copy_code_of_conduct(dest);
    results[7] = copy_issue_template(dest);
    results[8] = copy_pr_template(dest);
    results[9] = copy_architecture(dest);
    results[10] = copy_roadmap(dest);
    results[11] = copy_support(dest);
    results[12] = copy_install(dest);
    
    // Check if all operations succeeded
    for (int i = 0; i < 13; i++) {
        if (results[i] != 0) {
            return -1;
        }
    }
    
    return 0;
}

int copy_file_to_file(const char *src_full_path, const char *dest_full_path) {
    // Create parent directories for dest_full_path if needed
    char dest_dir[1024];
    strncpy(dest_dir, dest_full_path, sizeof(dest_dir));
    dest_dir[sizeof(dest_dir) - 1] = '\0';
    char *last_slash = strrchr(dest_dir, '/');
    if (last_slash) {
        *last_slash = '\0';
        struct stat st = {0};
        if (stat(dest_dir, &st) == -1) {
            if (mkdir(dest_dir, 0755) != 0 && errno != EEXIST) {
                perror("Error creating parent directory for destination file");
                return -1;
            }
        }
    }

    FILE *source = fopen(src_full_path, "rb");
    if (!source) {
        perror("Error opening source file (fopen)");
        fprintf(stderr, "Failed to open: %s\n", src_full_path);
        return -1;
    }

    FILE *destination_file = fopen(dest_full_path, "wb");
    if (!destination_file) {
        perror("Error opening destination file (fopen)");
        fprintf(stderr, "Failed to open for writing: %s\n", dest_full_path);
        fclose(source);
        return -1;
    }

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytes_read, destination_file) != bytes_read) {
            perror("Error writing to destination file (fwrite)");
            fclose(source);
            fclose(destination_file);
            return -1;
        }
    }

    if (ferror(source)) {
        perror("Error reading from source file (ferror)");
        fclose(source);
        fclose(destination_file);
        return -1;
    }

    fclose(source);
    fclose(destination_file);
    printf("Copied '%s' to '%s'\n", src_full_path, dest_full_path);
    return 0;
}
