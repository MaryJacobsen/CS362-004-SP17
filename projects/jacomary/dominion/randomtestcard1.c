#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define numTESTS 2000
#define TESTCARD adventurer

int main() {
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};
	int i, j, k;
	int seed;
	int numPlayers; 
	int handSize, deckSize; 
	int testCardPosition;
	int preHandCount, postHandCount, preDeckCount, postDeckCount;
	int handDiff, deckDiff; 
	int numCorrect = 0, numWrong = 0;
	struct gameState game;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	for (i = 0; i < numTESTS; i++) {

	  	numPlayers = (rand() % 2) + 2; // 2-4 players
	  	seed = rand();
	  	handSize = (rand() % 9) + 1;
	  	deckSize = rand() % 10;
		
	  	initializeGame(numPlayers, k, seed, &game);

		//Initiate valid state variables
		game.deckCount[0] = deckSize;
		game.handCount[0] = handSize;

		// Randomly filling hand and deck
		for (j = 0; j < deckSize; j++) {
			state.deck[0][j] = rand() % 27;
		}

		for (k = 0; k < handSize; k++) {
			state.hand[0][k] = rand() % 27;
		}

		// Randomly placing test card required
	  	testCardPosition = rand() % handSize;
		state.hand[0][testCardPosition] = adventurer;

		// set up all the pre-call variables
		preHandCount = state.handCount[0];
		preDeckCount = state.deckCount[0];

		playCard(testCardPosition, 1, 1, 1, &game);

		// record post-call variables
		postHandCount = state.handCount[0];
		postDeckCount = state.deckCount[0];

		// calculations to test accuracy of this test
		handDiff = postHandCount - preHandCount;
		deckDiff = preDeckCount - postDeckCount;
	
		if ((deckDiff) > -2) {
			wrongCount++;
		}
		else if (handDiff > 2 || handDiff < 0) {
			wrongCount++;
		}
		else {
			correctCount = correctCount+1;
		}
	}

	printf("%d Tests Complete\n", numTESTS);
	printf("Wrong Results: %d\n", numWrong);
	printf("Correct Results: %d\n", numCorrect);
	
	return 0;
}
