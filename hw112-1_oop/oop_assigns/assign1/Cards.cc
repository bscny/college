/* Copyright (c) 1999 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     Cards.cc
   NOTE
     You are asked to design this module.
     You need to draw the given number of cards and print them out.
     Assume that you are given a deck of 52 cards. The cards do not reappear.
     That is, you do not put a card back into the deck after it is drawn.
***************************************************************************/

//HOW TO PRINT CARD

#include<iostream>
#include"Cards.h"
#include"AnsiPrint.h"
using namespace std;

void print_the_card_to_be_deal(int *card_to_deal, int start_index, int num_of_card_to_print){
	int current_card;
	int current_suit;
	char replc[2];

	for(int height=0; height < kCardHeight; height++){ //print layer by layer
		for(int cnum=start_index ; cnum < (start_index + num_of_card_to_print); cnum++){ //print each card
			current_card = card_to_deal[cnum]%13;
			current_suit = card_to_deal[cnum]/13;

			if(current_suit == CLUB){ //set color to black, replace x to C
				for(int i = 0; i < kCardWidth; i++){
					if(card[current_card][height][i] == 'x'){
						AnsiPrint("C", black, white, false, false);
					}else{
						replc[0] = card[current_card][height][i];
						replc[1] = '\0';
						AnsiPrint(replc, black, white, false, false);
					}
				}
			}else if(current_suit == DIAMOND){ //set color to red, replace x to D
				for(int i = 0; i < kCardWidth; i++){
					if(card[current_card][height][i] == 'x'){
						AnsiPrint("D", red, white, false, false);
					}else{
						replc[0] = card[current_card][height][i];
						replc[1] = '\0';
						AnsiPrint(replc, red, white, false, false);
					}
				}
			}else if(current_suit == HEART){ //set color to red, replace x to H
				for(int i = 0; i < kCardWidth; i++){
					if(card[current_card][height][i] == 'x'){
						AnsiPrint("H", red, white, false, false);
					}else{
						replc[0] = card[current_card][height][i];
						replc[1] = '\0';
						AnsiPrint(replc, red, white, false, false);
					}
				}
			}else{ //set color to black, replace x to S
				for(int i = 0; i < kCardWidth; i++){
					if(card[current_card][height][i] == 'x'){
						AnsiPrint("S", black, white, false, false);
					}else{
						replc[0] = card[current_card][height][i];
						replc[1] = '\0';
						AnsiPrint(replc, black, white, false, false);
					}
				}
			}

			cout << " ";  // finish the row of one card
		}

		cout << "\n"; //finish one row of every card
	}
}
