/*
 * cardtest4.c
 *   
     
 */

/*
 * Include the following lines in your makefile:
 * 
 * cardtest4: cardtest4.c dominion.o rngs.o
 * gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
	int newCards = 0;
    	int discarded = 1;
//    	int newCoins = 0;
	int newActions = 0;
	int turnAction = 1;
	int newBuys = 0;
    	int shuffledCards = 0;
	int test_success = 1;
//	int i, j, m;
    	int handPos = 0;
//    	int remove1, remove2;
    	int seed = 1000;
    	int numPlayers = 2;
    	int player = 0;
	int otherPlayer = 1;
	struct gameState game, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	playSmithy(player, handPos, &testGame);	

	// Testing that the player got +3 cards	
	newCards = 3;
	//checking the hand	
	printf("\nhand count = %d, expected hand count = %d\n", testGame.handCount[player], game.handCount[player] + newCards - discarded);
	test_success = myassert(testGame.handCount[player] == (game.handCount[player] + newCards - discarded), test_success);

	//checking the deck
	printf("\ndeck count = %d, expected deck count = %d\n", testGame.deckCount[player], game.deckCount[player] - newCards + shuffledCards);	
	test_success = myassert(testGame.deckCount[player] == (game.deckCount[player] - newCards + shuffledCards), test_success);
	
	// Testing that the actions are unchanged
	newActions = 0;
	// decremented the actions by one because this unit test does not enter the playCard function which is in charge of decrementing the players actions when action cards are played	
	printf("\nnumber of actions = %d, expected number of actions = %d\n", testGame.numActions - turnAction, game.numActions + newActions - turnAction);
	test_success = myassert((testGame.numActions - turnAction) == (game.numActions + newActions - turnAction), test_success);
		
	// Testing that buys are unchanged
	newBuys = 0;
	printf("\nnumber of buys = %d, expected number of buys = %d\n", testGame.numBuys, game.numBuys + newBuys);
	test_success = myassert(testGame.numBuys == (game.numBuys + newBuys), test_success);

	// Testing that no state changes occured for the other player	
	printf("\nother player hand count = %d, other player expected hand count = %d\n", testGame.handCount[otherPlayer], game.handCount[otherPlayer]);
	test_success = myassert(testGame.handCount[otherPlayer] == (game.handCount[otherPlayer]), test_success);

	printf("\nother player deck count = %d, other player expected deck count = %d\n", testGame.deckCount[otherPlayer], game.deckCount[otherPlayer]);
	test_success = myassert(testGame.deckCount[otherPlayer] == (game.deckCount[otherPlayer]), test_success);

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
	
	//printf("\ntest_success = %d", test_success);
	if(test_success == 1){
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	}
	else {
		printf("\n >>>>> %s TEST FAILED <<<<<\n\n", TESTCARD);
	}
	return 0;
}
