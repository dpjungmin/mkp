#include <string.h>
#include <stdlib.h>

#include "mkp.h"

void set_prog(char *prog, const char *str)
{
        char *ptr = NULL;

        if ((ptr = strrchr(str, DIR_SEP)) != NULL)
                strcpy(prog, ++ptr);
        else
                strcpy(prog, str);
}

void set_template(char *template)
{
        char *env;

        if ((env = getenv(TEMPLATE_ENV)) == NULL)
                env = TEMPLATE_DEFAULT;

        strncpy(template, env, strlen(env));
}

void open_template(FILE *fp, char *template)
{
        if ((fp = fopen(template, "r")) == NULL) {
                char msg[MAX_MSG_LENGTH + MAX_PATH_LENGTH];
                sprintf(msg,"Failed to open \"%s\"", template);
                perror(msg);
                fprintf(stderr,
                        "Set an environment variable %s that points to the template file, or create \"%s\"\n",
                        TEMPLATE_ENV,
                        TEMPLATE_DEFAULT);
                exit(EXIT_FAILURE);
        }
}

int mkp(FILE *fp, char *fname)
{
        /* TODO: create "fname" and copy "fp" */
        printf("creating %s\n", fname);
        return(0);
}
