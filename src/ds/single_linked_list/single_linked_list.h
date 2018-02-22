#ifndef _SINGLE_LINKED_LIST_H_
#define _SINGLE_LINKED_LIST_H_

#include <stddef.h>

typedef struct node_s {
	const void *val;
	struct node_s *next;
} node_s;


node_s* list_append(node_s *head,
                    const void *val,
                    node_s* (*node_new)(const void *val));

void list_free(node_s *head,
               void (*node_free)(node_s *node));

#endif /* end of _SINGLE_LINKED_LIST_H_ */
