// By Jovanni Tjuandi (z5213864)
// player.c

// This function is to be implemented by the AI.
// It will be called when the player can take an action on their turn.
// The function is called repeatedly until they make the action
// END_TURN.
// If the player's turn is skipped, this funciton is not called for that
// player.

#include "Card.h"
#include "Game.h"

#include <stdio.h>

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


playerMove decideMove(Game game) {
   playerMove move;
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
      if (found == 1 && isValidMove (game, move) == 1) {
         return move;
      } else {
         move.action = DRAW_CARD;
         if (isValidMove (game, move) == 1) {
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
            
               if(found == 1) {
                  if (cardValue(current) >= cardValue(decide)){
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
      if (found == 1 && isValidMove (game, move) == 1) {
         if (cardValue(decide) == D) {
            move.nextColor = hand_color(game);
         }
         return move;
      } else {
         move.action = DRAW_CARD;
         if (isValidMove (game, move) == 1) {
            return move;
         } else {
            move.action = END_TURN;
            return move; 
         }
      }
   }
}
