#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "skip_list.h"
#include "arr_of_sorted_arrs.h"
using namespace std;

#define	  POW_N   20
#define   REPEATION   10

class Node{
	public:
		friend class My_list;

		Node(int v = -1){
			value = v;
			next = nullptr;
		}
	private:
		int value;
		Node *next;
};

class My_list{
	public:
		My_list(){
			head = nullptr;
			tail = nullptr;
		}
		~My_list(){
			Node *kill;
			if(head != nullptr){
				kill = head;
				head = head->next;
				delete kill;
			}
		}

		void push(int in_v){
			if(head == nullptr){
				head = new Node(in_v);
				tail = head;
			}else{
				Node *temp = new Node(in_v);
				tail->next = temp;
				tail = temp;
			}
		}

		int sum(){
			int sum = 0;
			Node *temp = head;
			while(temp != nullptr){
				sum += temp->value;
				temp = temp->next;
			}

			return sum;
		}
	private:
		Node *head;
		Node *tail;
};

int main(int argc, char **argv){
	list<int> std_list;
	My_list test_list;
	vector<int> std_array;
	Skip_List_v sk_list_vector;
	Skip_List_p sk_list_pointer;
	Skip_List_c_v sk_list_cheat_vector;
	Array_Sorted_Arrays arr_o_s_arr;
	int sum_std_list = 0, sum_mine = 0, sum_std_arr = 0, sum_sk_v = 0, sum_sk_p = 0, sum_sk_c_v = 0, sum_arr_o_arr = 0;
	int data_num = pow(2, POW_N) - 1;
	double ans[7] = {0, 0, 0, 0, 0, 0, 0};
	double start_t, end_t;
	srand(time(NULL));
	fstream p_in;

	p_in.open("result_linked_list_cmp", ios::in | ios::out | ios::app);

	// input data to ds
	for(int i = 0; i < data_num; i++){
		int val;
		cin >> val;

		std_list.push_back(val);
		std_array.push_back(val);
		test_list.push(val);
		sk_list_vector.insert(val);
		sk_list_pointer.insert(val);
		sk_list_cheat_vector.insert(val);
		arr_o_s_arr.insert(val);
	}

	for(int i = 0; i < REPEATION; i ++){
		sum_std_list = 0;
		start_t = clock();
		for(list<int>::iterator it = std_list.begin(); it != std_list.end(); it++){
			sum_std_list += *it;
		}
		end_t = clock();
		ans[0] += (end_t - start_t);

		start_t = clock();
		sum_mine = test_list.sum();
		end_t = clock();
		ans[1] += (end_t - start_t);

		sum_std_arr = 0;
		start_t = clock();
		for(int i = 0; i < data_num; i++){
			sum_std_arr += std_array[i];
		}
		end_t = clock();
		ans[2] += (end_t - start_t);

		start_t = clock();
		sum_sk_v = sk_list_vector.travel_bottom();
		end_t = clock();
		ans[3] += (end_t - start_t);

		sk_list_pointer.set_bottom_head();
		start_t = clock();
		sum_sk_p = sk_list_pointer.travel_bottom();
		end_t = clock();
		ans[4] += (end_t - start_t);

		start_t = clock();
		sum_sk_c_v = sk_list_cheat_vector.travel_bottom();
		end_t = clock();
		ans[5] += (end_t - start_t);

		start_t = clock();
		sum_arr_o_arr = arr_o_s_arr.travel_all();
		end_t = clock();
		ans[6] += (end_t - start_t);

		if((sum_std_list == sum_mine) && (sum_std_arr == sum_mine) && (sum_sk_v == sum_mine) && (sum_sk_p == sum_mine) && (sum_sk_c_v == sum_mine) && (sum_arr_o_arr == sum_mine)){

		}else{
			cout << "ERROR\n";
			cout << sum_std_list << " " << sum_mine << " " << sum_std_arr << " " << sum_sk_p << " " << sum_sk_c_v << "\n";
			return 0;
		}
	}

	p_in << "when n=2^" << POW_N << ", the time to travel all nodes\n\n";
	p_in << "STL's link list: ";
	p_in << fixed << (ans[0] / REPEATION) / CLOCKS_PER_SEC << "\n";
	p_in << "My link list: ";
	p_in << fixed << (ans[1] / REPEATION) / CLOCKS_PER_SEC << "\n";
	p_in << "STL's array: ";
	p_in << fixed << (ans[2] / REPEATION) / CLOCKS_PER_SEC << "\n";
	p_in << "skip list + vector: ";
	p_in << fixed << (ans[3] / REPEATION) / CLOCKS_PER_SEC << "\n";
	p_in << "skip list + pointer: ";
	p_in << fixed << (ans[4] / REPEATION) / CLOCKS_PER_SEC << "\n";
	p_in << "skip list + vector with no repeation: ";
	p_in << fixed << (ans[5] / REPEATION) / CLOCKS_PER_SEC << "\n";
	p_in << "array of sorted arrays: ";
	p_in << fixed << (ans[6] / REPEATION) / CLOCKS_PER_SEC << "\n";



	p_in.close();

	return 0;
}
