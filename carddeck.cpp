#include "carddeck.h"

CardDeck::CardDeck()
{
    ///Card card('A', 'C', 1);
    //deck[0] = card; //new Card('A', 'C');
    sizeOfDeck = 51;

    char ranks[] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
    char suits[] = {'C','D','H','S'};
    int counter = 0;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            card card1(ranks[j], suits[i], j + 2);
            deck[counter] = card1;
            counter++;
        }
    }// end outer for loop
}

void CardDeck::printDeck()
{
    for(int i = 0; i < 52; i++)
    {
        if(i%13 == 0)
            cout << endl;
        deck[i].printCard();
        cout << ", ";
    }
}

void CardDeck::shuffle()
{
    srand(time(NULL));
    int j;
    for(int i = 0; i < 52; i++)
    {
        j = rand()%52;
        card temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }
    sizeOfDeck = 51;
}

card CardDeck::getCard()
{
     //Card temp = drawPile[sizeDrawPile];
    card temp = deck[sizeOfDeck];

     // decrement size so it points to next card without removing previous card.
     sizeOfDeck--;
     return temp;
}
