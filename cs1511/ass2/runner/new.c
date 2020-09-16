// BEST

playerMove decideMove(Game game) {
   playerMove move;
   
   // if the top card is draw_two
   if (cardValue(topDiscard(game)) == DRAW_TWO) {
      Card counter;
      int count = 0;
      
      while (count < handCardCount(game)) {
         Card current = handCard(game, count);
         if (cardValue(current) == DRAW_TWO) {
            counter = current;
         }
         count = count + 1;
      }
      
      move.card = counter;
      move.action = PLAY_CARD;
      if (isValidMove (game, move) == 1) {
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
      Card decide;
      Card top = topDiscard(game);
      int count = 0;
      int largest = ZERO;
      int found = 0;
      
      while (count < handCardCount(game)) {
         Card current = handCard(game, count);
         if ((cardValue(current) >= largest) && (cardValue(top) == cardValue(current) || cardColor(top) == getCurrentColor(game) || cardSuit(top) == cardSuit(current))) {
            decide = current;
            int found = 1;
         }
         count = count + 1;
      }
      
      if (found == 0) {
         count = 0;
         while (count < handCardCount(game)) {
            Card current = handCard(game, count);
            if (cardValue(current) == ZERO) {
               decide = current;
            }
            count = count + 1;
         }
      }
      
      move.card = decide;
      move.action = PLAY_CARD;
      if (isValidMove (game, move) == 1) {
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


















playerMove decideMove(Game game) {
   playerMove move;
   
   // if the top card is draw_two
   if (cardValue(topDiscard(game)) == DRAW_TWO) {
      move.action = DRAW_CARD;
      if (isValidMove(game, move) == 0) {
         move.action = END_TURN;
      }
      return move;
   } else {
      Card decide;
      Card top = topDiscard(game);
      int count = 0;
      int found = 0;
      int largest_value = ZERO;
      
      while (count < handCardCount(game)) {
         Card current = handCard(game, count);
         if ((cardValue(current) >= largest) && (cardValue(top) == cardValue(current) || cardColor(top) == getCurrentColor(game) || cardSuit(top) == cardSuit(current))) {
            decide = current;
            found = 1;
         }
         count = count + 1;
      }
      
      move.card = decide;
      move.action = PLAY_CARD;
      if (isValidMove (game, move) == 1) {
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

























// CURRENT
playerMove decideMove(Game game) {
   playerMove move;
   
   // if the top card is draw_two
   if (cardValue(topDiscard(game)) == DRAW_TWO) {
      Card counter;
      int count = 0;
      
      while (count < handCardCount(game)) {
         Card current = handCard(game, count);
         if (cardValue(current) == DRAW_TWO) {
            counter = current;
         }
         count = count + 1;
      }
      
      move.card = counter;
      move.action = PLAY_CARD;
      if (isValidMove (game, move) == 1) {
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
      Card decide;
      Card top = topDiscard(game);
      int count = 0;
      int largest = ZERO;
      
      while (count < handCardCount(game)) {
         Card current = handCard(game, count);
         if ((cardValue(current) >= largest) && (cardValue(top) == cardValue(current) || cardColor(top) == getCurrentColor(game) || cardSuit(top) == cardSuit(current))) {
            decide = current;
         }
         count = count + 1;
      }
      
      move.card = decide;
      move.action = PLAY_CARD;
      if (isValidMove (game, move) == 1) {
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
