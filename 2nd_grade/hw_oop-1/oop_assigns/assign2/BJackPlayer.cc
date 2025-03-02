/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     BJackPlayer.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct. 5, 1998: Created.
***************************************************************************/

/* $Log: BJackPlayer.cc,v $
 * */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

using namespace std;
#include <iostream>
#include "AnsiPrint.h"
#include "CardPat.h"
#include "BJackPlayer.h"
#include "Card.h"
#include <string>

// default constructor: simply initialize the number of cards to 0
BJackPlayer::BJackPlayer(const char *input_name) {
	player_name = input_name;
	player_hand_card_num = 0;
	max_point = 0;
	min_point = 0;
	show_the_first_hand = false;
	is_busted = false;
}

// start the black jack game with a new card
void
BJackPlayer::start(void) {
	player_hand_card_num = 0;
	max_point = 0;
	min_point = 0;
	show_the_first_hand = false;
	is_busted = false;
}

// add a new card to the current hand.
// need to protect the array from overflowing
void 
BJackPlayer::addCard(Card newCard) {
	player_hand[player_hand_card_num] = newCard;
	player_hand_card_num ++;
}

// get the total points of the current hand in a black jack game
// cards with face vaules above 10 are treated as 10
// Ace's can be treated as 1 or 11 points

int
BJackPlayer::totalPoints(void) {
	int value_card;
	bool the_first_ACE_in_the_hand = true;
	max_point = 0;
	min_point = 0;

	for(int i = 0; i < player_hand_card_num; i++){
		if((player_hand[i].getPip() == 1) && (the_first_ACE_in_the_hand == true)){ // u got 2 possible points
			max_point += 11;
			min_point += 1;
		}else if(player_hand[i].getPip() > 10){
			max_point += 10;
			min_point += 10;
		}else{
			value_card = player_hand[i].getPip();

			max_point += value_card;
			min_point += value_card;
		}
	}

	/* normal return value
	if(max_point <= 21){
		return max_point;
	}else if(min_point <= 21){
		return min_point;
	}else{
		is_busted = true;
		return min_point;
	}
	*/

	// only in this assigment we need return this
	return min_point;
}

// set the status of the first card

void
BJackPlayer::openFirstCard(bool input_showFirst) {
	show_the_first_hand = input_showFirst;
}

// print the current hand to the screen graphically

void 
BJackPlayer::showCards() const {
	int card_current_printing = 0;
	int current_pip;
	int current_suit;
	char replc[2];
	int index_of_name = 0;

	while(card_current_printing < player_hand_card_num){ // there r still cards to print out
		index_of_name = 0;

		if((player_hand_card_num - card_current_printing) >= kNCardPerRow){ // print out kNCardPerRow cards at once
			
			for(int height = 0; height < kCardHeight; height++){ // print layer by layer
				if(player_name[index_of_name] != '\0'){
					cout << player_name[index_of_name] << " ";
					index_of_name ++;
				}else{
					cout<< "  ";
				}
				
				for(int cnum = 0; cnum < kNCardPerRow; cnum++){ // print each card
					current_pip = player_hand[card_current_printing + cnum].getPip();
					current_suit = player_hand[card_current_printing + cnum].getSuit();

					//special case: the first card
					if(((card_current_printing + cnum) == 0) && (show_the_first_hand == false)){
						AnsiPrint(card[13][height], black, white, false, false);
						cout << " ";
						continue;
					}

					if((current_suit == CLUB) || (current_suit == SPADE)){
						for(int i = 0; i < kCardWidth; i++){ // each element in one card
							if(card[current_pip - 1][height][i] == 'x'){
								player_hand[card_current_printing + cnum].print();
							}else{
								replc[0] = card[current_pip - 1][height][i];
								replc[1] = '\0';
								AnsiPrint(replc, black, white, false, false);
							}
						}
					}else{
						for(int i = 0; i < kCardWidth; i++){ // each element in one card
							if(card[current_pip - 1][height][i] == 'x'){
								player_hand[card_current_printing + cnum].print();
							}else{
								replc[0] = card[current_pip - 1][height][i];
								replc[1] = '\0';
								AnsiPrint(replc, red, white, false, false);
							}
						}
					}

					cout << " ";
				}

				cout << "\n";
			}

			cout << "\n";
			card_current_printing += kNCardPerRow;

		}else{  // print out (player_hand_card_num - card_current_printing) cards which is lefted
			
			for(int height = 0; height < kCardHeight; height++){ // print layer by layer
				if(player_name[index_of_name] != '\0'){
					cout << player_name[index_of_name] << " ";
					index_of_name ++;
				}else{
					cout << "  ";
				}
				
				for(int cnum = 0; cnum < (player_hand_card_num - card_current_printing); cnum++){ // print each card
					current_pip = player_hand[card_current_printing + cnum].getPip();
					current_suit = player_hand[card_current_printing + cnum].getSuit();

					//special case: the first card
					if(((card_current_printing + cnum)  == 0) && (show_the_first_hand == false)){
						AnsiPrint(card[13][height], black, white, false, false);
						cout << " ";
						continue;
					}

					if((current_suit == CLUB) || (current_suit == SPADE)){
						for(int i = 0; i < kCardWidth; i++){ // each element in one card
							if(card[current_pip - 1][height][i] == 'x'){
								player_hand[card_current_printing + cnum].print();
							}else{
								replc[0] = card[current_pip - 1][height][i];
								replc[1] = '\0';
								AnsiPrint(replc, black, white, false, false);
							}
						}
					}else{
						for(int i = 0; i < kCardWidth; i++){ // each element in one card
							if(card[current_pip - 1][height][i] == 'x'){
								player_hand[card_current_printing + cnum].print();
							}else{
								replc[0] = card[current_pip - 1][height][i];
								replc[1] = '\0';
								AnsiPrint(replc, red, white, false, false);
							}
						}
					}

					cout << " ";
				}

				cout << "\n";
			}

			cout << "\n";
			card_current_printing += (player_hand_card_num - card_current_printing);
		}
	}

	cout << "Total points: " << min_point << "\n";
}

