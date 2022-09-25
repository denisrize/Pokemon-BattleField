/*
 * BattleByCategory.c
 *
 *  Created on: Dec 11, 2021
 *      Author: ise
 */
#include "BattleByCategory.h"
#include "MaxHeap.h"
#include "LinkedList.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>


element list_cpy(element e){
	if(e == NULL) return NULL;
	return (MaxHeap)(e);

}
status list_free(element e){
	if(e == NULL) return failure;
	destroyHeap((MaxHeap)e);
	return success;

}
bool list_compare_by_key(element e,element key){
	if( key == NULL || e == NULL) return false;
	MaxHeap h = (MaxHeap)e;
	char* cat = (char*)key;
	return (bool)(strcmp(getHeapId(h),cat));
}
status list_print(element e){
	if(e == NULL) return failure;
	MaxHeap h = (MaxHeap)e;
	printHeap(h);
	return success;
}

struct battle_s{
	list l_list;
	char** cat_names;
	int numberOfCategories;
	getCategoryFunction getCatFunc;
	getAttackFunction getAttackFunc;
	printFunction printFunc;

};


Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement)
{
	Battle new = (Battle)malloc(sizeof(struct battle_s));
	new->getAttackFunc = getAttack;
	new->getCatFunc = getCategory;
	new->printFunc = printElement;
	new->numberOfCategories = numberOfCategories;
	new->l_list = NULL;
	new->cat_names = NULL;

	if(!numberOfCategories) return new;// no categories.

	if((new->l_list = createLinkedList(list_cpy ,list_free ,list_compare_by_key ,list_print ,list_compare_by_key )) == NULL)
	{
		free(new);
		return NULL;
	}
	new->cat_names = (char**)malloc(sizeof(char*)*numberOfCategories);
	char delim[] = ",";
	char *cat = strtok(categories, delim);
	int i;
	for(i=0;i<numberOfCategories;i++){
		if((appendNode(new->l_list,CreateHeap( capacity,cat,equalElement,copyElement ,freeElement,printElement))) == LIST_FAILURE){
			int j=0;
			while(j != i){
				free(new->cat_names[j]);
				new->cat_names[j] = NULL;
				j++;
			}
			destroyBattleByCategory(new);
			return NULL;
		}
		new->cat_names[i] = (char*)malloc(sizeof(strlen(cat)+1));
		strcpy(new->cat_names[i],cat);
		cat = strtok(NULL, delim);
	}
	return new;
}

status destroyBattleByCategory(Battle b)
{
	if( b == NULL) return failure;
	if( !b->numberOfCategories)
	{
		free(b);
		return success;
	}
	destroyList(b->l_list);
	int i;
	for(i=0;i<b->numberOfCategories;i++){
		if(b->cat_names[i] != NULL) free(b->cat_names[i]);
	}
	free(b->cat_names);
	free(b);
	return success;
}

status insertObject(Battle b, element e)
{
	char* cat = b->getCatFunc(e);
	MaxHeap h = (MaxHeap)searchByKeyInList(b->l_list,cat);
	if(h == NULL) return failure;

	HeapResult res = insertToHeap(h,e);
	if(res == HEAP_IS_FULL) return failure;
	if(res == HEAP_FAILURE) return memoryProblem;
	return success;

}

void displayObjectsByCategories(Battle b)
{
	displayList(b->l_list);
}

element removeMaxByCategory(Battle b,char* category)
{
	if(b == NULL) return NULL;
	MaxHeap h = searchByKeyInList(b->l_list,category);
	if( h == NULL) return NULL;
	return PopMaxHeap(h);

}

int getNumberOfObjectsInCategory(Battle b,char* category)
{
	MaxHeap h = searchByKeyInList(b->l_list,category);
	if(h == NULL) return -1;
	return getHeapCurrentSize(h);
}

element fight(Battle b,element e)
{
	if( b == NULL || e == NULL) return NULL;
	MaxHeap h;
	element currElement = NULL,bestForFight = NULL;
	int firstAttack ;
	int secondAttack;
	int result,i;
	for(i=0;i<b->numberOfCategories;i++) // search the element that is best for this fight in the list.
	{
		h = (MaxHeap)searchByKeyInList(b->l_list,b->cat_names[i]);
		currElement = TopMaxHeap(h);
		if(currElement == NULL) continue;

		if(bestForFight == NULL)
		{
			result = b->getAttackFunc(currElement,e,&firstAttack,&secondAttack);
			bestForFight = currElement;
			continue;
		}

		if(b->getAttackFunc(currElement,e,&firstAttack,&secondAttack) > result)
		{
			bestForFight = currElement;
			result = firstAttack - secondAttack;
		}

	}

	if(bestForFight == NULL) return NULL;
	b->getAttackFunc(bestForFight,e,&firstAttack,&secondAttack); // update attacks values
	printf("The final battle between:\n");
	b->printFunc(e);
	printf("In this battle his attack is :%d\n\n",secondAttack);
	printf("against ");
	b->printFunc(bestForFight);
	printf("In this battle his attack is :%d\n\n",firstAttack);
	if(result > 0)
	{
		printf("THE WINNER IS:\n");
		b->printFunc(bestForFight);
		return bestForFight;
	}
	if(result < 0)
	{
		printf("THE WINNER IS:\n");
		b->printFunc(e);
		return e;
	}

	printf("IT IS A DRAW.\n");
	return bestForFight;


}









