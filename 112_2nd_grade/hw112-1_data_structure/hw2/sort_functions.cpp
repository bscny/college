#include <iostream>
#include "sort_functions.h"
using namespace std;

inline void swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}

void insertion_sort(vector<int> &arr, int start_index, int end_index){
	int current;
	for(int i = 1; i < (end_index - start_index + 1); i++){
		current = i;
		while(current > 0){
			if(arr[current] < arr[current-1]){
				swap(arr[current], arr[current-1]);
				current --;
			}else{
				break;
			}
		}
	}
}

void merge_sort_recursive(vector<int> &arr, int start_index, int end_index){
	if(start_index >= end_index){
		return;
	}
	int mid = (start_index + end_index) / 2;

	merge_sort_recursive(arr, start_index, mid);
	merge_sort_recursive(arr, mid+1, end_index);

	//init sub arrays
	vector<int> left_sub_arr, right_sub_arr;
	int size_left = (mid - start_index + 1), size_right = (end_index - mid);
	int i;
	left_sub_arr.resize(size_left);
	right_sub_arr.resize(size_right);
	for(i = 0; i < size_right; i++){
		left_sub_arr[i] = arr[start_index + i];
		right_sub_arr[i] = arr[mid + 1 + i];
	}
	left_sub_arr[size_left - 1] = arr[mid];

	int current_index_left = 0, current_index_right = 0;
	int main_index = start_index;

	//merging
	while( (current_index_left < size_left) && (current_index_right < size_right) ){
		if(left_sub_arr[current_index_left] <= right_sub_arr[current_index_right]){
			arr[main_index] = left_sub_arr[current_index_left];
			current_index_left ++;
		}else{
			arr[main_index] = right_sub_arr[current_index_right];
			current_index_right ++;
		}
		main_index ++;
	}

	while(current_index_left < size_left){
		arr[main_index] = left_sub_arr[current_index_left];
		current_index_left ++;
		main_index ++;
	}

	while(current_index_right < size_right){
		arr[main_index] = right_sub_arr[current_index_right];
		current_index_right ++;
		main_index ++;
	}

	left_sub_arr.clear();
	right_sub_arr.clear();
}

void merge_sort_iterative(vector<int> &arr, int start_index, int end_index){
	int sub_arr_size;
	int start_left_sub_arr, mid, end_right_sub_arr;
	vector<int> left_sub_arr, right_sub_arr;
	int current_index_left, current_index_right;
	int size_left, size_right;
	int main_index;
	for(sub_arr_size = 1; sub_arr_size < (end_index - start_index + 1); sub_arr_size *= 2){
		//every segment of sub arrays
		for(start_left_sub_arr = start_index; start_left_sub_arr <= end_index; start_left_sub_arr += 2*sub_arr_size){
			if( (start_left_sub_arr + sub_arr_size - 1) > end_index){
				mid = end_index;
				end_right_sub_arr = end_index;
			}else{
				mid = start_left_sub_arr + sub_arr_size - 1;

				if( (mid + sub_arr_size) > end_index ){
					end_right_sub_arr = end_index;
				}else{
					end_right_sub_arr = mid + sub_arr_size;
				}
			}

			size_left = mid - start_left_sub_arr + 1;
			size_right = end_right_sub_arr - mid;
			left_sub_arr.resize(size_left);
			right_sub_arr.resize(size_right);
			current_index_left = 0;
			current_index_right = 0;
			main_index = start_left_sub_arr;

			//init sub arrays
			if(size_left == size_right){
				for(int i = 0; i < size_left; i++){
					left_sub_arr[i] = arr[start_left_sub_arr + i];
					right_sub_arr[i] = arr[mid + 1 + i];
				}
			}else{
				for(int i = 0; i < size_left; i++){
					left_sub_arr[i] = arr[start_left_sub_arr + i];
				}
				for(int i = 0; i < size_right; i++){
					right_sub_arr[i] = arr[mid + 1 + i];
				}
			}

			//merging
			while( (current_index_left < size_left) && (current_index_right < size_right) ){
				if(left_sub_arr[current_index_left] <= right_sub_arr[current_index_right]){
					arr[main_index] = left_sub_arr[current_index_left];
					current_index_left ++;
				}else{
					arr[main_index] = right_sub_arr[current_index_right];
					current_index_right ++;
				}
				main_index ++;
			}

			while(current_index_left < size_left){
				arr[main_index] = left_sub_arr[current_index_left];
				current_index_left ++;
				main_index ++;
			}

			while(current_index_right < size_right){
				arr[main_index] = right_sub_arr[current_index_right];
				current_index_right ++;
				main_index ++;
			}

			left_sub_arr.clear();
			right_sub_arr.clear();

		}
	}
}

