#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "mkp.h"

static inline int __fcpy(int to, int from)
{
        int n;
        char buf[MAX_BUF_SIZE];

        while ((n = read(from, buf, sizeof(buf))) > 0)
                if (write(to, buf, n) != n)
                        return -1;

        return 0;
}

void usage(int status)
{
        printf("Usage: %s filename(s)\n", PROGRAM_NAME);
        printf("   or: %s [options]\n\n", PROGRAM_NAME);
        printf("     --help     display this help and exit\n");
        printf("     --version  output version information and exit\n");
        exit(status);
}

void version(int status)
{
        printf("%s version %s\n", PROGRAM_NAME, VERSION);
        exit(status);
}

void set_template(char **template)
{
        if ((*template = getenv(TEMPLATE_ENV)) == NULL)
                *template = TEMPLATE_DEFAULT;
}

int open_template(const char *template)
{
        int fd;

        if ((fd = open(template, O_RDONLY)) == -1) {
                char msg[MAX_MSG_LENGTH + strlen(template) + 1];
                sprintf(msg,"Failed to open \"%s\"", template);
                perror(msg);
                fprintf(stderr,
                        "Set an environment variable %s that points to the template file, or create \"%s\"\n",
                        TEMPLATE_ENV,
                        TEMPLATE_DEFAULT);
                exit(EXIT_FAILURE);
        }

        return fd;
}

int mkp(int fd, char *fname, int flags)
{
        int fd2, mkp_create = flags & MKP_CREATE;

        if (!mkp_create && (fd2 = open(fname, O_WRONLY, S_IRUSR | S_IWUSR)) != -1) {
                fprintf(stderr, "\"%s\" already exists\n", fname);
                close(fd2);
                return -1;
        }

        if ((fd2 = open(fname, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1) {
                fprintf(stderr, "Failed to open \"%s\"\n", fname);
                return -1;
        }

        if (lseek(fd, (off_t)0, SEEK_SET) == -1) {
                perror("lseek");
                exit(EXIT_FAILURE);
        }

        if (__fcpy(fd2, fd) == -1) {
                fprintf(stderr, "Failed to copy \"%s\"\n", fname);
                close(fd2);
                return -1;
        }

        printf("Created \"%s\"\n", fname);
        close(fd2);
        return 0;
}

