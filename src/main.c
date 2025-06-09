#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "copy.h"
#include "print_utils.h"

int main(int argc, char *argv[]) {
    if (argc < 2 || strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_help(argv[0]);
        return EXIT_SUCCESS;
    }

    if (strcmp(argv[1], "init") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Missing destination directory.\n");
            print_help(argv[0]);
            return EXIT_FAILURE;
        }
        const char *dest = argv[argc - 1];

        if (argc == 3) {
            int r1 = copy_readme(dest);
            int r2 = copy_release_notes(dest);
            return (r1 == 0 && r2 == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
        } else if (argc == 4) {
            if (strcmp(argv[2], "--readme") == 0) {
                return copy_readme(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--release-notes") == 0) {
                return copy_release_notes(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--post") == 0) {
                return copy_post(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--contributing") == 0) {
                return copy_contributing(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--license") == 0) {
                return copy_license_template(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--security") == 0) {
                return copy_security(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--code-of-conduct") == 0) {
                return copy_code_of_conduct(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--issue-template") == 0) {
                return copy_issue_template(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--pr-template") == 0) {
                return copy_pr_template(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--architecture") == 0) {
                return copy_architecture(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--roadmap") == 0) {
                return copy_roadmap(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--support") == 0) {
                return copy_support(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--install") == 0) {
                return copy_install(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else if (strcmp(argv[2], "--all") == 0) {
                return copy_all_templates(dest) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
            } else {
                fprintf(stderr, "Unknown option: %s\n", argv[2]);
                print_help(argv[0]);
                return EXIT_FAILURE;
            }
        }
    }

    fprintf(stderr, "Unknown command or arguments.\n");
    print_help(argv[0]);
    return EXIT_FAILURE;
}