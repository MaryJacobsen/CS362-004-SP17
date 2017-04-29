/*
 * unittest2.c
 *   
     
 */

/*
 * Include the following lines in your makefile:
 * 
 * unittest2: unittest2.c dominion.o rngs.o
 * gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "fullDeckCount"

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

	game.hand[player][0] = silver;
	game.hand[player][1] = adventurer;
	game.hand[player][2] = estate;
	game.hand[player][3] = copper;
	game.hand[player][4] = smithy;
	game.handCount[player] = 5;

	game.deck[player][0] = estate;
	game.deck[player][1] = estate;
	game.deck[player][2] = copper;
	game.deck[player][3] = copper;
	game.deck[player][4] = silver;
	game.deckCount[player] = 5;
	
	game.discard[player][0] = remodel;
	game.discard[player][1] = estate;
	game.discard[player][2] = silver;
	game.discard[player][3] = adventurer;
	game.discard[player][4] = smithy;
	game.discardCount[player] = 5;


	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	//test case 1: checking for a card that isn't in there
	printf("\ntest case 1: counting a card that isn't there\n");	
	
	count = fullDeckCount(player, 11, &testGame);	
	
	printf("\ncount of card = %d, expected count of card = %d\n", count, 0);
	test_success = myassert(count == 0, test_success); 	
	
	printf("cards:\n");
	printf("hand ");
	for (i=0; i<testGame.handCount[player]; i++) {
		printf("(%d)", testGame.hand[player][i]);
	}
	printf("\ndeck ");
	for (i=0; i<testGame.deckCount[player]; i++) {
		printf("(%d)", testGame.deck[player][i]);
	}
	printf("\ndiscard ");
	for (i=0; i<testGame.discardCount[player]; i++) {
		printf("(%d)", testGame.discard[player][i]);
	}
	
		
	printf("\n*******************************************************\n");
	
	//test case 2: checking for a card that is in deck and hand
	printf("\ntest case 2: counting a card that is in the deck and hand\n");	
	
	count = fullDeckCount(player, 4, &testGame);	
	
	printf("\ncount of card = %d, expected count of card = %d\n", count, 3);
	test_success = myassert(count == 3, test_success); 	
	
	printf("cards:\n");
	printf("hand ");
	for (i=0; i<testGame.handCount[player]; i++) {
		printf("(%d)", testGame.hand[player][i]);
	}
	printf("\ndeck ");
	for (i=0; i<testGame.deckCount[player]; i++) {
		printf("(%d)", testGame.deck[player][i]);
	}
	printf("\ndiscard ");
	for (i=0; i<testGame.discardCount[player]; i++) {
		printf("(%d)", testGame.discard[player][i]);
	}
	
	printf("\n*******************************************************\n");
	
	//test case 3: checking for a card that is in deck, hand, and discard
	printf("\ntest case 3: counting a card that is in deck, hand, and discard\n");	
	
	count = fullDeckCount(player, 1, &testGame);	
	
	printf("\ncount of card = %d, expected count of card = %d\n", count, 4);
	test_success = myassert(count == 4, test_success); 	
	
	printf("cards:\n");
	printf("hand ");
	for (i=0; i<testGame.handCount[player]; i++) {
		printf("(%d)", testGame.hand[player][i]);
	}
	printf("\ndeck ");
	for (i=0; i<testGame.deckCount[player]; i++) {
		printf("(%d)", testGame.deck[player][i]);
	}
	printf("\ndiscard ");
	for (i=0; i<testGame.discardCount[player]; i++) {
		printf("(%d)", testGame.discard[player][i]);
	}

	printf("\n*******************************************************\n");

	//test case 4: checking for a card that is in just discard
	printf("\ntest case 4: counting a card that is just in the discard\n");	
	
	count = fullDeckCount(player, 12, &testGame);	
	
	printf("\ncount of card = %d, expected count of card = %d\n", count, 1);
	test_success = myassert(count == 1, test_success); 	
	
	printf("cards:\n");
	printf("hand ");
	for (i=0; i<testGame.handCount[player]; i++) {
		printf("(%d)", testGame.hand[player][i]);
	}
	printf("\ndeck ");
	for (i=0; i<testGame.deckCount[player]; i++) {
		printf("(%d)", testGame.deck[player][i]);
	}
	printf("\ndiscard ");
	for (i=0; i<testGame.discardCount[player]; i++) {
		printf("(%d)", testGame.discard[player][i]);
	}

	printf("\n*******************************************************\n");


	// Testing that no state changes occured for any of the players	
	printf("\nother player hand count = %d, other player expected hand count = %d\n", testGame.handCount[otherPlayer], game.handCount[otherPlayer]);
	test_success = myassert(testGame.handCount[otherPlayer] == (game.handCount[otherPlayer]), test_success);
	
	printf("\nplayer hand count = %d, player expected hand count = %d\n", testGame.handCount[player], game.handCount[player]);
	test_success = myassert(testGame.handCount[player] == (game.handCount[player]), test_success);

	printf("\nother player deck count = %d, other player expected deck count = %d\n", testGame.deckCount[otherPlayer], game.deckCount[otherPlayer]);
	test_success = myassert(testGame.deckCount[otherPlayer] == (game.deckCount[otherPlayer]), test_success);

	printf("\nplayer deck count = %d, player expected deck count = %d\n", testGame.deckCount[player], game.deckCount[player]);
	test_success = myassert(testGame.deckCount[player] == (game.deckCount[player]), test_success);

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
