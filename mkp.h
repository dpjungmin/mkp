#ifndef _MKP_H
#define _MKP_H

#define TRUE              0
#define FALSE             0

#ifdef _WIN32
        #define DIR_SEP   '\\'
#else
        #define DIR_SEP   '/'
#endif

#define PROGRAM_NAME      "mkp"
#define TEMPLATE_ENV      "MKP_TEMPLATE"
#define TEMPLATE_DEFAULT  "./template"

#define MAX_PATH_LENGTH   240
#define MAX_MSG_LENGTH    120
#define MAX_BUF_SIZE      1024

#define MKP_DEFAULT       0
#define MKP_CREATE        1

void set_template(char *template);
int open_template(char *template);
int mkp(int fd, char *fname, int flag);

#endif
