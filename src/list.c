#include "list.h"

/*
 * Create a new list node that points to an object.
 */
static inline struct list_node *__list_create_node(void *obj)
{
        struct list_node *new = malloc(sizeof(struct list_node));
        new->obj = obj;

        return new;
}

/*
 * Add a new list node between prev/next.
 */
static inline void __list_add(struct list_node *new,
                              struct list_node *prev,
                              struct list_node *next)
{
        next->prev = new;
        new->next = next;
        new->prev = prev;
        prev->next = new;
}

/*
 * Delete a list node by connecting prev/next.
 */
static inline void __list_del(struct list_node *prev,
                              struct list_node *next)
{
        next->prev = prev;
        prev->next = next;
}

size_t list_len(struct list *l)
{
        return l->size;
}

int list_empty(struct list *l)
{
        return l->size <= 0;
}

void list_push_back(void *obj, struct list *l)
{
        struct list_node *new = __list_create_node(obj);
        __list_add(new, l->anchor.prev, &l->anchor);
        l->size++;
}

void list_push_front(void *obj, struct list *l)
{
        struct list_node *new = __list_create_node(obj);
        __list_add(new, &l->anchor, l->anchor.next);
        l->size++;
}

void *list_back(struct list *l)
{
        struct list_node *node = list_last(l);

        if (!node)
                return NULL;

        return node->obj;
}

void *list_front(struct list *l)
{
        struct list_node *node = list_first(l);

        if (!node)
                return NULL;

        return node->obj;
}

void *list_pop_back(struct list *l)
{
        struct list_node *node = list_last(l);
        void *obj = NULL;

        if (!node)
                return NULL;

        obj = node->obj;
        list_erase(node, l);

        return obj;
}

void *list_pop_front(struct list *l)
{
        struct list_node *node = list_first(l);
        void *obj;

        if (!node)
                return NULL;

        obj = node->obj;
        list_erase(node, l);

        return obj;
}

void list_erase(struct list_node *n, struct list *l)
{
        __list_del(n->prev, n->next);
        free(n);
        l->size--;
}

void list_clear(struct list *l)
{
        struct list_node *node = NULL;
        struct list_node *prev = NULL;

        for (node = list_first(l);
             node;
             node = list_next(prev, l)) {
                __list_del(node->prev, node->next);
                prev = node->prev;
                free(node);
        }

        l->size = 0;
}

struct list_node *list_first(struct list *l)
{
        if (l->anchor.next == &l->anchor)
                return NULL;

        return l->anchor.next;
}

struct list_node *list_last(struct list *l)
{
        if (l->anchor.prev == &l->anchor)
                return NULL;

        return l->anchor.prev;
}

struct list_node *list_next(struct list_node *n, struct list *l)
{
        if (n->next == &l->anchor)
                return NULL;

        return n->next;
}

struct list_node *list_prev(struct list_node *n, struct list *l)
{
        if (n->prev == &l->anchor)
                return NULL;

        return n->prev;
}
