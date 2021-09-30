#include "mkp.h"
#include "list.h"

int main(int argc, char **argv)
{
        int carg;
        int fd;
        char *fname;
        pthread_t *thread;
        DEFINE_LIST(files);
        DEFINE_LIST(threads);
        int mkp_flags = MKP_DEFAULT;
        extern args_t args;

        if (argc == 2) {
                if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
                        usage(EXIT_FAILURE);
                if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)
                        version(EXIT_SUCCESS);
        }

        for (carg = 1; carg < argc; carg++) {
                if (argv[carg][0] == '-') {
                        switch (argv[carg][1]) {
                        case 'p':
                        case 'P':
                                args.printflag = TRUE;
                                break;
                        case 't':
                        case 'T':
                                args.tfile = argv[++carg];
                                break;
                        case 'o':
                        case 'O':
                                mkp_flags |= MKP_CREATE;
                                break;
                        default:
                                break;
                        }
                } else {
                        list_push_back((void *)argv[carg], &files);
                }
        }

        get_template(&fd);

        while ((fname = list_pop_front(&files))) {
                thread = malloc(sizeof(pthread_t));
                struct mkp_args *ma = malloc(sizeof(struct mkp_args));
                ma->fd = fd;
                ma->fname = fname;
                ma->flags = mkp_flags;
                pthread_create(thread, NULL, mkp, (void *)ma);
                list_push_back((void *)thread, &threads);
        }

        while ((thread = list_pop_front(&threads))) {
                pthread_join(*thread, NULL);
                free(thread);
        }

        close(fd);
        return 0;
}
