#include "intrusive_list.h"
#include <stddef.h>

void init_list(intrusive_list* l) {
	if (!l) return;

    l->head.next = &l->head;
    l->head.prev = &l->head;
}

void add_node(intrusive_node* after, intrusive_node* node){
	if (!after || !node) return;

	node->prev = after;
    node->next = after->next;
    
    node->prev->next = node;
    node->next->prev = node;
}

void remove_node(intrusive_node* node){
	if (!node || node->next == node->prev) return;

	(node->prev)->next = node->next;
	(node->next)->prev = node->prev;
}

int get_length(const intrusive_list* l){
	if (!l) return 0;

	int cnt = 0;
	intrusive_node* cur = l->head.next;
	while (cur != &l->head){
		cnt++;
		cur = cur->next;

		if (cnt >= 1000) break;
	}
	return cnt;
}
