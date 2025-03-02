#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "sort_functions.h"
using namespace std;

#define   MAX_N   26
#define   REPEAT   10

int main(int argc,char **argv){
	vector<int> array_iter_qsort;
	vector<int> array_iter_msort;
	vector<int> array_recur_qsort;
	vector<int> array_recur_msort;
	double start_t, end_t;
	int n, value;
	srand(time(NULL));
	double ans[4];

	for(int ii = 10; ii <= MAX_N; ii++){
		n = pow(2, ii);
		array_iter_qsort.resize(n);
		array_iter_msort.resize(n);
		array_recur_qsort.resize(n);
		array_recur_msort.resize(n);
		ans[0] = ans[1] = ans[2] = ans[3] = 0;
		for(int l = 0; l < REPEAT; l ++){
			for(int i = 0; i < n; i++){
				value = rand()%n;
				array_iter_qsort[i] = array_iter_msort[i] = array_recur_qsort[i] = array_recur_msort[i] = value;
			}

			start_t = clock();
			qsort_hoare_recursive(array_recur_qsort, 0, n-1);
			end_t = clock();
			ans[0] += (end_t - start_t);

			start_t = clock();
			qsort_hoare_iterative(array_iter_qsort, 0, n-1);
			end_t = clock();
			ans[1] += (end_t - start_t);
			
			start_t = clock();
			merge_sort_recursive(array_recur_msort, 0, n-1);
			end_t = clock();
			ans[2] += (end_t - start_t);

			start_t = clock();
			merge_sort_iterative(array_iter_msort, 0, n-1);
			end_t = clock();
			ans[3] += (end_t - start_t);
		}

		for(int i = 0; i < 4; i++){
			cout << fixed << (ans[i] / 10) / CLOCKS_PER_SEC << "\n";
		}

		array_iter_qsort.clear();
		array_iter_msort.clear();
		array_recur_qsort.clear();
		array_recur_msort.clear();

	}


	return 0;
}
