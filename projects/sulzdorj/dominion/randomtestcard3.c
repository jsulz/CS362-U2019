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
#include <limits.h>

struct checker {
    int numActionCheck;
    int numCoinCheck;
    int numBuysCheck;
    int numPlayedCardCountCheck;
    int supplyCardCheck;
    int deckCountCheck;
    int discardCountCheck;
    int discardCheck;
    int handCountCheck;
    int handCheck;
};

void compareStructs( struct gameState *prevGame, struct gameState *postGame, struct checker *infoHolder ){

    if( prevGame->numActions != postGame->numActions ){
        infoHolder->numActionCheck++;
    }

    if( prevGame->coins != postGame->coins ){
        infoHolder->numCoinCheck++;
    }

    if( prevGame->numBuys != postGame->numBuys ){
        infoHolder->numBuysCheck++;
    }

    if( prevGame->playedCardCount != postGame->playedCardCount ){
        infoHolder->numPlayedCardCountCheck++;
    }

    for( int i = 0; i < 27; i++ ){
        if( prevGame->supplyCount[i] != postGame->supplyCount[i] ){
            infoHolder->supplyCardCheck++;
            break;
        }
    }

    for( int i = 0; i < postGame->numPlayers; i++ ){
        if( prevGame->deckCount[i] != postGame->deckCount[i] ){
            infoHolder->deckCountCheck++;
            break;
        }
    }

    for( int i = 0; i < postGame->numPlayers; i++ ){
        if( prevGame->discardCount[i] != postGame->discardCount[i] ){
            infoHolder->deckCountCheck++;
            break;
        }
    }

    for( int i = 0; i < postGame->numPlayers; i++ ){
        int stop = 0;
        if( stop ){
            break;
        }
        for( int j = 0; j < postGame->discardCount[i]; j++ ) {
            if( prevGame->discard[i][j] != postGame->discard[i][j] ){
                infoHolder->discardCheck++;
                break;
            }
        }
    }
    for( int i = 0; i < postGame->numPlayers; i++ ){
        if( prevGame->handCount[i] != postGame->handCount[i] ){
            infoHolder->handCountCheck++;
            break;
        }
    }

    /* for( int i = 0; i < postGame->numPlayers; i++ ){
        int stop = 0;
        if( stop ){
            break;
        }
        for( int j = 0; j < postGame->handCount[i]; j++ ) {
            if( prevGame->hand[i][j] != postGame->hand[i][j] ){
                infoHolder->handCheck;
                break;
            }
        }
    }*/

}

void printResults( int failures, struct checker *infoH ){

    printf( "There were %d total failures\n", failures );
    printf( "In %d iterations of playing the Minion card, the number of actions were incorrect\n", infoH->numActionCheck );
    printf( "In %d iterations of playing the Minion card, the number of coins were incorrect\n", infoH->numCoinCheck );
    printf( "In %d iterations of playing the Minion card, the number of buys were incorrect\n", infoH->numBuysCheck );
    printf( "In %d iterations of playing the Minion card, the played cards were incorrect\n", infoH->numPlayedCardCountCheck );
    printf( "In %d iterations of playing the Minion card, the supply cards were incorrect\n", infoH->supplyCardCheck );
    printf( "In %d iterations of playing the Minion card, the players deck count were incorrect\n", infoH->deckCountCheck );
    printf( "In %d iterations of playing the Minion card, the players discard counts were incorrect\n", infoH->discardCountCheck );
    printf( "In %d iterations of playing the Minion card, the players discard piles were incorrect\n", infoH->discardCheck );
    printf( "In %d iterations of playing the Minion card, the players hands counts were incorrect\n", infoH->handCountCheck );
    //printf( "In %d iterations of playing the Minion card, the players hands were incorrect\n", infoH->handCountCheck );

}

void randomizeGameState( struct gameState *g ){

    g->numActions = rand() % INT_MAX - 10;
    g->coins = rand() % INT_MAX - 10;
    g->numBuys = rand() % INT_MAX - 10;
    g->playedCardCount = rand() % MAX_DECK;

    for( int i = 0; i < 27; i++ ){
        g->supplyCount[i] = rand() % INT_MAX;
        g->embargoTokens[i] = rand() % INT_MAX;
    }
    for( int i = 0; i < g->numPlayers; i++ ){
        g->deckCount[i] = rand() % 20;
    }
    for( int i = 0; i < g->numPlayers; i++ ){
        g->discardCount[i] = rand() % 20;
    }
    for( int i = 0; i < g->numPlayers; i++ ){
        for( int j = 0; j < MAX_DECK; j++ ) {
            g->discard[i][j] = rand() % 27;
        }
    }
    for( int i = 0; i < g->numPlayers; i++ ){
        g->handCount[i] = rand() % MAX_HAND;
    }
    for( int i = 0; i < g->numPlayers; i++ ){
        for( int j = 0; j < g->handCount[i]; j++ ) {
            g->hand[i][j] = rand() % 27;
        }
    }

}

