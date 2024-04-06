#ifndef _SORTED_ARR_H
#define _SORTED_ARR_H

#include <iostream>
#include <vector>
using namespace std;

class Sorted_Array{
	public:
		Sorted_Array();

		void insert(int in);
		void copy(vector<int> &in);

		void range_query(int small, int big, vector<int> &multiset) const;

	private:
		vector<int> arr;
		int size;

};

#endif
