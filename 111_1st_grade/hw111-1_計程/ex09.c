#include<stdio.h>
#include<stdlib.h>

int main(int argc,char **argv){
	char array[1000],str[100];
	int value=0,teller=0;
	int i=0,k=0;

	while(scanf("%s",array) != EOF){
		i=0;
		k=0;
		teller=0;
		value=0;
		while(1){
			if((array[i]>='0'&&array[i]<='9') || array[i]=='-'){
				str[k]=array[i];
				teller=1;
				k+=1;
			}else if(teller==1){
				str[k]='\0';
				teller=0;
				k=0;
				value+=atoi(str);
			}
			if(array[i]=='\0'){
				break;
			}
			i+=1;
		}
		printf("%d\n",value);
	}
}
