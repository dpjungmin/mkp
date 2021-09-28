#ifndef _LIST_H
#define _LIST_H

#include <stddef.h>
#include <stdlib.h>

/* 
 * Circular doubly linked list implemenation.
 */

struct list_node {
        void *obj;
        struct list_node *prev;
        struct list_node *next;
};

struct list {
        size_t size;
        struct list_node anchor;
};

#define LIST_INIT(_name)                        \
        { .size = 0,                            \
          .anchor.obj = NULL,                   \
          .anchor.next = &_name.anchor,         \
          .anchor.prev = &_name.anchor, }

#define DEFINE_LIST(_name)                      \
        struct list _name = LIST_INIT(_name)

extern size_t           list_len(struct list *l);
extern int              list_empty(struct list *l);
extern void             list_push_back(void *obj, struct list *l);
extern void             list_push_front(void *obj, struct list *l);
extern void             *list_back(struct list *l);
extern void             *list_front(struct list *l);
extern void             *list_pop_back(struct list *l);
extern void             *list_pop_front(struct list *l);
extern void             list_erase(struct list_node *n, struct list *l);
extern void             list_clear(struct list *l);
extern struct list_node *list_first(struct list *l);
extern struct list_node *list_last(struct list *l);
extern struct list_node *list_next(struct list_node *n, struct list *l);
extern struct list_node *list_prev(struct list_node *n, struct list *l);

#endif
