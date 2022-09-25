/*
 * MaxHeap.h
 *
 *  Created on: Dec 10, 2021
 *      Author: ise
 */

#ifndef MAXHEAP_H_
#define MAXHEAP_H_
#include "Defs.h"


typedef struct t_MaxHeap *MaxHeap;
typedef enum{HEAP_IS_FULL,HEAP_BAD_ARGUMENT,HEAP_SUCCESS,HEAP_FAILURE}HeapResult;

MaxHeap CreateHeap(int max_size,char* name,equalFunction,copyFunction ,freeFunction,printFunction);
HeapResult insertToHeap(MaxHeap, element);
HeapResult destroyHeap(MaxHeap );
HeapResult printHeap(MaxHeap);
element PopMaxHeap(MaxHeap);
element TopMaxHeap(MaxHeap);
char* getHeapId(MaxHeap);
int getHeapCurrentSize(MaxHeap);

#endif /* MAXHEAP_H_ */
