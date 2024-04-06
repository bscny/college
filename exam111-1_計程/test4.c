#include<stdio.h>

int func(char str[51],int i,char target,int support){
	if(str[i+1]=='\0'){
		return 0;
	}

	switch(str[i]){
		case 'H':
			if(target==str[i+1]){
				return func(str,i+1,'a',0);
			}else{
				return 1;
			}
			break;
		case 'a':
			if(target==str[i+1]){
				return func(str,i+1,'p',0);
			}else{
				return 1;
			}
			break;
		case 'p':
			if(support==0){
				if(target==str[i+1]){
					return func(str,i+1,'p',1);
				}else{
					return 1;
				}
			}else{
				if(target==str[i+1]){
					return func(str,i+1,'y',0);
				}else{
					return 1;
				}
			}
			break;
		case 'y':
			if(target==str[i+1]){
				return func(str,i+1,'H',0);
			}else{
				return 1;
			}
			break;
		default:
			return 1;
			break;
	}
}

int main(){
	int i=0;
	int teller;
	int datanum;
	char str[51];
	scanf("%d",&datanum);

	for(int k=0;k<datanum;k++){
		scanf("%s",str);
		switch(str[0]){
			case 'H':
				teller=func(str,i,'a',0);
				break;
			case 'a':
				teller=func(str,i,'p',0);
				break;
			case 'p':
				if(str[1]=='p'){
					teller=func(str,i,'p',1);
				}else{
					teller=func(str,i,'y',0);
				}
				break;
			case 'y':
				teller=func(str,i,'H',0);
				break;
			default:
				printf("SAD\n");
				break;

		}
		if(teller==1){
			printf("SAD\n");
		}else{
			printf("HAPPY\n");
		}
	}

	return 0;
}
