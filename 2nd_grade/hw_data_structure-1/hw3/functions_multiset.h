#ifndef _FUNCTIONS_MULTISET_H
#define _FUNCTIONS_MULTISET_H

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool equivalent(vector<int> multiset_1, vector<int> multiset_2){
	if(multiset_1.size() != multiset_2.size()){
		return false;
	}

	int n = multiset_2.size();

	sort(multiset_1.begin(), multiset_1.end());
	sort(multiset_2.begin(), multiset_2.end());

	for(int i = 0; i < n; i++){
		if(multiset_1[i] != multiset_2[i]){
			return false;
		}
	}

	return true;
}

void display_multiset(const vector<int> &multiset){
	for(int i = 0; i < int(multiset.size()); i++){
		cout << multiset[i] << "\n";
	}
}

#endif
