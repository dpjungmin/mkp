#ifndef _MKP_H
#define _MKP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "util.h"

#define PROGRAM_NAME      "mkp"
#define VERSION           "0.0.1"
#define TEMPLATE_ENV      "MKP_TEMPLATE"
#define TEMPLATE_DEFAULT  "./template"

#define MAX_MSG_LENGTH    120
#define MAX_BUF_SIZE      1024

#define MKP_DEFAULT       0
#define MKP_CREATE        1

extern void usage(int status);
extern void version(int status);
extern void set_template(char **template);
extern int  open_template(const char *template);
extern int  mkp(int fd, char *fname, int flags);

#endif
