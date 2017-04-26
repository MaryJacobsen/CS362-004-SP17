/*
 * cardtest2.c
 *   
     
 */

/*
 * Include the following lines in your makefile:
 * 
 * cardtest2: cardtest2.c dominion.o rngs.o
 * gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
	int newCards = 0;
    	int discarded = 1;
    	int newCoins = 0;
	int newActions = 0;
	int turnAction = 1;
	int newBuys = 0;
    	int shuffledCards = 0;
	int test_success = 1;
    	int i, j, m, z = 0;
    	int handPos = 0, bonus = 0;
    	int remove1, remove2;
    	int seed = 1000;
    	int numPlayers = 2;
    	int player = 0;
	int otherPlayer = 1;
	int cardDrawn = 0;
	int drawntreasure = 0;
	int temphand[MAX_HAND];
	struct gameState game, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1 -------------

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	playAdventurer(player, &testGame, drawntreasure, cardDrawn, temphand, z);

 	while(drawntreasure<2){
		if (game.deckCount[player] <1){ //if the deck is empty we need to shuffle discard and add to deck
	  		shuffle(player, &game);
		}
		drawCard(player, &game);
		cardDrawn = game.hand[player][game.handCount[player]-1]; //top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  		drawntreasure++;
		else{
	  		temphand[z]=cardDrawn;
	  		game.handCount[player]--; //this should just remove the top card (the most recently drawn one).
	  		z++;
		}
      	}
      	while(z-1>=0){
		game.discard[player][game.discardCount[player]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
      }

	//Testing that the cards put in hand were treasure cards
	
	//Testing that the cards discarded were not treasure cards

	// Testing the number of cards in hand
	printf("\nhand count = %d, expected hand count = %d\n", testGame.handCount[player], game.handCount[player]);
	test_success = myassert(testGame.handCount[player] == game.handCount[player], test_success);

	//checking the deck
	printf("\ndeck count = %d, expected deck count = %d\n", testGame.deckCount[player], game.deckCount[player]);	
	test_success = myassert(testGame.deckCount[player] == game.deckCount[player], test_success);
	
		
	// Testing that actionss are unchanged
	printf("\nnumber of actions = %d, expected number of actions = %d\n", testGame.numActions, game.numActions);
	test_success = myassert(testGame.numActions == (game.numActions), test_success);

	
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
