/*
CSCI 240         Program 10     Fall 2020

Programmer: Jacob Eul
 

Section: 0001

Date Due: December 04 2020

Purpose: plays first to 21 (card game)
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

// initializes the card class
class Card{
public:
    Card();
    void setCard( int , const char * );
    int getFace();
    const char * getSuit();
    void displayCard();

private:
    int face = 1;
    char suit[9] = {};
};



//Definition for a class that represents a deck of cards
class DeckOfCards
{
public:
  DeckOfCards();

  Card draw();
  void shuffle();
  bool isEmpty();

private:
  static const int MAX_CARDS = 52;       //Maximum number of cards in a deck
  static const int NUM_SUITS = 4;        //Number of card suits
  static const int CARDS_PER_SUIT = 13;  //Number of cards of each suit

  Card deck[MAX_CARDS];     //The deck of cards
  int topCard;              //The subscript of the card on the top of the deck
};



/**********   Code the Card class methods between these lines   **********/
// creates a card object from the class cards and assigns it a face value and a character array value
// arguments: none          returns: nothing
Card::Card(){
    face = ( rand() % 13 ) + 1;
    switch( (rand()%4)+1 ){
    case 1:
        strcpy( suit , "Clubs" );
        break;
    case 2:
        strcpy( suit , "Diamonds" );
        break;
    case 3:
        strcpy( suit , "Hearts" );
        break;
    case 4:
        strcpy( suit , "Spades" );
        break;
    default:
        break;
    }
    
}

// defines a method from the card class this function determines the suit of a given card
// arguments: int _face , const char * _suit  returns: Nothing
void Card::setCard( int _face , const char * _suit ){
    face = _face;
    if( _face < 1 || _face > 13 ){
        face = 1;
    }
    if( strcmp( _suit , "Clubs" )!=0 &&
        strcmp( _suit , "Diamonds") != 0 &&
        strcmp( _suit , "Hearts" ) != 0 &&
        strcmp( _suit , "Spades" ) != 0 ){
        strcpy( suit , "Hearts" );
    }else{
        strcpy( suit , _suit );
    }

    
}

// this method simply gets the face value from an object and returns it
// arguments: none          returns: nothing
int Card::getFace(){
    return face;
}

// this method simply gets the suit from an object and returns it
// arguments: none          returns: nothing
const char * Card::getSuit(){
    return suit;
}

// defines a method from the card class that will print the necessary info from a given object
// arguments: none          returns: nothing
void Card::displayCard(){
    switch( face ){
    case 1:
        cout << "Ace";
        break;
    case 11:
        cout << "Jack";
        break;
    case 12:
        cout << "Queen";
        break;
    case 13:
        cout << "King";
        break;
    default:
        cout << face;
        break;
    }
    cout << " of " << suit;
}

/*************************************************************************/


/***************************************************************
Constructor

Use: This creates a DeckOfCards object and then shuffles the
     cards

Arguments: none

Note: -1 is used to signal that no cards have been removed from
      the deck
***************************************************************/
DeckOfCards::DeckOfCards()
{
//An array of the 4 possible values for the card suits
const char suitVals[NUM_SUITS][9] = { "Clubs", "Diamonds", "Hearts", "Spades" };

int cardSub = 0;    //subscript to process the deck of cards

//Go through all 52 spots in the array of Cards and put a card
//at the location

for( int suitSub = 0; suitSub < NUM_SUITS; suitSub++ )
  {
  //For each of the suits, put in all of the cards for the suit
  for( int faceVal = 1; faceVal <= CARDS_PER_SUIT; faceVal++ )
    {
    //Put the card into the deck
    deck[ cardSub ].setCard( faceVal, suitVals[suitSub] );

    //Move to the next card in the deck
    cardSub++;
    }
  }

//shuffle the playing cards
shuffle();

//Set the top card location to -1 to indicate the deck is brand new
topCard = -1;
}



/***************************************************************
Method:  Card draw()

Use: This method draws a card from the top of the deck

Arguments: none

Returns: a Card object (the card on the top of the deck)
***************************************************************/

Card DeckOfCards::draw()
{
//Increment to get the subscript of the current top card
topCard++;

//return the card that is currently on the top of the deck
return deck[topCard];
}



/***************************************************************
Method:  void shuffle()

Use: This method shuffles the deck of cards

Arguments: none

Returns: nothing

Note: this method uses the random_shuffle function that is part
      of the algorithm library to shuffle the 52 cards
***************************************************************/

void DeckOfCards::shuffle()
{
//Shuffle all 52 cards that are in the deck

random_shuffle(deck, deck+MAX_CARDS);
}


/***************************************************************
Method:  bool isEmpty()

Use: This method determines if the deck of cards is empty( have
     all of the cards been drawn)

Arguments: none

Returns: boolean value: true if all of the cards have been drawn
                        false if there are still cards in the deck
***************************************************************/

bool DeckOfCards::isEmpty()
{
//if topCard subscript plus 1 is greater than 52, the deck is
//empty. Otherwise, there are cards that can be drawn.

return topCard + 1 >= MAX_CARDS;
}


int main()
{
    
    
    //Set the seed value for the random number generator
    srand( 0 );

    DeckOfCards deck;
    Card card;
    int currentPlayer = 1 , currentCardTotal = 0 , points = 0 , player1Score = 0 , player2Score = 0;
    
    // alternate players
    bool whichPlayer = true;
    while( !deck.isEmpty() ){
        if ( whichPlayer == true)
        {
            cout << "Player 1:" << endl;
            whichPlayer = false;
        }
        else
        {
            cout << "Player 2:" << endl;
            whichPlayer = true;
        }
        
        // draws the necessary cards
        currentCardTotal = 0;
        for( int i = 0; i < 3 && currentCardTotal < 21 && !deck.isEmpty(); i++ ){
            card = deck.draw();
            card.displayCard();
            switch( card.getFace() ){
            case 1:
                currentCardTotal+=1;
            case 11:
            case 12:
            case 13:
                currentCardTotal += 10;
                break;
            default:
                currentCardTotal += card.getFace();
                break;
            }
            cout << "   Total: " << currentCardTotal << endl;
        }
        cout << endl;
        
        // decides how many points to award
        if( currentCardTotal <= 21 ){
            points = 10;
            if( currentCardTotal == 21 ) points += 5;
            cout << "Congratulations player " << currentPlayer << "! " << points << " points awarded!";
        } else{
            cout << "Sorry player " << currentPlayer << " -- Busted!";
            points = 0;
        }
        cout << endl << "-------------------" << endl << endl;
        if( currentPlayer == 1 ){
            player1Score += points;
            currentPlayer++;
        } else{
            player2Score += points;
            currentPlayer--;
        }
    }
    
    // print the scores
    cout << "Player 1 score: " << player1Score << endl
        << "Player 2 score: " << player2Score
        << endl << endl
        << "Player " << ( player1Score > player2Score ? 1 : 2 ) << " won!";

    cout << "\n\n\n";

    return 0;
}

