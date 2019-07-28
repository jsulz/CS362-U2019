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

void compareStructs( struct gameState *prevGame, struct gameState *postGame, struct checker *infoHolder ){

    if( prevGame->numActions != postGame->numActions ){
        infoHolder->numActionCheck++;
    }

    if( prevGame->coins != postGame->coins ){
        infoHolder->numCoinCheck++;
    }

    if( prevGame->numBuys != postGame->numBuys ){
        infoHolder->numBuysCheck++;
    }

    if( prevGame->playedCardCount != postGame->playedCardCount ){
        infoHolder->numPlayedCardCountCheck++;
    }

    for( int i = 0; i < 27; i++ ){
        if( prevGame->supplyCount[i] != postGame->supplyCount[i] ){
            infoHolder->supplyCardCheck++;
            break;
        }
    }

    for( int i = 0; i < postGame->numPlayers; i++ ){
        if( prevGame->deckCount[i] != postGame->deckCount[i] ){
            infoHolder->deckCountCheck++;
            break;
        }
    }

    for( int i = 0; i < postGame->numPlayers; i++ ){
        if( prevGame->discardCount[i] != postGame->discardCount[i] ){
            infoHolder->deckCountCheck++;
            break;
        }
    }

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
    for( int i = 0; i < postGame->numPlayers; i++ ){
        if( prevGame->handCount[i] != postGame->handCount[i] ){
            infoHolder->handCountCheck++;
            break;
        }
    }

    for( int i = 0; i < postGame->numPlayers; i++ ){
        int stop = 0;
        if( stop ){
            break;
        }
        for( int j = 0; j < postGame->handCount[i]; j++ ) {
            if( prevGame->hand[i][j] != postGame->hand[i][j] ){
                infoHolder->handCheck;
                break;
            }
        }
    }

}

void printResults( int failures, struct checker *infoH ){

    printf( "There were %d total failures\n", failures );
    printf( "In %d iterations of playing the Minion card, the number of actions were incorrect\n", infoH->numActionCheck );
    printf( "In %d iterations of playing the Minion card, the number of coins were incorrect\n", infoH->numCoinCheck );
    printf( "In %d iterations of playing the Minion card, the number of buys were incorrect\n", infoH->numBuysCheck );
    printf( "In %d iterations of playing the Minion card, the played cards were incorrect\n", infoH->numPlayedCardCountCheck );
    printf( "In %d iterations of playing the Minion card, the supply cards were incorrect\n", infoH->supplyCardCheck );
    printf( "In %d iterations of playing the Minion card, the players deck count were incorrect\n", infoH->deckCountCheck );
    printf( "In %d iterations of playing the Minion card, the players discard counts were incorrect\n", infoH->discardCountCheck );
    printf( "In %d iterations of playing the Minion card, the players discard piles were incorrect\n", infoH->discardCheck );
    printf( "In %d iterations of playing the Minion card, the players hands counts were incorrect\n", infoH->handCountCheck );
    printf( "In %d iterations of playing the Minion card, the players hands were incorrect\n", infoH->handCountCheck );

}

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
    for( int i = 0; i < g->numPlayers; i++ ){
        g->handCount[i] = 5;
    }
    for( int i = 0; i < g->numPlayers; i++ ){
        for( int j = 0; j < g->handCount[i]; j++ ) {
            g->hand[i][j] = rand() % 27;
        }
    }

}

int main(){

    // Initialize variables here
    int players;
    int kingdomCards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse, sea_hag, tribute, gardens};
    int seed = 2;
    struct gameState prevGameState;
    struct gameState game;
    int result = 0;
    int handPos = 0, bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0;
    int supplyCount;
    int failures = 0;
    struct checker holding = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    // Seed a random number generator - I don't think this is necessary, but it's good practice 
    srand(time(NULL));

    for( int i = 0; i < 200; i++ ){


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

        randomizeGameState( &game );


        // Copy the state of the game before playing the card so we can test it against the state of the game after playing the card
        memcpy( &prevGameState, &game, sizeof( struct gameState ) );

        // Play the card
        result = cardEffect( minion, choice1, choice2, choice3, &game, handPos, &bonus );

        prevGameState.numActions += 1;
        int currentPlayer = whoseTurn( &prevGameState );
        discardCard( handPos, currentPlayer, &prevGameState, 0 );

        // If choice1 is 1, then we've chosen to get two coins
        if( choice1 == 1 ){
            prevGameState.coins += 2;
            // check stuff here
            int result = memcmp(&prevGameState, &game, sizeof(struct gameState));
            if( result != 0 ){
                failures++;
                compareStructs( &prevGameState, &game, &holding );
            } else {
                //printf("succeeded\n");
            }
        } 
        // Otherwise, we've chosen to discard our hand and get 4 more
        else {

            /*
            Bug #1: Stop the while loop below before all of the currentPlayer's cards have been
            discarded. Results in the player having 5 cards. 
            */
            while(numHandCards(&prevGameState) > 0) {
                discardCard(handPos, currentPlayer, &prevGameState, 0);
            }

            //draw 4
            for ( int i = 0; i < 4; i++) {
            drawCard(currentPlayer, &prevGameState);
            }

            //other players discard hand and redraw if hand size > 4
            for (int i = 0; i < prevGameState.numPlayers; i++) {
                if (i != currentPlayer) {
                    if ( prevGameState.handCount[i] > 4 ) {
                        //discard hand
                        while( prevGameState.handCount[i] > 0 ) {
                            discardCard(handPos, i, &prevGameState, 0);
                        }
                        //draw 4
                        for (int j = 0; j < 4; j++){
                            drawCard(i, &prevGameState);
                        }
                    }
                }  
            }
            int result = memcmp(&prevGameState, &game, sizeof(struct gameState));
            if( result != 0 ){
                failures++;
                compareStructs( &prevGameState, &game, &holding );
            }

        }
    }

    printResults( failures, &holding );


}