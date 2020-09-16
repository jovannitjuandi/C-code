// By Jovanni Tjuandi (z5213864)
// Game.c

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "Game.h"

#define HAND_CARD 7

typedef struct cardlist {
   Card card;
   struct cardlist *next;
} cardlist;

typedef struct player {
   int point;
   int moves;
   int card_play;
   int card_draw;
   cardlist *hand_list;
} player;

struct _game {
   color color;
   int current_turn;
   int current_player;
   int prev_player;
   cardlist *draw_pile;
   cardlist *discard_pile;
   int top_discard_turn;
   player player[NUM_PLAYERS];
   int deck_size;
   int winner;
   int twos;
};

// HELPER FUNCTION DECLARATIONS
static int deck_size (cardlist *head);
static cardlist *add_cardlist (Card add_card, cardlist *head);
static int check_same_card (Card first, Card second);
static int check_valid_card (Game game, playerMove move);
static int valid_draw (Game game, playerMove move);
static int valid_play (Game game, playerMove move);
static int valid_end (Game game, playerMove move);
static void playMove_draw (Game game, playerMove move);
static void playMove_play (Game game, playerMove move);
static void playMove_end (Game game, playerMove move);
static void discard_to_draw (Game game);


Game newGame(int deckSize, value values[], color colors[], suit suits[]) {
   Game game = calloc(1, sizeof(struct _game));

   // INITIALIZE DRAW_PILE
   int count = deckSize - 1;
   cardlist *head = NULL;

   game->draw_pile = NULL;

   while (count > 28) {
      Card new_card = newCard (values[count], colors[count], suits[count]);
      head = add_cardlist(new_card, head);
      count = count - 1;
   }

   game -> draw_pile = head;

   // INITIALIZE DISCARD_PILE
   head = NULL;
   count = 28;
   if (count == 28) {
      Card first_discard = newCard (values[count], colors[count], suits[count]);
      head = add_cardlist (first_discard, head);
   }
   game -> discard_pile = head;

   // INITIALIZE STATUS
   game -> current_turn = 0;
   game -> deck_size = deckSize;
   game -> top_discard_turn = -1;
   game -> prev_player = -1;
   game -> winner = NOT_FINISHED;
   if (cardValue(topDiscard(game)) == DRAW_TWO) {
      game -> twos = 1;
   } else {
      game -> twos = 0;
   }
   if (cardValue(topDiscard(game)) == A) {
      game -> current_player = 1;
   } else {
      game -> current_player = 0;
   }

   // INITIALIZE PLAYERS
   int i = 0;
   while (i < NUM_PLAYERS) {
      game->player[i].hand_list = NULL;
      game->player[i].point = 0;
      game->player[i].moves = 0;
      game->player[i].card_play = 0;
      game->player[i].card_draw = 0;
      i = i + 1;
   }
   
   // INITIALIZE PLAYER'S HANDS
   head = NULL;
   count = 27;
   while (count >= 0) {
      int player_num = count % NUM_PLAYERS;
      Card new = newCard (values[count], colors[count], suits[count]);
      game->player[player_num].hand_list = add_cardlist (new, game->player[player_num].hand_list);
      count = count - 1;
   }

   return game;
}

void destroyGame(Game game) {
   free(game);
}

int numCards(Game game) {
   cardlist *head = game -> draw_pile;
   int number_cards = 0;
   while (head != NULL) {
      number_cards = number_cards + 1;
      head = head -> next;
   }
   return number_cards;
}

int numOfSuit(Game game, suit suit) {
   cardlist *head = game -> draw_pile;
   int num_suit = 0;
   while (head != NULL) {
      if (cardSuit(head -> card) == suit) {
         num_suit = num_suit + 1;
      }
      head = head -> next;
   }
   return num_suit;
}

