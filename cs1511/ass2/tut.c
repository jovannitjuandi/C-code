void playMove(Game game, playerMove move) {
   if (move.action == PLAY_CARD) {
      // find card in player's hand
      Card play = move.card;
      struct cardlist *prev = game -> player[game -> current_player].hand_list;
      if (check_same_card (prev -> card, play) == 1) {
         game -> player[game -> current_player].hand_list = prev -> next;
         prev -> next = game -> discard_pile;
         game -> discard_pile = prev;
      } else {
         struct cardlist *pos = prev;
         while (pos != NULL) {
            pos = prev -> next;
            if (check_same_card (pos -> card, play) == 1) {
               prev -> next = pos -> next;
               pos -> next = game -> discard_pile;
               game -> discard_pile = pos;
            }
         prev = prev -> next;
         }
      }
       = game -> player[game -> current_player].card_draw + 1;
      game -> player[game -> current_player].moves = game -> player[game -> current_player].moves + 1;
   } else {
      
      // calculate point
      int pt = 0;
      struct cardlist *point = game -
      // update status
      game -> player[game -> current_player].card_play = game -> player[game -> current_player].card_play + 1;
      game -> player[game -> current_player].played_card = move.card;
      game -> player[game -> current_player].moves = game -> player[game -> current_player].moves + 1;
      game -> top_discard_turn = game -> numTurns(game);
      
      // check if win
      if (handCardCount(Game game) == 0) {
         game -> winner = game -> current_player;
      }
   } else if (move.action == DRAW_CARD) {
      struct cardlist *curr = game -> draw_pile;
      game -> draw_pile = curr -> next;
      curr -> next = game -> player[game -> current_player].hand_list;
      game -> player[game -> current_player].hand_list = curr;
      
      game -> player[game -> current_player].card_draw> player[game -> current_player].hand_list;
      while (point != NULL) {
         pt = pt + cardValue(point -> card);
         point = point -> next;
      }
      game -> player[game -> current_player].point = pt; 
      
      // add to move
      game -> player [game -> current_player].moves = game -> player [game -> current_player].moves + 1;
      
      // increase total turn
      game -> current_turn = game -> current_turn + 1;
      
      
      // reset previous player's moves
      if (game -> prev_player >= 0) {
         game -> player[game -> prev_player].moves = 0;
      }
      
      // reset card drawn and card played
      game -> player[game -> current_player].card_draw = 0;
      game -> player[game -> current_player].card_play = 0;
      
      // update current player and prev player
      game -> prev_player = game -> current_player;
      
      int current = game -> current_player;
      if (cardValue (topDiscard(game)) == A) {
         current = current + 2;
      } else {
         current = current + 1;
      }
      if (current > 3) {
         current = current - NUM_PLAYERS;
      }
      game -> current_player = current;
      
   }
}

