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
BJackDealer::BJackDealer(int nSet) : BJackPlayer("Dealer"){
	num_decks = nSet;
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

// give the dealer as many cards as necessary to exceed the player 
// of the given total points
// A special case happen when both of them have 21 points.
// It is a tie game and therefore the dealer does not get more cards.

void
BJackDealer::addCards(int oppTotal) {
	int current_point = 0;
	int cardID_for_dealer;
	Card card_for_dealer;

	while(1){
		current_point = 0;

		current_point = this->totalPoints();

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
		cardID_for_dealer = giveCard();
		card_for_dealer.setID(cardID_for_dealer);

		this->addCard(card_for_dealer);

	}

}

// Determine who has win the game.
// The total points that the dealer has should be greater than 
// the player at the point this function is called.

result
BJackDealer::judge(int oppTotal) const {
	int myTotal = 0;

	myTotal = this->totalPoints();

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

	this->BJackPlayer::start();
}

// shuffle the deck of cards
void 
BJackDealer::shuffle(void) {
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

