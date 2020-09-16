int isValidMove(Game game, playerMove move) {
   if (move.action == DRAW_CARD) { // DRAW_CARD
      if (cardValue(topDiscard(game)) == DRAW_TWO) {
         if (game -> player [currentPlayer (game)].card_play >= 1) {
            return FALSE;
         } else {
            if (game -> player [currentPlayer (game)].card_draw <= 2*getActiveDrawTwos(game)) {
               return TRUE;
            } else {
               return FALSE;
            }
         } 
      } else {
         if (game -> player [currentPlayer (game)].moves < 1) {
            return TRUE;
         } else {
            return FALSE;
         }
      }
   } else if (move.action == PLAY_CARD) { // PLAY_CARD
      // statuses
      int one_card = 0;
      int valid_card = 0;
      int have_card = 0;
      int not_two = 0;
      
      // less than one card
      if (game -> player [currentPlayer (game)].card_play < 1) {
         one_card = 1;
      }
      
      // valid_card
      if (cardValue(topDiscard(game)) == DRAW_TWO) {
         if (cardValue(move.card) == DRAW_TWO) {
            valid_card = 1;
         } else {
            valid_card = 0;
         }
      } else {
         if (cardValue(topDiscard(game)) == cardValue(move.card) || cardValue(move.card) == ZERO || getCurrentColor(game) == cardColor(move.card)
            || cardSuit(topDiscard(game)) == cardSuit(move.card)) {
               valid_card = 1;
         } else {
            valid_card = 0;
         }  
      }
      
      // card is in hand
      struct cardlist *head = game -> player[currentPlayer (game)]. hand_list;
      while (head != NULL) {
         if (check_same_card (move.card, head -> card) == 1) {
            have_card = 1;
         }
         head = head -> next;
      }
      
      if (cardValue(topDiscard(game)) != DRAW_TWO) {
         not_two = 1;
      }
      
      if (one_card == 1 && valid_card == 1 && have_card == 1 && not_two == 1) {
         return TRUE;
      } else {
         return FALSE;
      }
   } else { // END_TURN
      if (game -> player[currentPlayer (game)].card_play == 0 && cardValue(topDiscard(game)) == DRAW_TWO) {
         if (game -> player[currentPlayer (game)].card_draw == 2*getActiveDrawTwos(game)) {
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
}

