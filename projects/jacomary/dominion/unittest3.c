/*
 * unittest3.c
 *   
 */

/*
 * Include the following lines in your makefile:
 * 
 * unittest3: unittest3.c dominion.o rngs.o
 * gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "isGameOver"

int main() {
	int test_success = 1;
	int i;
    	int count;
    	int seed = 1000;
    	int numPlayers = 2;
    	int player = 0;
	int otherPlayer = 1;
	struct gameState game, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, remodel};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	

	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	
	printf("\n*******************************************************\n");

	//test case 1 supply and victory piles are full 
	
	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	gameOver = isGameOver(&testGame);	

	printf("\nfunction isGameOver returned %d, expected return value 0\n", gameOver);
	test_success = myassert(gameOver == 0, test_success);

	//test case 2 province pile is empty
	
	testGame.supplyCount[province] = 0;

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	gameOver = isGameOver(&testGame);	

	printf("\nfunction isGameOver returned %d, expected return value 1\n", gameOver);
	test_success = myassert(gameOver == 1, test_success);
	
	//test case 3: three supply piles are empty
	
	testGame.supplyCount[province] = 10;
	testGame.supplyCount[village] = 0;
	testGame.supplyCount[adventurer] = 0;
	testGame.supplyCount[minion] = 0;

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	gameOver = isGameOver(&testGame);	

	printf("\nfunction isGameOver returned %d, expected return value 1\n", gameOver);
	test_success = myassert(gameOver == 1, test_success);
	
	//test case 4: three supply piles are empty and provinces are empty
	
	testGame.supplyCount[province] = 0;
	testGame.supplyCount[village] = 0;
	testGame.supplyCount[adventurer] = 0;
	testGame.supplyCount[minion] = 0;

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	gameOver = isGameOver(&testGame);	

	printf("\nfunction isGameOver returned %d, expected return value 1\n", gameOver);
	test_success = myassert(gameOver == 1, test_success);

	//test case 5: two supply piles are empty, the game is almost over
	
	testGame.supplyCount[province] = 2;
	testGame.supplyCount[village] = 0;
	testGame.supplyCount[adventurer] = 0;
	testGame.supplyCount[minion] = 1;

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	gameOver = isGameOver(&testGame);	

	printf("\nfunction isGameOver returned %d, expected return value 1\n", gameOver);
	test_success = myassert(gameOver == 1, test_success);
	
	
	//testing that no state changes occured to the victory card piles
	printf("\nTesting the victory card piles\n");

	test_success = myassert(testGame.supplyCount[estate] == game.supplyCount[estate], test_success);
	test_success = myassert(testGame.supplyCount[duchy] == game.supplyCount[duchy], test_success);
	test_success = myassert(testGame.supplyCount[province] == game.supplyCount[province], test_success);

	//testing that no state changes occured to the kingdom card piles
	printf("\nTesting the kingdom card piles\n");

	test_success = myassert(testGame.supplyCount[adventurer] == game.supplyCount[adventurer], test_success);
	test_success = myassert(testGame.supplyCount[embargo] == game.supplyCount[embargo], test_success);
	test_success = myassert(testGame.supplyCount[village] == game.supplyCount[village], test_success);
	test_success = myassert(testGame.supplyCount[minion] == game.supplyCount[minion], test_success);
	test_success = myassert(testGame.supplyCount[mine] == game.supplyCount[mine], test_success);
	test_success = myassert(testGame.supplyCount[cutpurse] == game.supplyCount[cutpurse], test_success);
	test_success = myassert(testGame.supplyCount[sea_hag] == game.supplyCount[sea_hag], test_success);
	test_success = myassert(testGame.supplyCount[tribute] == game.supplyCount[tribute], test_success);
	test_success = myassert(testGame.supplyCount[smithy] == game.supplyCount[smithy], test_success);
	test_success = myassert(testGame.supplyCount[council_room] == game.supplyCount[council_room], test_success);
	
//	printf("\ntest_success = %d", test_success);
	if(test_success == 1){
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	}
	else {
		printf("\n >>>>> %s TEST FAILED <<<<<\n\n", TESTCARD);
	}
	return 0;
}
