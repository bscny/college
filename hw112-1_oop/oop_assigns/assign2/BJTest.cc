/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     BJTest.cc
   PURPOSE
     Homework assignment for simulating card game
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 5, 1998: Created.
	 Ming-Te Chi - Oct 1, 2023: revised.
***************************************************************************/

/* $Log: BJTest.cc,v $
 * */

extern "C" {
	#include <stdio.h>
	#include <stdlib.h>
	#include <assert.h>
}

using namespace std;
#include <iostream>
#include "AnsiPrint.h"
#include "Card.h"
#include "BJackPlayer.h"

/**
 * Print my id 
 */

void
PrintMyID(const char* studId) {

	char* str = new char[sizeof(studId)+5];
	sprintf(str, "ID: %s", studId);
	AnsiPrint(str, yellow, red, true, true);
	cout << endl << endl;
	delete [] str;

}


/**
 * PrintUsage
 */

void
PrintUsage(const char* progName) {

	assert(progName);
	cout << "Usage: " << progName << " [Seed] [ShowFirst(0/1)]" << endl;

}

void shuffle_deck(Card *deck, long seed){
	srand(seed);
	int index[kNCards];

	for(int i = 0; i < kNCards; i++){
		index[i] = i;
	}

	//start shuffling
	int temp;
	for(int i = 0; i < kNCards; i++){
		temp = rand() % (kNCards - i);
		deck[i].setID(index[temp]);

		index[temp] = index[kNCards - 1 - i];
	}
}

/**
 * Main Function Call
 */

int
main(int argc, char **argv) {

    bool showFirst = false;
    long seed = 0;

    if (argc==3) {
		showFirst = atoi(argv[2]); // the third argument shows the first card
    	seed=atoi(argv[1]);
	} else if (argc>1) {
		seed=atoi(argv[1]);
    } else {
        PrintUsage(argv[0]);
		exit(-1);
	}

    srand(seed);

    BJackPlayer bjplayer("Player");

    // put your code here

	// set a deck of cards
	Card deck[kNCards];
	// shuffle the deck
	shuffle_deck(deck, seed);


	// start the game
	int top_of_the_deck = 0;

	bjplayer.start();
	bjplayer.addCard(deck[top_of_the_deck]);
	top_of_the_deck ++;
	bjplayer.addCard(deck[top_of_the_deck]);
	top_of_the_deck ++;

	// player or dealer
	bjplayer.openFirstCard(showFirst);

	// add or no
	while(bjplayer.totalPoints() <= 21){
		bjplayer.addCard(deck[top_of_the_deck]);
		top_of_the_deck ++;
	}

	// show hand
	bjplayer.showCards();

    PrintMyID("111703040");
    
    return 0;
}

