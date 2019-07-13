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
    struct gameState game;
    struct gameState prevGameState;
    int result = 0;

    memset(&game, 23, sizeof(struct gameState));

    // Let everyone know what we're testing
    printf( "----------------- Test results from endTurn unit tests ----------------\n" );

    result = initializeGame( players, kingdomCards, seed, &game );
    printf("Initializing the game to %d players ", players );
    customAssert( result );

    // copy the current state of the game
    memcpy( &prevGameState, &game, sizeof( struct gameState ) );

    // End the turn
    result = endTurn( &game );
    printf( "Ending the current turn " );
    customAssert( result );

    // all of the cards in the player's hand should be set to -1
    int flag = 1;
    for( int i = 0; i < 5; i++ ){
        if( game.hand[0][i] != -1 ){
            flag = -1;
        }
    }
    result = flag; 
    printf("\tThe attempt to discard the previous player's cards " );
    customAssert( result );

    // The handCount for the previous player should be 0
    result = ( prevGameState.handCount[0] != game.handCount[0] && game.handCount[0] == 0 ) ? 1 : -1;
    printf("\tThe attempt to reset the previous player's hand count " );
    customAssert( result );

    // The state->whoseTurn should be the next player after this player
    result = ( prevGameState.whoseTurn + 1 == game.whoseTurn ) ? 1 : -1;
    printf("\tThe attempt to set the turn for the next player " );
    customAssert( result );

    // basic state variables should be set for the next player
    result = (game.outpostPlayed == 0) ? 1 : -1;
    printf("\tThe attempt to set the state for the outposts played has " );
    customAssert( result );

    // The phase should be 0
    result = (game.phase == 0) ? 1 : -1;
    printf("\tThe attempt to set the state phase of the game has " );
    customAssert( result );

    // Num actions should be reset to 1
    result = (game.numActions == 1) ? 1 : -1;
    printf("\tThe attempt to set the state for the number of actions available to the next player has " );
    customAssert( result );

    // num buys should be reset to 1
    result = (game.numBuys == 1) ? 1 : -1;
    printf("\tThe attempt to set the state for the number of buys available to the next player has " );
    customAssert( result );

    // Played card count should be 1
    result = (game.playedCardCount == 0) ? 1 : -1;
    printf("\tThe attempt to set the state for the number of cards played has " );
    customAssert( result );

    // Next player draws their hand
    result = ( game.handCount[game.whoseTurn] == 5 ) ? 1 : -1;
    printf("\tThe attempt to set the number of cards for the next player has " );
    customAssert( result );

    // and they get some coins - because we know we've just initialized the game, the next player shouldn't have any more than 5 coins
    result = ( game.coins <= 5 ) ? 1 : -1;
    printf("\tThe attempt to set the number of coins for the next player has " );
    customAssert( result );

    // Then let's end the turn again to make sure that we
    // wrapped around to the next player
    result = endTurn( &game );
    printf( "Ending the current turn to test the function wrapping around to the first player " );
    customAssert( result );
    
    return 0;
}