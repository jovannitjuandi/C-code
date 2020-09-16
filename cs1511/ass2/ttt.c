#include <stdio.h>
#include <assert.h>

#include "Game.h"
#include "Card.h"
#include "player.h"

#define STARTING_HAND_SIZE 7
#define NUM_PLAYERS 4

#define NUM_VALUES 16
#define NUM_COLORS 5
#define NUM_SUITS 5

// ADDITIONAL TEST FUNCTIONS DECLARATION

static void turn0(Game game);
static void test2 (void);
static void turn1(Game game);
static void turn2(Game game);
static void turn3(Game game);
static void turn4(Game game);
static void turn5(Game game);
static void turn6(Game game);
static void turn7(Game game);
static void turn8(Game game);
static void turn9(Game game);
static void turn10(Game game);
static void try_game (Game game);

// functions declarations from sample 1
static void check_initial_PlayerHand(Game game, int player, value values[], color colors[], suit suits[]);
static void check_initial_Deck(Game game, int deck_size, value values[], color colors[], suit suits[]);
static void check_initial_DiscardPile(Game game, int deck_size, value values[], color colors[], suit suits[]);

static int cardIsInHand(Game game, int player, int alreadyMatched[], value v, color c, suit s);
static int cardMatchesComponents(Card card, value v, color c, suit s);
static void printCardByComponents(value v, color c, suit s);

static void test1_init_deck_hands(void);


// functions declarations from sample 2
static Card findCardInHand(Game game, int player, value v, color c, suit s);
static Card findCardInDeck(Game game, value v, color c, suit s);
static void checkGameState(Game game, int expectedPlayer, int expectedTurn,
    int expectedMoves, int expectedPreviousPlayer, int expectedTopDiscardTurn);
static void checkTopDiscard(Game game, Card card);
static void test1_play_basic_hands(void);

int main (void){

     test1_init_deck_hands();
     test2();

return 0;
}

/*  ----------------------------------------
        ... Test functions below ...
*/

// ADDITIONAL TEST FUNCTIONS

static void try_game (Game game) {
    playerMove move;
    Card card;
    printf ("turn %d: \n", currentTurn(game));
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    printf ("a\n");
    move = decideMove (game);
    while (move.action != END_TURN){
        if (move.action == PLAY_CARD) {
            printf ("player %d playing ", currentPlayer(game));
            printCardByComponents(cardValue(move.card), cardColor(move.card), cardSuit(move.card));
            printf ("\n");
            printf ("b\n");
        } else if (move.action == DRAW_CARD) {
            printf ("player %d drawing \n", currentPlayer(game));
            printf ("c\n");
        }
        printf ("c.0\n");
        playMove (game, move);
        printf ("c.1\n");
        move = decideMove (game); // error at 17
        printf ("d\n");
        printf ("player %d move.action %d \n", currentPlayer(game), move.action);
    }
    if (move.action == END_TURN) {
        playMove (game, move);
        printf ("e\n");
    }
    printf ("decksize = %d\n", numCards(game));
    printf ("handCardCount = %d\n", handCardCount(game));
    printf ("f\n");
}

static void test2 (void) {
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
    
    Game game = newGame(deckSize, values, colors, suits);
    
    int j = 0;
    while (gameWinner(game) == NOT_FINISHED && j <= 25){
        printf ("\n");
        try_game(game);
        printf ("twoactive = %d\n", getActiveDrawTwos(game));
        j = j + 1;
    }
    printf ("decksize = %d\n", numCards(game));
    
}

static void turn0(Game game){
    playerMove move;
    Card card;

    // Let's check the initial state.
    printf("Checking the game state\n");
    checkGameState(game, 0, 0, 0, -1, -1);
    
    // top discard is 
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
        playMove (game, move);
    }
    checkGameState(game, 1, 1, 0, 0, 0);
}

static void turn1(Game game){
    playerMove move;
    Card card;

    // Let's check the initial state.
    printf("Checking the game state\n");
    checkGameState(game, 1, 1, 0, 0, 0);
    
    // top discard is 
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    
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
        playMove (game, move);
    }
    checkGameState(game, 2, 2, 0, 1, 1);
}

static void turn2(Game game){
    playerMove move;
    Card card;

    // Let's check the initial state.
    printf("Checking the game state\n");
    checkGameState(game, 2, 2, 0, 1, 1);
    
    // top discard is 
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    
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
        playMove (game, move);
    }
    checkGameState(game, 3, 3, 0, 2, 2);
}

