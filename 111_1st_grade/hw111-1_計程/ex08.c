#include<stdio.h>

void walker(int num,char array[num][num],int x,int y){
	char *element=&array[y][x];

	if(x<0 || y<0 || x>=num || y>=num){
		return;
	}
	if(*element != '#'){
		return;
	}

	if(*element == '#'){
		*element='0';
	}
	walker(num,array,x,y-1);
	walker(num,array,x,y+1);
	walker(num,array,x-1,y);
	walker(num,array,x+1,y);
}

int counter(){
	int value=0,num;
	scanf("%d",&num);
	char array[num][num],turn;

	scanf("%c",&turn);
	for(int i=0;i<num;i++){
		for(int k=0;k<num;k++){
			scanf("%c",&array[i][k]);
		}
		scanf("%c",&turn);
	}
	for(int i=0;i<num;i++){
		for(int k=0;k<num;k++){
			if(array[i][k] == '#'){
				walker(num,array,k,i);
				value+=1;
			}
		}
	}
	/*printf("-----------------\n");
	for(int i=0;i<num;i++){
		for(int k=0;k<num;k++){
			printf("%c",array[i][k]);
		}
		printf("\n");
	}
	printf("-----------------\n");*/

	return value;
}

int main(int argc,char **argv){
	int round;
	scanf("%d",&round);
	int value[round];

	for(int i=0;i<round;i++){
		value[i]=counter();
	}
	for(int i=0;i<round;i++){
		printf("%d\n",value[i]);
	}

	return 0;
}
