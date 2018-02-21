#ifndef _SINGLE_LINKED_LIST_H_
#define _SINGLE_LINKED_LIST_H_

#include <stddef.h>

typedef struct {
	void *val;
	node_s *next;
} node_s;

typedef struct list {
	size_t size;
	node *head;
	node *tail;
} list;


typedef void (*node_free)(node *node); 
typedef node* (*node_new)(void *val);
typedef int (*node_cmp)(void *lhs, void *rhs);

list* list_new(list *alloc);
list* list_free(list *lst, node_free free_node);

node* list_append(list *lst, void *val, node_new new_node);
node* list_push(list *lst, void *val, node_new new_node);

node* list_remove_val(list *lst, void *val, node_cmp test); 
node* list_remove_next(list *lst, node *after);
node* list_remove_tail(list *lst, node **tail);

node* list_find(list *lst, void *val, node_cmp test);

node* list_insert(list *lst, node *after, void *val, node_new new_node);

#define list_empty(list) (0 == (list) || 0 == (list)->head)
#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)

#define _unused_(x) ((void)(x))

#endif /* end of _SINGLE_LINKED_LIST_H_ */