void qsort_hoare_recursive(vector<int> &arr, int start_index, int end_index){
	if(start_index >= end_index){
		return;
	}
	swap(arr[start_index], arr[(start_index + end_index) / 2]);
	int pivot = arr[start_index];
	int smaller = start_index, bigger = end_index;

	while(true){
		while(arr[smaller] < pivot){
			smaller ++;
		}
		while(arr[bigger] > pivot){
			bigger --;
		}

		if(smaller >= bigger){
			break;
		}

		swap(arr[smaller], arr[bigger]);
		smaller ++;
		bigger --;
	}

	qsort_hoare_recursive(arr, start_index, bigger);
	qsort_hoare_recursive(arr, bigger + 1, end_index);
}

void qsort_hoare_iterative(vector<int> &arr, int start_index, int end_index){
	vector<int> stack(end_index - start_index + 1);
	int top = 1;
	stack[0] = start_index;
	stack[1] = end_index;
	int smaller, bigger;
	int pivot;

	while(top >= 0){
		end_index = stack[top--];
		start_index = stack[top--];
		swap(arr[start_index], arr[(start_index + end_index) / 2]);
		pivot = arr[start_index];
		bigger = end_index;
		smaller = start_index;

		while(true){
			while(arr[smaller] < pivot){
				smaller ++;
			}
			while(arr[bigger] > pivot){
				bigger --;
			}

			if(smaller >= bigger){
				break;
			}

			swap(arr[smaller], arr[bigger]);
			smaller ++;
			bigger --;
		}

		if(bigger > start_index){
			stack[++top] = start_index;
			stack[++top] = bigger;
		}

		if( (bigger + 1) < end_index){
			stack[++top] = bigger + 1;
			stack[++top] = end_index;
		}
	}
}

void qsort_lomuto_recursive(vector<int> &arr, int start_index, int end_index){
	if(start_index >= end_index){
		return;
	}
	swap(arr[start_index], arr[(start_index + end_index) / 2]);
	int pivot = arr[start_index];
	int smaller_equal = start_index;
	int current = start_index;
	//make smaller_equal-1 must be pivot
	swap(arr[start_index], arr[end_index]);

	while(current <= end_index){
		if(arr[current] <= pivot){
			swap(arr[current], arr[smaller_equal]);
			current ++;
			smaller_equal ++;
		}else{
			current ++;
		}
	}

	qsort_lomuto_recursive(arr, start_index, smaller_equal - 2);
	qsort_lomuto_recursive(arr, smaller_equal, end_index);
}

void qsort_lomuto_iterative(vector<int> &arr, int start_index, int end_index){
	vector<int> stack(end_index - start_index + 1);
	int top = 1;
	stack[0] = start_index;
	stack[1] = end_index;
	int smaller_equal, current;
	int pivot;

	while(top >= 0){
		end_index = stack[top--];
		start_index = stack[top--];
		swap(arr[start_index], arr[(start_index + end_index) / 2]);
		pivot = arr[start_index];
		smaller_equal = start_index;
		current = start_index;
		//make smaller_equal-1 must be pivot
		swap(arr[start_index], arr[end_index]);

		while(current <= end_index){
			if(arr[current] <= pivot){
				swap(arr[current], arr[smaller_equal]);
				current ++;
				smaller_equal ++;
			}else{
				current ++;
			}
		}

		if(start_index < (smaller_equal - 2) ){
			stack[++top] = start_index;
			stack[++top] = smaller_equal - 2;
		}

		if(smaller_equal < end_index){
			stack[++top] = smaller_equal;
			stack[++top] = end_index;
		}
	}
}

void qsort_3way_recursive(vector<int> &arr, int start_index, int end_index){
	if(start_index >= end_index){
		return;
	}
	swap(arr[start_index], arr[(start_index + end_index) / 2]);
	int pivot = arr[start_index];
	int smaller = start_index, bigger = end_index;
	int current = start_index;

	while(current <= bigger){
		if(arr[current] < pivot){
			swap(arr[current], arr[smaller]);
			current ++;
			smaller ++;
		}else if(arr[current] > pivot){
			swap(arr[current], arr[bigger]);
			bigger --;
		}else{
			current ++;
		}
	}

	qsort_3way_recursive(arr, start_index, smaller - 1);
	qsort_3way_recursive(arr, bigger + 1, end_index);
}

void counting_sort(vector<int> &arr, int start_index, int end_index){
	int max_value = -1;
	int i;
	int n = (end_index - start_index + 1);
	for(i = 0; i < n; i++){
		if(arr[i] > max_value){
			max_value = arr[i];
		}
	}
	vector<int> count_arr(max_value + 1);
	for(i = 0; i < (max_value + 1); i++){
		count_arr[i] = 0;
	}

	for(i = start_index; i < n; i++){
		count_arr[arr[i]] ++;
	}

	int main_index = 0;
	for(i = 0; i < (max_value + 1); i++){
		if(count_arr[i] != 0){
			for(int k = 0; k < count_arr[i]; k++){
				arr[main_index] = i;
				main_index ++;
			}
		}

		if(main_index >= n){
			break;
		}
	}
}
