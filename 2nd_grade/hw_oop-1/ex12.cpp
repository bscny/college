#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

void display_map(unordered_map<int , unordered_map<int, char> > &umap, int max_x, int max_y, int cur_x, int cur_y){
	cout << "***************\n";

	for(int y = max_y; y >= 0; y --){
		if(umap.find(y) == umap.end()){
			cout << "\n";
			continue;
		}else{
			for(int x = 0; x <= max_x; x ++){
				cout << "+";
				if(x == cur_x && y == cur_y){
					cout << "H";
				}else{
					cout << " ";
				}
				if(umap[y].find(x) == umap[y].end()){
					cout << "  ";
				}else{
					cout << umap[y][x] << " ";
				}
			}

			cout << "+\n";

		}

	}

	cout << "***************\n";

	/*for(int y = max_y; y >= 0; y--){
		if(umap.find(y) == umap.end()){
			continue;
		}else{
			for(int x = 0; x <= max_x; x++){
				if(umap[y].find(x) == umap[y].end()){
					continue;
				}else{
					cout << umap[y][x] << "\n";
				}
			}
		}
	}*/

}

int main(int argc, char **argv){
	unordered_map<int, unordered_map<int, char> > umap;
	int max_x = 0, max_y = 0;

	int room_num;
	cin >> room_num;
	for(int i = 0; i < room_num; i++){
		int x, y;
		char name;
		string t;
		cin >> x >> t >> x >> y >> t >> name;

		if(x > max_x){
			max_x = x; 
		}
		if(y > max_y){
			max_y = y;
		}

		umap[y][x] = name;
	}

	char move;
	int cur_x = 0, cur_y = 0;
	display_map(umap, max_x, max_y, cur_x, cur_y);

	for(int i = 0; i < 5; i ++){
		cin >> move;
		switch(move){
			case 'n':
				if( (umap.find(cur_y + 1) != umap.end()) && (umap[cur_y + 1].find(cur_x) != umap[cur_y + 1].end()) ){
					cur_y ++;
				}

				break;
			case 'e':
				if( (umap.find(cur_y) != umap.end()) && (umap[cur_y].find(cur_x + 1) != umap[cur_y].end()) ){
					cur_x ++;
				}

				break;
			case 's':
				if( (umap.find(cur_y - 1) != umap.end()) && (umap[cur_y - 1].find(cur_x) != umap[cur_y - 1].end()) ){
					cur_y --;
				}

				break;
			case 'w':
				if( (umap.find(cur_y) != umap.end()) && (umap[cur_y].find(cur_x - 1) != umap[cur_y].end()) ){
					cur_x --;
				}

				break;
		}

		display_map(umap, max_x, max_y, cur_x, cur_y);
	}

	return 0;
}
