/*
    Author: Jared Sulzdorf
    Test covers: playBaron() function in dominion.c
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "customAssert.h"
#include <limits.h>

/*
    A struct that we use to note if a value in the gameState struct is off.
 */
struct checker {
    int numActionCheck;
    int numCoinCheck;
    int numBuysCheck;
    int numPlayedCardCountCheck;
    int supplyCardCheck;
    int deckCountCheck;
    int discardCountCheck;
    int discardCheck;
    int handCountCheck;
    int handCheck;
};

/*
    Function that takes in the previous game state (after updating it with the oracle function),
    the game state after playing the card with the cardEffect() function, and the checker struct.
    Where the structs do not match, we increment a variable in the checker struct so that we can keep 
    track of how the test failed. 
 */
void compareStructs( struct gameState *prevGame, struct gameState *postGame, struct checker *infoHolder ){

    // If the number of actions between the two structs is different
    // Then capture that in the checker struct
    if( prevGame->numActions != postGame->numActions ){
        infoHolder->numActionCheck++;
    }

    // If the number of coins between the two structs is different
    // Then capture that in the checker struct
    if( prevGame->coins != postGame->coins ){
        infoHolder->numCoinCheck++;
    }

    // If the number of buys between the two structs is different
    // Then capture that in the checker struct 
    if( prevGame->numBuys != postGame->numBuys ){
        infoHolder->numBuysCheck++;
    }

    // If the number of played chards between the two structs is different
    // Then capture that in the checker struct
    if( prevGame->playedCardCount != postGame->playedCardCount ){
        infoHolder->numPlayedCardCountCheck++;
    }

    // If any of the supply count values for any of the cards is different
    // Then capture that in the checker struct
    for( int i = 0; i < 27; i++ ){
        if( prevGame->supplyCount[i] != postGame->supplyCount[i] ){
            infoHolder->supplyCardCheck++;
            break;
        }
    }

    // If any of the deck counts between any of the players is different
    // Then capture that in the checker struct
    for( int i = 0; i < postGame->numPlayers; i++ ){
        if( prevGame->deckCount[i] != postGame->deckCount[i] ){
            infoHolder->deckCountCheck++;
            break;
        }
    }

    // If any of the discard counts between any of the players is different
    // Then capture that in the checker struct
    for( int i = 0; i < postGame->numPlayers; i++ ){
        if( prevGame->discardCount[i] != postGame->discardCount[i] ){
            infoHolder->deckCountCheck++;
            break;
        }
    }

    // If any of the cards in any of the players' discard piles are different
    // Then capture that in the checker struct
    for( int i = 0; i < postGame->numPlayers; i++ ){
        int stop = 0;
        if( stop ){
            break;
        }
        for( int j = 0; j < postGame->discardCount[i]; j++ ) {
            if( prevGame->discard[i][j] != postGame->discard[i][j] ){
                infoHolder->discardCheck++;
                break;
            }
        }
    }

    // If any of the hand counts between any of the players is different
    // Then capture that in the checker struct
    for( int i = 0; i < postGame->numPlayers; i++ ){
        if( prevGame->handCount[i] != postGame->handCount[i] ){
            infoHolder->handCountCheck++;
            break;
        }
    }

    // If any of the cards in any of the players' hand piles are different
    // Then capture that in the checker struct
    for( int i = 0; i < postGame->numPlayers; i++ ){
        int stop = 0;
        if( stop ){
            break;
        }
        for( int j = 0; j < postGame->handCount[i]; j++ ) {
            if( prevGame->hand[i][j] != postGame->hand[i][j] ){
                infoHolder->handCheck++;
                break;
            }
        }
    }

}


/*
    A function that randomies the variables of a gameState struct
    in the allowed domain of each variable.
 */
void randomizeGameState( struct gameState *g ){

    g->numActions = rand() % INT_MAX - 10;
    g->coins = rand() % INT_MAX - 10;
    g->numBuys = rand() % INT_MAX - 10;
    g->playedCardCount = rand() % MAX_DECK;

    for( int i = 0; i < 27; i++ ){
        g->supplyCount[i] = rand() % INT_MAX;
        g->embargoTokens[i] = rand() % INT_MAX;
    }
    for( int i = 0; i < g->numPlayers; i++ ){
        g->deckCount[i] = rand() % MAX_DECK;
    }
    for( int i = 0; i < g->numPlayers; i++ ){
        g->discardCount[i] = rand() % MAX_DECK;
    }
    for( int i = 0; i < g->numPlayers; i++ ){
        for( int j = 0; j < MAX_DECK; j++ ) {
            g->discard[i][j] = rand() % 27;
        }
    }

    // We constrain this in our testing so that we can encounter more bugs in
    // the dominion.c version of this code
    for( int i = 0; i < g->numPlayers; i++ ){
        g->handCount[i] = rand() % 5;
    }

    for( int i = 0; i < g->numPlayers; i++ ){
        for( int j = 0; j < g->handCount[i]; j++ ) {
            g->hand[i][j] = rand() % 27;
        }
    }

}

/*
    A helper function that lets us see how many failures our tests encountered and where those failures were.
 */
