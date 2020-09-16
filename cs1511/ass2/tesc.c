// testC

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

// I GOT THIS FROM SAMPLE TEST
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

static Game init (void) {
    int deckSize = 30;
    value values[] = {
        DRAW_TWO, DRAW_TWO, DRAW_TWO, DRAW_TWO, A, A, D, FOUR, D, F,
        ZERO, NINE, F, ZERO, F, F, ZERO, B, A, A,
        FOUR, C, ONE, DRAW_TWO, C, NINE, SEVEN, A, A, D
    };

    color colors[] = {
        RED, BLUE, GREEN, YELLOW, RED, RED, RED, GREEN, GREEN, GREEN,
        GREEN, YELLOW, RED, YELLOW, YELLOW, RED, RED, YELLOW, PURPLE, RED,
        RED, PURPLE, BLUE, RED, BLUE, PURPLE, BLUE, BLUE, RED, YELLOW
    };

    suit suits[] = {
        HEARTS, QUESTIONS, SPADES, DIAMONDS, DIAMONDS, QUESTIONS, HEARTS, HEARTS, QUESTIONS, DIAMONDS,
        QUESTIONS, QUESTIONS, CLUBS, SPADES, HEARTS, CLUBS, QUESTIONS, QUESTIONS, QUESTIONS, DIAMONDS,
        HEARTS, HEARTS, QUESTIONS, QUESTIONS, CLUBS, CLUBS, CLUBS, DIAMONDS, SPADES, QUESTIONS
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

// printing status at the end of turn
static void stat_print (Game game) {
    printf ("deckSize: %d\n", numCards(game));
    printf ("discardSize: %d\n", count_discard(game));
    printf ("active twos: %d\n", getActiveDrawTwos(game));
    printf ("top discard turn: %d\n", getTopDiscardTurnNumber(game));
    printf ("player %d's points: %d\n", currentPlayer(game), playerPoints(game, currentPlayer(game)));
    printf ("player %d's handSize: %d\n", currentPlayer(game), handCardCount(game));
}

// printing moves made
static void print_action (playerMove move) {
    if (move.action == PLAY_CARD) {
        printf ("decided to PLAY\n");
    } else if (move.action == DRAW_CARD) {
        printf ("decided to DRAW\n");
    } else {
        printf ("decided to END\n");
    }
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



// printing status after ending turn
static void status_print (Game game) {
    printf ("------------------------\n");
    printf ("turn %d player %d\n", currentTurn(game), currentPlayer(game));
    printf ("previous player: %d\n", getPreviousTurnPlayer(game));
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
}

int main (void) {
   playerMove move;
   Game game = init();
   int count = 0;
   
   while (gameWinner(game) == NOT_FINISHED) {
      status_print (game);
      
      move = decideMove(game);
      while (move.action != END_TURN) {
         print_action(move);
         if (isValidMove (game, move) == TRUE) {
            output_statement (game, move);
            playMove (game, move);
         } else {
            output_statement (game, move);
         }
         move = decideMove(game);
      }
      print_action(move);
      if (move.action == END_TURN) {
         stat_print(game);
         output_statement (game, move);
         playMove(game, move);
      }
      count ++;
   }
   
   // checking the discard pile has only one card
   assert(getDeckCard(game,1) == NULL);
   
   if (gameWinner (game)!= NOT_FINISHED) {
      if (gameWinner (game) < NUM_PLAYERS) {
         printf ("player %d wins\n", gameWinner (game));
      } else {
         printf ("no one won\n");
      }
   }
}
