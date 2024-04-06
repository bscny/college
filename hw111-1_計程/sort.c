#include<stdio.h>
#include<stdlib.h>

int compare(const void *a,const void *b){
	int c=*(int*) a;
	int d=*(int*) b;
	return c-d;
}

int main(int argc,char **argv){
	int datanum;
	scanf("%d",&datanum);
	int array[datanum];

	for(int i=0;i<datanum;i++){
		scanf("%d",&array[i]);
	}

	/*for(int i=1;i<datanum;i++){
		current=i;
		for(int k=i-1;k>=0;k--){
			if(array[current]<array[k]){
				temp=array[k];
				array[k]=array[current];
				array[current]=temp;
				current=k;
			}
		}
	}*/
	qsort(array,datanum,sizeof(int),compare);

	for(int i=0;i<datanum;i++){
		printf("%d ",array[i]);
	}

	return 0;
}
