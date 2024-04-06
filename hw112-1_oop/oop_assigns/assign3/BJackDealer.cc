/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     BJackDealer.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 12, 1998: Created.
***************************************************************************/

/* $Log:$ */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
}

using namespace std;

#include <iostream>
#include <string>
#include <cstring>
#include "AnsiPrint.h"
#include "Card.h"
#include "BJackPlayer.h"
#include "BJackDealer.h"
#include "CardPat.h"

// constructor 
// nDeck is the number of standard decks that the dealer will deal with
BJackDealer::BJackDealer(int nSet) {
	num_decks = nSet;
	num_cards_in_hand = 0;
	name_of_dealer = "Dealer";
	first_card_is_faced_up = false;
	rand_seed = 1;
	all_cards = NULL;
	top_of_the_mixed_decks_index = 0;
	first_time_playing = 0;

}

// distribute a card to the player
int
BJackDealer::giveCard() {
	int withdraw_ID;

	withdraw_ID = all_cards[top_of_the_mixed_decks_index];
	top_of_the_mixed_decks_index ++;

	return withdraw_ID;

}

// give the dealer one card unconditionally
void 
BJackDealer::addCard() {
	int withdraw_ID;

	withdraw_ID = giveCard();

	cards_in_hand[num_cards_in_hand].setID(withdraw_ID);
	num_cards_in_hand ++;

}

// give the dealer as many cards as necessary to exceed the player 
// of the given total points
// A special case happen when both of them have 21 points.
// It is a tie game and therefore the dealer does not get more cards.

void
BJackDealer::addCards(int oppTotal) {
	int current_point = 0;
	int num_of_ace_in_hand = 0;
	int card_val;

	while(1){
		current_point = 0;
		num_of_ace_in_hand = 0;

		for(int i = 0; i < num_cards_in_hand; i++){
			card_val = cards_in_hand[i].getPip() + 1;
			if(card_val > 10){
				card_val = 10;
			}
			current_point += card_val;

			if(card_val == 1){
				num_of_ace_in_hand ++;
			}
		}
		if( (num_of_ace_in_hand >= 1) && ((current_point + 10) <= 21) ){
			current_point += 10;
		}

		if(oppTotal > 21){
			// get more than 16 and stop
			if(current_point >= 17){
				break;
			}
		}else if(oppTotal == 21){
			// get the same as player
			if(current_point >= oppTotal){
				break;
			}
		}else{
			// get more than player and stop
			if(current_point > oppTotal){
				break;
			}
		}

		//add card to the hand
		addCard();

	}

}

// Determine who has win the game.
// The total points that the dealer has should be greater than 
// the player at the point this function is called.

result
BJackDealer::judge(int oppTotal) const {
	int myTotal = 0;
	int num_of_ace_in_hand = 0;
	int card_val;

	for(int i = 0; i < num_cards_in_hand; i++){
		card_val = cards_in_hand[i].getPip() + 1;
		if(card_val > 10){
			card_val = 10;
		}
		myTotal += card_val;

		if(card_val == 1){
			num_of_ace_in_hand ++;
		}
	}
	if( (num_of_ace_in_hand >= 1) && ((myTotal + 10) <= 21) ){
		myTotal += 10;
	}

	if((myTotal > 21) && (oppTotal > 21)){
		return tie;
	}else if((myTotal == 21) && (oppTotal == 21)){
		return tie;
	}else if( (myTotal > 21) && (oppTotal <= 21) ){
		return win;
	}else if( (myTotal <= 21) && (oppTotal > 21)){
		return lose;
	}else{ // neither exceed 21
		if(myTotal < oppTotal){
			return win;
		}else{
			return lose;
		}
	}

}

// start a new game
// before starting a new game, check if there are enough cards left for 
// the next game.

void
BJackDealer::start(void) {
	if(first_time_playing == 0){
		shuffle();
		first_time_playing++;
	}
	if( ((kNCards * num_decks) - top_of_the_mixed_decks_index) < (17*num_decks) ){
		top_of_the_mixed_decks_index = 0;
		shuffle(rand());
	}

	first_card_is_faced_up = false;
	num_cards_in_hand = 0;
}

// shuffle the deck of cards
void 
BJackDealer::shuffle(void) {
	//srand(rand_seed);
	int total_card_num;
	int swap_index;
	int temp_i;
	total_card_num = (kNCards * num_decks);

	if(all_cards == NULL){
		all_cards = new int[total_card_num];
	}

	// init the whole mixed deck
	for(int i = 0; i < num_decks; i++){
		for(int v = 0; v < kNCards; v++){
			all_cards[(kNCards * i) + v] = v;
		}
	}

	// start shuffling the mixed deck
	for(int i = 0; i < total_card_num; i++){
		swap_index = (rand() % (total_card_num - i));
		temp_i = all_cards[swap_index];
		all_cards[swap_index] = all_cards[total_card_num -1 - i];
		all_cards[total_card_num -1 -i] = temp_i;
	}

	rand_seed ++;

}

// reset the seed before shuffling
void
BJackDealer::shuffle(long seed) {
	rand_seed = seed;
	srand(rand_seed);
	int total_card_num;
	int swap_index;
	int temp_i;
	total_card_num = (kNCards * num_decks);

	if(all_cards == NULL){
		all_cards = new int[total_card_num];
	}

	// init the whole mixed deck
	for(int i = 0; i < num_decks; i++){
		for(int v = 0; v < kNCards; v++){
			all_cards[(kNCards * i) + v] = v;
		}
	}

	// start shuffling the mixed deck
	for(int i = 0; i < total_card_num; i++){
		swap_index = (rand() % (total_card_num - i));
		temp_i = all_cards[swap_index];
		all_cards[swap_index] = all_cards[total_card_num -1 - i];
		all_cards[total_card_num -1 -i] = temp_i;
	}

	rand_seed ++;

}

// open the dealer's first card 
void 
BJackDealer::openFirstCard(void) {
	first_card_is_faced_up = true;
}

// show the dealer's hand to the screen
void 
BJackDealer::showCards(void) const {
	unsigned char s,p;
	char line[kCardWidth+1];
	int curCard=0, lastCard;

	while(curCard < num_cards_in_hand) {
		for(int i=0;i<kCardHeight;i++) {
			if(num_cards_in_hand > (curCard + kNCardPerRow) ){
				lastCard = curCard + kNCardPerRow;
			}else{
				lastCard = num_cards_in_hand;
			}

			if (i < int(name_of_dealer.length())) {
				cout << name_of_dealer[i] << " ";
			} else {
				cout << "  ";
			}
			for(int j=curCard;j<lastCard;j++) {
				s=cards_in_hand[j].getSuit();
				p=cards_in_hand[j].getPip();
				if ((j==0)&&(first_card_is_faced_up==false))
					p=13;
				for(int k=0;k<kCardWidth;k++) {
					line[k]=card[p][i][k];
					if (line[k]=='x')
						line[k]=cardAbbrev[s];
				}
				line[kCardWidth]='\0';
				AnsiPrint(line,cardColor[s],white);
				cout << " ";
			}
			cout << endl;
		}
		curCard=lastCard;
	}

	/*cout<<"dealer:\n";
	for(int i = 0; i < num_cards_in_hand; i++){
		cout << cards_in_hand[i].getID() << "(" <<cards_in_hand[i].getPip()+1<<")"<<" ";
	}
	cout<<"\n";*/

}

