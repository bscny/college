#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "sort_functions.h"
using namespace std;

#define   VAL_N   19
#define   MAX_K   20
#define   REPEAT   10

int main(int argc,char **argv){
	double start_t, end_t;
	int n, k, value;
	n = pow(2, VAL_N);
	vector<int> array_inssort(n);
    vector<int> array_msort(n);
    vector<int> array_lumoto(n);
    vector<int> array_hoare(n);
    vector<int> array_3way(n);
    vector<int> array_countsort(n);
	srand(time(NULL));
	double ans[6];

	for(int ii = 0; ii <= MAX_K; ii++){
		k = pow(2, ii);
		ans[0] = ans[1] = ans[2] = ans[3] = ans[4] = ans[5] = 0;
		
		for(int l = 0; l < REPEAT; l++){
			for(int i = 0; i < n; i++){
				value = rand() % k;
				array_inssort[i] = array_msort[i] = array_lumoto[i] = value;
				array_hoare[i] = array_3way[i] = array_countsort[i] = value;
			}

			start_t = clock();
			insertion_sort(array_inssort, 0, n-1);
			end_t = clock();
			ans[0] += (end_t - start_t);

			start_t = clock();
			merge_sort_iterative(array_msort, 0, n-1);
			end_t = clock();
			ans[1] += (end_t - start_t);
			
			start_t = clock();
			qsort_lomuto_iterative(array_lumoto, 0, n-1);
			end_t = clock();
			ans[2] += (end_t - start_t);

			start_t = clock();
			qsort_hoare_recursive(array_hoare, 0, n-1);
			end_t = clock();
			ans[3] += (end_t - start_t);

			start_t = clock();
			qsort_3way_recursive(array_3way, 0, n-1);
			end_t = clock();
			ans[4] += (end_t - start_t);

			start_t = clock();
			counting_sort(array_countsort, 0, n-1);
			end_t = clock();
			ans[5] += (end_t - start_t);
		}

		for(int i = 0; i < 6; i++){
			cout << fixed << (ans[i] / 10) / CLOCKS_PER_SEC << "\n";
		}

	}
	array_inssort.clear();
	array_msort.clear();
	array_lumoto.clear();
	array_hoare.clear();
	array_3way.clear();
	array_countsort.clear();


	return 0;
}
