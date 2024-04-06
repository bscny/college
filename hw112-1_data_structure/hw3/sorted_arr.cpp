#include "sorted_arr.h"

Sorted_Array::Sorted_Array(){
	size = 0;
}

void Sorted_Array::insert(int in){
	arr.push_back(in);
	size ++;
	int temp;

	for(int i = size-1; i > 0; i--){
		if(arr[i] < arr[i - 1]){
			// swap
			temp = arr[i];
			arr[i] = arr[i-1];
			arr[i-1] = temp;
		}else{
			break;
		}

	}

}

void Sorted_Array::copy(vector<int> &in){
	size = in.size();
	arr = in;
}

void Sorted_Array::range_query(int small, int big, vector<int> &multiset) const {
	if(size == 0){
		cout << "Empty ds\n";
		return ;
	}else if(size == 1){
		if( (arr[0] >= small) && (arr[0] <= big) ){
			multiset.clear();
			multiset.push_back(arr[0]);
			return ;
		}
	}

	if(multiset.size() != 0){
		// reset multiset
		multiset.clear();
	}

	int mid = 0;
	int start = 0, end = size - 1;

	// finding start
	while(start <= end){
		mid = (start + end) / 2;

		if(arr[mid] > small){
			end = mid - 1;
		}else if(arr[mid] < small){
			start = mid + 1;
		}else{
			break;
		}
	}

	if(arr[mid] == small){
		while( (mid > 0) && (arr[mid] == arr[mid - 1]) ){
			mid --;
		}
	}else if(arr[mid] < small){
		mid ++;
	}

	while(mid < size){
		if(arr[mid] <= big){
			multiset.push_back(arr[mid]);
			mid ++;
		}else{
			break;
		}
	}

}
