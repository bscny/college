#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	//char a='k';
	int len,instruction;
	scanf("%d %d",&len,&instruction);
	char str[len+1];
	scanf("%s",str);
	int mode,first,numsecond=0;
	char second[100];
	char checker[100];
	int mid,i,counter=0;
	
	while(scanf("%d%d%s",&mode,&first,second) != EOF){
		switch(mode){
			case 1:
				//replace
				str[first-1]=second[0];
				//printf("%s %d %c\n",str,first,second[0]);
				break;
			case 2:
				//check
				numsecond=atoi(second);
				counter=0;
				if((numsecond-first)%2 == 0){
					//mid
					mid=(first+numsecond)/2;
					i=0;
					while(first<mid){
						checker[i]=str[first-1];
						i++;
						first++;
					}
					i--;
					while(mid<numsecond){
						if(checker[i]!=str[mid]){
							printf("NO\n");
							counter=1;
							break;
						}
						i--;
						mid++;
					}
					if(counter==0){
						printf("YES\n");
					}
				}else{
					//xor
					mid=(first+numsecond-1)/2;
					i=0;
					while(first<=mid){
						checker[i]=str[first-1];
						i++;
						first++;
					}
					i--;
					while(mid<numsecond){
						if(checker[i]!=str[mid]){
							counter=1;
							printf("NO\n");
							break;
						}
						i--;
						mid++;
					}
					if(counter==0){
						printf("YES\n");
					}
				}
				//printf("%s %d %d\n",str,first,numsecond);
				break;
		}
		//printf("%s %d %s\n",str,first,second);
	}

	//printf("%s %d %c",str,first,second);
	

	return 0;
}
