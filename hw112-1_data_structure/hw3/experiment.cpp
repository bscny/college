#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "arr_of_sorted_arrs.h"
#include "skip_list.h"
#include "sorted_arr.h"
#include "functions_multiset.h"
using namespace std;

#define   POW_N   23
#define   MAX_POW_K   23
#define   REPEATION   10

int main(int argc, char **argv){
	Array_Sorted_Arrays arr_of_sorted_arr;
	Skip_List_p skip_list_p;
	Sorted_Array sorted_arr;
	vector<int> temp;  //  using it to fastened data insert for sorted_arr because it's O(n^2)
	vector<int> multiset_arr_sorted_arr, multiset_skip_list_p, multiset_sorted_arr;
	int data_num = pow(2, POW_N) - 1;
	double ans[3] = {0, 0, 0};
	double start_t, end_t;
	srand(time(NULL));
	fstream p_in;

	p_in.open("in_py", ios::in | ios::out | ios::trunc);

	// input data to ds
	for(int i = 0; i < data_num; i++){
		int val;
		cin >> val;

		arr_of_sorted_arr.insert(val);
		skip_list_p.insert(val);
		temp.push_back(val);
	}
	sort(temp.begin(), temp.end());
	sorted_arr.copy(temp);

	for(int pow_k = 0; pow_k <= MAX_POW_K; pow_k ++){
		int k = pow(2, pow_k);
		for(int i = 0; i < REPEATION; i ++){
			int a = rand() % data_num;
			
			multiset_arr_sorted_arr.clear();
			start_t = clock();
			arr_of_sorted_arr.range_query(a, a+k, multiset_arr_sorted_arr);
			end_t = clock();
			ans[0] += (end_t - start_t);

			multiset_skip_list_p.clear();
			start_t = clock();
			skip_list_p.range_query(a, a+k, multiset_skip_list_p);
			end_t = clock();
			ans[1] += (end_t - start_t);

			multiset_sorted_arr.clear();
			start_t = clock();
			sorted_arr.range_query(a, a+k, multiset_sorted_arr);
			end_t = clock();
			ans[2] += (end_t - start_t);

			if(equivalent(multiset_arr_sorted_arr, multiset_skip_list_p) && equivalent(multiset_skip_list_p, multiset_sorted_arr) ){
			
			}else{
				cout << "ERROR\n";
				return 0;
			}
		}

		for(int i = 0; i < 3; i++){
			p_in << fixed << (ans[i] / REPEATION) / CLOCKS_PER_SEC << "\n";
		}
	}

	p_in.close();

	return 0;
}
