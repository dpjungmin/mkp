#include "test.h"
#include "list.h"

void *test_list(void *args)
{
        DEFINE_LIST(l);

        CHECK(list_empty(&l));
        CHECK(list_len(&l) == (size_t)0);
        {
                list_push_back((void *)1, &l);
        }
        CHECK(list_back(&l) == (void *)1);
        CHECK(list_back(&l) == list_front(&l));
        {
                list_push_front((void *)2, &l);
        }
        CHECK(list_back(&l) == (void *)1);
        CHECK(list_front(&l) == (void *)2);
        CHECK(!list_empty(&l));
        CHECK(list_len(&l) == (size_t)2);
        {
                CHECK(list_pop_front(&l) == (void *)2);
        }
        CHECK(!list_empty(&l));
        CHECK(list_len(&l) == (size_t)1);
        CHECK(list_front(&l) == (void *)1);
        CHECK(list_back(&l) == (void *)1);
        {
                CHECK(list_pop_back(&l) == (void *)1);
        }
        CHECK(list_empty(&l));
        CHECK(list_len(&l) == (size_t)0);
        {
                list_push_back((void *)1, &l);
                list_push_back((void *)2, &l);
                list_push_back((void *)3, &l);
        }
        CHECK(!list_empty(&l));
        CHECK(list_len(&l) == (size_t)3);
        {
                list_clear(&l);
        }
        CHECK(list_empty(&l));
        CHECK(list_len(&l) == (size_t)0);

        return NULL;
}