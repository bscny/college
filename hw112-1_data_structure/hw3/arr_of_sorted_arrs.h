#ifndef _ARR_OF_SORTED_ARRS_H
#define _ARR_OF_SORTED_ARRS_H

#include <iostream>
#include <vector>
using namespace std;

class Array_Sorted_Arrays{
	public:
		Array_Sorted_Arrays();

		void insert(int target);
		void range_query(int small, int big, vector<int> &multiset) const;

		int travel_all() const;

	private:
		vector< vector<int> > arr_arrs;
		int current_arr_num;
		vector<int> arr_final_merge;

};

#endif
