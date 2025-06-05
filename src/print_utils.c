#include "print_utils.h"
#include <stdio.h>


void print_help(const char *prog) {
    printf("Usage:\n");
    printf("  %s init <destination>\n", prog);
    printf("  %s init --readme <destination>\n", prog);
    printf("  %s init --release-notes <destination>\n", prog);
    printf("  %s init --post <destination>\n", prog);
    printf("  %s help|-h|--help\n", prog);
}
