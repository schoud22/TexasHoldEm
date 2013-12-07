#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

class card
{
private:
    char rank, suit;
    string colour, cardName;
    int value;
    char cName[2];
public:
    card();
    card(char, char);
    card(char, char, int);
    int assignValue(char);
    void printCard(void);
    bool equals(card o);
    int compareRank(card o);
    char getSuit(void);
    int getValue(void);
    string getColour(void);
    void setCardName(char, char);
    string getCardName(void);

};

#endif // CARD_H
