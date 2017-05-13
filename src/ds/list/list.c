#include <list.h>
#include <stdio.h>

list* 
list_new(list* lst) {
	if (0 == lst) return lst;

	lst->size = 0;
	lst->head = 0;	
	lst->tail = 0;

	return lst;
}

void 
list_free(list *lst, list_node_free free_node) {
	if (0 == lst || 0 == free_node || list_empty(lst)) return;

	list_node *head = lst->head;
	_unused_(head);

	while (head) {
		printf("%s\n", (char*)head->data);
		head = head->next;
	}

}

list*
list_where(list *lst, list_node *node) {
	if (0 == lst || 0 == node) return lst;

	return 0;
}

list*
list_append(list *lst, list_node_new new_node, void *data) {
	if (0 == lst || 0 == new_node) return lst;

	//list_node **tail = &list_tail(lst);
	list_node *node = new_node(data);
	if (0 == node) return lst;
	node->data = data;

	if (list_empty(lst)) {
		list_head(lst) = list_tail(lst) = node;	
	} else {
		list_tail(lst) = list_tail(lst)->next = node;
	}	
	lst->size++;	

	return lst;
}

list*
list_insert(list *lst, void *data, list_node *where) {
	_unused_(data);
	_unused_(where);
	if (0 == lst) return lst;

	return 0;		
	
}
