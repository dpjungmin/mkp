#include "test.h"
#include "types.h"

struct routine r[] = {
        ROUTINE_INIT(test_list, "test_list"),
};

int main(int argc, char **argv)
{
        size_t i, n = sizeof(r) / sizeof(r[0]);

        for (i = 0; i < n; i++)
                pthread_create(&r[i].thread, NULL, r[i].sr, r[i].args);

        for (i = 0; i < n; i++)
                pthread_join(r[i].thread, NULL);

        return 0;
}
