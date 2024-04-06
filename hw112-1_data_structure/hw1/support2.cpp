#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<list>
using namespace std;

typedef struct data2{
	int num;
	int foo[int(pow(2,1)) - 1];
}tData_2;

void time_calculator_for_each_n_1(int n, double *time_k_is_1){
	double start_array, end_array;
	tData_2 temp;
	srand(time(NULL));
	vector<tData_2> array;

	for(int i = 0; i < n; i++){
        temp.num = rand()%10000;

        array.push_back(temp);
    }

	long long int sum_array;

	start_array = clock();
    for(int i = 0; i < n; i++){
        sum_array += array[i].num;
    }
    end_array = clock();

	*time_k_is_1 = ((end_array - start_array) / CLOCKS_PER_SEC);
}

int main(int argc, char **argv){
	double time_k_is_9 = 0, time_k_is_1 = 0;
	double average_time_k_is_9 = 0, average_time_k_is_1 = 0;

	for(int h = 10; h <= 28; h++){ // each h
		for(int i = 0; i < 10; i++){ // do 10 times
			time_calculator_for_each_n_1(pow(2, h), &time_k_is_1);

			average_time_k_is_1 += time_k_is_1;
		}
		average_time_k_is_1 /= 10;

		cout << fixed << average_time_k_is_1 << "\n";
	}


	return 0;
}
