/*
 * MainSecond.c
 *
 *  Created on: Dec 11, 2021
 *      Author: ise
 */
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "BattleByCategory.h"
#include "Pokemon.h"

PokemonType find_type(PokemonType arr_types,int num_of_types,char* type_name){
	int i;
	for(i=0;i< num_of_types;i++){
		int res = strcmp(arr_types[i].typeName,type_name);
		if( res == 0){
			return &(arr_types[i]);
		}
	}
	return NULL;

}

void finish_script(Battle b,PokemonType type_arr,int num_of_types,int flag){
	int i;
	if(b != NULL)destroyBattleByCategory(b);
	for(i=0;i<num_of_types;i++)
	{
		free(type_arr[i].typeName);
		free(type_arr[i].effective_against_me);
		free(type_arr[i].effective_against_others);
	}
	if(flag){
		printf("No memory available.\n");
		exit(1);
	}
	printf("All the memory cleaned and the program is safely closed.\n");
	exit(0);


}

Pokemon createPokemon(PokemonType type)
{

	char name[300];
	char specie[300];
	float height,weight;
	int attack;
	printf("Please enter Pokemon name:\n");
	scanf("%s",name);
	printf("Please enter Pokemon species:\n");
	scanf("%s",specie);
	printf("Please enter Pokemon height:\n");
	scanf("%f",&height);
	printf("Please enter Pokemon weight:\n");
	scanf("%f",&weight);
	printf("Please enter Pokemon attack:\n");
	scanf("%d",&attack);
	PokemonBio bio = (PokemonBio)malloc(sizeof(struct pokemon_b));
	if( bio == NULL)
	{
		return NULL;
	}
	Pokemon p = (Pokemon)malloc(sizeof(struct final_pokemon));
	if( p == NULL ){
		free(bio);
		return NULL;
	}
	init_bio(bio,weight,height,attack);
	if((init_pokemon(p,name, specie,  bio, type)) == failure)return NULL;
	return p;

}

status insertToBattle(Battle b ,PokemonType type_arr,int num_of_types, int capacity)
{
	PokemonType pType;
	char type[300];
	printf("Please enter Pokemon type name:\n");
	scanf("%s",type);
	if((pType = find_type(type_arr,num_of_types,type)) == NULL)
		{
			printf("Type name doesn't exist.\n");
			return failure;
		}
	if(getNumberOfObjectsInCategory(b,type) == capacity)
	{
		printf("Type at full capacity.\n");
		return failure;
	}

	Pokemon p = createPokemon(pType);
	if( p == NULL)  finish_script(b,type_arr,num_of_types,1);

	if(insertObject(b,p) == memoryProblem) finish_script(b,type_arr,num_of_types,1);
	printf("The Pokemon was successfully added.\n");
	print_pokemon(p);
	return success;


}

status removeStrongest(Battle b,PokemonType type_arr,int num_of_types)
{
	PokemonType type = NULL;
	Pokemon p = NULL;
	char name[300];
	printf("Please enter type name:\n");
	scanf("%s",name);
	if((type = find_type(type_arr,num_of_types,name)) == NULL)
		{
			printf("Type name doesn't exist.\n");
			return failure;
		}
	if(!type->num_pokemons)
		{
			printf("There is no Pokemon to remove.\n");
			return failure;
		}
	if((p = removeMaxByCategory(b,name)) == NULL && type->num_pokemons) finish_script(b,type_arr,num_of_types,1);

	printf("The strongest Pokemon was removed:\n");
	print_pokemon(p);
	destoryPokemon(p);
	type->num_pokemons--;
	return success;

}

status pokemonFight(Battle b,PokemonType type_arr,int num_of_types)
{
	PokemonType pType;
	char type[300];
	printf("Please enter Pokemon type name:\n");
	scanf("%s",type);
	if((pType = find_type(type_arr,num_of_types,type)) == NULL)
		{
			printf("Type name doesn't exist.\n");
			return failure;
		}
	Pokemon p = createPokemon(pType);
	if( p == NULL)  finish_script(b,type_arr,num_of_types,1);

	pType->num_pokemons--;
	printf("You choose to fight with:\n");
	print_pokemon(p);
	if((fight(b,p)) == NULL)
	{
		printf("There are no Pokemons to fight against you.\n");
		destoryPokemon(p);
		return failure;
	};
	destoryPokemon(p);
	return success;

}

char* getPokemonCat(element e)
{
 Pokemon p = (Pokemon)e;
 return p->type->typeName;
}

int getAttackPokemon(element e1 ,element e2 ,int* a1,int* a2)
{
	Pokemon p1 = (Pokemon)e1;
	Pokemon p2 = (Pokemon)e2;
	PokemonType againstMe = NULL;
	PokemonType againstOther = NULL;
	if(p1->type->effective_against_me) againstMe = find_type(*(p1->type->effective_against_me),p1->type->num_against_me,p2->type->typeName);
	if(p2->type->num_against_others) againstOther = find_type(*(p2->type->effective_against_others),p2->type->num_against_others,p1->type->typeName);
	*a1 = p1->my_bio->attack;
	*a2 = p2->my_bio->attack;
	if( ( againstMe != NULL) || ( againstOther != NULL))
		{
			*a1 = *a1 - 10;
		};
	againstMe = NULL;
	againstOther = NULL;
	if(p1->type->num_against_others) againstOther = find_type(*(p1->type->effective_against_others),p1->type->num_against_others,p2->type->typeName);
	if(p2->type->num_against_me) againstMe = find_type(*(p2->type->effective_against_me),p2->type->num_against_me,p1->type->typeName);
	if( ( againstMe != NULL) || ( againstOther != NULL))
		{
			*a2 = *a2 - 10;
		};

	return *a1 - *a2;

}

