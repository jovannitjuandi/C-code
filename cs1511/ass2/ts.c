// initialize draw_pile
   int count = deckSize - 1;
   cardlist *head = NULL;

   game->draw_pile = NULL;

   while (count >= 29) {
      Card new_card = newCard (values[count], colors[count], suits[count]);
      head = add_cardlist(new_card, head);
      count = count - 1;
   }

   game -> draw_pile = head;
