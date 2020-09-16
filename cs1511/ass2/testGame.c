// BY Jovanni Tjuandi (z5213864)
// testGame.c

// HEADER
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Card.h"
#include "Game.h"
#include "player.h"

#define STARTING_HAND_SIZE 7
#define NUM_PLAYERS 4

#define NUM_VALUES 16
#define NUM_COLORS 5
#define NUM_SUITS 5

// FUNCTIONS FROM SAMPLE TESTS DECLARATION
static void checkGameState (Game game, int expectedPlayer, int expectedTurn,
     int expectedMoves, int expectedPreviousPlayer, int expectedTopDiscardTurn);
static void printCardByComponents (value v, color c, suit s);

// PLAYER.C FUNCTION DECLARATION TO TEST DECIDEMOVE
static int hand_color (Game game);
playerMove decideMove (Game game);

// HELPER FUNCTIONS DECLARATIONS
static int count_discard (Game game);
static void printf_color (Game game);
static void status_print (Game game);
static void stat_print (Game game);
static void output_statement (Game game, playerMove move);
static void winner (Game game);
static void print_discardPile (Game game);
static void print_drawPile (Game game);

// TEST A HELPERS DECLARATIONS
static Game initA (void);
static void turnA0 (Game game);
static void turnA1 (Game game);
static void turnA2 (Game game);
static void turnA3 (Game game);
static void turnA4 (Game game);
static void turnA5 (Game game);
static void turnA6 (Game game);
static void turnA7 (Game game);
static void turnA8 (Game game);
static void turnA9 (Game game);
static void turnA10 (Game game);
static void Acont_turn (Game game);

// TEST B HELPERS DECLARATIONS
static Game initB (void);
static void turnB0 (Game game);
static void turnB1 (Game game);
static void turnB2 (Game game);
static void turnB3 (Game game);
static void turnB4 (Game game);

// TEST C HELPERS DECLARATIONS
static Game initC (void);
static void turnC0 (Game game);
static void turnC1 (Game game);
static void turnC2 (Game game);

// TEST CASES DECLARATIONS
static void testA (void);
static void testB (void);
static void testC (void);

// MAIN FUNCTION, COMMENT OUT THE ONES NOT TESTED
int main (void) {
    testA ();
    testB ();
    testC ();
}

/*-------------- FUNCTIONS IMPLEMENTATION --------------*/