static void turn3(Game game){
    playerMove move;
    Card card;

    // Let's check the initial state.
    printf("Checking the game state\n");
    checkGameState(game, 3, 3, 0, 2, 2);
    
    // top discard is 
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    
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
        playMove (game, move);
    }
    checkGameState(game, 0, 4, 0, 3, 3);
}

static void turn4(Game game){
    playerMove move;
    Card card;

    // Let's check the initial state.
    printf("Checking the game state\n");
    checkGameState(game, 0, 4, 0, 3, 3);
    
    // top discard is 
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    
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
        playMove (game, move);
    }
    checkGameState(game, 1, 5, 0, 0, 4);
}

static void turn5(Game game){
    playerMove move;
    Card card;

    // Let's check the initial state.
    printf("Checking the game state\n");
    checkGameState(game, 1, 5, 0, 0, 4);
    
    // top discard is 
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    
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
        playMove (game, move);
    }
    checkGameState(game, 2, 6, 0, 1, 5);
}

static void turn6(Game game){
    playerMove move;
    Card card;

    // Let's check the initial state.
    printf("Checking the game state\n");
    checkGameState(game, 2, 6, 0, 1, 5);
    
    // top discard is 
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    
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
        playMove (game, move);
    }
}

static void turn7(Game game){
    playerMove move;
    Card card;

    // Let's check the initial state.
    
    // top discard is 
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    
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
        playMove (game, move);
    }
}

static void turn9(Game game){
    playerMove move;
    Card card;

    // Let's check the initial state.
    
    
    // top discard is 
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    
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
        playMove (game, move);
    }
}

static void turn10(Game game){
    playerMove move;
    Card card;

    // Let's check the initial state.
    
    
    // top discard is 
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    
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
        playMove (game, move);
    }
}

static void turn8(Game game){
    playerMove move;
    Card card;

    // Let's check the initial state.
    
    
    // top discard is 
    printf ("top discard: ");
    printCardByComponents(cardValue(topDiscard(game)), cardColor(topDiscard(game)), cardSuit(topDiscard(game)));
    printf ("\n");
    
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
        playMove (game, move);
    }
}
// functions from sample 1
static void test1_init_deck_hands(void){
    int deck_size = 50;
    value values[] = {
        ZERO, ONE, DRAW_TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
        A, B, C, D, E, F, ZERO, ONE, DRAW_TWO, THREE,
        FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, A, B, C, D,
        E, F, ZERO, ONE, DRAW_TWO, THREE, FOUR, FIVE, SIX, SEVEN,
        EIGHT, NINE, A, B, C, D, E, F, ZERO, ONE
    };

    color colors[] = {
        RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,
        BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
        GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
        YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
        PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE
    };

    suit suits[] = {
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS,
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS,
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS,
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS,
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS
    };

    Game game = newGame(deck_size, values, colors, suits);

    printf("Checking if current player is 0\n\n");
    assert(currentPlayer(game) == 0);

    printf("Checking if current turn is 0\n\n");
    assert(currentTurn(game) == 0);

    printf("Checking if number of turns is 1\n\n");
    assert(numTurns(game) == 1);

    printf("Checking if current moves in turn is 0\n\n");
    assert(currentTurnMoves(game) == 0);

    printf("Checking if player from previous turn is -1\n\n");
    assert(getPreviousTurnPlayer(game) == -1);

    printf("Checking if top of discard pile was played in turn -1\n\n");
    assert(getTopDiscardTurnNumber(game) == -1);

    check_initial_Deck(game, deck_size, values, colors, suits);
    printf("\n");

    check_initial_DiscardPile(game, deck_size, values, colors, suits);
    printf("\n");

    check_initial_PlayerHand(game, 0, values, colors, suits);
    printf("\n");

    check_initial_PlayerHand(game, 1, values, colors, suits);
    printf("\n");

    check_initial_PlayerHand(game, 2, values, colors, suits);
    printf("\n");

    check_initial_PlayerHand(game, 3, values, colors, suits);
    printf("\n");


    printf("Trying to destroy the game\n\n");
    destroyGame(game);

    printf("initial testing PASS!\n");

}

/*  ----------------------------------------
        ... Helper functions below ...
*/

