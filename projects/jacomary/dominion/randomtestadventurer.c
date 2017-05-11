#include "dominion.h"
#include "dominion_helpers.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TESTS 10000
#define TESTCARD "adventurer"
#define PRINT 1

int countTreasures(struct gameState game, int player) {
	int count = 0, i;
	
	for (i = 0; i < game.deckCount[player]; i++) {
		if (game.deck[player][i] == copper || game.deck[player][i] == silver || game.deck[player][i] == gold) {	
			count++;
		}
	}
	
	for (i = 0; i < game.discardCount[player]; i++) {
		if (game.discard[player][i] == copper || game.discard[player][i] == silver || game.discard[player][i] == gold) {
			count++;
		}
	}
	
	return count;
}


int assert1(int result, char *errorMsg, int testNumber) {
	if (!result) {
	   	if(PRINT) fprintf(stderr, "ASSERTION FAILURE ON TEST %d: %s\n", testNumber, errorMsg);
		return 1;
	}
}


int main() {

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	sea_hag, tribute, smithy};

	int numTest, numPlayers, player, seed, card, value, i; 
	int numTreasures = 0, drawnTreasure = 0, cardDrawn = 0, z = 0, discarded = 1;;
	int numFailed = -1;
	int adventurerPos[4];
	int temphand[MAX_HAND];
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
			
			//Place an adventurer card in each player's hand
			adventurerPos[player] = rand() % game.handCount[player];
			game.hand[player][adventurerPos[player]] = adventurer;
		}

		player = rand() % numPlayers;
		game.whoseTurn = player;
		
		//Copy the game state
		memcpy(&gameAfterCall, &game, sizeof game);
		if(assert1(!memcmp(&gameAfterCall, &game, sizeof game), "game and gameAfterCall are not the same", numTest) == 1) numFailed++;
		
		numTreasures = countTreasures(game, player);
		if (numTreasures > 2) {
			numTreasures = 2;
		}
		
		//Call playAdventurer

		if(assert1(playAdventurer(player, &gameAfterCall, drawnTreasure, cardDrawn, temphand, z) == 0, "function playAdventurer failed", numTest) == 1) numFailed++;
		
		//tests

		if(assert1(gameAfterCall.handCount[player] == game.handCount[player] + numTreasures - discarded, "error in adding treasures to hand", numTest) == 1) numFailed++;
		
		for (i = 1; i <= numTreasures; i++) {
			if(assert1(gameAfterCall.hand[player][gameAfterCall.handCount[player]-i] == copper || 
			        gameAfterCall.hand[player][gameAfterCall.handCount[player]-i] == silver ||
			        gameAfterCall.hand[player][gameAfterCall.handCount[player]-i] == gold, "cards put into hand were not treasures", numTest) == 1) numFailed++;
		}

		//checking that actions were unchanged
		if(assert1(gameAfterCall.numActions == game.numActions, "actions were changed", numTest) == 1) numFailed++;

		//checking that buys were unchanged
		if(assert1(gameAfterCall.numBuys == game.numBuys, "buys were changed", numTest) == 1) numFailed++;

		//changing the player
		if(player == numPlayers) player--;
		
		else player++;

		//Testing that no state changes occured for another player	
		if(assert1(gameAfterCall.handCount[player] == (game.handCount[player]), "another player's hand was changed", numTest) == 1) numFailed++;

		if(assert1(gameAfterCall.deckCount[player] == (game.deckCount[player]), "another player's deck was changed", numTest) == 1) numFailed++;
		
		//testing that no state changes occured to the victory card piles
		if(assert1(gameAfterCall.supplyCount[estate] == game.supplyCount[estate], "estate pile was changed", numTest) == 1) numFailed++;
		if(assert1(gameAfterCall.supplyCount[duchy] == game.supplyCount[duchy], "duchy pile was changed", numTest) == 1) numFailed++;
		if(assert1(gameAfterCall.supplyCount[province] == game.supplyCount[province], "province pile was changed", numTest) == 1) numFailed++;

		//testing that no state changes occured to the kingdom card piles
		if(assert1(gameAfterCall.supplyCount[adventurer] == game.supplyCount[adventurer], "adventurer pile was changed", numTest) == 1) numFailed++;
		if(assert1(gameAfterCall.supplyCount[embargo] == game.supplyCount[embargo], "embargo pile was changed", numTest) == 1) numFailed++;	
		if(assert1(gameAfterCall.supplyCount[village] == game.supplyCount[village], "village pile was changed", numTest) == 1) numFailed++;
		if(assert1(gameAfterCall.supplyCount[minion] == game.supplyCount[minion], "minion pile was changed", numTest) == 1) numFailed++;
		if(assert1(gameAfterCall.supplyCount[mine] == game.supplyCount[mine], "mine pile was changed", numTest) == 1) numFailed++;
		if(assert1(gameAfterCall.supplyCount[cutpurse] == game.supplyCount[cutpurse], "cutpurse pile was changed", numTest) == 1) numFailed++;
		if(assert1(gameAfterCall.supplyCount[sea_hag] == game.supplyCount[sea_hag], "sea hag pile was changed", numTest) == 1) numFailed++;
		if(assert1(gameAfterCall.supplyCount[tribute] == game.supplyCount[tribute], "tribute pile was changed", numTest) == 1) numFailed++;
		if(assert1(gameAfterCall.supplyCount[smithy] == game.supplyCount[smithy], "smithy pile was changed", numTest) == 1) numFailed++;
		if(assert1(gameAfterCall.supplyCount[gardens] == game.supplyCount[gardens], "gardens pile was changed", numTest) == 1) numFailed++;

	}

	printf("*-*-*-*-* RANDOM TESTS COMPLETE *-*-*-*-*\n");
	printf("Number of failed tests = %d out of %d total\n", numFailed, MAX_TESTS);
	
	return 0;
}
