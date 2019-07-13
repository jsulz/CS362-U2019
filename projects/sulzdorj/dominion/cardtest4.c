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
    int result = 0;
    int playersArr[MAX_PLAYERS];

    // Let everyone know what we're testing
    printf( "----------------- Test results from getWinners unit tests ----------------\n" );

    result = initializeGame( players, kingdomCards, seed, &game );

    for( int i = 0; i < players; i++ ){
        if( i == 0 ){
            game.handCount[i] = 5;
            for( int j = 0; j < game.handCount[i]; j++ ){
                game.hand[i][j] = province;
            }
        }
        if( i == 1 ){
            game.discardCount[i] = 5;
            for( int j = 0; j < 5; j++ ){
                game.hand[i][j] = curse;
            }
        }
    }

    result = getWinners( playersArr, &game );
    printf("Call to getWinnders " );
    customAssert( result );

    printf( "\tSetting the first player as the winner " );
    customAssert( playersArr[0] );

    for( int i = 0; i < players; i++ ){
        if( i == 0 ){
            game.handCount[i] = 5;
            for( int j = 0; j < game.handCount[i]; j++ ){
                game.hand[i][j] = curse;
            }
        }
        if( i == 1 ){
            game.discardCount[i] = 5;
            for( int j = 0; j < 5; j++ ){
                game.hand[i][j] = province;
            }
        }
    }

    result = getWinners( playersArr, &game );
    printf("Call to getWinnders " );
    customAssert( result );
    printf( "\tSetting the second player as the winner " );
    customAssert( playersArr[1] );

    result = (playersArr[2] == 0 && playersArr[3] == 0 ) ? 1 : -1;
    printf("\tIgnoring players scores " );
    customAssert( result );

    return 0;
    
}