static void check_initial_Deck(Game game, int deck_size, value values[], color colors[], suit suits[]){

    int deckStart = NUM_PLAYERS * STARTING_HAND_SIZE + 1;
    int expectedCards = deck_size - NUM_PLAYERS * STARTING_HAND_SIZE - 1;

    int i = 0;
    Card card = getDeckCard(game, i);
    while (card != NULL && i < expectedCards){
        int originalDeckIndex = deckStart + i;

        int v = values[originalDeckIndex];
        int c = colors[originalDeckIndex];
        int s = suits[originalDeckIndex];

        printf("Checking card %d in deck is ", i);
        printCardByComponents(v, c, s);
        printf("\n");

        assert(cardMatchesComponents(card, v, c, s));

        i += 1;
        card = getDeckCard(game, i);
    }

    printf("Checking the deck has %d cards\n", expectedCards);
    assert(i == expectedCards);
}

static void check_initial_DiscardPile(Game game, int deck_size, value values[], color colors[], suit suits[]){
    Card card;
    int firstCard = NUM_PLAYERS * STARTING_HAND_SIZE;

    printf("Checking top of discard pile is ");
    printCardByComponents(values[firstCard], colors[firstCard], suits[firstCard]);
    printf("\n");

    card = getDiscardPileCard(game, 0);
    assert(cardMatchesComponents(card, values[firstCard], colors[firstCard], suits[firstCard]));

    printf("Checking there are no other cards in the discard pile\n");

    card = getDiscardPileCard(game, 1);
    assert(card == NULL);
}


static void check_initial_PlayerHand(Game game, int player, value values[], color colors[], suit suits[]){
    int originalDeck_index = player;

    // Array to keep track of the index of cards in a player's hand we've already
    // matched against
    int alreadyMatched[STARTING_HAND_SIZE];
    int i = 0;
    while (i < STARTING_HAND_SIZE){
        alreadyMatched[i] = FALSE;
        i = i + 1;
    }

    int k = 0;
    while(k < STARTING_HAND_SIZE){

        int v = values[originalDeck_index];
        int c = colors[originalDeck_index];
        int s = suits [originalDeck_index];
        originalDeck_index = originalDeck_index + NUM_PLAYERS;

        printf("\n---------- ----------------- ------------ \n");
        printf("Checking card ");
        printCardByComponents(v, c, s);
        printf(" is in player %d's hand\n", player);

        assert(cardIsInHand(game, player, alreadyMatched, v, c, s));
        k = k + 1;
    }

    Card card = getHandCard(game, player, STARTING_HAND_SIZE);
    assert( card == NULL );

    printf("Finish checking hand for player %d , OK. ", player);

}


static int cardIsInHand(Game game, int player, int alreadyMatched[], value v, color c, suit s){
    int i = 0;
    Card card = getHandCard(game, player, i);
    while (card != NULL){
        if (cardMatchesComponents(card, v, c, s) && !alreadyMatched[i]){
            alreadyMatched[i] = TRUE;
            return TRUE;
        }

        i++;
        card = getHandCard(game, player, i);
    }

    return FALSE;
}

static int cardMatchesComponents(Card card, value v, color c, suit s){
    return cardValue(card) == v && cardColor(card) == c && cardSuit(card) == s;
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

// functions from sample 2
static void checkTopDiscard(Game game, Card card){
    assert(getDiscardPileCard(game, 0) == card);
}

static Card findCardInHand(Game game, int player, value v, color c, suit s){
    int i = 0;
    Card card = getHandCard(game, player, i);
    while (card != NULL){
        if (cardMatchesComponents(card, v, c, s)){
            return card;
        }

        i++;
        card = getHandCard(game, player, i);
    }

    return NULL;
}

static Card findCardInDeck(Game game, value v, color c, suit s){
    int i = 0;
    Card card = getDeckCard(game, i);
    while (card != NULL){
        if (cardMatchesComponents(card, v, c, s)){
            return card;
        }

        i++;
        card = getDeckCard(game, i);
    }

    return NULL;
}

static void checkGameState(Game game, int expectedPlayer, int expectedTurn,
        int expectedMoves, int expectedPreviousPlayer, int expectedTopDiscardTurn){

    assert(currentPlayer(game) == expectedPlayer);
    assert(currentTurn(game) == expectedTurn);
    assert(numTurns(game) == expectedTurn + 1);
    assert(currentTurnMoves(game) == expectedMoves);
    assert(getPreviousTurnPlayer(game) == expectedPreviousPlayer);
    assert(getTopDiscardTurnNumber(game) == expectedTopDiscardTurn);
}
