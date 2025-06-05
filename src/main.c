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