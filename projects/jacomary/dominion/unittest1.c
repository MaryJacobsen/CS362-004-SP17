/*
 * unittest1.c
 *   
     
 */

/*
 * Include the following lines in your makefile:
 * 
 * unittest1: unittest1.c dominion.o rngs.o
 * gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "endTurn"

int main() {
	int test_success = 1;
	int i;
//    	int count;
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

	game.hand[player][0] = silver;
	game.hand[player][1] = adventurer;
	game.hand[player][2] = estate;
	game.hand[player][3] = copper;
	game.hand[player][4] = smithy;


	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	//test case 1
	endTurn(&testGame);	

	//testing that the hand was discarded
	printf("\ndiscard pile: ");
	for(i=0; i<testGame.discardCount[player]; i++){
		printf("(%d)", testGame.discard[player][i]);
	}
	
	printf("\nexpected discard pile: ");
	for (i=0; i<game.handCount[player]; i++) {
		printf("(%d)", game.hand[player][i]);
	}
	printf("\n");
	if(game.handCount[player] == testGame.discardCount[player]) {
		for(i=0; i<game.handCount[player]; i++){
			test_success = myassert(game.hand[player][i] == testGame.discard[player][i], test_success);
		}
	}
	else {
		printf("test failed\n");
		test_success = 0;
	}

	//checking that player hand is empty
	printf("\nplayer hand count = %d, player expected hand count = 0\n", testGame.handCount[player]);
	test_success = myassert(testGame.handCount[player] == 0, test_success);
	
	//checking that player deck didn't change
	printf("\nplayer deck count = %d, player expected deck count = %d\n", testGame.deckCount[player], game.deckCount[player]);
	test_success = myassert(testGame.deckCount[player] == (game.deckCount[player]), test_success);
		
	printf("\n*******************************************************\n");
	//checking that the number of actions was reset to 1
	printf("\nactions: %d, expected actions: 1\n", testGame.numActions);
	test_success = myassert(testGame.numActions == 1, test_success);

	//checking that the number of buys was reset to 1
	printf("\nbuys: %d, expected buys: 1\n", testGame.numBuys);
	test_success = myassert(testGame.numBuys == 1, test_success);
	
	//checking the number of coins (should be at 3 since the hand has one silver (2) and one copper (1)) 
	printf("\ncoins: %d, expected coins: 3\n", testGame.coins);
	test_success = myassert(testGame.coins == 3, test_success);
	
	//checking that the phase was reset to 0
	printf("\nphase: %d, expected phase: 0\n", testGame.phase);
	test_success = myassert(testGame.phase == 0, test_success);
	
	//checking that the number of cards played was reset to 0
	printf("\ncards played: %d, expected cards: 0\n", testGame.playedCardCount);
	test_success = myassert(testGame.playedCardCount == 0, test_success);
	//checking that the outpost played was reset to false
	printf("\noutpost played: %d, expected outpost played: 0\n", testGame.outpostPlayed);
	test_success = myassert(testGame.outpostPlayed == 0, test_success);
	
	printf("\n*******************************************************\n");

	// Testing for other players	
	printf("\nother player hand count = %d, other player expected hand count = 5\n", testGame.handCount[otherPlayer]);
	test_success = myassert(testGame.handCount[otherPlayer] == 5, test_success);
	
	printf("\nother player deck count = %d, other player expected deck count = 5", testGame.deckCount[otherPlayer]);
	test_success = myassert(testGame.deckCount[otherPlayer] == 5, test_success);

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
