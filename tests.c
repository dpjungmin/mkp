#include "util.h"

void test1(void)
{
        CHECK(1, "test1");
}

void test2(void)
{
        CHECK(1, "test2");
}

int main(int argc, char **argv)
{
        test1();
        test2();

        printf("No problems found\n");
}
