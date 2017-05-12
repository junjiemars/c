#include <list.h>

list* list_init(list* lst) {
	if (0 == lst) return 0;

	lst->size = 0;
	lst->head = 0;	

	return lst;
}

void list_free(list *lst, list_node_free free_node) {
	if (0 == lst || 0 == list_head(lst) || 0 == free_node) return;

	list_node **head = &list_head(lst);

	while (head) {
		free_node((*head)->data);			
		head = &(*head)->next;
	}
}

