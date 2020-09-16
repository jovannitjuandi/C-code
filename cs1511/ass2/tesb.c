// testB

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
            //printCardByComponents(cardValue(getDeckCard (game, 0)), cardColor(getDeckCard (game, 0)), cardSuit(getDeckCard (game, 0)));
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

//printing status before ending turn
static void stat_print (Game game) {
    printf ("deckSize: %d\n", numCards(game));
    printf ("active twos: %d\n", getActiveDrawTwos(game));
    printf ("top discard turn: %d\n", getTopDiscardTurnNumber(game));
    printf ("player %d's points: %d\n", currentPlayer(game), playerPoints(game, currentPlayer(game)));
    printf ("player %d's handSize: %d\n", currentPlayer(game), handCardCount(game));
}

// printing status after ending turn
static void status_print (Game game) {
    printf ("------------------------\n");
    printf ("previous player: %d\n", getPreviousTurnPlayer(game));
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    printf ("turn %d player %d\n", currentTurn(game), currentPlayer(game));
}

static Game init (void) {
    int deckSize = 29;
    value values[] = {
        DRAW_TWO, DRAW_TWO, DRAW_TWO, DRAW_TWO, A, A, D, FOUR, D, F,
        ZERO, NINE, F, ZERO, F, F, ZERO, B, A, A,
        FOUR, C, ONE, DRAW_TWO, C, NINE, SEVEN, ZERO, DRAW_TWO
    };

    color colors[] = {
        RED, BLUE, GREEN, YELLOW, RED, RED, RED, GREEN, GREEN, GREEN,
        GREEN, YELLOW, RED, YELLOW, YELLOW, RED, RED, YELLOW, PURPLE, RED,
        RED, PURPLE, BLUE, RED, BLUE, PURPLE, BLUE, BLUE, RED
    };

    suit suits[] = {
        HEARTS, QUESTIONS, SPADES, DIAMONDS, DIAMONDS, QUESTIONS, HEARTS, HEARTS, QUESTIONS, DIAMONDS,
        QUESTIONS, QUESTIONS, CLUBS, SPADES, HEARTS, CLUBS, QUESTIONS, QUESTIONS, QUESTIONS, DIAMONDS,
        HEARTS, HEARTS, QUESTIONS, QUESTIONS, CLUBS, CLUBS, CLUBS, DIAMONDS, SPADES
    };
    
    return newGame(deckSize, values, colors, suits);
}

static void print_discardPile (Game game) {
   printf("The discardPile : \n");
   int i = 0;
   while (getDiscardPileCard(game, i) != NULL) {
      printCardByComponents(cardValue(getDiscardPileCard(game, i)), cardColor(getDiscardPileCard(game, i)), cardSuit(getDiscardPileCard(game, i)));
      printf ("\n");
      i = i + 1;
   }
}

static void print_drawPile (Game game) {
   printf("The drawPile : \n");
   int i = 0;
   while (getDeckCard(game, i) != NULL) {
      printCardByComponents(cardValue(getDeckCard(game, i)), cardColor(getDeckCard(game, i)), cardSuit(getDeckCard(game, i)));
      printf ("\n");
      i = i + 1;
   }
}

static void turn0 (Game game) {
    playerMove move;
    Card card;
    
    // playing a card
    move.action = PLAY_CARD;
    card = newCard(DRAW_TWO, RED, HEARTS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // ending turn
    stat_print(game);
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
}

static void turn1 (Game game) {
    playerMove move;
    Card card;
    
    // playing a card
    move.action = PLAY_CARD;
    card = newCard(DRAW_TWO, BLUE, QUESTIONS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // ending turn
    stat_print(game);
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
}

static void turn2 (Game game) {
    playerMove move;
    Card card;
    
    // playing a card
    move.action = PLAY_CARD;
    card = newCard(DRAW_TWO, GREEN, SPADES);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // ending turn
    stat_print(game);
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
}

static void turn3 (Game game) {
    playerMove move;
    Card card;
    
    // testing decideMove
    move = decideMove (game);
    while (move.action != END_TURN){
        output_statement(game, move);
        playMove (game, move);
        move = decideMove (game);
    }
    
    // ending turn
    if (move.action == END_TURN) {
        stat_print(game);
        printf ("player %d end turn \n", currentPlayer(game));
        playMove (game, move);
        
    }
}

static void turn4 (Game game) {
    playerMove move;
    Card card;
    
    print_drawPile(game);
    print_discardPile(game);
    // drawing empty deck
    move.action = DRAW_CARD;
    output_statement(game, move);
    playMove (game, move);
    print_drawPile(game);
    print_discardPile(game);
       
    int i = 0;
    while (i < 2*getActiveDrawTwos(game) && gameWinner(game) == NOT_FINISHED) {
       // drawing empty deck
       move.action = DRAW_CARD;
       output_statement(game, move);
       playMove (game, move);
       printf ("deckSize: %d\n", numCards(game));
    }
    // ending turn
    move.action = END_TURN;
    stat_print(game);
    printf ("player %d end turn \n", currentPlayer(game));
    playMove (game, move);
    
    /*playerMove move;
    Card card;
    
    // testing decideMove
    move = decideMove (game);
    while (move.action != END_TURN){
        output_statement(game, move);
        playMove (game, move);
        move = decideMove (game);
    }
    
    // ending turn
    if (move.action == END_TURN) {
        stat_print(game);
        printf ("player %d end turn \n", currentPlayer(game));
        playMove (game, move);
        
    }*/
}

static void test_reshuffle (void) {
   Game game = init ();
   assert(getDeckCard(game, 0) == NULL);
   print_drawPile(game);
   print_discardPile(game);
   printf ("TOP DISCARD: ");
   printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
   printf ("\nactive twos: %d\n", getActiveDrawTwos(game));
   printf ("************************STARTING***********************\n\n");
   
   turn0 (game);
   print_drawPile(game);
   print_discardPile(game);
   
   printf ("***********************************************\n\n");
   turn1 (game);
   print_drawPile(game);
   print_discardPile(game);
   
   printf ("***********************************************\n\n");
   turn2 (game);
   print_drawPile(game);
   print_discardPile(game);
   
   printf ("***********************************************\n\n");
   turn3 (game);
   print_drawPile(game);
   print_discardPile(game);
   
   printf ("***********************************************\n\n");
   turn4 (game);
   print_drawPile(game);
   print_discardPile(game);
   
   if (gameWinner (game)!= NOT_FINISHED) {
      if (gameWinner (game) < NUM_PLAYERS) {
         printf ("player %d wins\n", gameWinner (game));
      } else {
         printf ("no one won\n");
      }
   }
}

int main (void) {
   test_reshuffle();
}
