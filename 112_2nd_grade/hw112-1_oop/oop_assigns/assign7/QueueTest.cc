/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     QueueTest.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Dec 11, 1998: Created.
***************************************************************************/

/* $Log:$ */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
}

#include <iostream>
#include <fstream>
#include "AnsiPrint.h"
#include "Queue.h"
using namespace std;

/**
 * Print my id 
 */

void
PrintMyID(const char *studId) {

  char *str= new char[strlen(studId)+5];
  sprintf(str,"ID: %s",studId);
  AnsiPrint(str, yellow, red, true, true);
  cout << endl ;
  delete [] str;

}

/**
 * PrintUsage
 */

void
PrintUsage(const char *progName) {

    assert(progName);
	cout << "Usage: " << progName << " intfile [charfile]" << endl;
}

int
main(int argc, char **argv) {

	istream *is1 = &cin, *is2 = &cin;

	if (argc>3) {
		PrintUsage(argv[0]);
		exit(-1);
	} else if (argc>2) {
		is2 = new ifstream(argv[2]);
		if (!(*is2)) {
			cerr << "Can't open file " << argv[2] << endl;
			exit(1);
		}
	} 
	if (argc>1) {
		is1 = new ifstream(argv[1]);
		if (!(*is1)) {
			cerr << "Can't open file " << argv[1] << endl;
			exit(2);
		}
	}

	// You need to provide testing exercises here

	try{
		Queue<int> *int_queue_ptr;
		int_queue_ptr = new Queue<int>;

		int temp_int;
		char temp_char;

		while( (*is1) >> temp_int ){
			int_queue_ptr->enqueue(temp_int);
		}

		// test cp constructor
		Queue<int> int_queue = *int_queue_ptr;
		//test destructor
		delete int_queue_ptr;

		Queue<char> in_char_queue;

		while( (*is2) >> temp_char){
			in_char_queue.enqueue(temp_char);
		}

		Queue<char> char_queue;
		//test cp assigment
		char_queue = in_char_queue;

		//start to dequeue
		AnsiPrint("Interger Queue:\n", yellow, nochange, true, false);
		int n = int_queue.get_Data_num();
		for(int i = 0; i < n; i ++){
			cout << int_queue.dequeue() << "\n";
		}
		AnsiPrint("Character Queue:\n", yellow, nochange, true, false);
		n = char_queue.get_Data_num();
		for(int i = 0; i < n; i ++){
			cout << char_queue.dequeue() << "\n";
		}
		cout << char_queue.dequeue() << "\n";
	}catch(int error){
		switch(error){
			case PROBLEM_1_QUEUE_H:
				AnsiPrint("internal error", red, yellow, true, false);
				cout << "\n";
				break;
			case PROBLEM_2_QUEUE_H:
				AnsiPrint("can't allocate more memory", red, yellow, true, false);
				break;
			case PROBLEM_3_QUEUE_H:
				AnsiPrint("Attempt to dequeue empty queue", red, yellow, true, false);
				cout << "\n";
				break;
		}
	}

	PrintMyID("111703040");
	return 0;
    
}
