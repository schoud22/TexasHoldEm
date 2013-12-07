#include "card.h"

card::card()
{
}

card::card(char aRank, char aSuit)
{
    rank = aRank;
    suit = aSuit;
    value = assignValue(aRank);

    if(aSuit == 'C' || aSuit == 'S' || aSuit == 'c' || aSuit == 's')
        colour = "black";
    else if(aSuit == 'D' || aSuit == 'H' || aSuit == 'd' || aSuit == 'h')
        colour = "red";
    setCardName(suit, rank);
}

card::card(char aRank, char aSuit, int aValue)
{
    /*bool valid = isValid(aRank, aSuite);
    if(valid)
    {*/
    rank = aRank;
    suit = aSuit;
    value = aValue;

    if(aSuit == 'C' || aSuit == 'S' || aSuit == 'c' || aSuit == 's')
        colour = "black";
    else if(aSuit == 'D' || aSuit == 'H' || aSuit == 'd' || aSuit == 'h')
        colour = "red";
    setCardName(suit, rank);
}

int card::assignValue(char aRank)
{
    if(aRank == 'A')
        return 14;
    else if(aRank == '2')
        return 2;
    else if(aRank == '3')
        return 3;
    else if(aRank == '4')
        return 4;
    else if(aRank == '5')
        return 5;
    else if(aRank == '6')
        return 6;
    else if(aRank == '7')
        return 7;
    else if(aRank == '8')
        return 8;
    else if(aRank == '9')
        return 9;
    else if(aRank == 'T')
        return 10;
    else if(aRank == 'J')
        return 11;
    else if(aRank == 'Q')
        return 12;
    else if(aRank == 'K')
        return 13;
    else
        return 0;
}

void card::printCard()
{
    cout << cardName;
}


/*
 * Exact card match
*/
bool card::equals(card o)
{
    if(this->rank == o.rank && this->suit == o.suit)
        return 1;
    else
        return 0;
}

int card::compareRank(card o)
{
    if(this->value == o.value)
        return 0;
    else if(this->value < o.value)
        return -1;
    else //if(this->value > o.value)
        return 1;
}


char card::getSuit()
{
    return suit;
}

int card::getValue()
{
    return value;
}

string card::getColour()
{
    return colour;
}

void card::setCardName(char aSuit, char aRank)
{
    aSuit = aSuit + 32;
    cName[0] = aSuit;
    cName[1] = aRank;
    cardName = cName;
}

string card::getCardName()
{
    return cardName;
}
