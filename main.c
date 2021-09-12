#include <string.h>
#include <unistd.h>

#include "mkp.h"

int main(int argc, char **argv)
{
        char *template;
        int fd;

        if (argc == 2) {
                if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
                        usage(EXIT_FAILURE);
                if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)
                        version(EXIT_SUCCESS);
        }

        set_template(&template);
        fd = open_template(template);

        while (--argc)
                (void)mkp(fd, *++argv, MKP_DEFAULT);

        close(fd);
        return 0;
}
