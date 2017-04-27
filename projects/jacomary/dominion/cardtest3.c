/*
 * cardtest3.c
 *   
     
 */

/*
 * Include the following lines in your makefile:
 * 
 * cardtest3: cardtest3.c dominion.o rngs.o
 * gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "remodel"

int main() {
	int newCards = 0;
    	int discarded = 1;
    	int newCoins = 0;
	int newActions = 0;
	int turnAction = 1;
	int newBuys = 0;
    	int shuffledCards = 0;
	int test_success = 1;
    	int i, j, m, n, r;
    	int handPos = 0, bonus = 0;
    	int remove1, remove2;
	int choice1, choice2 = 4;
	int gain = 0;
    	int seed = 1000;
    	int numPlayers = 2;
    	int player = 0;
	int otherPlayer = 1;
	struct gameState game, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, remodel};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1 -------------

	// testing that the card gained can be up to two more than the card trashed and that the gained card is in discard pile each time
	game.hand[player][0] = remodel;
	game.hand[player][1] = adventurer;
	game.hand[player][2] = estate;
	game.hand[player][3] = copper;
	game.hand[player][4] = smithy;
	
	// copy the game state to a test case	
	memcpy(&testGame, &game, sizeof(struct gameState));

	//testing the gained card costing two more than the trashed card
	printf("\ncard to trash costs %d, card to gain costs %d\n", getCost(game.hand[player][4]), getCost(7));
 	
	r = playRemodel(4, 7, handPos, player, &testGame, m, n);
	
	printf("playRemodel returned %d, expected to return %d\n", r, 0);
	
	if(r == -1){
	   	test_success = myassert(0, test_success);
	}
	printf("\n");
	
	printf("Gained card %d should be in the discard pile\n", game.hand[player][1]);
	printf("discard pile contents: ");
	for(i=0; i<testGame.discardCount[player]; i++){
	   	printf("(%d)", testGame.discard[player][i]);
	   	if(testGame.discard[player][i] == 7){
		   	gain = 1;
		}
	}
	printf("\n");
	if(gain == 0){
		test_success = myassert(0, test_success);
	}


	
	printf("\n**************************************************\n\n");

	//cycling through each choice to trash
	for (i=1; i<game.handCount[player]; i++){
		game.hand[player][0] = remodel;
		game.hand[player][1] = copper;
		game.hand[player][2] = estate;
		game.hand[player][3] = duchy;
		game.hand[player][4] = village;
		

		// copy the game state to a test case
		memcpy(&testGame, &game, sizeof(struct gameState));

		printf("starting cards: ");
		for(j=0; j<testGame.handCount[player]; j++){
			printf("(%d)", testGame.hand[player][j]);
		}
		printf("\n");

		choice1 = i;
		remove1 = testGame.hand[player][i];

		playRemodel(choice1, choice2, handPos, player, &testGame, m, n);	

		printf("\nremoved: (%d)\n\n", remove1);
		printf("ending cards: ");

		//tests that the removed card is no longer in the player's hand
		for(j=0; j<testGame.handCount[player]; j++){
		   	printf("(%d)", testGame.hand[player][j]);
			test_success = myassert(testGame.hand[player][j] != remove1, test_success);
		}

		printf("\nexpected: ");
		for(j=1; j<game.handCount[player]; j++){
		   	if(game.hand[player][j] != game.hand[player][i]){
			   	printf("(%d)", game.hand[player][j]);
			}
		}
		printf("\n\n");
		// tests for the appropriate number of remaining cards
		newCards = 0;
		discarded = 2;
		
		printf("hand count = %d, expected = %d\n", testGame.handCount[player], game.handCount[player] + newCards - discarded);
		test_success = myassert(testGame.handCount[player] == game.handCount[player] + newCards - discarded, test_success);

		printf("deck count = %d, expected = %d\n", testGame.deckCount[player], game.deckCount[player] - newCards + shuffledCards);
		test_success = myassert(testGame.deckCount[player] == game.deckCount[player] - newCards + shuffledCards, test_success);
		
		printf("\n**************************************************\n\n");
	}


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
	printf("\nTesting the kindom card piles\n");

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
