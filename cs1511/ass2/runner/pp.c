// The player of Final Card-Down. v1.1.0
//
// !!! DO NOT CHANGE THIS FILE !!!
#include "Game.h"
#include "player.h"
#include "Card.h"
static int checkCard (Game game);
static Card checkCard2 (Game game);

static int checkCard (Game game){
    int i = 0;
    Card play;
    
    while(i < handCardCount(game)){
        Card head = handCard(game, i);
        
        if(cardValue(head) == DRAW_TWO){
            return 1;
        }
        i++;
    }
}

static Card checkCard2 (Game game){
    int i = 0;
    Card play;
    
    while(i < handCardCount(game)){
        Card head = handCard(game, i);
        
        if(cardValue(head) == DRAW_TWO){
            play = head;
            return play;
        }
        i++;
    }
} 
   
playerMove decideMove(Game game){
    playerMove move;
    
    if(cardValue(topDiscard(game)) == DRAW_TWO){
        if(checkCard(game) == 1){
            if(isValidMove(game, move) == 1){
                move.card = checkCard2(game);
                move.action = PLAY_CARD;
            }
            else{
                if(isValidMove(game, move) == 1){
                    move.action = DRAW_CARD;
                }
                else{
                    move.action = END_TURN;
                }
            }
        }
    }
    else{
        if(isValidMove(game, move) == 1){
            int i = 0;
            Card x;
            
            while(i < handCardCount(game)){
                Card head = handCard(game, i);
                
                if(cardValue(topDiscard(game)) == cardValue(x) || cardSuit(head -> card) == cardSuit(x) || cardColor(head -> card) == cardColor(x)){
                    x = head;
                    break;
                }
                i++;
            } 
            move.card = x;
            move.action = PLAY_CARD;
        }     
        else{
            if(isValidMove(game, move) == 1){
                move.action = DRAW_CARD;
            }
            else{
                move.action = END_TURN;
            }
        }
    }
}


