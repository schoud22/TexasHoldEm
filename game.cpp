#include "game.h"

game::game()
{
}
int callValue = 0;
game::game(player *human, player *AI)
{
    size = 0;
    deck = CardDeck();
    deck.shuffle();
    cout << "Shuffling cards, please wait..." << endl << endl;

    deal(human, AI);
    deck.printDeck();
    cout << endl << endl;
    human->displayHand();
    cout << endl << endl;
    AI->displayHand();            
}
int game::setUpBlinds(player *human, player *AI){
    pot = 0;
    if(human->getChips() >= 20 && AI->getChips() >= 20)
    {
        if(human->bigBlind)
        {
            human->subtractChips(20);
            AI->subtractChips(10);
            pot = pot + 30;
            return 10;
        }
        else
        {
            human->subtractChips(10);
            callValue = 10;
            AI->subtractChips(20);
            pot = pot + 30;
            return 10;
        }
    }
    else
    {
        int amount = human->getChips();
        if(amount > AI->getChips())
            amount = AI->getChips();


        human->subtractChips(amount);
        AI->subtractChips(amount);
        pot = pot + (amount * 2);
        return 0;

    }
    return 0;
}

int game::getCallValue(){
    return callValue;
}

int game::getPot(){
    return pot;
}

void game::addToPot(int value){
    pot += value;
}

void game::clearPot(){
    pot = 0;
}

void game::giveCards(player *human, player *AI)
{
    for(int j = 0; j < size; j++)
    {
        human->drawCard(tableCards[j]);
        AI->drawCard(tableCards[j]);
    }
}

void game::flop()
{
    card flop;
    for(int i = 0; i < 3; i++)
    {
        flop = deck.getCard();
        tableCards[i] = flop;
        size++;
    }
}

void game::getNextCard()
{
    card temp = deck.getCard();
    tableCards[size] = temp;
    size++;
}

void game::fold(player *human, bool bigBlind)
{
   cout << "new game starting now" << endl;
   deck.shuffle();
   deck.printDeck();
   human->bigBlind = bigBlind;
   clearTableCards();
}

void game::clearTableCards()
{
    size = 0;
    card blank;
    for(int i = 0; i < 5; i++)
    {
        tableCards[i] = blank;
    }
}

void game::deal(player *human, player *AI)
{
    card temp;
    // Deal out the cards
    for(int i = 0; i < 2; i++)
    {
        temp = deck.getCard();
        human->drawCard(temp);
        temp = deck.getCard();
        AI->drawCard(temp);
    }
}


