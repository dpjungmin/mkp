#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <stdlib.h>

#define TEST_FAILURE(msg) do { \
        fprintf(stderr, "%s\n", msg); \
        abort(); \
} while(0)

#define EXPECT(exp, c) __builtin_expect((exp), (c))

#define CHECK(cond, msg) do { \
        if (EXPECT(!(cond), 0)) { \
                TEST_FAILURE(msg); \
        } \
} while(0)

#endif
