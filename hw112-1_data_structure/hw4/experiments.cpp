#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <set>
using namespace std;

#define   MIN_POW_N   10
#define   MAX_POW_N   25
#define   REPEATION   10
const int DATA_RANGE = pow(2, 30);

void test_insertion(const int &data_num, unordered_multiset<int> &hash_table, multiset<int> &bstree, double ans_ex1[2]){
	if(hash_table.empty() == false || bstree.empty() == false){
		cout << "ERROR ins\n";
		return ;
	}
	srand(time(NULL));

	double start, end;
	for(int n = 0; n < data_num; n ++){
		int value = rand() % DATA_RANGE;
		/*int value = rand() % (DATA_RANGE / 2);
		value *= 2;*/
		/*if(hash_table.count(value) != 0){
			n--;
			continue;
		}*/

		start = clock();
		hash_table.insert(value);
		end = clock();
		ans_ex1[0] += (end - start);

		start = clock();
		bstree.insert(value);
		end = clock();
		ans_ex1[1] += (end - start);
	}
}

void test_find(const int &data_num, unordered_multiset<int> &hash_table, multiset<int> &bstree, double ans_ex2[2]){
	if(hash_table.size() != bstree.size()){
		cout << "ERROR diff size\n";
		return ;
	}else if(int(hash_table.size()) != data_num){
		cout << "ERROR weong data size\n";
		return ;
	}
	srand(time(NULL));

	double start, end;
	for(int i = 0; i < 10000; i ++){
		int value = rand() % DATA_RANGE;
		//int value = -1;
		//int value = -1 * (rand() % DATA_RANGE);
		/*int value = rand() % (DATA_RANGE / 2);
		value *= 2;
		value += 1;*/
		int temp;

		start = clock();
		temp = hash_table.count(value);
		end = clock();
		ans_ex2[0] += (end - start);

		/*if(temp != 0){
			cout << "ERROR\n";
			return ;
		}*/

		start = clock();
		temp = bstree.count(value);
		end = clock();
		ans_ex2[1] += (end - start);

		/*if(temp != 0){
			cout << "ERROR\n";
			return ;
		}*/
	}
}

int main(int argc, char **argv){
	multiset<int> bstree;
	unordered_multiset<int> hash_table;
	fstream p_in_ex1, p_in_ex2;
	int data_num;
	double ans_ex1[2];
	double ans_ex2[2];

	p_in_ex1.open("in_py_ex1", ios::in | ios::out | ios::trunc);
	p_in_ex2.open("in_py_ex2", ios::in | ios::out | ios::trunc);

	for(int pow_n = MIN_POW_N; pow_n <= MAX_POW_N; pow_n ++){
		data_num = pow(2, pow_n);
		ans_ex1[0] = 0;
		ans_ex1[1] = 0;
		ans_ex2[0] = 0;
		ans_ex2[1] = 0;

		cout << pow_n << "\n";

		for(int i = 0; i < REPEATION; i ++){
			test_insertion(data_num, hash_table, bstree, ans_ex1);
			test_find(data_num, hash_table, bstree, ans_ex2);

			bstree.clear();
			hash_table.clear();
		}

		for(int i = 0; i < 2; i++){
			p_in_ex1 << fixed << (ans_ex1[i] / REPEATION) / CLOCKS_PER_SEC << "\n";
			p_in_ex2 << fixed << (ans_ex2[i] / REPEATION) / CLOCKS_PER_SEC << "\n";
		}
	}

	p_in_ex1.close();
	p_in_ex2.close();

	return 0;
}
