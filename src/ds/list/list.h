
#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>

typedef struct list_node {
	void *data;
	struct list_node *next;
} list_node;

typedef struct list {
	size_t size;

	list_node *head;
} list;


typedef void (*list_node_free)(void *data); 

list* list_init(list *lst);
void list_free(list *lst, list_node_free free_node);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)

#endif
