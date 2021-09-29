#include "mkp.h"
#include "list.h"

int main(int argc, char **argv)
{
        int carg, fd, mkp_flags = MKP_DEFAULT;
        char *fname;
        DEFINE_LIST(list);
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
                        list_push_back((void *)argv[carg], &list);
                }
        }

        get_template(&fd);

        while ((fname = list_pop_front(&list)))
                (void)mkp(fd, fname, mkp_flags);

        close(fd);
        return 0;
}
