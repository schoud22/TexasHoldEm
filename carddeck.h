#ifndef CARDDECK_H
#define CARDDECK_H
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "card.h"

class CardDeck
{
private:
    card deck[52];
    //Card drawPile[52];
    int sizeOfDeck;
public:
    CardDeck();
    void printDeck(void);
    void shuffle(void);
    card getCard(void);
};

#endif // CARDDECK_H
