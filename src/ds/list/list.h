
#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>

typedef struct list_node {
	void *val;
	struct list_node *next;
} list_node;

typedef struct list {
	size_t size;
	list_node *head;
	list_node *tail;
} list;


typedef void (*list_node_free)(list_node *node); 
typedef list_node* (*list_node_new)(void *val);
typedef int (*list_node_cmp)(void *lhs, void *rhs);

list* list_new(list *alloc);
list* list_free(list *lst, list_node_free free_node);

list_node* list_append(list *lst, void *val, list_node_new new_node);
list_node* list_push(list *lst, void *val, list_node_new new_node);

list_node* list_remove(list *lst, void *val, list_node_cmp test); 
list_node* list_remove_next(list *lst, list_node *after);

list_node* list_find(list *lst, void *val, list_node_cmp test);

list_node* list_insert(list *lst, 
	list_node *after, 
	void *val, 
	list_node_new new_node);

#define list_empty(list) (0 == (list)->head)
#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)

#define _unused_(x) ((void)(x))

#endif