long double game::winningHand(card hand[])// or send pointer
{
    int arr[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < 7; i++)
    {
        arr[(hand[i].getValue()) - 1]++;

        if(hand[i].getValue() == 14) // Ace goes to position 14 and 1
            arr[0]++;
    }

    for(int j = 0; j < 14; j++)
    {
        cout << arr[j] << ", ";
    }

    int pair[3] = {0, 0, 0};
    int pairCounter = 2;
    //int twoPair = 0;
    int trips[2] = {0, 0};
    int tripsCounter = 1;
    //int fullHouse = 0;
    int quads = 0;
    int straight = 0;
    int flush = 0;
    //int straightFlush = 0;
    char suit;

    // Check for a flush
    int flushSuit = flushCheck(hand);
    flush = flushSuit % 100;

    cout << endl << "%%%%%%%flush suit  " << flushSuit << endl;
    cout << "%%%%%%%flush  " << flush << endl;

    /*
     *    UNRESOLVED BUGS:
     *    straight flush from A to 5 not recognized. Just seen as flush to Ace
     *    Also eg. straight flush to 6 and a straight to 7, the straight wins
     */

    // Check for Straight
    int counter = 0;
    for(int j = 13; j >= 0; j--)
    {
        if(arr[j] != 0)
            counter++;
        else
            counter = 0;

        if(counter == 5)
            straight = j + 5; //5 + (double)(j + 5)/100;
    } // End of Straight check

    cout << "%%%%%%%straight  " << straight << endl;

    //------------------------------------------------------------------------------------------------
    // Check for a Straight Flush
    if(flushSuit < 115)
        suit = 'S';
    else if(flushSuit < 215)
        suit = 'C';
    else if(flushSuit < 315)
        suit = 'H';
    else
        suit = 'D';

    if((straight > 0) && (flush > 0))
    {
        if(straight == flush)
        {
            for(int k = 6; k > 3; k--)
            {
                if((hand[k].getSuit() == suit) && (hand[k].getValue() == straight))
                {
                    cout << " YES at stage 1" << endl;
                    for(int j = k - 4; j >= 0; j--)
                    {
                        cout << " YES at stage 2" << endl;
                        if((hand[j].getSuit() == suit) && (hand[j].getValue() == straight - 4))
                        {
                            return (9 + (long double)straight/100); // returns value of Straight Flush
                        }
                    }

                }

            }
        }
    }
    // End of straight flush check
    //------------------------------------------------------------------------------------------------

    for(int j = 13; j > 0; j--)
    {
        if(arr[j] == 4)
        {
            quads = j + 1;
            break;
        }
        else if(arr[j] == 3)
        {
            trips[tripsCounter] = j + 1;
            tripsCounter--;
        }
        else if(arr[j] == 2)
        {
            pair[pairCounter] = j + 1;
            pairCounter--;
        }
    }

    // if quads then return
    if(quads > 0)
        return (8 + (long double)quads / 100);

    // if full house then return
    else if((trips[1] > 0) && (pair[2] > 0))
        return (7 + (long double)trips[1] / 100);

    // if flush then return
    else if(flush > 0)
        return (6 + (long double)flush / 100);

    // if straight then return
    else if(straight > 0)
        return (5 + (long double)straight / 100);

    // if three of a kind then return
    else if(trips[1] > 0)
        return (4 + (long double)trips[1] / 100);

    // if two pairs then return
    else if(pairCounter < 1){
        int kicker = 0;
        for(int i = 0; i < 7; i++){
            if(hand[i].getValue() != pair[2] && hand[i].getValue() != pair[1])
                kicker = hand[i].getValue();
        }
        return (3 + ((long double)pair[2] / 100) + ((long double)pair[1] / 10000) + ((long double)kicker / 1000000));
     }

    // if one pair then return
    else if(pair[2] > 0){
        int kicker2 = 0, counter = 0;
        for(int i = 6; i >= 0; i--){
            if(hand[i].getValue() != pair[2] && counter != 3){
                kicker2 = kicker2 + hand[i].getValue();
                counter++;
            }
        }
        return (2 + ((long double)pair[2] / 100) + ((long double)kicker2 / 10000));
     }

    // else return value of high card
    else{
        int kicker3 = 0, counter = 0;
        for(int i = 6; i >= 0; i--){
            if(hand[i].getValue() != pair[2] && counter != 4){
                kicker3 = kicker3 + hand[i].getValue();
                counter++;
            }
        }
        return (1 + ((long double)hand[6].getValue() / 100) + ((long double)kicker3 / 10000));
    }
}// end of winningHand()


    /*
     *
     */
    int game::flushCheck(card hand[])
    {
        int spade = 0, club = 0, heart = 0, diamond = 0;

        for(int i = 0; i < 7; i++)
        {
            if(hand[i].getSuit() == 'S')
                spade++;
            else if(hand[i].getSuit() == 'C')
                club++;
            else if(hand[i].getSuit() == 'H')
                heart++;
            else if(hand[i].getSuit() == 'D')
                diamond++;
            else
                cout << "ERROR" << endl;
        }

        char suit;
        bool exist = false;

        if(spade >= 5)
        {
            suit = 'S';
            exist = true;
        }
        else if(club >= 5)
        {
            suit = 'C';
            exist = true;
        }
        else if(heart >= 5)
        {
            suit = 'H';
            exist = true;
        }
        else if(diamond >= 5)
        {
            suit = 'D';
            exist = true;
        }

        if(exist)
        {
            for(int j = 6; j > 3; j--)
            {
                if(hand[j].getSuit() == suit)
                {
                    if(suit == 'S')
                        return hand[j].getValue() + 100; //return (6 + ((double)hand[j].getValue()/100));
                    else if(suit == 'C')
                        return hand[j].getValue() + 200;
                    else if(suit == 'H')
                        return hand[j].getValue() + 300;
                    else
                        return hand[j].getValue() + 400;
                }
            }
        }

        return 0;


    }// end of flush()


