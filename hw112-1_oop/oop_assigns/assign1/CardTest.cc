/* Copyright (c) 1999 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
  NAME
  CardTest.cc
  PURPOSE
  Testing card displaying
  NOTES

  AUTHOR
  Tsai-Yen Li (li@cs.nccu.edu.tw)
  HISTORY
  Tsai-Yen Li - Oct 7, 1999: Created.
 ***************************************************************************/

/* $Log:$ */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
}

#include <iostream>
#include "AnsiPrint.h"
#include "Cards.h"

using namespace std;

/**
 * Print my id 
 */
void PrintMyID(const char *studId) {

	char *str= new char[sizeof(studId)+5];
	// we put string in a buffer first 
	sprintf(str,"ID: %s",studId);
	// print the buffer out with color
	AnsiPrint(str,yellow,red, true, true);
	cout << endl << endl;
	delete [] str;

}


/**
 * PrintUsage
 */
void PrintUsage(const char *progName) {

	assert(progName);
	cout << "Usage: " << progName << " NCards [Seed]" << endl;

}

/**
 * Main Function Call
 */
int main(int argc, char **argv) {

	int ncards=0;  // number of cards to draw
	srand(30);

	if (argc==3) {
		long seed=atoi(argv[2]); // the third argument is the seed
		srand(seed);
		ncards=atoi(argv[1]); // the second argument is the number of cards
	} else if (argc==2) {
		ncards=atoi(argv[1]);
	} else {
		PrintUsage(argv[0]);
		exit(-1);
	}

	if(ncards > 52){
		cout << "Sorry, number of cards can not be greater than 52.\n";

		return 0;
	}

	// You are asked to fill in a few missing statements here

	//init the whole deck
	int deck[52];
	for(int i=0; i<52; i++){
		deck[i] = i+1;
	}

	//get the required cards
	int card_to_deal[ncards];
	int temp_index;
	for(int i=0; i<ncards; i++){
		temp_index = rand()%(52-i);
		card_to_deal[i] = deck[temp_index];
		//cout << card_to_deal[i] << " ";

		deck[temp_index] = deck[51-i];
	}

	//start to print cards
	int start_index = 0;
	while(start_index < ncards){ //there r still cards to print
		if((ncards - start_index) >= 5){ //print out 5 card at once
			//func (pass the card_to_deal[], start_index, 5)
			print_the_card_to_be_deal(card_to_deal, start_index, 5);
			start_index += 5;
		}else{  //print out the card lefted (ncards - start_index) at once
			//func (pass the card_to_deal[], start_index, (ncards - start_index))
			print_the_card_to_be_deal(card_to_deal, start_index, ncards - start_index);
			break;
		}
	}

	// Print my id at the end of the program
	PrintMyID("111703040");

	return 0;

}
