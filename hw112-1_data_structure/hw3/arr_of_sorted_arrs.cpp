#include "arr_of_sorted_arrs.h"

Array_Sorted_Arrays::Array_Sorted_Arrays(){
	current_arr_num = 1;
	arr_arrs.resize(1);

	arr_final_merge.resize(1);
}

void Array_Sorted_Arrays::insert(int target){
	// read in the target
	if(arr_arrs[0].size() == 0){
		arr_arrs[0].resize(1, target);
		return ;
	}

	// store target first and merge to main
	arr_final_merge[0] = target;
	int tar_layer = 1;
	vector<int> temp;

	while(1){
		int left_i = 0, right_i = 0, merge_i = 0;
		int n = arr_arrs[tar_layer - 1].size();
		temp.resize(n * 2);

		// merging each layer
		while((left_i < n) && (right_i < n)){
			if(arr_arrs[tar_layer - 1][left_i] <= arr_final_merge[right_i]){
				temp[merge_i] = arr_arrs[tar_layer - 1][left_i];
				left_i ++;
			}else{
				temp[merge_i] = arr_final_merge[right_i];
				right_i ++;
			}

			merge_i ++;

		}
		//element left in the main ds
		while(left_i < n){
			temp[merge_i] = arr_arrs[tar_layer - 1][left_i];
			left_i ++;
			merge_i ++;
		}
		// element left int arr_final_merge
		while(right_i < n){
			temp[merge_i] = arr_final_merge[right_i];
			right_i ++;
			merge_i ++;
		}
		arr_final_merge = temp;  // copy assignment
		arr_arrs[tar_layer - 1].clear();
		tar_layer ++;

		//checking if target layer is availible of input datas
		if(current_arr_num < tar_layer){    //  creat a new layer
			arr_arrs.push_back(arr_final_merge);
			current_arr_num = tar_layer;
			break;
		}else{
			if(arr_arrs[tar_layer - 1].size() == 0){
				arr_arrs[tar_layer - 1] = arr_final_merge;
				break;
			}
		}

	}

}

void Array_Sorted_Arrays::range_query(int small, int big, vector<int> &multiset) const {
	if( (current_arr_num == 1) && (arr_arrs[0].size() == 0) ){
		cout << "Empty ds\n";
		return ;
	}

	if(multiset.size() != 0){
		// reset multiset
		multiset.clear();
	}

	int mid = 0, start, end, size;
	// apply b-search to find RQ in every layer
	for(int layer = 0; layer < current_arr_num; layer ++){
		size = arr_arrs[layer].size();
		start = 0;
		end = size - 1;

		while(start <= end){
			mid = (start + end) / 2;

			if(arr_arrs[layer][mid] > small){
				end = mid - 1;
			}else if(arr_arrs[layer][mid] < small){
				start = mid + 1;
			}else{
				break;
			}
		}

		if(arr_arrs[layer][mid] == small){
			while( (mid > 0) && (arr_arrs[layer][mid] == arr_arrs[layer][mid - 1]) ){
				mid --;
			}
		}else if(arr_arrs[layer][mid] < small){
			mid ++;
		}

		// found the place to start making multiset
		while(mid < size){
			if(arr_arrs[layer][mid] <= big){
				multiset.push_back(arr_arrs[layer][mid]);
				mid ++;
			}else{
				break;
			}
		}

	}

}

int Array_Sorted_Arrays::travel_all() const {
	int ans = 0;
	for(int i = 0; i < current_arr_num; i++){
		int n = arr_arrs[i].size();

		for(int j = 0; j < n; j++){
			ans += arr_arrs[i][j];
		}
	}

	return ans;
}
