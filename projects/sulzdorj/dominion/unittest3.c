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
    printf( "----------------- Test results from Ambassador unit tests ----------------\n" );

    result = initializeGame( players, kingdomCards, seed, &game );

    memcpy( &prevGameState, &game, sizeof( struct gameState) );

    // play with choice #1 revealing the ambassador card and trying to return 1 copy of it - should fail
    choice1 = ambassador;
    choice2 = 1;
    game.hand[0][0] = ambassador;
    result = cardEffect( ambassador, choice1, choice2, choice3, &game, handPos, &bonus );
    printf( "Revealing ambassador card " );
    customAssert( result );

    // play with choice #1 revealing a copper card and trying to return 1 copy of it - should succeed
    memcpy( &game, &prevGameState, sizeof( struct gameState) );
    choice1 = copper;
    choice2 = 0;
    game.hand[0][0] = ambassador;
    result = cardEffect( ambassador, choice1, choice2, choice3, &game, handPos, &bonus );
    printf( "Revealing a copper card " );
    customAssert( result );

    // should have choice2 less cards (account for losing the ambassador card as well)
    result = ( prevGameState.handCount[0] - choice2 - 1 == game.handCount[0] ) ? 1 : -1;
    printf( "\tTesting to see if there are %d less cards ", choice2 );
    customAssert( result );

    // each player should have choice2 more copies of this card in their discard
    for( int i = 1; i < players; i++ ){
        result = ( prevGameState.discardCount[i] + 1 == game.discardCount[i] ) ? 1 : -1;
        printf( "\tTesting to see if player %d has %d more cards in their discard pile ", i + 1, 1 );
        customAssert( result );
    }    

    // play with choice #1 revealing a copper card and trying to return 1 copy of it - should succeed
    memcpy( &game, &prevGameState, sizeof( struct gameState) );
    choice1 = copper;
    choice2 = 1;
    game.hand[0][0] = ambassador;
    result = cardEffect( ambassador, choice1, choice2, choice3, &game, handPos, &bonus );
    printf( "Revealing a copper card " );
    customAssert( result );

    // should have choice2 less cards
    result = ( prevGameState.handCount[0] - choice2 == game.handCount[0] ) ? 1 : -1;
    printf( "\tTesting to see if there are %d less cards ", choice2 );
    customAssert( result );

    // each player should have choice2 more copies of this card in their discard
    for( int i = 1; i < players; i++ ){
        result = ( prevGameState.discardCount[i] + choice2 == game.discardCount[i] ) ? 1 : -1;
        printf( "\tTesting to see if player %d has %d more cards in their discard pile ", i + 1, choice2 );
        customAssert( result );
    }  

    // play with choice #1 revealing a copper card and trying to return 2 copies of it - should fail
    memcpy( &game, &prevGameState, sizeof( struct gameState) );
    choice1 = copper;
    choice2 = 2;
    game.hand[0][0] = ambassador;
    result = cardEffect( ambassador, choice1, choice2, choice3, &game, handPos, &bonus );
    printf( "Revealing a copper card " );
    customAssert( result );

    // should have choice2 less cards
    result = ( prevGameState.handCount[0] - choice2 == game.handCount[0] ) ? 1 : -1;
    printf( "\tTesting to see if there are %d less cards ", choice2 );
    customAssert( result );

    // each player should have choice2 more copies of this card in their discard
    for( int i = 1; i < players; i++ ){
        result = ( prevGameState.discardCount[i] + 1 == game.discardCount[i] ) ? 1 : -1;
        printf( "\tTesting to see if player %d has %d more cards in their discard pile ", i + 1, choice2 );
        customAssert( result );
    }  

    return 0;
    
}