//testGame.c

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
//playing normal cards test
static void turn0(Game game){
    playerMove move;
    Card card;

    // checking initial state.
    printf("Checking the game state\n");
    checkGameState(game, 0, 0, 0, -1, -1);
    
    // initial top discard should be 
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    
    // checking player 0 playing
    move = decideMove (game);
    while (move.action != END_TURN){
        if (move.action == PLAY_CARD) {
            printf ("player %d playing ", currentPlayer(game));
            printCardByComponents(cardValue(move.card), cardColor(move.card), cardSuit(move.card));
            printf ("\n");
        }
        playMove (game, move);
        move = decideMove (game);
    }
    if (move.action == END_TURN) {
        stat_print(game);
        printf ("player %d end turn \n", currentPlayer(game));
        playMove (game, move);
        status_print(game);
        
    }
    checkGameState(game, 1, 1, 0, 0, 0);
}
// checking zero can play against any top discard 
static void turn1 (Game game) {
    playerMove move;
    Card card;
    
    // playing a zero card with no similar quality
    move.action = PLAY_CARD;
    card = newCard(ZERO, YELLOW, SPADES);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // ending turn
    stat_print(game);
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    status_print(game);
}

//checking play only card i have and cannot end turn too soon
static void turn2 (Game game) {
    playerMove move;
    Card card;
    
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
    
    // playing a card with same color
    move.action = PLAY_CARD;
    card = newCard(F, YELLOW, HEARTS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove (game, move);
    
    // ending turn
    stat_print(game);
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    status_print(game);
}

// checking player can't draw after playing draw two
static void turn3 (Game game) {
    playerMove move;
    Card card;
    
    // playing a draw two
    move.action = PLAY_CARD;
    card = newCard(DRAW_TWO, YELLOW, DIAMONDS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove (game, move);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    // ending turn
    stat_print(game);
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    status_print(game);
}

// checking if can draw or play after putting draw two
static void turn4 (Game game) {
    playerMove move;
    Card card;
    
    // checking what decideMove wants to do
    move = decideMove (game);
    output_statement (game, move);
    playMove(game, move);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    // trying to play another card
    move.action = PLAY_CARD;
    card = newCard(NINE, YELLOW, QUESTIONS);
    move.card = card;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    // ending turn
    stat_print(game);
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    status_print(game);
}

static void turn5 (Game game) {
    playerMove move;
    Card card;
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // trying to draw
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    // trying to play
    move.action = PLAY_CARD;
    move.card = newCard(DRAW_TWO, BLUE, QUESTIONS);
    assert(isValidMove(game, move) == FALSE);
    output_statement (game, move);
    
    // ending turn
    stat_print(game);
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    status_print(game);
}

static void turn6 (Game game) {
    playerMove move;
    Card card;
    
    // trying to play
    move.action = PLAY_CARD;
    move.card = newCard(DRAW_TWO, GREEN, SPADES);
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // ending turn
    stat_print(game);
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    status_print(game);
}

static void turn7 (Game game) {
    playerMove move;
    Card card;
    
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
    stat_print(game);
    move.action = END_TURN;
    output_statement (game, move);
    playMove(game, move);
    status_print(game);
}

static void turn8 (Game game) {
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
        status_print(game);
        
    }
}

static void turn9 (Game game) {
    playerMove move;
    Card card;
    
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
    stat_print(game);
    move = decideMove(game);
    output_statement (game, move);
    playMove(game, move);
    status_print(game);
}

static void turn10 (Game game) {
    playerMove move;
    Card card;
    
    // trying to play
    move.action = PLAY_CARD;
    move.card = newCard(A, RED, DIAMONDS);
    assert(isValidMove(game, move) == TRUE);
    output_statement (game, move);
    playMove(game, move);
    
    // ending turn
    stat_print(game);
    move = decideMove(game);
    output_statement (game, move);
    playMove(game, move);
    status_print(game);
}

static void cont_turn (Game game) {
    playerMove move;
    Card card;
    
    while (gameWinner(game) == NOT_FINISHED) {
        move = decideMove(game);
        while(move.action != END_TURN) {
            print_action (move);
            if (isValidMove (game, move) == 1) {
                output_statement(game, move);
                playMove (game, move);
            } else {
                output_statement(game, move);
            }
            move = decideMove(game);
        }
        if (move.action == END_TURN) {
            stat_print(game);
            playMove(game, move);
            status_print(game);
        }
    }
    
    if (gameWinner (game)!= NOT_FINISHED) {
      if (gameWinner (game) < NUM_PLAYERS) {
         printf ("player %d wins\n", gameWinner (game));
      } else {
         printf ("no one won\n");
      }
   }
}

int main (void) {
      Game game = init();
      turn0(game);
      turn1(game);
      turn2(game);
      turn3(game);
      turn4(game);
      turn5(game);
      turn6(game);
      turn7(game);
      turn8(game);
      turn9(game);
      turn10(game);
      cont_turn(game);
}
