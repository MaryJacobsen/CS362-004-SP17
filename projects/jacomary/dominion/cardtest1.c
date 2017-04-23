/*
 * cardtest4.c
 *   
     
 */

/*
 * Include the following lines in your makefile:
 * 
 * cardtest4: cardtest4.c dominion.o rngs.o
 * gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
	int newCards = 0;
    	int discarded = 1;
    	int newCoins = 0;
    	int shuffledCards = 0;

    	int i, j, m;
    	int handPos = 0, bonus = 0;
    	int remove1, remove2;
    	int seed = 1000;
    	int numPlayers = 2;
    	int player = 0;
	struct gameState game, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: --------------
	printf("TEST 1: \n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	playVillage(player, handPos, &testGame);	
	
	newCards = 1;	
	printf("hand count = %d, expected hand count = %d\n", testGame.handCount[player], game.handCount[player] + newCards - discarded);
	return 0;
}
