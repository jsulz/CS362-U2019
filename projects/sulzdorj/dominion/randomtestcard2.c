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

    for( int i = 0; i < 5; i++ ){


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
        printf( "Playing the card with choice1 set to %d and choice2 set to %d ", choice1, choice2 );
        customAssert( result );

        // If choice1 is 1, then we've chosen to get two coins
        if( choice1 == 1 ){

            // so we test for that here 
            result = ( prevGameState.coins + 2 == game.coins ) ? 1 : -1;
            printf( "\tTesting to see if there are two more coins " );
            customAssert( result );

            // And we test the number of actions
            result = ( prevGameState.numActions + 1 == game.numActions ) ? 1 : -1;
            printf( "\tTesting to see that we got one additional action " );
            customAssert( result );
            
            // and test that no one else's hands changed
            for( int i = 1; i < players; i++ ){
                result = ( prevGameState.handCount[i] == game.handCount[i] ) ? 1 : -1;
                printf( "\tTesting to see that player %d's hand count did not change ", i );
                customAssert( result );
                if( result == -1 ){
                    printf( "\t\tPlayer %d should have %d cards, instead they have %d\n", i, prevGameState.handCount[i], game.handCount[i] );
                }
            }

        } 
        // Otherwise, we've chosen to discard our hand and get 4 more
        else {

            // Picking up four new cards - so you should be able to compare your old hand with your new hand
            result = ( prevGameState.handCount[0] - 1 == game.handCount[0] ) ? 1 : -1;
            printf( "\tTesting to see if the player moved from 5 to 4 cards " );
            customAssert( result );
            if( result == -1 ){
                printf( "\t\tPlayer one should have 4 cards, instead they have %d\n", game.handCount[0] );
            }

            // And we should test to make sure we didn't get two more coins
            result = ( prevGameState.coins == game.coins ) ? 1 : -1;
            printf( "\tTesting to see that there are the same number of coins " );
            customAssert( result );

           // And we test the number of actions
            result = ( prevGameState.numActions + 1 == game.numActions ) ? 1 : -1;
            printf( "\tTesting to see that we got one additional action " );
            customAssert( result );

            // and test that everyone that had 5 cards now has 4 and that our player has 4 cards as well
            // and that our player with less than 5 cards in their hands didn't have their handcount changed
            // and test that no one else's hands changed
            for( int i = 0; i < players; i++ ){
                if( prevGameState.handCount[i] >= 5 ){
                    result = ( game.handCount[i] == 4 ) ? 1 : -1;
                    printf( "\tTesting to see if player %d\'s handcount moved from %d to 4 ", i + 1, prevGameState.handCount[i] );
                    customAssert( result );
                    if( result == -1 ){
                        printf( "\t\tPlayer %d should have 4 cards, instead they have %d\n", i + 1, game.handCount[i] );
                    }
                } else {
                    result = ( game.handCount[i] == prevGameState.handCount[i] ) ? 1 : -1;
                    printf( "\tTesting to see if player %d\'s handcount stayed the same ", i + 1 );
                    customAssert( result ); 
                    if( result == -1 ){
                        printf( "\t\tPlayer %d should have %d cards, instead they have %d\n", i, prevGameState.handCount[i], game.handCount[0] );
                    }
                }

            }
        }

    }


}