element copyPokemon(element e)
{
	return e;
}

int equalPokemon(element e1,element e2)
{
	Pokemon p1 = (Pokemon)e1;
	Pokemon p2 = (Pokemon)e2;

	if(p1->my_bio->attack > p2->my_bio->attack) return 1;
	if(p1->my_bio->attack < p2->my_bio->attack) return -1;
	return 0;

}

status printPokemon(element e)
{
	if( e == NULL)return failure;
	print_pokemon((Pokemon)e);
	return success;
}

status freePokemon(element e)
{
	return destoryPokemon((Pokemon)e);
}

int main(int argc,char* argv[]){
	int num_of_types = atoi(argv[1]);
	int capacity = atoi(argv[2]);
	pokemon_type type_arr[num_of_types];

	FILE *file;
	char line[300];
	char delim[] = " :,\t\n\r"; // ignore all of this chars
	file = fopen(argv[3],"r");

	// read line by line
	fgets(line, sizeof(line), file);
	fgets(line, sizeof(line), file);
	char *input = strtok(line, delim);
	char allTypes[300];
	if(num_of_types) strcat(allTypes,input);
	int i;

	for(i=0;i<num_of_types;i++)
	{

		if(init_type(&type_arr[i],input) == failure) finish_script(NULL,type_arr,i,1); // memory problem free the i numbers of types we already took.
		if(i+1 < num_of_types)
		{
			input = strtok(NULL, delim);
			strcat(allTypes,",");
			strcat(allTypes,input);
		}

	}
	// -------------------- initialize battle --------------

	 Battle battlePokemons =  createBattleByCategory( capacity,num_of_types,allTypes,equalPokemon, copyPokemon, freePokemon, getPokemonCat, getAttackPokemon, printPokemon);
	 if(battlePokemons == NULL) finish_script(NULL,type_arr,num_of_types,1);

	//-------------- initialize against --------------------
	fgets(line, sizeof(line), file);
	input = strtok(line, delim); // typeA gets the name of the first type

	while(strcmp(line,"Pokemons") != 0){

		char *command = strtok(NULL, delim);// what kind of command to excute against_me or against_other?
		char *typeB = strtok(NULL, delim); // typeB get the name of the second type

		while( typeB != NULL){

			PokemonType A = find_type(type_arr,num_of_types,input);
			PokemonType B = find_type(type_arr,num_of_types,typeB);
			if(strcmp(command,"effective-against-me") == 0){

				if(add_against_me(A,B) == failure){
					finish_script(battlePokemons,type_arr,num_of_types,1);
				}
			}else{
				if(add_against_others(A,B) == failure){
					finish_script(battlePokemons,type_arr,num_of_types,1);
				}
			}
			typeB = strtok(NULL, delim);

		}

		fgets(line, sizeof(line), file);
		input = strtok(line, delim);
	}



// -------------------- initialize pokemons -----------------

	while(fgets(line, sizeof(line), file) != NULL){
		char *pokemon_name = strtok(line, delim);
		char *specie = strtok(NULL, delim);
		double height = atof(strtok(NULL, delim));
		double weight = atof(strtok(NULL, delim));
		double attack = atof(strtok(NULL, delim));
		char *type_name = strtok(NULL, delim);
		PokemonBio bio = (PokemonBio)malloc(sizeof(struct pokemon_b));
		if(bio == NULL)	finish_script(battlePokemons,type_arr,num_of_types,1);


		init_bio(bio,weight,height,attack);
		PokemonType type = find_type(type_arr,num_of_types,type_name);
		Pokemon p = (Pokemon)malloc(sizeof(struct final_pokemon));
		if( p == NULL)	{
			free(bio);
			finish_script(battlePokemons,type_arr,num_of_types,1);
		}

		if(init_pokemon(p,pokemon_name,specie,bio,type) == failure){
			finish_script(battlePokemons,type_arr,num_of_types,1);
		}
		insertObject(battlePokemons,p);
		bio = NULL;
		p = NULL;
	}


	fclose(file);

	// ---------------- main menu -------------------

	char choise ;
	while( choise != 6){
		printf("Please choose one of the following numbers:\n");
		printf("1 : Print all Pokemons by types\n");
		printf("2 : Print all Pokemons types\n");
		printf("3 : Insert Pokemon to battles training camp\n");
		printf("4 : Remove strongest Pokemon by type\n");
		printf("5 : Fight\n");
		printf("6 : Exit\n");
		scanf(" %c",&choise);

		switch(choise){
			case '1':

				displayObjectsByCategories(battlePokemons);
				break;
			case '2':
				for(i=0;i<num_of_types;i++){
					print_pokemon_type(&(type_arr[i]));
					}
				break;
			case '3':
				insertToBattle(battlePokemons,type_arr, num_of_types,capacity);
				break;
			case '4':
				removeStrongest(battlePokemons,type_arr,num_of_types);
				break;
			case '5':
				pokemonFight(battlePokemons,type_arr,num_of_types);
				break;
			case '6':
				finish_script(battlePokemons,type_arr,num_of_types,0);
				break;
			default:
				printf("Please choose a valid number.\n");
				break;
		}
	}
	return 0;
}

