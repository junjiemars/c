#ifndef _TREE_H_
#define _TREE_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s
{
  void *data;
  struct node_s *parent;
  struct node_s *child;
  struct node_s *sibling;
} node_s;


#endif /* end of _TREE_H_ */