int numOfColor(Game game, color color) {
   cardlist *head = game -> draw_pile;
   int num_color = 0;
   while (head != NULL) {
      if (cardColor(head -> card) == color) {
         num_color = num_color + 1;
      }
      head = head -> next;
   }
   return num_color;
}

int numOfValue(Game game, value value) {
   cardlist *head = game -> draw_pile;
   int num_value = 0;
   while (head != NULL) {
      if (cardValue(head -> card) == value) {
         num_value = num_value + 1;
      }
      head = head -> next;
   }
   return num_value;
}

int currentPlayer(Game game) {
   return game -> current_player;
}

int currentTurn(Game game) {
   return game -> current_turn;
}

int playerPoints(Game game, int player) {
   cardlist *head = game -> player [player].hand_list; 
   int point = 0;
   while (head != NULL) {
      point = point + cardValue(head -> card);
      head = head -> next;
   }
   return point;  
}

Card topDiscard(Game game) {
   cardlist *head = game -> discard_pile;
   Card top = head -> card;
   return top;
}

int numTurns(Game game) {
   return (game -> current_turn) + 1;
}

int currentTurnMoves(Game game) {
   return game -> player[game -> current_player].moves;
}

int getNumberOfTwoCardsAtTop(Game game) {
   cardlist *head = game -> discard_pile;
   int twos = 0;
   while (head != NULL && cardValue(head -> card) == DRAW_TWO) {
      twos = twos + 1;
   }
   return twos;
}

int getCurrentColor(Game game) {
   return game -> color;
}

int getPreviousTurnPlayer(Game game) {
   return game -> prev_player;
}

int getTopDiscardTurnNumber(Game game) {
   return game -> top_discard_turn;
}

int getActiveDrawTwos(Game game) {
   return game -> twos;
}

int playerCardCount(Game game, int player) {
   cardlist *head = game->player[player].hand_list;
   int card = 0;
   while (head != NULL) {
      card = card + 1;
      head = head -> next;
   }
   return card;
}

int handCardCount(Game game) {
   cardlist *head = game->player[currentPlayer(game)].hand_list;
   int card = 0;
   while (head != NULL) {
      card = card + 1;
      head = head -> next;
   }
   return card;
}

Card handCard(Game game, int card) {
   int count = 0;
   cardlist *current = game -> player[currentPlayer(game)].hand_list;
   while (count < card && current != NULL) {
      current = current -> next;
      count = count + 1;
   }
   if (current != NULL) {
      return current -> card;
   } else {
      return NULL;
   }
}

int isValidMove(Game game, playerMove move) {
   if (gameWinner(game) == NOT_FINISHED) {
      if (move.action == DRAW_CARD) {
         return valid_draw (game, move);
      } else if (move.action == PLAY_CARD) {
         return valid_play (game, move);
      } else {
         return valid_end (game, move);
      }
   } else {
      return FALSE;
   }
}

void playMove(Game game, playerMove move) {
   if (move.action == PLAY_CARD) {
      playMove_play (game, move);
   } else if (move.action == DRAW_CARD) {
      playMove_draw (game, move);
   } else {
      playMove_end (game, move);
   }
}

int gameWinner(Game game) {
   return game -> winner;
}

Card getDeckCard (Game game, int n) {
   int count = 0;
   cardlist *current = game -> draw_pile;
   while (count < n && current != NULL) {
      current = current -> next;
      count = count + 1;
   }
   if (current != NULL) {
      return current -> card;
   } else {
      return NULL;
   }
}

Card getDiscardPileCard (Game game, int n) {
   int count = 0;
   cardlist *current = game -> discard_pile;
   while (count < n && current != NULL) {
      current = current -> next;
      count = count + 1;
   }
   if (current != NULL) {
      return current -> card;
   } else {
      return NULL;
   }
}

Card getHandCard (Game game, int player, int n) {
   int count = 0;
   cardlist *current = game -> player[player].hand_list;
   while (count < n && current != NULL) {
      current = current -> next;
      count = count + 1;
   }
   if (current != NULL) {
      return current -> card;
   } else {
      return NULL;
   }
}


