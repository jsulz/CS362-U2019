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
    int players;
    int kingdomCards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse, sea_hag, tribute, gardens};
    int seed = 2;
    struct gameState prevGameState;
    struct gameState game;
    int result = 0;
    int handPos = 0, bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0;
    int supplyCount;

    // Seed a random number generator - I don't think this is necessary, but it's good practice 
    srand(time(NULL));

    for( int i = 0; i < 10; i++ ){

        // Generate a random number of players between 2 and 4
        players = rand() % 2 + 2;

        // generate two random cards between 1 and 100 (we want to test cards that are outside the boundaries of reasonable, knowing that these should fail)
        // victory cards 1, 2, or 3
        // tresure cards are 4, 5, or 6
        // action cards are everything else

        // clear the game struct
        memset(&game, 23, sizeof(struct gameState));
        memset(&prevGameState, 23, sizeof(struct gameState));
        // Initialize our game
        result = initializeGame( players, kingdomCards, seed, &game );

        // Copy the state of the game before playing the card so we can test it against the state of the game after playing the card
        memcpy( &prevGameState, &game, sizeof( struct gameState ) );


        // Play the card
        result = cardEffect( tribute, choice1, choice2, choice3, &game, handPos, &bonus );
        printf( "Playing the card with choice1 set to %d and choice2 set to %d ", choice1, choice2 );
        customAssert( result );


    }


}