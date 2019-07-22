/*
    Author: Jared Sulzdorf
    Test covers: drawCard() function in dominion.c
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

    // Let everyone know what we're testing
    printf( "----------------- Test results from drawCard unit tests ----------------\n" );

    result = initializeGame( players, kingdomCards, seed, &game );

    memcpy( &prevGameState, &game, sizeof( struct gameState ) );

    // test with non-empty deck
    result = drawCard( 0, &game );
    printf( "Calling the drawCard function with a non-empty deck " );
    customAssert( result );
    
    // first card from the deck into the hand
    result = ( prevGameState.deck[0][game.handCount[0]-1] == game.hand[0][game.handCount[0]-1] ) ? 1 : -1;
    printf( "\tMoving the first card from the player's deck into their hand ");
    customAssert( result );
    
    result = ( game.handCount[0] == 6 ) ? 1 : -1;
    printf( "\tTesting that the first player now has 6 cards " );
    customAssert( result );

    game.deckCount[1] = 0;
    // any cards in discard pile become new deck
    result = drawCard( 1, &game );
    printf( "Calling the drawCard function with an empty deck and nothing in the discard pile " );
    customAssert( result );

    // move five cards from player 1's deck into the discard pile
    for( int i = 0; i < 5; i++){
        game.discard[1][i] = game.deck[0][i];
    }
    // note that there are 5 cards in that pile now
    game.discardCount[1] = 5;
    // any cards in discard pile become new deck
    result = drawCard( 1, &game );
    printf( "Calling the drawCard function with an empty deck and cards available in the discard pile " );
    customAssert( result );
    
    result = ( game.handCount[1] == 1 ) ? 1 : -1;
    printf( "\tTesting that the second player has one card " );
    customAssert( result );

    return 0;
    
}