// HELPER FUNCTIONS

static void playMove_end (Game game, playerMove move) {
   // checking if anyone wins
   if (handCardCount(game) == 0) {
      game -> winner = currentPlayer(game);
   }
   
   // update point
   game -> player[game -> current_player].point = playerPoints (game, game -> current_player); 
   
   // add to move
   game -> player [game -> current_player].moves = game -> player [game -> current_player].moves + 1;
   
   // increase total turn
   game -> current_turn = game -> current_turn + 1;
   
   // reset card drawn and card played
   game -> player[game -> current_player].card_draw = 0;
   game -> player[game -> current_player].card_play = 0;
   game -> player[game -> current_player].moves = 0;
 
   // update current player and prev player
   game -> prev_player = game -> current_player;
   
   int current = game -> current_player;
   if (cardValue (topDiscard(game)) == A && getTopDiscardTurnNumber(game) == currentTurn(game) - 1) {
      current = current + 2;
   } else {
      current = current + 1;
   }
   
   if (current >= NUM_PLAYERS) {
      current = current - NUM_PLAYERS;
   }
   game -> current_player = current;
}

static void playMove_play (Game game, playerMove move) {
// find card in player's hand
   struct cardlist *prev = game -> player[currentPlayer(game)].hand_list;
   if (check_same_card (prev -> card, move.card) == 1) {
      game -> player[currentPlayer(game)].hand_list = prev -> next;
      prev -> next = game -> discard_pile;
      game -> discard_pile = prev;
   } else {
      struct cardlist *pos = prev -> next;
      while (pos != NULL) {
         pos = prev -> next;
         if (check_same_card (pos -> card, move.card) == 1) {
            prev -> next = pos -> next;
            pos -> next = game -> discard_pile;
            game -> discard_pile = pos;
            pos = NULL;
         }
      prev = prev -> next;
      }
   }
   
   // change current color if D
   if (cardValue(move.card) == D) {
      game -> color = move.nextColor;
   } else {
      game -> color = cardColor(move.card);
   }
   
   // add active two if 2
   if (cardValue(move.card) == DRAW_TWO) {
      game -> twos = game -> twos + 1;
   }
   
   //check if player wins
   if (handCardCount(game) == 0) {
      game -> winner = currentPlayer(game);  
   }
   
   // update status
   game -> player[currentPlayer(game)].card_play = game -> player[currentPlayer(game)].card_play + 1;
   game -> player[currentPlayer(game)].moves = game -> player[currentPlayer(game)].moves + 1;
   game -> top_discard_turn = game -> current_turn;
}

static void playMove_draw (Game game, playerMove move) {
   // if draw_pile is initially empty
   if (numCards(game) == 0 && game -> deck_size < 30) {
      if (game -> discard_pile -> next == NULL) {
         game -> winner = NO_WINNER;
      } else {
         discard_to_draw (game);
      }
   } 

   if (gameWinner(game) == NOT_FINISHED) {
      // draw the card
      struct cardlist *curr = game -> draw_pile;
      game -> draw_pile = curr -> next;
      curr -> next = game -> player[currentPlayer(game)].hand_list;
      game -> player[currentPlayer(game)].hand_list = curr;

      // update status
      game -> player[currentPlayer(game)].card_draw = game -> player[currentPlayer(game)].card_draw + 1;
      game -> player[currentPlayer(game)].moves = game -> player[currentPlayer(game)].moves + 1;
      if (game -> player [currentPlayer(game)].card_draw == 2*getActiveDrawTwos(game)) {
         game -> twos = 0;
      }
   }

   // if draw_pile is empty
   if (numCards(game) == 0 && game -> deck_size >= 30) {
      if (game -> discard_pile -> next == NULL) {
         game -> winner = NO_WINNER;
      } else {
         discard_to_draw (game);
      }
   }
}

