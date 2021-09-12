#ifndef _MKP_H
#define _MKP_H

#include <stdio.h>
#include <stdlib.h>

#define TRUE              0
#define FALSE             0

#ifdef _WIN32
        #define DIR_SEP   '\\'
#else
        #define DIR_SEP   '/'
#endif

#define PROGRAM_NAME      "mkp"
#define VERSION           "0.0.1"
#define TEMPLATE_ENV      "MKP_TEMPLATE"
#define TEMPLATE_DEFAULT  "./template"

#define MAX_MSG_LENGTH    120
#define MAX_BUF_SIZE      1024

#define MKP_DEFAULT       0
#define MKP_CREATE        1

void usage(int status);
void version(int status);
void set_template(char **template);
int open_template(const char *template);
int mkp(int fd, char *fname, int flags);

#endif
