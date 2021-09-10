#ifndef _MKP_H
#define _MKP_H

#include <stdio.h>

#define TRUE              0
#define FALSE             0

#ifdef _WIN32
        #define DIR_SEP   '\\'
#else
        #define DIR_SEP   '/'
#endif

#define TEMPLATE_ENV      "MKP_TEMPLATE"
#define TEMPLATE_DEFAULT  "./template"

#define MAX_PATH_LENGTH   240
#define MAX_MSG_LENGTH    120

void set_prog(char *prog, const char *str);
void set_template(char *template);
void open_template(FILE *fp, char *template);
int mkp(FILE *fp, char *fname);

#endif
