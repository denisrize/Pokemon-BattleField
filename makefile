PokemonsBattles: MainSecond.o BattleByCategory.o MaxHeap.o LinkedList.o Pokemon.o
	gcc MainSecond.o BattleByCategory.o MaxHeap.o LinkedList.o Pokemon.o -o PokemonsBattles

BattleByCategory.o: BattleByCategory.c BattleByCategory.h Defs.h MaxHeap.h LinkedList.h 
	gcc -c BattleByCategory.c 	

MainSecond.o: MainSecond.c BattleByCategory.h Defs.h Pokemon.h
	gcc -c MainSecond.c 
	
MaxHeap.o: MaxHeap.c MaxHeap.h Defs.h
	gcc -c MaxHeap.c

LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
	
Pokemon.o: Pokemon.c Pokemon.h Defs.h
	gcc -c Pokemon.c
			
clean:
	rm -f*.o
	






	
