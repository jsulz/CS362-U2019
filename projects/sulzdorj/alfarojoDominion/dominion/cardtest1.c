/*
    Author: Jared Sulzdorf
    Test covers: InitializeGame() function in dominion.c
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
    int MAXIMUM_PLAYERS = 5;
    int kingdomCards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse, sea_hag, tribute, gardens};
    int kingdomCardsFaulty[10] = {ambassador, ambassador, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int seed = 2;
    struct gameState game;
    int result = 0;

    // Let everyone know what we're testing
    printf( "----------------- Test results from initializeGame unit tests ----------------\n" );

    // First off, we do a loop for 1 - 5 and test the state of the game each time
    // Each time we give it a fair deck and check the number of curse, victory, and treasure cards
    // We also check each player's cards
    for( int playerCount = 1; playerCount <= MAXIMUM_PLAYERS; playerCount++ ){

        // clear the gamestate struct
        memset(&game, 23, sizeof(struct gameState));

        // check for correct initialization - should fail on 1 and 5
        result = initializeGame( playerCount, kingdomCards, seed, &game );
        printf("Initializing the game to %d players ", playerCount );
        customAssert( result );

        if( playerCount == 2 ){
            // there should be 10 curse cards in the supply
            result = (game.supplyCount[curse] == 10) ? 1 : -1;
            printf( "\tThe check of the number of curse cards for a game with %d players ", playerCount );
            customAssert( result );

            // there should be 8 of each type of victory cards in the supply
            result = (game.supplyCount[estate] == 8) ? 1 : -1;
            printf( "\tThe check of the number of estate cards for a game with %d players ", playerCount );
            customAssert( result );

            result = (game.supplyCount[duchy] == 8) ? 1 : -1;
            printf( "\tThe check of the number of duchy cards for a game with %d players ", playerCount );
            customAssert( result );

            result = (game.supplyCount[province] == 8) ? 1 : -1;
            printf( "\tThe check of the number of province cards for a game with %d players ", playerCount );
            customAssert( result );

            // there should be 46 copper cards in the supply
            result = (game.supplyCount[copper] == 46) ? 1 : -1;
            printf( "\tThe check of the number of copper cards for a game with %d players ", playerCount );
            customAssert( result );

            // there should be 40 silver cards in the supply
            result = (game.supplyCount[silver] == 40) ? 1 : -1;
            printf( "\tThe check of the number of silver cards for a game with %d players ", playerCount );
            customAssert( result );

            // there should be 30 gold cards in the supply
            result = (game.supplyCount[gold] == 30) ? 1 : -1;
            printf( "\tThe check of the number of gold cards for a game with %d players ", playerCount );
            customAssert( result );

        } else if( playerCount == 3 ){
            // there should be 20 curse cards in the supply
            result = (game.supplyCount[curse] == 20) ? 1 : -1;
            printf( "\tThe check of the number of curse cards for a game with %d players ", playerCount );
            customAssert( result );

            // there should be 12 of each type of victory cards in the supply
            result = (game.supplyCount[estate] == 12) ? 1 : -1;
            printf( "\tThe check of the number of estate cards for a game with %d players ", playerCount );
            customAssert( result );

            result = (game.supplyCount[duchy] == 12) ? 1 : -1;
            printf( "\tThe check of the number of duchy cards for a game with %d players ", playerCount );
            customAssert( result );

            result = (game.supplyCount[province] == 12) ? 1 : -1;
            printf( "\tThe check of the number of province cards for a game with %d players ", playerCount );
            customAssert( result );

            // there should be 39 copper cards in the supply
            result = (game.supplyCount[copper] == 39) ? 1 : -1;
            printf( "\tThe check of the number of copper cards for a game with %d players ", playerCount );
            customAssert( result );

            // there should be 40 silver cards in the supply
            result = (game.supplyCount[silver] == 40) ? 1 : -1;
            printf( "\tThe check of the number of silver cards for a game with %d players ", playerCount );
            customAssert( result );

            // there should be 30 gold cards in the supply
            result = (game.supplyCount[gold] == 30) ? 1 : -1;
            printf( "\tThe check of the number of gold cards for a game with %d players ", playerCount );
            customAssert( result );

        } else if( playerCount == 4 ){
            // there should be 30 curse cards in the supply
            result = (game.supplyCount[curse] == 30) ? 1 : -1;
            printf( "\tThe check of the number of curse cards for a game with %d players ", playerCount );
            customAssert( result );

            // there should be 12 of each type of victory cards in the supply
            result = (game.supplyCount[estate] == 12) ? 1 : -1;
            printf( "\tThe check of the number of estate cards for a game with %d players ", playerCount );
            customAssert( result );

            result = (game.supplyCount[duchy] == 12) ? 1 : -1;
            printf( "\tThe check of the number of duchy cards for a game with %d players ", playerCount );
            customAssert( result );

            result = (game.supplyCount[province] == 12) ? 1 : -1;
            printf( "\tThe check of the number of province cards for a game with %d players ", playerCount );
            customAssert( result );

            // there should be 32 copper cards in the supply
            result = (game.supplyCount[copper] == 32) ? 1 : -1;
            printf( "\tThe check of the number of copper cards for a game with %d players ", playerCount );
            customAssert( result );

            // there should be 40 silver cards in the supply
            result = (game.supplyCount[silver] == 40) ? 1 : -1;
            printf( "\tThe check of the number of silver cards for a game with %d players ", playerCount );
            customAssert( result );

            // there should be 30 gold cards in the supply
            result = (game.supplyCount[gold] == 30) ? 1 : -1;
            printf( "\tThe check of the number of gold cards for a game with %d players ", playerCount );
            customAssert( result );
        }

    }

    // check with faulty deck - i.e., one that has the same of multiple types of cards
    memset(&game, 23, sizeof(struct gameState));
    result = initializeGame( 2, kingdomCardsFaulty, seed, &game );
    printf("Initializing the game with a deck that has multiple of the same type of cards " );
    customAssert( result );
    
    return 0;
}