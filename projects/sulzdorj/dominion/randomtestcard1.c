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
        for( int j = 0; j < MAX_DECK; j++ ) {
            g->hand[i][j] = rand() % 27;
        }
    }
    for( int i = 0; i < g->numPlayers; i++ ){
        g->handCount[i] = rand() % MAX_HAND;
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

    // Seed a random number generator - I don't think this is necessary, but it's good practice 
    srand(time(NULL));

    for( int i = 0; i < 500; i++ ){

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

        // Copy the state of the game before playing the card so we can test it against the state of the game after playing the card
        memcpy( &prevGameState, &game, sizeof( struct gameState ) );

        supplyCount = rand() % 5;
        game.supplyCount[estate] = supplyCount;

        // If we have a situation where we can force a player's hand to encounter some bugs, let's do so
        if( choice1 == 1 && supplyCount == 2 ){

            for( int i = 0 ; i < game.handCount[0]; i++ ){
                game.hand[0][i] = copper;
            }

        }

        // Play the card
        result = cardEffect( baron, choice1, choice2, choice3, &game, handPos, &bonus );
        printf( "Playing the card with choice1 set to %d and choice2 set to %d ", choice1, choice2 );
        customAssert( result );

        //If we decide to discard an estate
        if( choice1 == 1 ){
            // Test to see if we got an additional buy
            result = ( prevGameState.numBuys + 1 == game.numBuys ) ? 1 : -1;
            printf( "\tTesting to see if there is one more buy " );
            customAssert( result );

            // If supplyCount is 2, then we know we should not have gotten more coins and instead should have
            // recieved an additional estate card in our discard, so let's check that
            if( supplyCount == 2 ){

                // Check to make sure we didn't get more coins
                result = ( prevGameState.coins == game.coins );
                printf( "\tMaking sure we didn't get more coins " );
                customAssert( result );

                // Check to make sure we got an estate
                result = ( game.discard[0][0] == estate ) ? 1 : -1;
                printf( "\tChecking to see if we got an extra estate card because our hand contains only coppers " );
                customAssert( result );

            } 
            // Otherwise, we should have got more coins
            else {
                // Test to see if we got more coins
                result = ( prevGameState.coins + 4 == game.coins ) ? 1 : -1;
                printf( "\tTesting to see if there are four more coins after discarding estate card ");
                customAssert( result );

            }

        } else {
            // otherwise, check to see if we got a new estate card
            if( supplyCount == 2 ){
                result = ( game.discard[0][0] == estate ) ? 1 : -1;
                printf( "\tChecking to see if we got an extra estate card because we asked for it " );
                customAssert( result );
            } 
        }


    }


}