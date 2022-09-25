/*
 * LinkedList.h
 *
 *  Created on: Dec 10, 2021
 *      Author: ise
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "Defs.h"

typedef struct t_LinkedList *list;
typedef bool (*compareByKeyFucntion)(element,element);
typedef enum{LIST_IS_EMPTY,LIST_BAD_ARGUMENT,LIST_SUCCESS,LIST_FAILURE} ListResult;

list createLinkedList(copyFunction ,freeFunction ,compareFunction ,printFunction ,compareByKeyFucntion );
ListResult destroyList(list);
ListResult appendNode(list,element);
ListResult deleteNode(list,element);
ListResult displayList(list);
element searchByKeyInList(list,element); // take element of type pokemon name and extract from heap her type.

#endif /* LINKEDLIST_H_ */
