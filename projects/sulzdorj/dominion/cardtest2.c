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
    int cardCounter = 0;
    int cards[20];

    // clear the gamestate struct
    memset(&game, 23, sizeof(struct gameState));

    // Let everyone know what we're testing
    printf( "----------------- Test results from shuffle unit tests ----------------\n" );

    result = initializeGame( players, kingdomCards, seed, &game );
    printf("Initializing the game to %d players ", players );
    customAssert( result );

    for( int i = 0; i < players; i++ ){
        for( int j = 0; j < 10; j++ ){
            cards[cardCounter] = game.deck[i][j];
            cardCounter++;
        }
    }

    result = shuffle( 0, &game );
    printf("Shuffling player one\'s deck " );
    customAssert( result );
    int flag = -1;
    for( int i = 0; i < 10; i++ ){
        if( cards[i] != game.deck[0][i] ){
            flag = 1;
        }
    }
    result = flag;
    printf("\tChecking the contents of player one\'s deck to ensure it has been shuffled " );
    customAssert( result );

    result = shuffle( 1, &game );
    printf("Shuffling player two\'s deck " );
    customAssert( result );
    flag = -1;
    for( int i = 10; i < 20; i++ ){
        if( cards[i] != game.deck[1][i] ){
            flag = 1;
        }
    }
    result = flag;
    printf("\tChecking the contents of player two\'s deck to ensure it has been shuffled  " );
    customAssert( result );

    game.deckCount[0] = 0;
    result = shuffle( 0, &game );
    printf("Shuffling the deck of a player whose deck count is 0 " );
    customAssert( result );
    
    return 0;
}