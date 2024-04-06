#include<stdio.h>

int main(int argc,char **argv){
	unsigned int value=0x8AAC3;
	int round,x;

	while(scanf("%d",&round) != EOF){
		scanf("%X",&value);
		for(int i=0;i<round;i++){
			scanf("%d",&x);
			value=value&(~(1<<(x)));
		}
		printf("%06X\n",value);
	}

	return 0;
}
