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
		list_head(lst) = list_tail(lst) = node;	
	} else {
		list_tail(lst) = list_tail(lst)->next = node;
	}	
	lst->size++;	

	return node;
}

list_node*
list_push(list *lst, void *val, list_node_new new_node) {
	if (0 == lst || 0 == new_node) return 0;

	list_node *node = new_node(val);
	if (0 == node) return 0;

	if (list_empty(lst)) {
		lst->head = lst->tail = node;
	} else {
		node->next = lst->head;
		lst->head = node;	
	}
	lst->size++;

	return node;
}

list*
list_remove(list *lst, void *val, list_node_comp test, list_node_free free_node) {
	if (0 == lst || 0 == lst->head || 0 == test || 0 == free_node)	return lst;
	
	list_node **pp = &lst->head;
	list_node *node = lst->head;

	while (node) {
		list_node *del = 0;
		if (0 == test(node->val, val)) {
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

list_node*
list_find(list *lst, void *val, list_node_comp test) {
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
