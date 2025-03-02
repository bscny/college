#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "skip_list.h"
#include "functions_multiset.h"
using namespace std;

#define   POW_N   20
#define   MAX_POW_K   20
#define   REPEATION   10

int main(int argc, char **argv){
	Skip_List_v skip_list_v;
	Skip_List_p skip_list_p;
	Skip_List_c_v skip_list_c_v;
	vector<int> multiset_skip_list_v, multiset_skip_list_p, multiset_skip_list_c_v;
	int data_num = pow(2, POW_N) - 1;
	double ans[3] = {0, 0, 0};
	double start_t, end_t;
	srand(time(NULL));
	fstream p_in;

	p_in.open("in_py_compare", ios::in | ios::out | ios::trunc);

	// input data to ds
	for(int i = 0; i < data_num; i++){
		int val;
		cin >> val;

		skip_list_v.insert(val);
		skip_list_p.insert(val);
		skip_list_c_v.insert(val);
	}

	for(int pow_k = 0; pow_k <= MAX_POW_K; pow_k ++){
		int k = pow(2, pow_k);
		for(int i = 0; i < REPEATION; i ++){
			int a = rand() % data_num;
			
			multiset_skip_list_v.clear();
			start_t = clock();
			skip_list_v.range_query(a, a+k, multiset_skip_list_v);
			end_t = clock();
			ans[0] += (end_t - start_t);

			multiset_skip_list_p.clear();
			start_t = clock();
			skip_list_p.range_query(a, a+k, multiset_skip_list_p);
			end_t = clock();
			ans[1] += (end_t - start_t);

			multiset_skip_list_c_v.clear();
			start_t = clock();
			skip_list_c_v.range_query(a, a+k, multiset_skip_list_c_v);
			end_t = clock();
			ans[2] += (end_t - start_t);

			if(equivalent(multiset_skip_list_p, multiset_skip_list_v) && equivalent(multiset_skip_list_v, multiset_skip_list_c_v) ){
			
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
