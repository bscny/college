#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<list>
using namespace std;

#define   k   9
#define   MAX_h   20
#define   fir_experiment   0
#define   sec_experiment   1

typedef struct data{
	int num;
	int foo[int(pow(2, k)) -1];
}tData;

void time_calculator_for_each_n(int n, double *time_array_used, double *time_list_used){
	double start_array, start_list, end_array, end_list;
	tData temp;
	srand(time(NULL));
	vector<tData> array;
	list<tData> linkedlist;

	//experiment 1: give n value
	//array
	start_array = clock();
	for(int i = 0; i < n; i++){
		temp.num = rand()%10000;
		
		array.push_back(temp);
	}
	end_array = clock();
	
	//linkedlist
	start_list = clock();
	for(int i = 0; i < n; i++){
		temp.num = rand()%10000;
		
		linkedlist.push_back(temp);
	}
	end_list = clock();

	time_array_used[fir_experiment] = ((end_array - start_array) / CLOCKS_PER_SEC);
	time_list_used[fir_experiment] = ((end_list - start_list) / CLOCKS_PER_SEC);

	//experiment 2: add n object
	long long int sum_array, sum_list;

	//array
	start_array = clock();
	for(int i = 0; i < n; i++){
		sum_list += array[i].num;
	}
	end_array = clock();

	//linkedlist
	start_list = clock();
	for(list<tData>::iterator it = linkedlist.begin(); it != linkedlist.end(); it++){
		sum_array += it->num;
	}
	end_list = clock();

	time_array_used[sec_experiment] = ((end_array - start_array) / CLOCKS_PER_SEC);
	time_list_used[sec_experiment] = ((end_list - start_list) / CLOCKS_PER_SEC);
}

int main(int argc, char **argv){
	double time_array_used[2], time_list_used[2];
	double average_time_array_used[2], average_time_list_used[2];

	for(int h = 10; h <= MAX_h; h++){ // each h
		average_time_array_used[fir_experiment] = 0;
		average_time_array_used[sec_experiment] = 0;
		average_time_list_used[fir_experiment] = 0;
		average_time_list_used[sec_experiment] = 0;
		for(int i = 0; i < 10; i++){ // do 10 times
			time_calculator_for_each_n(pow(2, h), time_array_used, time_list_used);

			average_time_array_used[fir_experiment] += time_array_used[fir_experiment];
			average_time_array_used[sec_experiment] += time_array_used[sec_experiment];
			average_time_list_used[fir_experiment] += time_list_used[fir_experiment];
			average_time_list_used[sec_experiment] += time_list_used[sec_experiment];
		}
		average_time_array_used[fir_experiment] /= 10;
		average_time_array_used[sec_experiment] /= 10;
		average_time_list_used[fir_experiment] /= 10;
		average_time_list_used[sec_experiment] /= 10;

		cout << fixed << average_time_array_used[fir_experiment] << "\n" << average_time_list_used[fir_experiment]  << "\n";
		cout << fixed << average_time_array_used[sec_experiment] << "\n" << average_time_list_used[sec_experiment]  << "\n";
	}

	return 0;
}