// TEST CASES
static void testA (void) {
   printf ("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
   printf ("\nTESTING REGULAR GAME WITH A WINNER\n");
   Game game = initA ();
   turnA0 (game);
   turnA1 (game);
   turnA2 (game);
   turnA3 (game);
   turnA4 (game);
   turnA5 (game);
   turnA6 (game);
   turnA7 (game);
   turnA8 (game);
   turnA9 (game);
   turnA10 (game);
   Acont_turn (game);
   destroyGame (game);
   printf ("GAME DESTROYED\n");
   printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
}

static void testB (void) {
    printf ("\nTESTING WHEN DRAWPILE RUNS OUT AND NO ONE WINS\n");
    Game game = initB ();
    turnB0 (game);
    turnB1 (game);
    turnB2 (game);
    turnB3 (game);
    turnB4 (game);
    destroyGame (game);
    printf ("GAME DESTROYED\n");
    printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
}

static void testC (void) {
    printf ("\nTESTING EFFECTS OF CARD A AND GAME UNFINISHED\n");
    Game game = initC();
    turnC0 (game);
    turnC1 (game);
    turnC2 (game);
    destroyGame (game);
    printf ("GAME DESTROYED\n");
    printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
}

// FUNCTIONS FROM SAMPLE TESTS
static void checkGameState (Game game, int expectedPlayer, int expectedTurn,
    int expectedMoves, int expectedPreviousPlayer, int expectedTopDiscardTurn) {

    assert(currentPlayer(game) == expectedPlayer);
    assert(currentTurn(game) == expectedTurn);
    assert(numTurns(game) == expectedTurn + 1);
    assert(currentTurnMoves(game) == expectedMoves);
    assert(getPreviousTurnPlayer(game) == expectedPreviousPlayer);
    assert(getTopDiscardTurnNumber(game) == expectedTopDiscardTurn);
}

static void printCardByComponents (value v, color c, suit s) {
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

// PLAYER.C TO TEST DECIDEMOVE
static int hand_color (Game game) {
   int red = 0;
   int blue = 0;
   int green = 0;
   int yellow = 0;
   int purple = 0;
   
   int count = 0;
   while (count < handCardCount (game)) {
      if (cardColor(handCard (game, count)) == RED) {
         red = red + 1;
      } else if (cardColor(handCard (game, count)) == BLUE) {
         blue = blue + 1;
      } else if (cardColor(handCard (game, count)) == GREEN) {
         green = green + 1;
      } else if (cardColor(handCard (game, count)) == YELLOW) {
         yellow = yellow + 1;
      } else if (cardColor(handCard (game, count)) == PURPLE) {
         purple = purple + 1;
      }
      count = count + 1;
   }
   
   int largest = red;
   int color = RED;
   if (blue > largest) {
      largest = blue;
      color = BLUE;
   }
   if (green > largest) {
      largest = green;
      color = GREEN;
   }
   if (yellow > largest) {
      largest = yellow;
      color = YELLOW;
   }
   if (purple > largest) {
      largest = purple;
      color = PURPLE;
   }
   return color;
}

playerMove decideMove (Game game) {
   playerMove move;
   // if the top card is draw_two
   if (cardValue(topDiscard(game)) == DRAW_TWO) {
      Card counter = NULL;
      int count = 0;
      int found = 0;
      
      while (count < handCardCount(game)) {
         Card current = handCard(game, count);
         if (cardValue(current) == DRAW_TWO) {
            counter = current;
            found = 1;
         }
         count = count + 1;
      }
      
      move.card = counter;
      move.action = PLAY_CARD;
      if (found == 1 && isValidMove(game, move) == 1) {
         return move;
      } else {
         move.action = DRAW_CARD;
         if (isValidMove(game, move) == 1) {
            return move;
         } else {
            move.action = END_TURN;
            return move;         
         }
      }
   } else {
      Card decide = NULL;
      Card top = topDiscard(game);
      int count = 0;
      int found = 0;
      
      while (count < handCardCount(game)) {
         Card current = handCard(game, count);
         
         if (cardColor(current) == getCurrentColor(game) || 
            cardSuit(current) == cardSuit(top) || 
            cardValue(current) == cardValue(top)) {
            
               if(found == 1){
                  if (cardValue(current) >= cardValue(decide)) {
                     decide = current;
                  }
               } else {
                  decide = current;
                  found = 1;
               }
      
         }
         count = count + 1;
      }
      
      if (found == 0) {
         count = 0;
         while (count < handCardCount(game)) {
            Card current = handCard(game, count);
            if (cardValue(current) == ZERO) {
               decide = current;
               found = 1;
            }
            count = count + 1;
         }
      }
      
      move.card = decide;
      move.action = PLAY_CARD;
      if (found == 1 && isValidMove(game, move) == 1) {
         if (cardValue(decide) == D) {
            move.nextColor = hand_color(game);
         }
         return move;
      } else {
         move.action = DRAW_CARD;
         if (isValidMove(game, move) == 1) {
            return move;
         } else {
            move.action = END_TURN;
            return move; 
         }
      }
   }
}

// HELPER FUNCTIONS
// counting cards in discard pile
static int count_discard (Game game) {
   int count = 0;
   while (getDiscardPileCard(game, count) != NULL) {
      count = count + 1;
   }
   return count;
}

// printing color
static void printf_color (Game game) {
    int color = getCurrentColor(game);
    char* colorStrings[NUM_COLORS] = {
        "RED", "BLUE", "GREEN", "YELLOW", "PURPLE"
    };
    printf ("       CurrentColor : %s\n", colorStrings[color]);
}

// printing status at the start of turn
static void status_print (Game game) {
    printf ("****************************************************\n");
    printf ("previous player: %d\n", getPreviousTurnPlayer(game));
    printf ("top discard    : ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), 
    cardSuit(topDiscard(game)));
    printf ("\n");
    printf ("player %d's points   : %d\n", currentPlayer(game), playerPoints(game, 
            currentPlayer(game)));
    printf ("player %d's handSize : %d\n", currentPlayer(game), handCardCount(game));
    printf ("turn %d player %d\n", currentTurn(game), currentPlayer(game));
    printf ("------------------------------------\n");
}

// printing status at the end of turn
static void stat_print (Game game) {
    printf ("-----------------------------------\n");
    printf_color (game);
    printf ("           deckSize : %d\n", numCards(game));
    printf ("        discardSize : %d\n", count_discard(game));
    printf ("        active twos : %d\n", getActiveDrawTwos(game));
    printf ("   top discard turn : %d\n", getTopDiscardTurnNumber(game));
    printf ("  player %d's points : %d\n", getPreviousTurnPlayer(game), 
            playerPoints(game, getPreviousTurnPlayer(game)));
    printf ("player %d's handSize : %d\n", getPreviousTurnPlayer(game), 
            playerCardCount(game, getPreviousTurnPlayer(game)));
}

//printing output statements
static void output_statement (Game game, playerMove move) {
    if (move.action == PLAY_CARD) {
        if (isValidMove(game, move) == 1) {
            printf ("player %d playing ", currentPlayer(game));
            printCardByComponents(cardValue(move.card), cardColor(move.card), 
                cardSuit(move.card));
            printf ("\n");
        } else {
            printf ("player %d can't play ", currentPlayer(game));
            printCardByComponents(cardValue(move.card), cardColor(move.card), 
                cardSuit(move.card));
            printf ("\n");
        }
    } else if (move.action == DRAW_CARD) {
        if (isValidMove(game, move) == 1) {
            printf ("player %d drawing ", currentPlayer(game));
            if (getDeckCard (game, 0) != NULL) {
                printCardByComponents(cardValue(getDeckCard (game, 0)), 
                cardColor(getDeckCard (game, 0)), cardSuit(getDeckCard (game, 0)));
            }
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
// declare winner
static void winner (Game game) {
    if (gameWinner (game)!= NOT_FINISHED) {
        if (gameWinner (game) < NUM_PLAYERS) {
            printf ("player %d WINS!!\n", gameWinner (game));
        } else {
            printf ("NOBODY WINS!!\n");
        }
    } else {
        printf ("NOT FINISHED!!\n");
    }
}
// printing the discardPile
static void print_discardPile (Game game) {
   printf ("-------------------------------------\n");
   printf("The discardPile : \n");
   int i = 0;
   while (getDiscardPileCard(game, i) != NULL) {
      printCardByComponents(cardValue(getDiscardPileCard(game, i)), 
      cardColor(getDiscardPileCard(game, i)), cardSuit(getDiscardPileCard(game, i)));
      printf ("\n");
      i = i + 1;
   }
}

// printing the drawPile
static void print_drawPile (Game game) {
   printf ("-------------------------------------\n");
   printf("The drawPile : \n");
   int i = 0;
   while (getDeckCard(game, i) != NULL) {
      printCardByComponents(cardValue(getDeckCard(game, i)), 
      cardColor(getDeckCard(game, i)), cardSuit(getDeckCard(game, i)));
      printf ("\n");
      i = i + 1;
   }
}

// TEST A HELPERS
// initializing game A
static Game initA (void) {
   int deckSize = 40;
   value values[] = {
      DRAW_TWO, DRAW_TWO, DRAW_TWO, DRAW_TWO, A, A, D, FOUR, 
      D, F, ZERO, NINE, F, ZERO, F, F, 
      ZERO, B, A, A, FOUR, C, ONE, DRAW_TWO, 
      C, NINE, SEVEN, ZERO, C, D, E, F, 
      ZERO, ONE, DRAW_TWO, THREE, FOUR, FIVE, SIX, SEVEN
   };

   color colors[] = {
      RED, BLUE, GREEN, YELLOW, RED, RED, RED, GREEN, 
      GREEN, GREEN, GREEN, YELLOW, RED, YELLOW, YELLOW, RED, 
      RED, YELLOW, PURPLE, RED, RED, PURPLE, BLUE, RED, 
      BLUE, PURPLE, BLUE, BLUE, RED, YELLOW, YELLOW, RED, 
      YELLOW, BLUE, YELLOW, GREEN, YELLOW, RED, YELLOW, GREEN
   };

   suit suits[] = {
      HEARTS, QUESTIONS, SPADES, DIAMONDS, DIAMONDS, QUESTIONS, HEARTS, HEARTS, 
      QUESTIONS, DIAMONDS, QUESTIONS, QUESTIONS, CLUBS, SPADES, HEARTS, CLUBS, 
      QUESTIONS, QUESTIONS, QUESTIONS, DIAMONDS, HEARTS, HEARTS, QUESTIONS, QUESTIONS, 
      CLUBS, CLUBS, CLUBS, DIAMONDS, SPADES, QUESTIONS, HEARTS, DIAMONDS, 
      CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS
   };

   printf ("Initial DeckSize: %d", deckSize);
   return newGame(deckSize, values, colors, suits);
}

//playing normal cards test
static void turnA0(Game game){

    printf("\nCHECKING INITIAL GAME STATE\n");
    checkGameState(game, 0, 0, 0, -1, -1);
    
    printf ("\ntesting if decideMove plays the largest value\n");
    playerMove move;
    Card card;
    
    status_print(game);
    
    // checking player 0 playing
    move = decideMove (game);
    while (move.action != END_TURN){
        if (move.action == PLAY_CARD) {
            printf ("player %d playing ", currentPlayer(game));
            printCardByComponents(cardValue(move.card), cardColor(move.card), 
                cardSuit(move.card));
            printf ("\n");
        } 
        playMove (game, move);
        move = decideMove (game);
    }
    
    assert (cardValue(topDiscard(game)) == F);
    
    checkGameState(game, 0, 0, 1, -1, 0);
    
    if (move.action == END_TURN) {
        printf ("player %d end turn \n", currentPlayer(game));
        playMove (game, move);
        stat_print(game);
    }
    checkGameState(game, 1, 1, 0, 0, 0);
}

// checking zero can play against any top discard 
static void turnA1 (Game game) {
    printf ("\ntesting if zero can play against anything\n");
    playerMove move;
    Card card;
    status_print(game);
    
    // playing a zero card with no similar quality
    move.action = PLAY_CARD;
    card = newCard(ZERO, YELLOW, SPADES);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // ending turn
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    stat_print(game);
}

//checking play only card i have and cannot end turn too soon
static void turnA2 (Game game) {
    printf ("\ntesting that we can't play a card that's not in hand\n");
    printf ("testing that end_turn is invalid with 0 moves a turn\n");
    playerMove move;
    Card card;
    status_print(game);
    
    // playing a card they don't have
    move.action = PLAY_CARD;
    card = newCard(ZERO, YELLOW, SPADES);
    move.card = card;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    // ending turn
    move.action = END_TURN;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    checkGameState(game, 2, 2, 0, 1, 1);
    
    // playing a card with same color
    move.action = PLAY_CARD;
    card = newCard(F, YELLOW, HEARTS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove (game, move);
    
    checkGameState(game, 2, 2, 1, 1, 2);
    
    // ending turn
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    stat_print(game);
    
    checkGameState(game, 3, 3, 0, 2, 2);
}

// checking player can't draw after playing draw two
static void turnA3 (Game game) {
    printf ("\ntesting that we can't draw after playing draw_two\n");
    playerMove move;
    Card card;
    status_print(game);
    
    // playing a draw two
    move.action = PLAY_CARD;
    card = newCard(DRAW_TWO, YELLOW, DIAMONDS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove (game, move);
    
    checkGameState(game, 3, 3, 1, 2, 3);
    assert(getActiveDrawTwos(game) == 1);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    checkGameState(game, 3, 3, 1, 2, 3);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    checkGameState(game, 3, 3, 1, 2, 3);
    
    // ending turn
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    stat_print(game);
    
    checkGameState(game, 0, 4, 0, 3, 3);
}

// checking if can draw or play after putting draw two
static void turnA4 (Game game) {
    printf ("\ntesting that after playing we can't draw or play\n");
    playerMove move;
    Card card;
    status_print(game);
    
    // checking what decideMove wants to do
    move = decideMove (game);
    output_statement (game, move);
    playMove(game, move);
    
    checkGameState(game, 0, 4, 1, 3, 4);
    assert(getActiveDrawTwos(game) == 2);
    assert(cardValue(topDiscard(game)) == 2);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    checkGameState(game, 0, 4, 1, 3, 4);
    
    // trying to play another card
    move.action = PLAY_CARD;
    card = newCard(NINE, YELLOW, QUESTIONS);
    move.card = card;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    checkGameState(game, 0, 4, 1, 3, 4);
    
    // ending turn
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    stat_print(game);
}

// can't play or draw after drawing appropiate cards
static void turnA5 (Game game) {
    printf ("\ntesting that we only draw appropriate cards in a turn\n");
    playerMove move;
    Card card;
    status_print(game);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    checkGameState(game, 1, 5, 1, 0, 4);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    checkGameState(game, 1, 5, 2, 0, 4);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    checkGameState(game, 1, 5, 3, 0, 4);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    checkGameState(game, 1, 5, 4, 0, 4);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    // trying to play
    move.action = PLAY_CARD;
    move.card = newCard(DRAW_TWO, BLUE, QUESTIONS);
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    checkGameState(game, 1, 5, 4, 0, 4);
    
    // ending turn
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    stat_print(game);
}

static void turnA6 (Game game) {
    printf ("\ntesting that active_draw_two resets after someone draws appropriate cards\n");
    playerMove move;
    Card card;
    status_print(game);
    
    assert(getActiveDrawTwos(game) == 0);
    
    // trying to play
    move.action = PLAY_CARD;
    move.card = newCard(DRAW_TWO, GREEN, SPADES);
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    assert(getActiveDrawTwos(game) == 1);
    
    // ending turn
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    stat_print(game);
}

static void turnA7 (Game game) {
    printf ("\ntesting that zero can't play against active two\n");
    playerMove move;
    Card card;
    status_print(game);
    
    // trying to play a zero above active draw two
    move.action = PLAY_CARD;
    move.card = newCard(ZERO, BLUE, DIAMONDS);
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    // trying to play
    move.action = PLAY_CARD;
    move.card = newCard(DRAW_TWO, RED, QUESTIONS);
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // ending turn
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    stat_print(game);
}

static void turnA8 (Game game) {
    printf ("\ntesting decideMove wants to draw the right cards\n");
    playerMove move;
    Card card;
    status_print(game);
    
    // testing decideMove
    move = decideMove (game);
    while (move.action != END_TURN){
        output_statement(game, move);
        playMove (game, move);
        move = decideMove (game);
    }
    
    checkGameState(game, 0, 8, 4, 3, 7);
    
    // ending turn
    if (move.action == END_TURN) {
        printf ("player %d end turn \n", currentPlayer(game));
        playMove (game, move);
        stat_print(game);
        
    }
}

static void turnA9 (Game game) {
    printf ("\ntesting that only appropriate card can be played\n");
    printf ("testing that a card can only be played once in a turn\n");
    playerMove move;
    Card card;
    status_print(game);
    
    // trying to play invalid card
    move.action = PLAY_CARD;
    move.card = newCard(NINE, PURPLE, SPADES);
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    // trying to play
    move.action = PLAY_CARD;
    move.card = newCard(A, RED, QUESTIONS);
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // trying to play the same card
    move.action = PLAY_CARD;
    move.card = newCard(A, RED, QUESTIONS);
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    // ending turn
    move = decideMove(game);
    output_statement (game, move);
    playMove(game, move);
    stat_print(game);
}

static void turnA10 (Game game) {
    printf ("\ntesting that A skips a turn\n");
    playerMove move;
    Card card;
    status_print(game);
    
    // trying to play
    move.action = PLAY_CARD;
    move.card = newCard(A, RED, DIAMONDS);
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    checkGameState(game, 3, 10, 1, 1, 10);
    
    // ending turn
    move = decideMove(game);
    output_statement (game, move);
    playMove(game, move);
    stat_print(game);
    
    checkGameState(game, 1, 11, 0, 3, 10);
}

// the rest of the game until someone wins
static void Acont_turn (Game game) {
    printf ("\ntesting that game continues until someone wins\n");
    playerMove move;
    Card card;
    
    while (gameWinner(game) == NOT_FINISHED) {
        move = decideMove(game);
        while(move.action != END_TURN) {
            status_print(game);
            if (isValidMove (game, move) == 1) {
                output_statement(game, move);
                playMove (game, move);
            } else {
                output_statement(game, move);
            }
            move = decideMove(game);
        }
        if (move.action == END_TURN) {
            output_statement(game, move);
            playMove(game, move);
            stat_print(game);
        }
    }
    
    assert(gameWinner(game) == 3);
    winner (game);
}

// TEST B HELPERS
// initializing game B
static Game initB (void) {
    int deckSize = 30;
    value values[] = {
        DRAW_TWO, DRAW_TWO, DRAW_TWO, DRAW_TWO, A, A, D, FOUR, D, F,
        ZERO, NINE, F, ZERO, F, F, ZERO, B, A, A,
        FOUR, C, ONE, DRAW_TWO, C, NINE, SEVEN, ZERO, DRAW_TWO, A
    };

    color colors[] = {
        RED, BLUE, GREEN, YELLOW, RED, RED, RED, GREEN, GREEN, GREEN,
        GREEN, YELLOW, RED, YELLOW, YELLOW, RED, RED, YELLOW, PURPLE, RED,
        RED, PURPLE, BLUE, RED, BLUE, PURPLE, BLUE, BLUE, RED, RED
    };

    suit suits[] = {
        HEARTS, QUESTIONS, SPADES, DIAMONDS, DIAMONDS, QUESTIONS, HEARTS, HEARTS, QUESTIONS, DIAMONDS,
        QUESTIONS, QUESTIONS, CLUBS, SPADES, HEARTS, CLUBS, QUESTIONS, QUESTIONS, QUESTIONS, DIAMONDS,
        HEARTS, HEARTS, QUESTIONS, QUESTIONS, CLUBS, CLUBS, CLUBS, DIAMONDS, SPADES, CLUBS
    };
    
    printf ("Initial DeckSize: %d", deckSize);
    return newGame(deckSize, values, colors, suits);
}
static void turnB0 (Game game) {
    playerMove move;
    Card card;
    
    printf("\nCHECKING INITIAL GAME STATE\n");
    checkGameState(game, 0, 0, 0, -1, -1);
    assert(numCards(game) == 1);
    
    printf ("\ntesting activedrawtwos when game starts with draw_two\n");
    assert(getActiveDrawTwos(game) == 1);
    status_print(game);
    
    // playing a card
    move.action = PLAY_CARD;
    card = newCard(DRAW_TWO, RED, HEARTS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    assert(getActiveDrawTwos(game) == 2);
    
    // ending turn
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    stat_print(game);
    
    print_drawPile(game);
    print_discardPile(game);
}

static void turnB1 (Game game) {
    playerMove move;
    Card card;
    
    printf ("\ntesting activedrawtwos with draw_two\n");
    status_print(game);
    
    // playing a card
    move.action = PLAY_CARD;
    card = newCard(DRAW_TWO, BLUE, QUESTIONS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    assert(getActiveDrawTwos(game) == 3);
    
    // ending turn
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    stat_print(game);
    
    print_drawPile(game);
    print_discardPile(game);
}

static void turnB2 (Game game) {
    playerMove move;
    Card card;
    
    printf ("\ntriggering what next player moves\n");
    status_print(game);
    
    // playing a card
    move.action = PLAY_CARD;
    card = newCard(DRAW_TWO, GREEN, SPADES);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    assert(getActiveDrawTwos(game) == 4);
    
    // ending turn
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    stat_print(game);
    
    print_drawPile(game);
    print_discardPile(game);
}

static void turnB3 (Game game) {
    playerMove move;
    Card card;
    
    printf ("\ntesting decideMove decision with DRAW_TWO\n");
    status_print(game);
    
    move = decideMove(game);
    while(move.action != END_TURN) {
        if (isValidMove (game, move) == 1) {
            output_statement(game, move);
            playMove (game, move);
        } else {
            output_statement(game, move);
        }
        move = decideMove(game);
    }
    
    assert(cardValue(topDiscard(game)) == DRAW_TWO);
    assert(getActiveDrawTwos(game) == 5);
    
    if (move.action == END_TURN) {
        output_statement(game, move);
        playMove(game, move);
        stat_print(game);
    }
    
    print_drawPile(game);
    print_discardPile(game);
}

static void turnB4 (Game game) {
    playerMove move;
    Card card;
    
    printf ("\ntesting if there's no-winner while player is drawing cards\n");
    printf ("testing activeDrawTwo haven't reset untill appropriate cards drawn\n");
    status_print(game);
    
    move.action = DRAW_CARD;
    printf ("\n");
    output_statement(game, move);
    playMove (game, move);

    int i = 0;
    while (i < 2*getActiveDrawTwos(game) && gameWinner(game) == NOT_FINISHED) {
       print_drawPile(game);
       print_discardPile(game);
       move.action = DRAW_CARD;
       printf ("\n");
       output_statement(game, move);
       playMove (game, move);
    }
    move.action = END_TURN;
    print_drawPile(game);
    print_discardPile(game);
    output_statement(game, move);
    playMove (game, move);
    stat_print(game);
    
    assert(numCards(game) == 0);
    assert(count_discard(game) == 1);
    
    assert(getActiveDrawTwos(game) == 5);
    assert(gameWinner(game) == NO_WINNER);
    winner (game);
}

// TEST C HELPERS
// initializing game C
static Game initC (void) {
    int deckSize = 35;
    value values[] = {
        DRAW_TWO, DRAW_TWO, DRAW_TWO, DRAW_TWO, A, A, D, FOUR, D, F,
        ZERO, NINE, F, ZERO, F, F, ZERO, B, A, A,
        FOUR, C, ONE, DRAW_TWO, C, NINE, SEVEN, A, A, D, F, A, NINE, ONE, B
    };

    color colors[] = {
        RED, BLUE, GREEN, YELLOW, RED, RED, RED, GREEN, GREEN, GREEN,
        GREEN, YELLOW, RED, YELLOW, YELLOW, RED, RED, YELLOW, PURPLE, RED,
        RED, PURPLE, BLUE, RED, BLUE, PURPLE, BLUE, BLUE, RED, YELLOW,
        RED, BLUE, YELLOW, PURPLE, GREEN
    };

    suit suits[] = {
        HEARTS, QUESTIONS, SPADES, DIAMONDS, DIAMONDS, QUESTIONS, HEARTS, HEARTS, QUESTIONS, DIAMONDS,
        QUESTIONS, QUESTIONS, CLUBS, SPADES, HEARTS, CLUBS, QUESTIONS, QUESTIONS, QUESTIONS, DIAMONDS,
        HEARTS, HEARTS, QUESTIONS, QUESTIONS, CLUBS, CLUBS, CLUBS, DIAMONDS, SPADES, QUESTIONS,
        HEARTS, DIAMONDS, QUESTIONS, CLUBS, SPADES
    };
    
    printf ("Initial DeckSize: %d", deckSize);
    return newGame(deckSize, values, colors, suits);
}

static void turnC0(Game game){

    // checking initial state.
    printf("\nCHECKING INITIAL GAME STATE\n");
    checkGameState(game, 1, 0, 0, -1, -1);
    
    printf ("\ntesting if starting discard value is A\n");
    playerMove move;
    Card card;
    
    status_print(game);
    
    // playing another A
    move.action = PLAY_CARD;
    card = newCard(A, RED, QUESTIONS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    checkGameState(game, 1, 0, 1, -1, 0);
    
    move.action = END_TURN;
    printf ("player %d end turn \n", currentPlayer(game));
    playMove (game, move);
    stat_print(game);
        
    checkGameState(game, 3, 1, 0, 1, 0);
    
}

static void turnC1(Game game){
    printf ("\ntesting if next player is skipped\n");
    playerMove move;
    Card card;
    
    checkGameState(game, 3, 1, 0, 1, 0);
    status_print(game);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    checkGameState(game, 3, 1, 1, 1, 0);
    
    // ending turn
    stat_print(game);
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    
    checkGameState(game, 0, 2, 0, 3, 0);
    
}

static void turnC2(Game game){
    printf ("\ntesting this player is not skipped skipped\n");
    playerMove move;
    Card card;
    
    checkGameState(game, 0, 2, 0, 3, 0);
    status_print(game);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    checkGameState(game, 0, 2, 1, 3, 0);
    
    // ending turn
    stat_print(game);
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    
    checkGameState(game, 1, 3, 0, 0, 0);
    
    assert(gameWinner(game) == NOT_FINISHED);
    winner(game);
}
