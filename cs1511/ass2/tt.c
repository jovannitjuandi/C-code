#include <stdio.h>
#include "Game.h"
#include "Card.h"

// State of the game
struct _game {
    
    struct card_node *p1;
    struct card_node *p2;
    struct card_node *p3;
    struct card_node *p4;
    struct card_node *drawPile;
    struct card_node *discardPile;
    int currentTurn;
    int currentPlayer;
    
};

//contains the card and the pointer to the next card
struct card_node {
    struct card_node *next;
    Card card; // for each node, it points to a card
};


// Distribute cards to players
static struct card_node *cardplayer(struct card_node *entry, int player, 
                                int count, struct card_node *head) {

    struct card_node *p = NULL;
    
    if (count % 4 == player) {
        if (p == NULL) {
            p = entry;
            return p;
        } else {
            entry -> next = head;
            head = entry;
            return head;
        }
    }    
            
}


// Create a new game engine.
//
// This creates a game with a deck of the given size
// and the value, color, and suit of each card to be taken from
// each of the arrays in order.
//
// Your game will always have 4 players. Each player starts with a hand
// of 7 cards. The first card from the deck is given to player 0, the
// second to player 1, the third to player 2, the fourth to player 3,
// the fifth to player 0, and so on until each player has 7 cards.
Game newGame(int deckSize, value values[], color colors[], suit suits[]){
        
    // set up the game
    newGame->turnNum = 0;
    
    
    game->p1 = NULL;
    game->p2 = NULL;
    game->p3 = NULL;
    game->p4 = NULL;
    
    // Distribute the deck to players
    int i = 0;
    while (i < deckSize) {
        new    
    
    // Make deck
    int count = 0;    
    while (count < 28) {
        int player = count % 4;
        
        struct card_node *entry = malloc(sizeof(struct card_node));
        Card c = newCard(values[count], color[count], suits[count]);
        
        entry->card = c;
        entry->next = NULL;
        
        if (player == 0) {
            game->p1 = cardplayer(entry, player, count, game->p1);
        } else if (player == 1) {
            game->p2 = cardplayer(entry, player, count, game->p2);
        } else if (player == 2) {
            game->p3 = cardplayer(entry, player, count, game->p3);
        } else {
            game->p4 = cardplayer(entry, player, count, game->p4);
        }
        
        count = count + 1;
    }
    
    // First card flipped over and placed to the discarPile
    if (count == 28) {
       struct card_node *entry = malloc(sizeof(struct card_node));
       Card c = newCard(values[count], color[count], suits[count]);
       entry -> card = c;
       entry -> next = NULL;
       game->discardPile =  entry;
    }
    
    // Creates drawPile with the remaining cards
    count = deckSize - 1;
    game->drawPile = NULL;
    while (count >= 29) {
       struct card_node *entry = malloc(sizeof(struct card_node));
       Card c = newCard(values[count], color[count], suits[count]);
       entry -> card = c;
       entry -> next = game->drawPile;
       game->drawPile =  entry;
       count = count - 1;
    }      
    
    return game;
}