int oracle( int choice1, int choice2, int currentPlayer, int nextPlayer, int *tributeRevealedCards, struct gameState *prevGameState, struct gameState *game, struct checker *holding ){

    int failure = 0;


    if ((prevGameState->discardCount[nextPlayer] + prevGameState->deckCount[nextPlayer]) <= 1){

        if (prevGameState->deckCount[nextPlayer] > 0){
        tributeRevealedCards[0] = prevGameState->deck[nextPlayer][prevGameState->deckCount[nextPlayer]-1];
        prevGameState->deckCount[nextPlayer]--;
        }
        else if (prevGameState->discardCount[nextPlayer] > 0){
        tributeRevealedCards[0] = prevGameState->discard[nextPlayer][prevGameState->discardCount[nextPlayer]-1];
        prevGameState->discardCount[nextPlayer]--;
        }
        else{
        //No Card to Reveal
        }

    } else{

        if (prevGameState->deckCount[nextPlayer] == 0){
        for (int i = 0; i < prevGameState->discardCount[nextPlayer]; i++){
            prevGameState->deck[nextPlayer][i] = prevGameState->discard[nextPlayer][i];//Move to deck
            prevGameState->deckCount[nextPlayer]++;
            prevGameState->discard[nextPlayer][i] = -1;
            prevGameState->discardCount[nextPlayer]--;
        }

        shuffle(nextPlayer,prevGameState);//Shuffle the deck
        } 

        tributeRevealedCards[0] = prevGameState->deck[nextPlayer][prevGameState->deckCount[nextPlayer]-1];
        prevGameState->deck[nextPlayer][prevGameState->deckCount[nextPlayer]--] = -1;
        prevGameState->deckCount[nextPlayer]--;

        tributeRevealedCards[1] = prevGameState->deck[nextPlayer][prevGameState->deckCount[nextPlayer]-1];
        prevGameState->deck[nextPlayer][prevGameState->deckCount[nextPlayer]--] = -1;
        prevGameState->deckCount[nextPlayer]--;

    }    

    if (tributeRevealedCards[0] == tributeRevealedCards[1]){//If we have a duplicate card, just drop one 
        prevGameState->playedCards[prevGameState->playedCardCount] = tributeRevealedCards[1];
        prevGameState->playedCardCount++;
        tributeRevealedCards[1] = -1;
    }

    // Fixed this loop so that it doesn't go out of bounds
    for (int i = 0; i < 2; i ++){
        if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold ){//Treasure cards
        prevGameState->coins += 2;
        }
        else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province 
                        || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall){//Victory Card Found
            drawCard(currentPlayer, prevGameState);
            drawCard(currentPlayer, prevGameState);
        }
        else{//Action Card
        // fixed this so that we check to make sure this wasn't flagged for being a duplicate
        if( tributeRevealedCards[i] != -1 ){
            prevGameState->numActions = prevGameState->numActions + 2;
        }
        }
    }

    int result = memcmp(prevGameState, game, sizeof(struct gameState));
    if( result != 0 ){
        failure = 1;
        compareStructs( prevGameState, game, holding );
    }

    return failure;

}

int main(){

    // Initialize variables here
    int players;
    int kingdomCards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse, sea_hag, tribute, gardens};
    int seed = 2;
    struct gameState prevGameState;
    struct gameState game;
    int result = 0;
    int handPos = 0, bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0;
    int tributeRevealedCards[2] = {-1, -1};
    int failures = 0; 
    struct checker holding = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Seed a random number generator - I don't think this is necessary, but it's good practice 
    srand(time(NULL));

    for( int i = 0; i < 5000; i++ ){

        // Generate a random number of players between 2 and 4
        players = rand() % 2 + 2;

        // Generate random numbers between 0 and 1 for our choice1 variable
        // We do this even though we know that the tribute card doesn't take "choices" 
        // in the same way as the other cards
        choice1 = rand() % 2;
        // And based on that choice, toggle choice2
        if( choice1 == 0 ){
            choice2 = 1;
        } else {
            choice2 = 0;
        }

        // generate two random cards between 1 and 100 (we want to test cards that are outside the boundaries of reasonable, knowing that these should fail)
        // victory cards 1, 2, or 3
        // tresure cards are 4, 5, or 6
        // action cards are everything else

        // clear the game struct
        memset(&game, 23, sizeof(struct gameState));
        memset(&prevGameState, 23, sizeof(struct gameState));
        // Initialize our game
        result = initializeGame( players, kingdomCards, seed, &game );

        // never executing if our discard count + deck count for next player is <=1
        // never executing if our deckcount for our next player is 0

        randomizeGameState( &game );

        // Copy the state of the game before playing the card so we can test it against the state of the game after playing the card
        memcpy( &prevGameState, &game, sizeof( struct gameState ) );

        int currentPlayer = whoseTurn(&game);
        int nextPlayer = currentPlayer + 1;
        if (nextPlayer > (game.numPlayers - 1)){
            nextPlayer = 0;
        }

        // Play the card
        result = cardEffect( tribute, choice1, choice2, choice3, &game, handPos, &bonus );

        failures += oracle( choice1, choice2, currentPlayer, nextPlayer, tributeRevealedCards, &prevGameState, &game, &holding);

    }

    printResults( failures, &holding );


}