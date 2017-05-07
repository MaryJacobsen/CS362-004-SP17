#include "dominion.h"
#include "dominion_helpers.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TESTS 10000
#define TESTCARD "smithy"


int assert1(int result, char *errorMsg, int testNumber) {
	if (!result) {
		fprintf(stderr, "ASSERTION FAILURE ON TEST %d: %s\n", testNumber, errorMsg);
		return 1;
	}
}


int main() {

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	sea_hag, tribute, smithy};

	int numTest, numPlayers, player, seed, card, value; 
	int numFailed = 0;
	int smithyPos[4];
	struct gameState game, gameAfterCall;
	time_t t;
	
	srand((unsigned) time(&t));
	
	printf("-*-*-*-*-*-*-*-*- Random Testing Card: %s -*-*-*-*-*-*-*-*-\n", TESTCARD);

	for (numTest = 0; numTest < MAX_TESTS; numTest++) {
		numPlayers = (rand() % 3) + 2;

		seed = rand();

		initializeGame(numPlayers, k, seed, &game);

		//Randomly give each player cards
		for (player = 0; player < numPlayers; player++) {
			//Randomly assign number of cards to each player
			game.handCount[player] = (rand() % (MAX_HAND - 1)) + 1;
			game.deckCount[player] = rand() % (MAX_DECK - game.handCount[player]);
			game.discardCount[player] = rand() % (MAX_DECK - game.handCount[player] - game.deckCount[player]);
			
			//Randomly give each player a deck
			for (card = 0; card < game.deckCount[player]; card++) {
				value = rand() % 13;
				if (value < 10)
					game.deck[player][card] = k[value];
				else if (value == 10)
					game.deck[player][card] = copper;
				else if (value == 11)
					game.deck[player][card] = silver;
				else if (value == 12)
					game.deck[player][card] = gold;
				else
					if(assert1(1, "not a valid card", numTest) == 1) numFailed++;
			}

			//Randomly give each player a discard pile
			for (card = 0; card < game.discardCount[player]; card++) {
				value = rand() % 13;
				if (value < 10)
					game.discard[player][card] = k[value];
				else if (value == 10)
					game.discard[player][card] = copper;
				else if (value == 11)
					game.discard[player][card] = silver;
				else if (value == 12)
					game.discard[player][card] = gold;
				else
					if(assert1(1, "not a valid card", numTest) == 1) numFailed++;
			}
			
			//Randomly give each player a hand
			for (card = 0; card < game.handCount[player]; card++) {
				value = rand() % 13;
				if (value < 10)
					game.hand[player][card] = k[value];
				else if (value == 10)
					game.hand[player][card] = copper;
				else if (value == 11)
					game.hand[player][card] = silver;
				else if (value == 12)
					game.hand[player][card] = gold;
				else
					if(assert1(1, "not a valid card", numTest) == 1) numFailed++;
			}
			
			//Place a smithy card in each player's hand
			smithyPos[player] = rand() % game.handCount[player];
			game.hand[player][smithyPos[player]] = smithy;
		}

		player = rand() % numPlayers;
		game.whoseTurn = player;
		
		//Copy the game state
		memcpy(&gameAfterCall, &game, sizeof game);
		if(assert1(!memcmp(&gameAfterCall, &game, sizeof game), "game and gameAfterCall are not the same", numTest) == 1) numFailed++;
		
		//Call playSmithy
		if(assert1(playSmithy(smithyPos[player], player, &gameAfterCall) == 0, "function playSmithy failed", numTest) == 1) numFailed++;	

		//tests
		
		//+3 minus smithy because it was discard so +2
		if(assert1(gameAfterCall.handCount[player] == game.handCount[player] + 2, "error in adding 3 cards to hand", numTest) == 1) numFailed++;

		
		if(assert1(gameAfterCall.playedCards[gameAfterCall.playedCardCount-1] == smithy, "the last played card was not smithy", numTest) == 1) numFailed++;
			
	}

	printf("*-*-*-*-* RANDOM TESTS COMPLETE *-*-*-*-*\n");
	printf("Number of failed tests = %d out of %d total\n", numFailed, MAX_TESTS);

	return 0;
}
