// HEADER
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "player.h"
#include "Card.h"

#define STARTING_HAND_SIZE 7
#define NUM_PLAYERS 4

#define NUM_VALUES 16
#define NUM_COLORS 5
#define NUM_SUITS 5

// FUNCTIONS FROM SAMPLE TESTS
static void checkGameState(Game game, int expectedPlayer, int expectedTurn,
        int expectedMoves, int expectedPreviousPlayer, int expectedTopDiscardTurn){

    assert(currentPlayer(game) == expectedPlayer);
    assert(currentTurn(game) == expectedTurn);
    assert(numTurns(game) == expectedTurn + 1);
    assert(currentTurnMoves(game) == expectedMoves);
    assert(getPreviousTurnPlayer(game) == expectedPreviousPlayer);
    assert(getTopDiscardTurnNumber(game) == expectedTopDiscardTurn);
}

static void printCardByComponents(value v, color c, suit s){
    char* valueStrings[NUM_VALUES] = {
        "ZERO", "ONE", "DRAW_TWO", "THREE", "FOUR",
        "FIVE", "SIX", "SEVEN", "EIGHT", "NINE",
        "A", "B", "C", "D", "E", "F"
    };

    char* colorStrings[NUM_COLORS] = {
        "RED", "BLUE", "GREEN", "YELLOW", "PURPLE"
    };

    char* suitStrings[NUM_SUITS] = {
        "HEARTS", "DIAMONDS", "CLUBS", "SPADES", "QUESTIONS"
    };

    printf("%s %s of %s", colorStrings[c], valueStrings[v], suitStrings[s]);
}

// HELPER FUNCTIONS
// initializing game
static Game init1 (void) {
    int deckSize = 50;
    value values[] = {
        DRAW_TWO, DRAW_TWO, DRAW_TWO, DRAW_TWO, A, A, D, FOUR, D, F,
        ZERO, NINE, F, ZERO, F, F, ZERO, B, A, A,
        FOUR, C, ONE, DRAW_TWO, C, NINE, SEVEN, ZERO, C, D,
        E, F, ZERO, ONE, DRAW_TWO, THREE, FOUR, FIVE, SIX, SEVEN,
        EIGHT, NINE, A, B, C, D, E, F, ZERO, ONE
    };

    color colors[] = {
        RED, BLUE, GREEN, YELLOW, RED, RED, RED, GREEN, GREEN, GREEN,
        GREEN, YELLOW, RED, YELLOW, YELLOW, RED, RED, YELLOW, PURPLE, RED,
        RED, PURPLE, BLUE, RED, BLUE, PURPLE, BLUE, BLUE, RED, YELLOW,
        YELLOW, RED, YELLOW, BLUE, YELLOW, GREEN, YELLOW, RED, YELLOW, GREEN,
        RED, PURPLE, PURPLE, BLUE, PURPLE, PURPLE, GREEN, PURPLE, PURPLE, GREEN
    };

    suit suits[] = {
        HEARTS, QUESTIONS, SPADES, DIAMONDS, DIAMONDS, QUESTIONS, HEARTS, HEARTS, QUESTIONS, DIAMONDS,
        QUESTIONS, QUESTIONS, CLUBS, SPADES, HEARTS, CLUBS, QUESTIONS, QUESTIONS, QUESTIONS, DIAMONDS,
        HEARTS, HEARTS, QUESTIONS, QUESTIONS, CLUBS, CLUBS, CLUBS, DIAMONDS, SPADES, QUESTIONS,
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS,
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS
    };
    
    return newGame(deckSize, values, colors, suits);
}

// counting cards in discard pile
static int count_discard (Game game) {
   int count = 0;
   while (getDiscardPileCard(game, count) != NULL) {
      count = count + 1;
   }
   return count;
}

// check stats
static void check_stat (Game game, int ex_decksize, int ex_discardsize, int ex_active, int ex_hand) {
   assert(numCards(game) == ex_decksize);
   assert(count_discard(game) == ex_discard);
   assert(getActiveDrawTwos(game) == ex_active);
   assert(handCardCount(game) == ex_hand);
}

// printing color
static void prints_color (Game game) {
    int color = getCurrentColor(game);
    char* colorStrings[NUM_COLORS] = {
        "RED", "BLUE", "GREEN", "YELLOW", "PURPLE"
    };
    printf ("CurrentColor: %s\n", colorStrings[color]);
}

// printing status at the start of turn
static void status_print (Game game) {
    printf ("*************************************************************\n");
    printf ("previous player: %d\n", getPreviousTurnPlayer(game));
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    printf ("turn %d player %d\n", currentTurn(game), currentPlayer(game));
}

// printing status at the end of turn
static void stat_print (Game game) {
    printf ("-------------------------------------\n");
    prints_color (game);
    printf ("deckSize: %d\n", numCards(game));
    printf ("discardSize: %d\n", count_discard(game));
    printf ("active twos: %d\n", getActiveDrawTwos(game));
    printf ("top discard turn: %d\n", getTopDiscardTurnNumber(game));
    printf ("player %d's points: %d\n", currentPlayer(game), playerPoints(game, currentPlayer(game)));
    printf ("player %d's handSize: %d\n", currentPlayer(game), handCardCount(game));
}

//printing output statements
static void output_statement (Game game, playerMove move) {
    if (move.action == PLAY_CARD) {
        if (isValidMove(game, move) == 1) {
            printf ("player %d playing ", currentPlayer(game));
            printCardByComponents(cardValue(move.card), cardColor(move.card), cardSuit(move.card));
            printf ("\n");
        } else {
            printf ("player %d can't play ", currentPlayer(game));
            printCardByComponents(cardValue(move.card), cardColor(move.card), cardSuit(move.card));
            printf ("\n");
        }
    } else if (move.action == DRAW_CARD) {
        if (isValidMove(game, move) == 1) {
            printf ("player %d drawing ", currentPlayer(game));
            printCardByComponents(cardValue(getDeckCard (game, 0)), cardColor(getDeckCard (game, 0)), cardSuit(getDeckCard (game, 0)));
            printf ("\n");
        } else {
            printf ("player %d can't draw ", currentPlayer(game));
            printf ("\n");
        }
    } else {
        if (isValidMove(game, move) == 1) {
            printf ("player %d end turn ", currentPlayer(game));
            printf ("\n");
        } else {
            printf ("player %d can't end turn ", currentPlayer(game));
            printf ("\n");
        }
    }
}
