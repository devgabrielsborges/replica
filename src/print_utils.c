#include "print_utils.h"
#include <stdio.h>


void print_help(const char *prog) {
    printf("Usage:\n");
    printf("  %s init <destination>\n", prog);
    printf("  %s init --readme <destination>\n", prog);
    printf("  %s init --release-notes <destination>\n", prog);
    printf("  %s init --post <destination>\n", prog);
    printf("  %s init --contributing <destination>\n", prog);
    printf("  %s init --license <destination>\n", prog);
    printf("  %s init --security <destination>\n", prog);
    printf("  %s init --code-of-conduct <destination>\n", prog);
    printf("  %s init --issue-template <destination>\n", prog);
    printf("  %s init --pr-template <destination>\n", prog);
    printf("  %s init --architecture <destination>\n", prog);
    printf("  %s init --roadmap <destination>\n", prog);
    printf("  %s init --support <destination>\n", prog);
    printf("  %s init --install <destination>\n", prog);
    printf("  %s init --all <destination>\n", prog);
    printf("  %s help|-h|--help\n", prog);
    printf("\nTemplate Categories:\n");
    printf("  --readme          README generation templates\n");
    printf("  --release-notes   Release notes templates\n");
    printf("  --post           LinkedIn post templates\n");
    printf("  --contributing   Contributing guidelines templates\n");
    printf("  --license        License selection templates\n");
    printf("  --security       Security policy templates\n");
    printf("  --code-of-conduct Code of conduct templates\n");
    printf("  --issue-template  Issue template prompts\n");
    printf("  --pr-template    Pull request template prompts\n");
    printf("  --architecture   Architecture documentation templates\n");
    printf("  --roadmap        Project roadmap templates\n");
    printf("  --support        Support documentation templates\n");
    printf("  --install        Installation guide templates\n");
    printf("  --all            Copy all available templates\n");
}
