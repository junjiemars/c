#include <_algo_.h>


struct node_s {
	int val;
	struct node_s *next;
};

#define LIST_SIZE 5


static void show_linked_list(struct node_s*);
static struct node_s* reverse1(struct node_s*);
struct node_s* reverse2(struct node_s*, struct node_s*, struct node_s*);

int
main(void)
{
	struct node_s *lst = calloc(LIST_SIZE, sizeof(*lst));
	for (int i = 0; i < LIST_SIZE-1; i++) {
		lst[i].val = i+1;
		lst[i].next = &lst[i+1];
	}
	lst[LIST_SIZE-1].val = LIST_SIZE;
	lst[LIST_SIZE-1].next = 0;

	printf("reverse linked list\n----------\n");
	show_linked_list(lst);

	struct node_s *lst1 = reverse1(lst);
	show_linked_list(lst1);

	struct node_s *lst2 = reverse2(lst1, 0, lst1);
	show_linked_list(lst2);

	free(lst);

	return 0;
}


void
show_linked_list(struct node_s *head) {
	for (struct node_s *p = head; p; p = p->next) {
		printf("%02i @%p -> %p\n", p->val, p, p->next);
	}
	printf("----------\n");
}

struct node_s*
reverse1(struct node_s *head) {
	struct node_s *previous = 0;
	struct node_s *current = head;
	while (current->next) {
		struct node_s *next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	current->next = previous;
	return current;
}

struct node_s*
reverse2(struct node_s *head,
				 struct node_s *previous,
				 struct node_s *current) {
	if (!current->next) {
		current->next = previous;
		return current;
	}
	struct node_s *next = current->next;
	current->next = previous;
	return reverse2(head, current, next);
}
