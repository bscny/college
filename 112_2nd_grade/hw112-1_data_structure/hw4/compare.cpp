#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <vector>
using namespace std;

#define   MIN_POW_N   10
#define   MAX_POW_N   25
#define   REPEATION   10
const int DATA_RANGE = pow(2, 30);

void test_insertion(const int &data_num, unordered_multiset<int> &hash_table, vector<int> &array, double ans[2]){
	if(hash_table.empty() == false || array.empty() == false){
		cout << "ERROR ins\n";
		return ;
	}
	srand(time(NULL));

	double start, end;
	for(int n = 0; n < data_num; n ++){
		int value = rand() % DATA_RANGE;

		start = clock();
		hash_table.insert(value);
		end = clock();
		ans[0] += (end - start);

		start = clock();
		array.push_back(value);
		end = clock();
		ans[1] += (end - start);
	}
}

int main(int argc, char **argv){
	vector<int> array;
	unordered_multiset<int> hash_table;
	fstream p_in_cmp;
	int data_num;
	double ans[2];

	p_in_cmp.open("in_py_cmp", ios::in | ios::out | ios::trunc);

	for(int pow_n = MIN_POW_N; pow_n <= MAX_POW_N; pow_n ++){
		data_num = pow(2, pow_n);
		ans[0] = 0;
		ans[1] = 0;

		cout << pow_n << "\n";

		for(int i = 0; i < REPEATION; i ++){
			test_insertion(data_num, hash_table, array, ans);

			array.clear();
			hash_table.clear();
		}

		for(int i = 0; i < 2; i++){
			p_in_cmp << fixed << (ans[i] / REPEATION) / CLOCKS_PER_SEC << "\n";
		}
	}

	p_in_cmp.close();

	return 0;
}
