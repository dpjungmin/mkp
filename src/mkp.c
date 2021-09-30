#include "mkp.h"

args_t args = ARGS_INIT;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

static inline void __set_template(char **template)
{
        if (args.tfile) {
                *template = args.tfile;
                return;
        }

        if ((*template = getenv(TEMPLATE_ENV)) == NULL)
                *template = TEMPLATE_DEFAULT;
}

static inline void __open_template(int *fd, const char *template)
{
        if ((*fd = open(template, O_RDONLY)) == -1) {
                char msg[MAX_MSG_LENGTH + strlen(template) + 1];
                sprintf(msg,"Failed to open \"%s\"", template);
                perror(msg);
                fprintf(stderr,
                        "Set an environment variable \"%s\" that points to the template file, or create a file named \"%s\" in the current directory\n",
                        TEMPLATE_ENV,
                        TEMPLATE_DEFAULT);
                exit(EXIT_FAILURE);
        }
}

static inline int __fcpy(int to, int from)
{
        int n;
        char buf[MAX_BUF_SIZE];

        while ((n = read(from, buf, sizeof(buf))) > 0)
                if (write(to, buf, n) != n)
                        return -1;

        return 0;
}

static inline void __display(const char *fmt, ...)
{
        if (!args.printflag)
                return;

        va_list ap;

        va_start(ap, fmt);
        vfprintf(stdout, fmt, ap);
}

void usage(int status)
{
        printf("Usage: %s filename(s)\n", PROGRAM_NAME);
        printf("   or: %s [options]\n\n", PROGRAM_NAME);
        printf("     --help          display this help and exit\n");
        printf("     --version       output version information and exit\n");
        printf("     -t [filename]   set template file to [filename]\n");
        printf("     -p              enable printing logs\n");
        printf("     -o              rewrite an existing file\n");
        exit(status);
}

void version(int status)
{
        printf("%s version %s\n", PROGRAM_NAME, VERSION);
        exit(status);
}

void get_template(int *fd)
{
        char *template;

        __set_template(&template);
        __open_template(fd, template);
}

void *mkp(void *args)
{   
        struct mkp_args *ma = args;
        const int mkp_create = ma->flags & MKP_CREATE;
        int fd;

        if (!mkp_create && (fd = open(ma->fname, O_WRONLY, S_IRUSR | S_IWUSR)) != -1) {
                fprintf(stderr, "\"%s\" already exists\n", ma->fname);
                close(fd);
                pthread_exit(NULL);
        }

        if ((fd = open(ma->fname, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1) {
                fprintf(stderr, "Failed to open \"%s\"\n", ma->fname);
                pthread_exit(NULL);
        }

        pthread_mutex_lock(&m);
        {
                if (lseek(ma->fd, (off_t)0, SEEK_SET) == -1) {
                        perror("lseek");
                        pthread_mutex_unlock(&m);
                        exit(EXIT_FAILURE);
                }

                if (__fcpy(fd, ma->fd) == -1) {
                        fprintf(stderr, "Failed to copy \"%s\"\n", ma->fname);
                        close(fd);
                        pthread_mutex_unlock(&m);
                        pthread_exit(NULL);
                }
        }
        pthread_mutex_unlock(&m);

        __display("mkp: created \"%s\"\n", ma->fname);
        close(fd);
        free(ma);

        return NULL;
}

