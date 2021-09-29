#ifndef _MKP_H
#define _MKP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

#include "util.h"

#define PROGRAM_NAME      "mkp"
#define VERSION           "0.0.1"
#define TEMPLATE_ENV      "MKP_TEMPLATE"
#define TEMPLATE_DEFAULT  "template"

#define MAX_MSG_LENGTH    120
#define MAX_BUF_SIZE      1024

#define MKP_DEFAULT       0
#define MKP_CREATE        1

typedef struct args {
        int printflag;
        char *tfile;
} args_t;

#define ARGS_INIT                       \
        { .printflag = FALSE,           \
          .tfile = NULL, }

extern void usage(int status);
extern void version(int status);
extern void get_template(int *fd);
extern int  mkp(int fd, char *fname, int flags);

#endif
