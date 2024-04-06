#include<stdio.h>

int main(int argc,char **argv){
	float height=0,weight=0;
	float bmi=0;

	scanf("%f",&height);
	scanf("%f",&weight);
	bmi=(10000*weight)/(height*height);
	printf("%.2f",bmi);
	
	return 0;
}

