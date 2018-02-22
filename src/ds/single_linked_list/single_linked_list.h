#ifndef _SINGLE_LINKED_LIST_H_
#define _SINGLE_LINKED_LIST_H_

#include <stddef.h>

typedef struct node_s {
	void *val;
	struct node_s *next;
} node_s;


node_s* list_append(node_s *head,
                    void *val,
                    node_s* (*node_new)(void *val));

void list_free(node_s *head,
               void (*node_free)(node_s *node));

node_s* list_find(node_s *head,
                  const void *val,
                  int (*node_cmp)(const void *val1, const void* val2));

void list_delete(node_s **head,
                 const void *val,
                 int (*cmp)(const void *val1, const void* val2),
                 void (*free)(node_s *node));


#endif /* end of _SINGLE_LINKED_LIST_H_ */
