#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int job_num = 3;
	int x = 3;
	int min, max;
	int a, b;
	double start, end;
	start = clock();
	for(int i = 0; i < 1000; i ++){
		i ++;
		i --;
	}
	end = clock();
	srand(time(NULL) * (start - end));

	//job_num = rand()%50 + 1;
	//x = rand()%50 + 2;

	printf("%d\n", job_num);
	for(int i = 0; i < job_num; i++){
		min = 1;
		max = x;
		a = rand() % ((max-2) - min + 1) + min;
		b = rand() % (max - (a+1) + 1) + (a+1);
		printf("%d %d\n", a, b);
	}
	printf("1 %d", x);

	return 0;
}
