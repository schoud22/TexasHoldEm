#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "card.h"

using namespace std;

class player
{
private:
    string name;
    int chips, sizeOfHand;
    card hand[7];

public:
    double handValue;
    bool bigBlind;
    player();
    player(bool);
    void setName(string);
    string getName(void);
    bool getBigBlind(void);
    void drawCard(card);
    card* getHand(void);
    int cardExists(card);
    void clearHand(void);
    void sortHand(void);
    int getChips(void);
    void subtractChips(int);
    void addToChips(int);
    void displayHand(void);



};

#endif // PLAYER_H
