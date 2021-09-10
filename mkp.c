#include <string.h>

#include "mkp.h"

void set_prog(char *prog, const char *str)
{
        char *ptr = NULL;

        if ((ptr = strrchr(str, DIR_SEP)) != NULL)
                strcpy(prog, ++ptr);
        else
                strcpy(prog, str);
}

int mkp(FILE *fp, char *fname)
{
        /* TODO: create "fname" and copy "fp" */
        printf("creating %s\n", fname);
        return(0);
}
