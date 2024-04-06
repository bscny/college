#include<stdio.h>

int main(int argc,char **argv){
	int num=60;
	int x=10,y,z;
	int counter=0;

	for(x=10;;x++){
		for(y=2*x;;y++){
			for(z=3*x;(x+y+z)<=num;z++){
				if((x+y+z)==num){
					counter+=1;
					printf("1");
				}
			}
		}
	}

	return 0;
}
