#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "carddeck.h"
#include "player.h"
#include "card.h"

using namespace std;

class game
{
private:    
    CardDeck deck;
    //player human, AI;
    int bet, pot, size;
public:
    card tableCards[5];
    game();
    game(player*, player*);
    void deal(player*, player*);
    long double winningHand(card[]);
    int getPot();
    int flushCheck(card[]);
    void clearTableCards();
    void fold(player*, bool);
    void addToPot(int);
    void clearPot();
    void flop();
    void getNextCard();
    int getCallValue();
    void giveCards(player*, player*);
    int setUpBlinds(player*, player*);
};

#endif // GAME_H
