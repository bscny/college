#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "functions_multiset.h"
#include "sorted_arr.h"
#include "skip_list.h"
#include "arr_of_sorted_arrs.h"
#include "backtrace.h"
using namespace std;

#define   POW_N   20

void range_query_std(const vector<int> &arr_std, int small, int big, vector<int> &multiset_std){
	int n = pow(2, POW_N);

	multiset_std.clear();

	for(int i = 0; i < n; i++){
		if( (arr_std[i] >= small) && (arr_std[i] <= big) ){
			multiset_std.push_back(arr_std[i]);
		}
	}
}

int main(int argc, char **argv){
	//debug setting
	set_signal_handler();

	//Sorted_Array sorted_arr;
	//Skip_List_v skip_list_v;
	//Array_Sorted_Arrays arr_s_a;
	vector<int> arr_std;

	//Skip_List_p skip_list_p;
	Skip_List_c_v skip_list_c_v;

	int n = pow(2, POW_N) - 1;
	srand(time(NULL));

	vector<int> multiset_test;
	vector<int> multiset_std;

	for(int i = 0; i < n; i++){
		int val = (rand() % n);
		//skip_list_v.insert(val);
		//arr_s_a.insert(val);
		arr_std.push_back(val);

		//skip_list_p.insert(val);
		skip_list_c_v.insert(val);
	}

	//sort(arr_std.begin(), arr_std.end());
	//sorted_arr.copy(arr_std);

	int a = rand() % n;
	//int a = pow(2, POW_N) + 1;
	//int b = a + pow(2, (rand() % POW_N));
	int b = a + pow(2, POW_N);

	//sorted_arr.range_query(a, b, multiset_test);
	//skip_list_v.range_query(a, b, multiset_test);
	//arr_s_a.range_query(a, b, multiset_test);
	range_query_std(arr_std, a, b, multiset_std);

	skip_list_c_v.range_query(a, b, multiset_test);

	cout << equivalent(multiset_std, multiset_test) << "\n";

	return 0;
}
