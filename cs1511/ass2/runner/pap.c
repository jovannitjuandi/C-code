// The player of Final Card-Down. v1.1.0

#include "player.h"
#include "Game.h"
#include "Card.h"

// This function is to be implemented by the AI.
// It will be called when the player can take an action on their turn.
// The function is called repeatedly until they make the action
// END_TURN.
// If the player's turn is skipped, this funciton is not called for that
// player.
playerMove decideMove(Game game);

playerMove decideMove(Game game) {
    
    int count=0;
    int currMove=0;

    playerMove move;

    if (move.action == PLAY_CARD) {       
    
        int i =0;

        int PLAY = FALSE;
        int DRAW = FALSE;
       
        while (i< handCardCount(game) && PLAY == FALSE) {

            move.card = handCard(game,i);
            if (isValidMove(game,move) == TRUE) {

                PLAY = TRUE;
            }

            i++;
        }

        if (PLAY == FALSE) {

            move.action = DRAW_CARD;
            DRAW = FALSE;

            if(isValidMove(game,move) == TRUE) {

                DRAW = TRUE;
            }
        }

    }

    currMove++;

    if(move.action == END_TURN) {

        count++;
        currMove = 0;
    }

    return move;
}
