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
	//int newCards = 0;
    	//int discarded = 1;
    	//int newCoins = 0;
	//int newActions = 0;
	//int turnAction = 1;
	//int newBuys = 0;
    	//int shuffledCards = 0;
	int test_success = 1;
    	int i, j, m; 
	int z = 0;
    	//int handPos = 0; 
	//int bonus = 0;
    	//int remove1, remove2;
    	int seed = 1000;
    	int numPlayers = 2;
    	int player = 0;
	int otherPlayer = 1;
	int cardDrawn = 0;
	int drawntreasure = 0;
	int treasureOne, treasureTwo, testTreasureOne, testTreasureTwo;
	int temphand[MAX_HAND];
	struct gameState game, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


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

	//Testing that the cards put in hand were the correct treasure cards
	
	//getting top two cards in hand
	treasureOne = game.hand[player][game.handCount[player]-2];	
	treasureTwo = game.hand[player][game.handCount[player]-1];
	testTreasureOne = testGame.hand[player][game.handCount[player]-2];	
	testTreasureTwo = testGame.hand[player][game.handCount[player]-1];

	//checking that they are treasure cards
	test_success = myassert(treasureOne == copper || treasureOne == silver || treasureOne == gold, test_success);	
	test_success = myassert(treasureTwo == copper || treasureTwo == silver || treasureTwo == gold, test_success);
	test_success = myassert(testTreasureOne == copper || testTreasureOne == silver || testTreasureOne == gold, test_success);
	test_success = myassert(testTreasureTwo == copper || testTreasureTwo == silver || testTreasureTwo == gold, test_success);

	//checking that both game and testGame got the same treasure cards
	printf("\nfirst drawn treasure = %d, expected first drawn treasure = %d (note: 4 is copper, 5 is silver, 6 is gold)\n", testTreasureOne, treasureOne);
	test_success = myassert(testTreasureOne == treasureOne, test_success);
	printf("\nsecond drawn treasure = %d , expected second drawn treasure = %d (note: 4 is copper, 5 is silver, 6 is gold)\n", testTreasureTwo, treasureTwo);
	test_success = myassert(testTreasureTwo == treasureTwo, test_success);
	
	//Testing the number of cards discarded
	printf("\nnumber of cards discarded = %d, expected number of cards discarded = %d\n", testGame.discardCount[player], game.discardCount[player]);
	test_success = myassert(testGame.discardCount[player] == game.discardCount[player], test_success);

	//Testing that the cards discarded were not treasure cards
	for(i = 0; i < game.discardCount[player]; i++) {
		test_success = myassert(game.discard[player][i] != copper && game.discard[player][i] != silver && game.discard[player][i] != gold, test_success);
	}
	
	for(j = 0; j < testGame.discardCount[player]; j++) {	
		test_success = myassert(testGame.discard[player][j] != copper && testGame.discard[player][j] != silver && testGame.discard[player][j] != gold, test_success);
	}

	// Testing the number of cards in hand
	printf("\nhand count = %d, expected hand count = %d\n", testGame.handCount[player], game.handCount[player]);
	test_success = myassert(testGame.handCount[player] == game.handCount[player], test_success);

	//checking the number of cards in deck
	printf("\ndeck count = %d, expected deck count = %d\n", testGame.deckCount[player], game.deckCount[player]);	
	test_success = myassert(testGame.deckCount[player] == game.deckCount[player], test_success);
	
		
	// Testing that actionss are unchanged
	printf("\nnumber of actions = %d, expected number of actions = %d\n", testGame.numActions, game.numActions);
	test_success = myassert(testGame.numActions == (game.numActions), test_success);

	
	// Testing that buys are unchanged
	printf("\nnumber of buys = %d, expected number of buys = %d\n", testGame.numBuys, game.numBuys);
	test_success = myassert(testGame.numBuys == game.numBuys, test_success);

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
