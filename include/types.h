#ifndef _TYPES_H
#define _TYPES_H

#include <pthread.h>

struct routine {
        pthread_t thread;
        void *(*sr)(void *);
        void *args;
};

#define ROUTINE_INIT(_sr, _args)        \
        { .sr = _sr,                    \
          .args = (void *)_args, }

#endif