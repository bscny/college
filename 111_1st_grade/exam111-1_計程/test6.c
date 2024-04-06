#include<stdio.h>

int main(){
	int people,constraint;
	scanf("%d%d",&people,&constraint);
	int arr[people];
	int counter=0

	for(int i=0;i<people;i++){
		scanf("%d",arr[i]);
		if(arr[i]>=constraint){
			counter++;
		}
	}

	return 0;
}
