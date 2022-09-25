/*
 * LinkedList.c
 *
 *  Created on: Dec 10, 2021
 *      Author: ise
 */

#include "LinkedList.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct t_node{
	element data;
	struct t_node* next;

}Node;

struct t_LinkedList{
	copyFunction copyFunc;
	freeFunction freeFunc;
	compareFunction compareFunc;
	printFunction printFunc;
	compareByKeyFucntion byKeyFunc;
	Node* head;
	Node* tail;
};

list createLinkedList(copyFunction copyElement,freeFunction freeElement,compareFunction compareElements,printFunction printElement,compareByKeyFucntion byKeyElement){
	list new = (list)malloc(sizeof(struct t_LinkedList));
	if(new == NULL) return NULL;
	new->copyFunc = copyElement;
	new->freeFunc = freeElement;
	new->compareFunc = compareElements;
	new->printFunc = printElement;
	new->byKeyFunc = byKeyElement;
	new->head = NULL;
	new->tail = NULL;
	return new;
}

ListResult appendNode(list l_list,element new){
	if(new == NULL) return LIST_FAILURE;
	element newElement = l_list->copyFunc(new);

	if(l_list->head == NULL) // empty list
	{
		l_list->head = malloc(sizeof(Node));
		if(l_list->head == NULL) return LIST_FAILURE;

		l_list->head->data = newElement;
		l_list->head->next = NULL;
		l_list->tail = l_list->head;
		return LIST_SUCCESS;
	}
	// if the list is not empty, add to the end.
	l_list->tail->next = malloc(sizeof(Node));
	if(l_list->tail->next == NULL) return LIST_FAILURE;

	l_list->tail = l_list->tail->next;
	l_list->tail->data = newElement;
	l_list->tail->next = NULL;
	return LIST_SUCCESS;
}

ListResult deleteNode(list l_list,element e){
	if(l_list->head) return LIST_IS_EMPTY;
	if(e == NULL) return LIST_BAD_ARGUMENT;
	Node* curr = l_list->head;

	if(l_list->compareFunc(curr->data,e)) // equal to first node.
	{
		l_list->freeFunc(curr->data);
		free(curr);
		l_list->head = NULL;
		return LIST_SUCCESS;
	}
	curr = curr->next;
	Node* prev = l_list->head;
	while(curr != NULL){

		if(l_list->compareFunc(curr->data,e)) // check if equal
		{
			l_list->freeFunc(curr->data);
			prev->next = curr->next;
			free(curr);
			return LIST_SUCCESS;

		}
		prev = curr;
		curr = curr->next;
	}
	return LIST_FAILURE;

}

ListResult destroyList(list l_list){
	if(l_list == NULL) return LIST_BAD_ARGUMENT;

	if(l_list->head == NULL) // initialized empty list
	{
		free(l_list);
		return LIST_SUCCESS;
	}
	Node* curr = l_list->head;
	Node* prev = l_list->head;

	while(curr != NULL){
		l_list->freeFunc(curr->data); // free element
		curr = curr->next;
		free(prev); // free node
		prev = curr;
	}
	free(l_list); // free list
	return LIST_SUCCESS;


}

ListResult displayList(list l_list){
	if(l_list == NULL) return LIST_BAD_ARGUMENT;

	if(l_list->head == NULL) return LIST_IS_EMPTY;

	Node* curr = l_list->head;
	while(curr != NULL){
		l_list->printFunc(curr->data);
		curr = curr->next;
	}
	return LIST_SUCCESS;
}

element searchByKeyInList(list l_list,element key)
{
	if(key == NULL || l_list == NULL) return NULL;

	Node* curr = l_list->head;
	while(curr != NULL){
		if(!(l_list->byKeyFunc(curr->data,key))) return curr->data;
		curr = curr->next;
	}
	return NULL;
}













