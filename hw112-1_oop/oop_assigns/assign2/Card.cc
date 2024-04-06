/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     Card.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 5, 1998: Created.
***************************************************************************/

/* $Log: Card.cc,v $
 * */

using namespace std;
#include <iostream>
#include <assert.h>
#include "AnsiPrint.h"
#include "CardPat.h"
#include "Card.h"


// constructor
/*Card::Card(int newId) {

}*/


// Accessor: card id is an integer between 0 and 51.
// Cards of the same pips are together.
// In other words, cards are in the following order:
//    1S 1H 1D 1C 2S 2H ...

int
Card::getID() const {
	return card_id;
}

// get the pip of the card (0-12)
int
Card::getPip() const {
	return card_pip;
}

// get the suit of the card (0-3)
int
Card::getSuit() const {
	return card_suit;
}

// modifier: set id directly
void
Card::setID(int newId) {
	card_id = newId;
	card_suit = newId / 13;
	card_pip = (newId % 13) + 1;
}

// print the suit name and face value of the card
void
Card::print(void) const {
	if(card_suit == CLUB){
		AnsiPrint("C", black, white, false, false);
	}else if(card_suit == DIAMOND){
		AnsiPrint("D", red, white, false, false);
	}else if(card_suit == HEART){
		AnsiPrint("H", red, white, false, false);
	}else{
		AnsiPrint("S", black, white, false, false);
	}
}
