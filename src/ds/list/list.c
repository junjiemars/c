#include <list.h>
#include <string.h>

list* 
list_new(list *alloc) {
	if (0 == alloc) return alloc;
	memset(alloc, 0, sizeof(list));

	return alloc;
}

void 
list_free(list *lst, list_node_free free_node) {
	if (0 == lst || 0 == free_node || list_empty(lst)) return;

	list_node *head = lst->head;

	while (head) {
		list_node *next = head->next;
		free_node(head);
		head = next;
	}
}

list_node*
list_append(list *lst, void *val, list_node_new new_node) {
	if (0 == lst || 0 == new_node) return 0;

	list_node *node = new_node(val);
	if (0 == node) return 0;

	if (list_empty(lst)) {
		lst->tail = lst->head = node;
	} else {
		lst->tail = lst->tail->next = node;
	}
	lst->size++;	

	return node;
}

list_node*
list_push(list *lst, void *val, list_node_new new_node) {
	if (0 == lst || 0 == new_node) return 0;

	list_node *node = new_node(val);
	if (0 == node) return 0;

	list_node **pp = &lst->head;
	list_node *head = lst->head;

	*pp = node;
	node->next = head;
	lst->size++;

	if (0 == head) {
		lst->tail = node;
	}

	return node;
}

list_node*
list_remove(list *lst, void *val, list_node_cmp test) {
	if (0 == lst || list_empty(lst) || 0 == test)	return 0;
	
	list_node **pp = &lst->head;
	list_node *node = lst->head;

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

list_node*
list_find(list *lst, void *val, list_node_cmp test) {
	if (0 == lst || 0 == test) return 0;

	list_node *node = lst->head;

	while (node) {
		if (0 == test(node->val, val)) {
			return node;
		}
		node = node->next;
	}
	
	return 0;
}

list_node*
list_insert(list* lst, list_node *after, void *val, list_node_new new_node) {
	if (0 == lst || 0 == after || 0 == new_node) return 0;

	list_node *node = new_node(val);
	if (0 == node) return 0;
	
	if (after->next) {
		node->next = after->next;
	}
	after->next = node;
	lst->size++;

	return node;		
}
