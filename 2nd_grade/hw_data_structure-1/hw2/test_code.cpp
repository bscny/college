#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include "sort_functions.h"
using namespace std;

#define   MAX_N   19

int main(int argc,char **argv){
	vector<int> array_sample;
	vector<int> array_test;
	int n, value;
	int k = pow(2,20);
	double start, end;
	srand(time(NULL));

	for(int ii = 10; ii <= MAX_N; ii++){
		n = pow(2, ii);
		array_sample.resize(n);
		array_test.resize(n);
		for(int i = 0; i < n; i++){
			value = rand()%k;
			array_sample[i] = value;
			array_test[i] = value;
		}
	
		sort(array_sample.begin(), array_sample.end());
		
		start = clock();
		qsort_lomuto_iterative(array_test, 0, n-1);
		end = clock();

		for(int i = 0; i < n; i++){
			if(array_sample[i] != array_test[i]){
				cout << "WRONG\n";
				return 0;
			}
		}

		cout<<fixed<<(end - start)/CLOCKS_PER_SEC<<endl;

		array_sample.clear();
		array_test.clear();

	}


	return 0;
}
