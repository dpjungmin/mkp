#include <stdio.h>
#include <stdlib.h>

#include "mkp.h"

int main(int argc, char *argv[])
{
        char prog[MAX_PATH_LENGTH];
        char *template;
        FILE *fp;

        set_prog(prog, *argv);

        if ((template = getenv(TEMPLATE)) == NULL)
                template = DEFAULT_TEMPLATE;

        if ((fp = fopen(template, "r")) == NULL) {
                char msg[MAX_MSG_LENGTH];
                sprintf(msg, "Failed to open \"%s\"", template);
                perror(msg);
                exit(EXIT_FAILURE);
        }

        while (--argc) {
                mkp(fp, *++argv);
        }
}
