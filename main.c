#include <stdio.h>
#include <stdlib.h>

#include "mkp.h"

int main(int argc, char *argv[])
{
        char prog[MAX_PATH_LENGTH];
        char template[MAX_PATH_LENGTH];
        FILE *fp = NULL;

        set_prog(prog, *argv);
        set_template(template);
        open_template(fp, template);

        while (--argc) {
                /* TODO: spawn threads to call mkp */
                mkp(fp, *++argv);
        }
}