static int valid_end (Game game, playerMove move) {
   if (game -> player[currentPlayer(game)].card_play == 0 && cardValue(topDiscard(game)) == DRAW_TWO) {
      if (game -> player[currentPlayer(game)].card_draw == 2*getActiveDrawTwos(game)) {
         return TRUE;
      } else {
         return FALSE;
      }
   } else if (game -> player[currentPlayer (game)].moves != 0) {
      return TRUE;
   } else {
      return FALSE;
   }
}

static int valid_draw (Game game, playerMove move) {
   if ((cardValue(topDiscard(game)) == DRAW_TWO) && 
      (game -> player[currentPlayer(game)].card_play == 0) && 
      (getActiveDrawTwos(game) == 0) && game -> player [currentPlayer (game)].moves < 1) {
      return TRUE;
   } else if ((cardValue(topDiscard(game)) == DRAW_TWO) && 
      (game -> player[currentPlayer(game)].card_play == 0) && 
      (game -> player [currentPlayer (game)].card_draw < 2*getActiveDrawTwos(game))) {
      return TRUE;
   } else if (cardValue(topDiscard(game)) != DRAW_TWO && 
      game -> player [currentPlayer (game)].moves < 1) {
      return TRUE;
   } else {
      return FALSE;
   }
}

static int valid_play (Game game, playerMove move) {
   // statuses
   int one_card = 0;
   int valid_card = 0;
   int have_card = 0;

   // less than one card
   if (game -> player [currentPlayer (game)].moves < 1) {
      one_card = 1;
   }

   // valid_card
   if (cardValue(topDiscard(game)) == DRAW_TWO && getActiveDrawTwos (game) != 0) {
      if (cardValue(move.card) == DRAW_TWO) {
         valid_card = 1;
      } else {
         valid_card = 0;
      }
   } else {
      valid_card = check_valid_card (game, move);
   }

   // card is in hand
   struct cardlist *head = game -> player[currentPlayer (game)]. hand_list;
   while (head != NULL) {
      if (check_same_card (move.card, head -> card) == 1) {
         have_card = 1;
      }
      head = head -> next;
   }

   if (one_card == 1 && valid_card == 1 && have_card == 1) {
      return TRUE;
   } else {
      return FALSE;
   }
}

static void discard_to_draw (Game game) {
   cardlist *prev = game -> discard_pile -> next;
   if (prev == NULL) {
      game -> winner = NO_WINNER;
   } else if (prev -> next == NULL) {
      game -> discard_pile -> next = prev -> next;
      prev -> next = game -> draw_pile;
      game -> draw_pile = prev;
   } else {
      cardlist *curr = game -> discard_pile -> next;
      while (curr != NULL) {
         game -> discard_pile -> next = curr -> next;
         curr -> next = game -> draw_pile;
         game -> draw_pile = curr;
         curr = game -> discard_pile -> next;
      }
   }
}

static int deck_size (cardlist *head) {
   int size = 0;
   while (head != NULL) {
      size = size + 1;
      head = head -> next;
   }  
   return size;
}

static cardlist *add_cardlist (Card add_card, cardlist *head) {
   cardlist *entry = calloc (1, sizeof(cardlist));
   entry -> card = add_card;
   entry -> next = head;
   head = entry;
   return head;
} 

static int check_same_card (Card first, Card second) {
   if (cardColor(first) == cardColor(second) && 
      cardValue(first) == cardValue(second) && 
      cardSuit(first) == cardSuit(second)) {
      return 1;
   } else {
      return 0;
   }
}

static int check_valid_card (Game game, playerMove move) {
   if (cardValue(topDiscard(game)) == cardValue(move.card) 
      || cardValue(move.card) == ZERO 
      || getCurrentColor(game) == cardColor(move.card)
      || cardSuit(topDiscard(game)) == cardSuit(move.card)) {
         return 1;
   } else {
      return 0;
   }  
}
