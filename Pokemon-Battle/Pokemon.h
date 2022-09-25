/*
 * Pokemon.h
 *
 *  Created on: Nov 20, 2021
 *      Author: ise
 */
#include <stdio.h>
#include "Defs.h"


#ifndef POKEMON_H_
#define POKEMON_H_

typedef struct Pokemon_t{
	char* typeName;
	int num_pokemons;
	int num_against_me;
	int num_against_others;
	struct Pokemon_t** effective_against_me ; // array of pointers
	struct Pokemon_t** effective_against_others ;// array of pointers

}pokemon_type;

typedef struct pokemon_b{
	float height;
	float weight;
	int attack;
}pokemon_bio;

typedef struct final_pokemon{
	char* name ;
	char* specie ;
	pokemon_type* type;
	pokemon_bio* my_bio;
}pokemon;

typedef struct Pokemon_t *PokemonType;
typedef struct final_pokemon *Pokemon;
typedef struct  pokemon_b *PokemonBio;

// function declarations


/*init_pokemon: initialize struct of pokemon that was only declared in main .
 * 				arguments:  all arguments are passed by pointers.
 * 							pokemon* - points to the uninitialize struct of pokemon declared in main module.
 * 							char * - points to a name and species that we got in main.
 * 							pokemon_bio* - points to  bio struct that declared and initialize in main.
 * 							pokemon_type* - points to type struct that was declared and initialize in main.
 * 				return: if species/name wasn't allocated right then return value is failure,else success.
		*/
status init_pokemon(Pokemon,char* ,char* ,PokemonBio,pokemon_type * );

/*init_type: initialize struct of pokemon_type by pointer that was only declared in main.
 *  All integers initialize to 0 and pointers to null except the name that we get from main.
 *  		arguments:pokemon_type* - points to the uninitialize struct of pokemon_type declared in main module.
 *  					char* - points to the name of type we got in the main module.
 *  					return: if name wasn't allocated right then return value is failure,else success.
 *  */

status init_type(PokemonType,char* );

/*init_bio: initialize a sturct of pokemon bio that was declared uninitialized in main by pointer. The values of struct it gets are by values(height,weight,attack).
 * 	  		return: the function return is void because i didn't allocated memory for pokemon_bio( no need for dynamic memory ),
 * 	  		so there is no need for status back from the function it will be always success.
 *  */
void init_bio(PokemonBio ,float ,float ,int );

/* add_against_me,add_against_others(by pointer): add struct of pokemon type to other pokemon type effective_against_me/others list by increasing allocated memory
 * for the list by one size of pointer to pokemon type.The function also increasing the value of num_against_me/others by one.
 * 							arguments: two pointers to a of pokemon type struct.
 * 							return: if effective_against_me/others list wasn't allocated right then return value is failure,else success.
 * */
status add_against_me(PokemonType,PokemonType );

status add_against_others(PokemonType,PokemonType );

/*remove_against_me,remove_against_others(by pointer): The functions first at all finds in effective_against_me/other list of the first pokemon type
 *  the index of the second pokemon type we want to remove from there. Then before it allocate less memory for the list it moves every type pokemon
 *  that exist in the array from that index +1 by one left like this: effective_against_me/other[index] = effective_against_me/other[index+1] until the end of this array.
 *  after this it allocate less memory by one size of pokemon_type pointer for  effective_against_me/other array.
 *  return: if the allocation went wrong return value is failure,else success.
 *  */

status remove_against_me(PokemonType ,PokemonType );

status remove_against_others(PokemonType ,PokemonType );

/* print_pokemon: prints out all of the pokemons fields. gets a pointer to pokemon struct.
  */
void print_pokemon(Pokemon );
/*
 print_pokemon_type: prints out all of the pokemons type fields. gets a pointer to pokemon type struct.
 *  */
void print_pokemon_type(PokemonType );

status destoryPokemon(Pokemon);

#endif /* POKEMON_H_ */
