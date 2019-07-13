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
    printf( "----------------- Test results from Tribute unit tests ----------------\n" );

    result = initializeGame( players, kingdomCards, seed, &game );

    /* Test 1 */
    memcpy( &prevGameState, &game, sizeof( struct gameState) );

    // Set the next player's last two cards in their deck so we know what to expect
    game.deck[1][game.deckCount[1] - 1 ] = copper;
    game.deck[1][game.deckCount[1] - 2 ] = estate;

    result = cardEffect( tribute, choice1, choice2, choice3, &game, handPos, &bonus );
    printf( "Playing tribute card " );
    customAssert( result );

    // The player that played the card should have two more cards in their hand
    // this will fail because of my bug #2
    result = ( prevGameState.handCount[0] + 2 == game.handCount[0] ) ? 1 : -1;
    printf( "\tTesting to see if player one has two more cards in their hand " );
    customAssert( result );
    if( result == -1 ){
        printf( "\t\tThey were expected to have %d and instead have %d\n", prevGameState.handCount[0] + 2, game.handCount[0]);
    }

    // and two more coins
    // This should succeed
    result = ( prevGameState.coins + 2 == game.coins ) ? 1 : -1;
    printf( "\tTesting to see if player one has two more coins " );
    customAssert( result );
    if( result == -1 ){
        printf( "\t\tThey were expected to have %d and instead have %d\n", prevGameState.coins + 2, game.coins );
    }

    // but no additional actions
    result = ( prevGameState.numActions == game.numActions ) ? 1 : -1;
    printf( "\tTesting to see if player one has the same number of actions " );
    customAssert( result );
    if( result == -1 ){
        printf( "\t\tThey were expected to have %d and instead have %d\n", prevGameState.numActions, game.numActions );
    }


    /* Test 2 */

    memcpy( &game, &prevGameState, sizeof( struct gameState ) );

    // set the next player's deck count to 1 to trigger the situation where a player only has one card in their deck
    game.deckCount[1] = 1;

    // and set the one card in their deck to a silver card
    game.deck[1][0] = silver;

    result = cardEffect( tribute, choice1, choice2, choice3, &game, handPos, &bonus );
    printf( "Playing tribute card " );
    customAssert( result );

    // The player that played the card should have the same number of cards in their hand
    result = ( prevGameState.handCount[0] == game.handCount[0] ) ? 1 : -1;
    printf( "\tTesting to see if player one has the same number of cards in their hand " );
    customAssert( result );
    if( result == -1 ){
        printf( "\t\tThey were expected to have %d and instead have %d\n", prevGameState.handCount[0], game.handCount[0]);
    }

    // The player that played the card should have two more coins in their hand
    result = ( prevGameState.coins + 2 == game.coins ) ? 1 : -1;
    printf( "\tTesting to see if player one has two more coins " );
    customAssert( result );
    if( result == -1 ){
        printf( "\t\tThey were expected to have %d and instead have %d\n", prevGameState.coins + 2, game.coins );
    }

    // but no additional actions
    result = ( prevGameState.numActions == game.numActions ) ? 1 : -1;
    printf( "\tTesting to see if player one has the same number of actions " );
    customAssert( result );
    if( result == -1 ){
        printf( "\t\tThey were expected to have %d and instead have %d\n", prevGameState.numActions, game.numActions );
    }

    /* Test 3 */

    memcpy( &game, &prevGameState, sizeof( struct gameState ) );

    // set the next player's deck count to 0
    game.deckCount[1] = 0;
    // And their discard pile to 5 to trigger the sitaution where the card is pulled from the discard pile
    game.discardCount[1] = 5;
    // And give the discard pile a (gold) treasure and anction card
    game.discard[1][0] = gold;
    game.discard[1][1] = baron;

    result = cardEffect( tribute, choice1, choice2, choice3, &game, handPos, &bonus );
    printf( "Playing tribute card " );
    customAssert( result );
    if( result == -1 ){
        printf( "\t\t " );
    }

    // The player that played the card should have the same number of cards in their hand
    result = ( prevGameState.handCount[0] == game.handCount[0] ) ? 1 : -1;
    printf( "\tTesting to see if player one has the same number of cards in their hand " );
    customAssert( result );
    if( result == -1 ){
        printf( "\t\tThey were expected to have %d and instead have %d\n", prevGameState.handCount[0], game.handCount[0]);
    }

    // The player that played the card should have two more coins in their hand
    result = ( prevGameState.coins + 2 == game.coins ) ? 1 : -1;
    printf( "\tTesting to see if player one has two more coins " );
    customAssert( result );
    if( result == -1 ){
        printf( "\t\tThey were expected to have %d and instead have %d\n", prevGameState.coins + 2, game.coins );
    }

    // but no additional actions
    result = ( prevGameState.numActions + 2 == game.numActions ) ? 1 : -1;
    printf( "\tTesting to see if player one has two more actions " );
    customAssert( result );
    if( result == -1 ){
        printf( "\t\tThey were expected to have %d and instead have %d\n", prevGameState.numActions + 2, game.numActions );
    }

    return 0;
    
}