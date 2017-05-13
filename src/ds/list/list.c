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

list*
list_where(list *lst, list_node *node) {
	if (0 == lst || 0 == node) return lst;

	return 0;
}

list*
list_append(list *lst, void *val, list_node_new new_node) {
	if (0 == lst || 0 == new_node) return lst;

	list_node *node = new_node(val);
	if (0 == node) return lst;
	node->data = val;

	if (list_empty(lst)) {
		list_head(lst) = list_tail(lst) = node;	
	} else {
		list_tail(lst) = list_tail(lst)->next = node;
	}	
	lst->size++;	

	return lst;
}

list*
list_push(list *lst, void *val, list_node_new new_node) {
	if (0 == lst || 0 == new_node) return lst;

	list_node *node = new_node(val);
	if (0 == node) return lst;
	node->data = val;

	if (list_empty(lst)) {
		lst->head = lst->tail = node;
	} else {
		node->next = lst->head;
		lst->head = node;	
	}
	lst->size++;

	return lst;
}

list*
list_remove(list *lst, void *val, list_node_free free_node) {
	if (0 == lst || 0 == lst->head || 0 == free_node)	return lst;
	
	list_node **pp = &lst->head;
	list_node *node = lst->head;

	while (node) {
		list_node *del = 0;
		if (node->data == val) {
			*pp = node->next;
			del = node;
		}

		pp = &node->next;
		node = node->next;

		if (del) {	
			free_node(del);
			lst->size--;
			break;
		}
	}

	return lst;
}

list*
list_insert(list *lst, void *data, list_node *where) {
	_unused_(data);
	_unused_(where);
	if (0 == lst) return lst;

	return 0;		
	
}
