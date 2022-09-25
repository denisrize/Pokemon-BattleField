/*
 * MaxHeap.c
 *
 *  Created on: Dec 10, 2021
 *      Author: ise
 */

#include "MaxHeap.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>


struct t_MaxHeap{
	char* name;
	int max_size;
	int size;
	element* e_arr;
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction printFunc;
	equalFunction equalFunc;
};

MaxHeap CreateHeap(int max_size,char* name,equalFunction equalFunc,copyFunction cpyFunc,freeFunction freeFunc,printFunction printFunc){
	MaxHeap new = (MaxHeap)malloc(sizeof(struct t_MaxHeap));
	if(new == NULL) return NULL;
	new->size = 0;
	new->max_size = max_size;
	new->e_arr = NULL;

	new->name = malloc(strlen(name)+1);
	if(new->name == NULL){
		free(new);
		return NULL;
	}
	strcpy(new->name,name);

	new->copyFunc = cpyFunc;
	new->freeFunc = freeFunc;
	new->equalFunc = equalFunc;
	new->printFunc = printFunc;
	return new;
}

HeapResult destroyHeap(MaxHeap m_heap){
	if(m_heap == NULL) return HEAP_BAD_ARGUMENT;

	free(m_heap->name);
	int size = m_heap->size;
	while(size){
		m_heap->freeFunc(m_heap->e_arr[size-1]);
		size--;
	}
	if(m_heap->size)free(m_heap->e_arr);
	free(m_heap);
	return HEAP_SUCCESS;
}

HeapResult insertToHeap(MaxHeap m_heap, element new){
	if(new == NULL || m_heap == NULL) return HEAP_BAD_ARGUMENT;

	element newElement = m_heap->copyFunc(new);
	if(newElement == NULL) return HEAP_FAILURE;

	m_heap->size++;
	if( m_heap->size > m_heap->max_size) return HEAP_IS_FULL;
	m_heap->e_arr = (element*)realloc(m_heap->e_arr,sizeof(element)*m_heap->size);
	if ( m_heap->e_arr == NULL){
	free(m_heap->name);
	free(m_heap);
	free(newElement);
	return HEAP_FAILURE;
	}
	m_heap->e_arr[m_heap->size-1] = newElement;

	int child = m_heap->size-1;
	int parent = (child/2) - 1 ;
	if(child % 2 ) parent = child/2;
	element temp;
	while(child && m_heap->equalFunc(m_heap->e_arr[child],m_heap->e_arr[parent]) == 1)// while element isn't max and element bigger then is parent switch between them.
	{
		temp = m_heap->e_arr[parent];
		m_heap->e_arr[parent] = m_heap->e_arr[child];
		m_heap->e_arr[child] = temp;

		child = parent;
		if(child % 2 ) parent =  child/2;
		else parent = (child/2) - 1 ;

	}
	return HEAP_SUCCESS;

}

element PopMaxHeap(MaxHeap m_heap)
{
	if(m_heap == NULL || !m_heap->size) return NULL;
	element max = m_heap->e_arr[0];
	m_heap->e_arr[0] = m_heap->e_arr[m_heap->size-1];
	m_heap->size--;
	m_heap->e_arr = (element*)realloc(m_heap->e_arr,sizeof(element)*(m_heap->size));

	if(m_heap->size && m_heap->e_arr == NULL) {
	free(max);
	free(m_heap->name);
	free(m_heap);
	return NULL;
	}
	if(!(m_heap->size)) return max; //no elements left in the heap.

	int i = 0;
	int left =1;
	int right = 2;
	element temp;
	while(1) // max heapify.
	{
		int largest = i;

		if(left < m_heap->size &&  m_heap->equalFunc(m_heap->e_arr[left], m_heap->e_arr[i]) == 1) largest = left;

		if(right < m_heap->size && m_heap->equalFunc(m_heap->e_arr[right],m_heap->e_arr[largest]) == 1) largest = right;
		if(largest == i) break;
		temp = m_heap->e_arr[largest];
		m_heap->e_arr[largest] = m_heap->e_arr[i];
		m_heap->e_arr[i] = temp;

		i = largest;
		left = i*2;
		right = i*2+1;

	}
	return max; // don't free the element, no need to return copy.

}

element TopMaxHeap(MaxHeap m_heap){
	if(m_heap == NULL || !m_heap->size) return NULL;

	element max = m_heap->copyFunc(m_heap->e_arr[0]);
	if(max == NULL) return NULL;
	return max;

}

char* getHeapId(MaxHeap m_heap){
	return m_heap->name;
}

int getHeapCurrentSize(MaxHeap m_heap){
	return m_heap->size;
}

HeapResult printHeap(MaxHeap m_heap){
	if(m_heap == NULL) return HEAP_BAD_ARGUMENT;
	printf("%s:\n", m_heap->name);
	if(!m_heap->size){
		printf("No elements.\n\n");
		return HEAP_SUCCESS;
	}

	element temp[m_heap->size];
	int size = m_heap->size;
	int i;
	for(i=0;i<size;i++){
		temp[i] = PopMaxHeap(m_heap);
		printf("%d. ",i+1);
		m_heap->printFunc(temp[i]);
	}
	for(i=0;i<size;i++){
		insertToHeap(m_heap,temp[i]);
	}
	return HEAP_SUCCESS;
}









