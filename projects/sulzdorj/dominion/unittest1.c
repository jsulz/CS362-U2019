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

int main(){

    // Initialize variables here
    int players = 2;
    int kingdomCards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse, sea_hag, tribute, gardens};
    int seed = 2;
    struct gameState prevGameState;
    struct gameState game;
    int result = 0;
    int handPos = 0, bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0;


    // Let everyone know what we're testing
    printf( "----------------- Test results from Baron unit tests ----------------\n" );

    result = initializeGame( players, kingdomCards, seed, &game );

    memcpy( &prevGameState, &game, sizeof( struct gameState) );

    // Test choice1 where we try to make sure no bugs are tripped
    choice1 = 1;
    // we don't want to take any chances about our hand, so we give ourselves a bunch of estates
    for( int i = 0; i < game.handCount[0]; i++ ){
        game.hand[0][i] = estate;
    }
    result = cardEffect( baron, choice1, choice2, choice3, &game, handPos, &bonus );
    printf( "Playing baron card with choice 1 and trying to avoid bugs " );
    customAssert( result );

    result = ( prevGameState.numBuys + 1 == game.numBuys ) ? 1 : -1;
    printf( "\tTesting to see if there is one more buy " );
    customAssert( result );

    result = ( prevGameState.coins + 4 == game.coins );
    printf( "\tTesting to see if there are four more coins after discarding estate card ");
    customAssert( result );

    // Test choice1 where we create a scenario where our first bug is introduced
    choice1 = 1;
    // Copy the previous game state into the current game state
    memcpy( &game, &prevGameState, sizeof( struct gameState) );
    for( int i = 0; i < game.handCount[0]; i++ ){
         if( i == 0 ){
            game.hand[0][i] = estate;
        } else {
            game.hand[0][i] = copper;
        }
    }

    result = cardEffect( baron, choice1, choice2, choice3, &game, handPos, &bonus );
    printf( "Playing baron card with choice 1 and tripping bug #1" );
    customAssert( result );

    result = ( prevGameState.numBuys + 1 == game.numBuys ) ? 1 : -1;
    printf( "\tTesting to see if there is one more buy " );
    customAssert( result );

    result = ( prevGameState.coins + 4 == game.coins ) ? 1 : -1;
    printf( "\tTesting to see if there are four more coins after discarding estate card ");
    customAssert( result );

    result = ( prevGameState.handCount[0] - 1 == game.handCount[0] ) ? 1 : -1;
    printf( "\tTesting to make sure a card was discarded " );
    customAssert( result );

    // Test situation where player has no estate cards in hand but still chooses to discard one
    memcpy( &game, &prevGameState, sizeof( struct gameState) );
    choice1 = 1;
    for( int i = 0; i < game.handCount[0]; i++ ){
        game.hand[0][i] = copper;
    }

    result = cardEffect( baron, choice1, choice2, choice3, &game, handPos, &bonus );
    printf( "Playing baron card with no estate cards " );
    customAssert( result );

    result = ( prevGameState.coins == game.coins ) ? 1 : -1;
    printf( "\tTesting to make sure we were not awarded any extra coins ");
    customAssert( result );

    // Test situation where you don't discard an estate but don't introduce our bug
    memcpy( &game, &prevGameState, sizeof( struct gameState) );
    choice1 = 0; 
    choice2 = 1;

    result = cardEffect( baron, choice1, choice2, choice3, &game, handPos, &bonus );
    printf( "Playing baron card with choice 2 and trying to avoid bug #2 " );
    customAssert( result );

    result = ( prevGameState.coins == game.coins ) ? 1 : -1;
    printf( "\tTesting to make sure we were not awarded any extra coins ");
    customAssert( result );

    result = ( prevGameState.discardCount[0] + 1 == game.discardCount[0] ) ? 1 : -1;
    printf( "\tTesting to make sure we added an estate card to our discard pile ");
    customAssert( result );

    // Test situation where you don't discard an estate and introduce our bug
    memcpy( &game, &prevGameState, sizeof( struct gameState) );
    choice1 = 0; 
    choice2 = 1;

    game.supplyCount[estate] = 1;

    result = cardEffect( baron, choice1, choice2, choice3, &game, handPos, &bonus );
    printf( "Playing baron card with choice #2 and introducing bug #2 " );
    customAssert( result );

    result = ( prevGameState.coins == game.coins ) ? 1 : -1;
    printf( "\tTesting to make sure we were not awarded any extra coins ");
    customAssert( result );

    result = ( prevGameState.discardCount[0] + 1 == game.discardCount[0] ) ? 1 : -1;
    printf( "\tTesting to make sure we added an estate card to our discard pile ");
    customAssert( result );

    return 0;
    
}