#include<stdio.h>

int count(int x){  
	x = (x & 0x55555555) + ((x & 0xaaaaaaaa) >> 1);  
	x = (x & 0x33333333) + ((x & 0xcccccccc) >> 2);  
	x = (x & 0x0f0f0f0f) + ((x & 0xf0f0f0f0) >> 4);  
	x = (x & 0x00ff00ff) + ((x & 0xff00ff00) >> 8);  
	x = (x & 0x0000ffff) + ((x & 0xffff0000) >> 16);  
	
	return x;  
}

void level_1(){
	int num=0;
	int value;

	while(scanf("%d",&value) != EOF){
		if(count(value)==1){
			num+=1;
		}
	}
	printf("%d",num);
}

void level_2(){
	int value,ans=0;

	while(scanf("%d",&value) != EOF){
		ans=ans^value;
	}
	printf("%d",ans);
}

int main(){
	int mode;
	scanf("%d",&mode);
	switch(mode){
		case 1:
			level_1();
			break;
		case 2:
			level_2();
			break;
		default:
			printf("Wrong level number!");
			break;
	}
	return 0;
}

