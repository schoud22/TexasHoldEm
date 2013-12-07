#include "player.h"
#include "informationdialogue.h"

player::player()
{
}

/*string aName,*/
player::player(bool isBigBlind)
{
    InformationDialogue myInformationDialoge;
    string chipCount = myInformationDialoge.getBankRoll();
    //name = aName;
    bigBlind = isBigBlind;
    chips = atoi(chipCount.c_str());
    sizeOfHand = 0;
    handValue = 0.0;
}

bool player::getBigBlind()
{
    return bigBlind;
}

void player::subtractChips(int amount)
{
    if(amount > chips){
        chips = chips - chips;
    }
    else{
        chips = chips - amount;
    }
}

void player::addToChips(int amount)
{
    chips = chips + amount;
}

void player::setName(string aName)
{
    name = aName;
}

string player::getName()
{
    return name;
}

void player::drawCard(card aCard)
{

    hand[sizeOfHand] = aCard;
    sizeOfHand ++;
    sortHand();
}

card* player::getHand()
{
    card *handPtr = hand;
    return handPtr;
    //return hand;
}

/*Card removeCard(int index)
{
    //int index = cardExists(aCard);
    //if(exists)
    Card temp = hand[index];
    // shift everything to overwrite removed card
    for(int i = index; i <= sizeOfHand; i++)
    {
        hand[i] = hand[i+1];
    }

    sizeOfHand--;
    return temp;
}*/

int player::cardExists(card aCard)
{
    for(int i = 0; i < sizeOfHand; i++)
    {
        if(hand[i].equals(aCard))
        {
            return i;
        }
    }
    cout << "That card is not in your hand" << endl;
    return -1;
}

void player::clearHand()
{
    sizeOfHand = 0;
    card blank;
    for(int i = 0; i < 7; i++)
    {
        hand[i] = blank;
    }
}

void player::sortHand()
{
    for(int i = sizeOfHand - 1; i > 0; i--)
    {
        if(hand[i].compareRank(hand[i-1]) < 0)
        {
            // swap
            card temp = hand[i];
            hand[i] = hand[i-1];
            hand[i-1] = temp;
        }

    }
}

int player::getChips()
{
    return chips;
}

void player::displayHand()
{
    for(int i = 0; i < sizeOfHand; i++)
    {
        hand[i].printCard();
        cout << ", ";
    }
}

