#include <stdio.h>
typedef enum {
    RED,
    BLUE,
    GREEN,
    YELLOW,
    PURPLE
} color;

// The various suits that a card can have.
typedef enum {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES,
    QUESTIONS
} suit;

// The various values that a card can have.
typedef enum {
    ZERO,
    ONE,
    DRAW_TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    A,
    B,
    C,
    D,
    E,
    F
} value;

typedef struct _card {
    value value;
    color color;
    suit suit;
} card;

int main (void) {
   card first;
   first.value = A;
   first.suit = DIAMONDS;
   first.color = BLUE;
   printf ("%d\n", first.suit);
}

// HOW TO KNOW WHAT IS THE THIRD COLOR IN COLOR ENUMERATION (YELLOW)
