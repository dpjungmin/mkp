#ifndef _TEST_H
#define _TEST_H

#include <stdio.h>
#include <pthread.h>

#define FAILED(msg) do {                                        \
        fputs(msg, stderr);                                     \
        pthread_exit(NULL);                                     \
} while(0)

#define EXPECT(exp, c) __builtin_expect((exp), (c))

#define CHECK(cond) do {                                        \
        if (EXPECT(!(cond), 0))                                 \
                FAILED((char *)args);                           \
} while(0)

#define TEST(_name) void *_name(void *args);

extern TEST(test_list);

#endif