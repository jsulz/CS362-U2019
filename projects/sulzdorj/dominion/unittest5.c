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
    int handPos = 0, bonus = 0;

    // Let everyone know what we're testing
    printf( "----------------- Test results from Mine unit tests ----------------\n" );

    result = initializeGame( players, kingdomCards, seed, &game );

    /* Test 1 - fair test*/
    memcpy( &prevGameState, &game, sizeof( struct gameState) );

    // set the player's hand so we always know what to pick
    game.hand[0][0] = mine;
    game.hand[0][1] = silver;
    game.hand[0][2] = curse;
    game.hand[0][3] = province;
    game.hand[0][4] = copper;

    result = cardEffect( mine, 1, gold, 0, &game, handPos, &bonus );
    printf( "playing the mine " );
    customAssert( result );

    // Make sure that the silver card is no longer in the hand
    result = 1;
    printf( "\tDropping the lone silver card " );
    for( int i = 0; i < game.handCount[0]; i++ ){
        if( game.hand[0][i] == silver  ){
            result = -1;
            break;
        }
    }
    customAssert( result );

    // Check that the last card in the hand is the card we tried to trade for
    result = -1;
    printf( "\tPicking up a gold card gold card " );
    for( int i = 0; i < game.handCount[0]; i++ ){
        if( game.hand[0][i] == gold  ){
            result = 1;
            break;
        }
    }
    customAssert( result );

    /* Test 2 - run into my bug */
    memcpy( &game, &prevGameState, sizeof( struct gameState) );

    // set the player's hand so we always know what to pick
    game.hand[0][0] = copper;
    game.hand[0][1] = curse;
    game.hand[0][2] = curse;
    game.hand[0][3] = province;
    game.hand[0][4] = curse;

    result = cardEffect( mine, 0, silver, 0, &game, handPos, &bonus );
    printf( "Playing the mine " );
    customAssert( result );

    // Make sure that the copper card is no longer in the hand
    result = 1;
    printf( "\tDropping the lone copper card " );
    for( int i = 0; i < game.handCount[0]; i++ ){
        if( game.hand[0][i] == copper  ){
            result = -1;
            break;
        }
    }
    customAssert( result );

    // Check that the last card in the hand is the card we tried to trade for
    result = -1;
    printf( "\tPicking up a silver card " );
    for( int i = 0; i < game.handCount[0]; i++ ){
        if( game.hand[0][i] == gold  ){
            result = 1;
            break;
        }
    }
    customAssert( result );

    /* Test 3 - try to pick up a card with an irrational value */
    memcpy( &game, &prevGameState, sizeof( struct gameState) );

    // set the player's hand so we always know what to pick
    game.hand[0][0] = copper;
    game.hand[0][1] = silver;
    game.hand[0][2] = gold;
    game.hand[0][3] = curse;
    game.hand[0][4] = curse;

    result = cardEffect( mine, 1, 100, 0, &game, handPos, &bonus );
    printf( "Playing the mine " );
    customAssert( result );

    // Make sure that the silver card is no longer in the hand
    result = 1;
    printf( "\tDropping the silver card " );
    for( int i = 0; i < game.handCount[0]; i++ ){
        if( game.hand[0][i] == silver  ){
            result = -1;
            break;
        }
    }
    customAssert( result );

    // Check that the last card in the hand is the card we tried to trade for
    result = -1;
    printf( "\tPicking up a card with an irrational value " );
    for( int i = 0; i < game.handCount[0]; i++ ){
        if( game.hand[0][i] == 100  ){
            result = 1;
            break;
        }
    }
    customAssert( result );

    return 0;
    
}