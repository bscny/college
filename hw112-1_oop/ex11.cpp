#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main(int argc, char **argv){
	map< char, vector<int> > azmap;
	char c;
	for (c = 'a'; c <= 'z'; c++){
		int now = (int)c - 96;
		vector<int> vect;
		for(int i = 0; i < now; i++){
			vect.push_back(i);
		}
		azmap[c] = vect;
	}

	// reading in
	int command, tar_val;
	char tar_char;
	bool finded;
	
	while(cin >> tar_char){
		cin >> command >> tar_val;
		vector<int> &tar_vec = azmap[tar_char];
		finded = false;

		switch(command){
			case 0:
				for(int i = 0; i < tar_vec.size(); i ++){
					if(tar_vec[i] == tar_val){
						cout << i << " ";
						finded = true;
						break;
					}
				}
				if(finded == false){
					return 0;
				}

				break;
			case 1:
				for(vector<int>::reverse_iterator rit = tar_vec.rbegin(); rit != tar_vec.rend(); rit ++){
					if(*rit == tar_val){
						cout << distance(rit.base(), end(tar_vec)) << " ";
						finded = true;
						break;
					}
				}
				if(finded == false){
					return 0;
				}

				break;
			case 2:
				vector<int> temp_vec;
				for(int i = 0; i < tar_vec.size(); i ++){
					if(i % 2 == 0){
						temp_vec.push_back(tar_vec[i]);
					}
				}
				if(tar_val > temp_vec.size()){
					return 0;
				}else{
					cout << temp_vec[tar_val - 1] << " ";
				}
				break;
		}
	}

	return 0;
}
