/*
 * Defs.h
 *
 *  Created on: Dec 10, 2021
 *      Author: ise
 */

#ifndef DEFS_H_
#define DEFS_H_

typedef enum e_bool { true ,false } bool;
typedef enum e_status { success, failure,memoryProblem} status;

typedef void * element;
typedef element(*copyFunction) (element);
typedef status(*freeFunction) (element);
typedef status(*printFunction) (element);
typedef bool(*compareFunction)(element,element);
typedef int(*equalFunction) (element, element);//1 first bigger, 0 - same, -1 second bigger // check pokemons with same type
typedef char*(*getCategoryFunction)(element);
typedef int(*getAttackFunction)(element firstElem ,element secondElem ,int*
attackFirst,int* attackSecond); // return the first attack - second attack . also produce the attack of each element, The function transmits the information
//through the pointers received in the function.
//this function gets the types and attack of two pokemons . it will correct the attack by
//weakness or strongest against each other if needed by 10 and then return the sub between them.
#endif /* DEFS_H_ */
