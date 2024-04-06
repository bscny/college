#ifndef _SKIP_LIST_H
#define _SKIP_LIST_H

#include <iostream>
#include <vector>
using namespace std;

class Node_v{
	public:
		friend class Skip_List_v;

		Node_v();
		Node_v(int v, int h);
	private:
		int value;
		vector<Node_v*> arr_next;
};

class Skip_List_v{
	public:
		Skip_List_v();
		~Skip_List_v();

		int get_Random_height() const;
		void insert(int target);
		void range_query(int small, int big, vector<int> &multiset) const;

		int travel_bottom();

	private:
		const double probability;  // P of going up
		int current_height;
		Node_v *head;  // will point towards a sentinel first

};

// for compare usage, because Skip_List is tooooo slow, make sure it's pointer's fault
// implementing another version with pure pointer controll

// p stand for pointer
class Node_p{
	public:
		friend class Skip_List_p;

		Node_p();
		Node_p(int v);
	private:
		int value;
		Node_p *next;
		Node_p *down;
};

class Skip_List_p{
	public:
		Skip_List_p();
		~Skip_List_p();
		
		int get_Random_height() const;
		void insert(int target);
		void range_query(int small, int big, vector<int> &multiset) const;

		void set_bottom_head();
		int travel_bottom();

	private:
		const double probability;
		int current_height;
		Node_p *head;
		Node_p *bottom_head;
};

// give a cheating test
// c stand for cheating v stand for vector
class Node_c_v{
	public:
		friend class Skip_List_c_v;

		Node_c_v();
		Node_c_v(int v, int h);
	private:
		int value;
		int repeated_num;
		vector<Node_c_v*> arr_next;
};

class Skip_List_c_v{
	public:
		Skip_List_c_v();
		~Skip_List_c_v();

		int get_Random_height() const;
		void insert(int target);
		void range_query(int small, int big, vector<int> &multiset) const;

		int travel_bottom();

		void display();

	private:
		const double probability;  // P of going up
		int current_height;
		Node_c_v *head;  // will point towards a sentinel first

};

#endif
