/*
 * Pokemon.c
 *
 *  Created on: Nov 20, 2021
 *      Author: ise
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"




status init_pokemon(Pokemon new,char* name,char* species, PokemonBio bio,PokemonType type){
	new->name = (char*)malloc(strlen(name)+1);// malloc the excat size of chars and +1 char for \0
	if(name == NULL){
		return failure;
	}
	new->specie = (char*)malloc(strlen(species)+1);
	if(new->specie == NULL ){
		free(new->name);
		return failure;
	}
	strcpy(new->name,name);
	strcpy(new->specie,species);
	new->my_bio = bio;
	new->type = type;
	new->type->num_pokemons++;
	return success;

}

status init_type(PokemonType new,char* name){
	new->typeName = (char*)malloc(strlen(name)+1);// malloc the excat size of chars and +1 char for \0
	if(new->typeName == NULL){
		return failure;
	}
	new->num_against_me=0;
	new->num_against_others=0;
	new->num_pokemons=0;
	new->effective_against_me=NULL;
	new->effective_against_others=NULL;
	strcpy(new->typeName,name);
	return success;
}

void init_bio(PokemonBio new,float weight,float height,int attack){
	new->weight = weight;
	new->height = height;
	new->attack = attack;
}

void print_pokemon(Pokemon p ){
	printf("%s :\n",p->name);
	printf("%s, %s Type.\n",p->specie,p->type->typeName);
	printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n",p->my_bio->height,p->my_bio->weight,p->my_bio->attack);
}


void print_pokemon_type(PokemonType p){

	printf("Type %s -- %d pokemons\n",p->typeName,p->num_pokemons);
	if(!p->num_against_me && !p->num_against_others) {
		printf("\n");
		return;
	}
	if(p->num_against_me)printf("\tThese types are super-effective against %s:" ,p->typeName);
	int i;
	for(i=0;i<p->num_against_me;i++){
		if(i+1 == (p->num_against_me)){
			printf("%s\n",p->effective_against_me[i]->typeName);
			break;
		}
		printf("%s ,",p->effective_against_me[i]->typeName);

	}

	if(p->num_against_others)printf("\t%s moves are super-effective against:",p->typeName);
	else printf("\n");
	for(i=0;i<p->num_against_others;i++){
		if(i+1 == (p->num_against_others)){
			printf("%s\n",p->effective_against_others[i]->typeName);
			printf("\n");
			break;
		}

		printf("%s ,",p->effective_against_others[i]->typeName);

		}
}


status add_against_me(PokemonType A,PokemonType B){

	A->num_against_me++;
	A->effective_against_me = (pokemon_type**)realloc(A->effective_against_me,sizeof(pokemon_type*)*(A->num_against_me));
	if(A->effective_against_me == NULL){
		return failure;
	}
	A->effective_against_me[A->num_against_me-1] = B;
	return success;
}

status add_against_others(PokemonType A,PokemonType B){

	A->num_against_others++;

	A->effective_against_others = (pokemon_type**)realloc(A->effective_against_others,sizeof(pokemon_type*)*(A->num_against_others));
	if(A->effective_against_others == NULL){
		return failure;
	}
	A->effective_against_others[A->num_against_others-1] = B;
	return success;
}

status remove_against_me(PokemonType A,PokemonType B){

	int i,index = -1;
	for(i=0;i<A->num_against_me;i++){
		if(A->effective_against_me[i] == B){
			index = i;
		}
	}
	if(index == -1){
		return failure;
	}

	int j;
	for(i=index,j=index+1;j<A->num_against_me;i++,j++){
		A->effective_against_me[i] = A->effective_against_me[j];
	}
	A->num_against_me--;
	A->effective_against_me = (pokemon_type**)realloc(A->effective_against_me,sizeof(pokemon_type*)*(A->num_against_me));
	return success;

}

status remove_against_others(PokemonType A,PokemonType B){
	int i,index = -1;
	for(i=0;i<A->num_against_others;i++){
		if(A->effective_against_others[i] == B){
			index = i;
		}
	}
	if(index == -1){
		return failure;
	}

	int j;
	for(i=index,j=index+1;j<A->num_against_others;i++,j++){
		A->effective_against_others[i] = A->effective_against_others[j];
	}
	A->num_against_others--;
	A->effective_against_others = (pokemon_type**)realloc(A->effective_against_others,sizeof(pokemon_type*)*(A->num_against_others));
	return success;
}

status destoryPokemon(Pokemon p)
{
	if(p == NULL) return failure;
	free(p->name);
	free(p->specie);
	free(p->my_bio);
	free(p);
	return success;
}









