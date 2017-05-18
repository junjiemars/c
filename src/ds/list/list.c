#include <list.h>
#include <string.h>

list* 
list_new(list *alloc) {
	if (0 == alloc) return alloc;
	memset(alloc, 0, sizeof(list));

	return alloc;
}

list* 
list_free(list *lst, node_free free_node) {
	if (0 == lst || 0 == free_node || list_empty(lst)) return lst;

	node *head = lst->head;

	while (head) {
		node *next = head->next;
		free_node(head);

		lst->size--;
		head = next;
	}

	return lst;
}

node*
list_append(list *lst, void *val, node_new new_node) {
	if (0 == lst || 0 == new_node) return 0;

	node *node = new_node(val);
	if (0 == node) return 0;

	if (list_empty(lst)) {
		lst->tail = lst->head = node;
	} else {
		lst->tail = lst->tail->next = node;
	}
	lst->size++;	

	return node;
}

node*
list_push(list *lst, void *val, node_new new_node) {
	if (0 == lst || 0 == new_node) return 0;

	node *n = new_node(val);
	if (0 == n) return 0;

	node **pp = &lst->head;
	node *head = lst->head;

	*pp = n;
	n->next = head;
	lst->size++;

	if (0 == head) {
		lst->tail = n;
	}

	return n;
}

node*
list_remove_val(list *lst, void *val, node_cmp test) {
	if (0 == lst || list_empty(lst) || 0 == test)	return 0;
	
	node **pp = &lst->head;
	node *node = lst->head;

	while (node) {
		if (0 == test(node->val, val)) {
			*pp = node->next;
			lst->size--;
			return node;
		}

		pp = &node->next;
		node = node->next;
	}

	return 0;
}

node*
list_remove_next(list *lst, node *after) {
	if (0 == lst || 0 == after || 0 == after->next) return 0;

	node *remove = after->next;
	if (lst->tail == remove) {
		lst->tail = after;
	}
	after->next = after->next->next;	
	lst->size--;
		
	return remove;
}

node*
list_find(list *lst, void *val, node_cmp test) {
	if (0 == lst || 0 == test) return 0;

	node *node = lst->head;

	while (node) {
		if (0 == test(node->val, val)) {
			return node;
		}
		node = node->next;
	}
	
	return 0;
}

node*
list_insert(list* lst, node *after, void *val, node_new new_node) {
	if (0 == lst || 0 == new_node) return 0;

	if (0 == after || after == lst->tail) {
		return list_append(lst, val, new_node);
	}

	node *n = new_node(val);
	if (0 == n) return 0;
	
	node **pp = &after->next;
	n->next = *pp;
	*pp = n;

	lst->size++;

	return n;		
}
