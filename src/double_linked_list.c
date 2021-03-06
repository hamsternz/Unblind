#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#include "double_linked_list.h"
#include "unblind.h"
d_linked_list_t *linked_list_d_create() {
	d_linked_list_t *new = (d_linked_list_t *)malloc(sizeof(d_linked_list_t));
	new->head = NULL;
	new->tail = NULL;
	new->curr = 0;
	return new;
}

void linked_list_d_add(d_linked_list_t *dll, void *value, int x, int y) {
	dll_node_t *new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
	new_node->value = value;
	new_node->x = x;
	new_node->y = y;

	if(dll->head == NULL) {
		new_node->next = NULL;
		new_node->prev = NULL;
		dll->head = new_node;
		dll->tail = new_node;
		return;
	}
	dll_node_t *curr = dll->head;
	while(curr) {
		if(curr->next == NULL) {
			dll->tail = new_node;
			curr->next = new_node;
			new_node->prev = curr;
			new_node->next = NULL;
			return;
		}
		curr = curr->next;
	}
}

dll_node_t *linked_list_d_pop(d_linked_list_t *dll) {
	if(dll->head != NULL) {
		print_to_log("head isn't null");
		// dll_node_t n = *dll->tail;
		dll->tail = dll->tail->prev;
		if(dll->tail == NULL) {
			print_to_log("setting head to null");
			dll->head = NULL;
		} else {
			dll->tail->next = NULL;
		}
		print_to_log("old tail gone");

		// n->prev = NULL;
		return NULL;
	}
	return NULL;
}

dll_node_t *linked_list_d_get(d_linked_list_t *dll, int i) {
	if(dll->head == NULL) {
		return NULL;
	}
	dll_node_t *tmp = dll->head;
	for(int j = 0; j < i; j++) {
		tmp = tmp->next;
		if(tmp == NULL) {
			return NULL;
		}
	}
	dll->curr++;
	return tmp;
}

void setup_unblind_ur_manager(undo_redo_manager_t *ur_manager) {
	ur_manager->stack_u = linked_list_d_create();
	ur_manager->stack_r = linked_list_d_create();
}