void printResults( int failures, struct checker *infoH ){

    printf( "There were %d total failures\n", failures );
    printf( "In %d iterations of playing the Baron card, the number of actions were incorrect\n", infoH->numActionCheck );
    printf( "In %d iterations of playing the Baron card, the number of coins were incorrect\n", infoH->numCoinCheck );
    printf( "In %d iterations of playing the Baron card, the number of buys were incorrect\n", infoH->numBuysCheck );
    printf( "In %d iterations of playing the Baron card, the played cards were incorrect\n", infoH->numPlayedCardCountCheck );
    printf( "In %d iterations of playing the Baron card, the supply cards were incorrect\n", infoH->supplyCardCheck );
    printf( "In %d iterations of playing the Baron card, the players deck count were incorrect\n", infoH->deckCountCheck );
    printf( "In %d iterations of playing the Baron card, the players discard counts were incorrect\n", infoH->discardCountCheck );
    printf( "In %d iterations of playing the Baron card, the players discard piles were incorrect\n", infoH->discardCheck );
    printf( "In %d iterations of playing the Baron card, the players hands counts were incorrect\n", infoH->handCountCheck );
    printf( "In %d iterations of playing the Baron card, the players hands were incorrect\n", infoH->handCountCheck );

}

int oracle( int choice1, int choice2, struct gameState *prevGameState, struct gameState *game, struct checker *holding ){

    int failure = 0;
        if( choice1 == 1 ){

            int currentPlayer = whoseTurn( prevGameState );
            prevGameState->numBuys++;//Increase buys by 1!
                int p = 0;//Iterator for hand!
                int card_not_discarded = 1;//Flag for discard set!

                while(card_not_discarded){

                if (prevGameState->hand[currentPlayer][p] == estate){//Found an estate card!

                   prevGameState->coins += 4;//Add 4 coins to the amount of coins
                    prevGameState->discard[currentPlayer][prevGameState->discardCount[currentPlayer]] = prevGameState->hand[currentPlayer][p];
                    prevGameState->discardCount[currentPlayer]++;

                    for (;p < prevGameState->handCount[currentPlayer]; p++){
                    prevGameState->hand[currentPlayer][p] = prevGameState->hand[currentPlayer][p+1];
                    }

                    prevGameState->hand[currentPlayer][prevGameState->handCount[currentPlayer]] = -1;
                    prevGameState->handCount[currentPlayer]--;
                    card_not_discarded = 0;//Exit the loop
                }
                else if (p > prevGameState->handCount[currentPlayer]){

                    if (supplyCount(estate, prevGameState) > 0){
                        gainCard(estate, prevGameState, 0, currentPlayer);
                        prevGameState->supplyCount[estate]--;//Decrement estates

                    if (supplyCount(estate, prevGameState) == 0){
                        isGameOver(prevGameState);
                    }
                    }
                    card_not_discarded = 0;//Exit the loop
                }
                    
                else{
                    p++;//Next card
                }
                }

            int result = memcmp(prevGameState, game, sizeof(struct gameState));
            if( result != 0 ){
                failure = 1;
                compareStructs( prevGameState, game, holding );
            } else {
                //printf("succeeded\n");
            }

        } else {
            prevGameState->numBuys++;
            int currentPlayer = whoseTurn( prevGameState );
            if (supplyCount(estate, prevGameState) > 0){

                gainCard(estate, prevGameState, 0, currentPlayer);//Gain an estate
                prevGameState->supplyCount[estate]--;//Decrement Estates

                if (supplyCount(estate, prevGameState) == 0){
                    isGameOver(prevGameState);
                }

            }
            int result = memcmp(prevGameState, game, sizeof(struct gameState));
            if( result != 0 ){
                failure = 1;
                compareStructs( prevGameState, game, holding );
            }
        }

    return failure;
}


int main(){

    // Initialize variables here
    int players;
    int kingdomCards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse, sea_hag, tribute, gardens};
    int seed = 2;
    struct gameState prevGameState;
    struct gameState game;
    struct checker holding = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int result = 0;
    int handPos = 0, bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0;
    int estateSupply;
    int failures = 0;

    // Seed a random number generator - I don't think this is necessary, but it's good practice 
    srand(time(NULL));

    for( int i = 0; i < 10000; i++ ){

        // Generate random numbers between 0 and 1 for our choice1 variable
        choice1 = rand() % 2;
        // And based on that choice, toggle choice2
        if( choice1 == 0 ){
            choice2 = 1;
        } else {
            choice2 = 0;
        }

        // Generate a random number of players between 2 and 4
        players = rand() % 2 + 2;

        // clear the game struct
        memset(&game, 23, sizeof(struct gameState));
        memset(&prevGameState, 23, sizeof(struct gameState));

        // Initialize our game
        result = initializeGame( players, kingdomCards, seed, &game );

        // randomize all of the state variables in the game state
        randomizeGameState( &game );

        estateSupply = rand() % 5;
        game.supplyCount[estate] = estateSupply;

        // If we have a situation where we can force a player's hand to encounter some bugs, let's do so
        if( choice1 == 1 && estateSupply == 2 ){

            for( int i = 0 ; i < game.handCount[0]; i++ ){
                game.hand[0][i] = copper;
            }

        }

        // Copy the state of the game before playing the card so we can test it against the state of the game after playing the card
        memcpy( &prevGameState, &game, sizeof( struct gameState ) );

        // Play the card
        result = cardEffect( baron, choice1, choice2, choice3, &game, handPos, &bonus );

        failures += oracle( choice1, choice2, &prevGameState, &game, &holding );


    }

    printResults( failures, &holding );


}