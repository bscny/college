/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     BJackGame.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 12, 1998: Created.
***************************************************************************/

/* $Log:$ */

#include <iostream>
#include "AnsiPrint.h"
#include "Card.h"
#include "BJackGame.h"
#include "BJackPlayer.h"
#include "BJackDealer.h"

using namespace std;

// only constructor
// Must be given a valid (initialized) game player and dealer
// Menu is constructed internally to provide basic text interface
// We must use an initialization list here.
BJackGame::BJackGame(BJackPlayer &bjp, BJackDealer &bjd) : menu(sizeof(menuItems)/sizeof(char *),menuItems), bjplayer(bjp), bjdealer(bjd){
	game_started = false;
	chip_of_player = initCredit;
	chip_of_dealer = initCredit;

}

// one run of the game
// take and process a user action
// show current hands for both players at the end of a run.
bool
BJackGame::oneRun() {
	menu.print();
	int mode;
	mode = menu.getAnswer();

	switch(mode){
		case 1:
			//one more card
			moreCard();
			break;
		case 2:
			//enough
			enough();
			break;
		case 3:
			//restart
			restart();
			break;
		case 4:
			//quit
			return false;
			break;
	}

	return true;
  
}

// give the player one more card
// check if we can do that first
void 
BJackGame::moreCard() {
	if(game_started == false){
		cout << "Game Over\n";
		bjplayer.showCards();
		bjdealer.showCards();
		return ;
	}

	if(bjplayer.totalPoints() > 21){
		cout << "You are over 21 already\n";
		bjplayer.showCards();
		bjdealer.showCards();
		return ;
	}

	int cardID_for_player;

	cardID_for_player = bjdealer.giveCard();

	Card card_for_player(cardID_for_player);

	bjplayer.addCard(card_for_player);
	
	bjplayer.showCards();
	bjdealer.showCards();
}

// give the dealer enough cards to try to win the player
// determine who win the game at the end
void 
BJackGame::enough() {
	if(game_started == false){
		cout << "Game Over\n";
		bjplayer.showCards();
		bjdealer.showCards();
		return ;
	}

	int current_point_of_player;
	result res_of_each_round;

	current_point_of_player = bjplayer.totalPoints();

	bjdealer.addCards(current_point_of_player);

	res_of_each_round = bjdealer.judge(current_point_of_player);

	if(res_of_each_round == tie){
		cout << "It's a Tie.(You have " << chip_of_player << " Credits, I have " << chip_of_dealer << " Credits.)\n";

	}else if(res_of_each_round == lose){
		chip_of_player --;
		chip_of_dealer ++;
		cout << "I win. Try again.(You have " << chip_of_player << " Credits, I have " << chip_of_dealer << " Credits.)\n";

	}else if(res_of_each_round == win){
		chip_of_player ++;
		chip_of_dealer --;
		cout << "You win. Good job.(You have " << chip_of_player << " Credits, I have " << chip_of_dealer << " Credits.)\n";

	}

	bjplayer.showCards();

	bjdealer.openFirstCard();
	bjdealer.showCards();

	game_started = false;

}

// restart the game by giving each player two new cards
// need to check if any one broke (bankrupt).
void 
BJackGame::restart() {
	if((chip_of_player == 0) || (chip_of_dealer == 0)){
		cout << "Sorry. Game over. No loan here.\n";
		bjplayer.showCards();
		bjdealer.showCards();
		return ;
	bjdealer.showCards();
	}

	if(game_started == true){
		cout << "Game is not over yet. Choose 'enough' to end a game\n";
		bjplayer.showCards();
		bjdealer.showCards();
		return ;
	}else{
		game_started = true;
	}

	bjdealer.start();
	bjplayer.start();

	bjplayer.openFirstCard();

	int cardID_for_player;
	Card card_for_player;

	for(int i = 0; i < 2; i++){
		cardID_for_player = bjdealer.giveCard();
		card_for_player.setID(cardID_for_player);

		bjplayer.addCard(card_for_player);

		cardID_for_player = bjdealer.giveCard();
		card_for_player.setID(cardID_for_player);

		bjdealer.addCard(card_for_player);
	}

	bjplayer.showCards();

	bjdealer.showCards();
}

