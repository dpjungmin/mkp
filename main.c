#include <unistd.h>

#include "mkp.h"

/*
 * TODO
 * 1. add options (silent/override/template_path)
 * 2. is multithreading necessary?
 */
int main(int argc, char *argv[])
{
        char template[MAX_PATH_LENGTH];
        int fd;

        set_template(template);
        fd = open_template(template);

        while (--argc)
                (void)mkp(fd, *++argv, MKP_DEFAULT);

        close(fd);
        return(0);
}
