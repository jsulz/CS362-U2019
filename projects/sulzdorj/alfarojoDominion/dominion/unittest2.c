/*
    Author: Jared Sulzdorf
    Test covers: playMinion() function in dominion.c
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
    int players = 4;
    int kingdomCards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse, sea_hag, tribute, gardens};
    int seed = 2;
    struct gameState prevGameState;
    struct gameState game;
    int result = 0;
    int handPos = 0, bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0;


    // Let everyone know what we're testing
    printf( "----------------- Test results from Minion unit tests ----------------\n" );

    result = initializeGame( players, kingdomCards, seed, &game );

    // Each player should draw 5 cards except for a control player
    for( int i = 0; i < players; i++ ){
        if( i != 0 ){
            for( int j = 0; j < 6; j++ ){
                drawCard( i, &game );
            }
        } else{
            for( int j = 0; j < 4; j++ ){
                drawCard( i, &game );
            }
        }
    }
    for( int i = 0; i < players; i++ ){
        printf( "%d\n", game.handCount[i] );
    }

    memcpy( &prevGameState, &game, sizeof( struct gameState) );

    // put the minion card in our hand because it gets discarded
    game.hand[0][0] = minion;

    // Choice 1 results in game.numCoins being +2
    choice1 = 1;
    result = cardEffect( minion, choice1, choice2, choice3, &game, handPos, &bonus );

    printf( "Playing minion card with choice #1 " );
    customAssert( result );

    result = ( prevGameState.numActions + 1 == game.numActions ) ? 1 : -1;
    printf( "\tTesting to see if the player was awarded +1 actions ");
    customAssert( result );

    result = ( prevGameState.coins + 2 == game.coins ) ? 1 : -1;
    printf( "\tTesting to see if the player was awarded +2 coins ");
    customAssert( result );

    // Choice 2 results in discarding your hand (so your player's discardCount should increase by 4)
    choice1 = 0; 
    choice2 = 1;
    // copy the prev game state into the game state so we can reset our state
    memcpy( &game, &prevGameState, sizeof( struct gameState ) );
    for( int i = 0; i < players; i++ ){
        printf( "%d\n", game.handCount[i] );
    }
    result = cardEffect( minion, choice1, choice2, choice3, &game, handPos, &bonus );

    printf( "Playing minion card with choice #2 " );
    customAssert( result );

    // should still get +1 actions
    result = ( prevGameState.numActions + 1 == game.numActions ) ? 1 : -1;
    printf( "\tTesting to see if the player was awarded +1 actions ");
    customAssert( result );

    // Picking up four new cards - so you should be able to compare your old hand with your new hand
    result = ( prevGameState.handCount[0] - 1 == game.handCount[0] ) ? 1 : -1;
    printf( "\tTesting to see if the player moved from 5 to 4 cards " );
    customAssert( result );
    if( result == -1 ){
        printf( "\t\tPlayer one should have 4 cards, instead they have %d\n", game.handCount[0] );
    }

    // And each other player with 5 cards discarding their cards and drawing 4 new cards
    for( int i = 1; i < players; i++ ){
        if( prevGameState.handCount[i] >= 5 ){
            result = ( game.handCount[i] == 4 ) ? 1 : -1;
            printf( "%d\n", game.handCount[i] );
            printf( "\tTesting to see if player %d\'s handcount moved from 5 to 4 ", i + 1 );
            customAssert( result );
            if( result == -1 ){
                printf( "\t\tPlayer %d should have 4 cards, instead they have %d\n", i + 1, game.handCount[i] );
            }
        } else {
            result = ( game.handCount[i] == prevGameState.handCount[i] ) ? 1 : -1;
            printf( "\tTesting to see if player %d\'s handcount stayed the same ", i + 1 );
            customAssert( result ); 
        }
    }
    for( int i = 0; i < players; i++ ){
        printf( "%d\n", game.handCount[i] );
    }
    return 0;
    
}