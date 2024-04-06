#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
using namespace std;

#define   POW_N   20

int main(int argc, char **argv){
	srand(time(NULL));
	int n = pow(2, POW_N) - 1;
	fstream p_datas;

	p_datas.open("datas", ios::in | ios::out | ios::trunc);

	for(int i = 0; i < n; i++){
		p_datas << rand() % n << "\n";
	}

	p_datas.close();

	return 0;
}
