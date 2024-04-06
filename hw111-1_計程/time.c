#include<stdio.h>

#define  maxdata  10000

int timechart(char c){
	int array[16]={6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};

	return array[c-'A'];
}

int main(int argc,char **argv){
	char inputstring[maxdata][50];
	int id=0;
	char day[7][4]={"mon","tue","wed","thu","fri","sat","sun"};
	int datanum=0,i=0,charcounter=0;
	int next;
	int nextc;

	while(scanf("%s",inputstring[datanum]) != EOF){
		i=0;
		while(inputstring[datanum][i] != '\0'){
			if(inputstring[datanum][i]=='N'){
				break;
			}
			if(inputstring[datanum][i]!='[' && inputstring[datanum][i]!=']'){
				if(inputstring[datanum][i-1]!='[' || inputstring[datanum][i+1]!=']'){
					switch(inputstring[datanum][i]){
						case '1':
							inputstring[datanum][i]='C';
							break;
						case '2':
							inputstring[datanum][i]='D';
							break;
						case '3':
							inputstring[datanum][i]='E';
							break;
						case '4':
							inputstring[datanum][i]='F';
							break;
						case 'C':
							inputstring[datanum][i]='G';
							break;
						case 'D':
							inputstring[datanum][i]='H';
							break;
						case '5':
							inputstring[datanum][i]='I';
							break;
						case '6':
							inputstring[datanum][i]='J';
							break;
						case '7':
							inputstring[datanum][i]='K';
							break;
						case '8':
							inputstring[datanum][i]='L';
							break;
						case 'E':
							inputstring[datanum][i]='M';
							break;
						case 'F':
							inputstring[datanum][i]='N';
							break;
						case 'G':
							inputstring[datanum][i]='O';
							break;
						case 'H':
							inputstring[datanum][i]='P';
							break;
					}
				}
			}
			i++;
		}
		datanum+=1;
	}

	for(i=0;i<datanum;i++){
		charcounter=0;
		if(inputstring[i][charcounter]=='N'){
			printf("NAN\n");
		}else{
			while(inputstring[i][charcounter] != '\0'){
				if(inputstring[i][charcounter]=='[' && inputstring[i][charcounter+2]==']'){
					switch(inputstring[i][charcounter+1]){
						case '1':
							printf("mon/");
							id=0;
							break;
						case '2':
							printf("tue/");
							id=1;
							break;
						case '3':
							printf("wed/");
							id=2;
							break;
						case '4':
							printf("thu/");
							id=3;
							break;
						case '5':
							printf("fri/");
							id=4;
							break;
						case '6':
							printf("sat/");
							id=5;
							break;
						case '7':
							printf("sun/");
							id=6;
							break;
					}
					charcounter+=1;
				}else if(inputstring[i][charcounter-1]==']'){
					nextc=inputstring[i][charcounter]+1;
					next=charcounter+1;
					printf("%02d",timechart(inputstring[i][charcounter]));
					while(inputstring[i][next] != '\0'){
						if(inputstring[i][next] == nextc){
							next+=1;
							nextc+=1;
						}else if(inputstring[i][next]=='['){
							printf("~%02d, ",1+timechart(inputstring[i][next-1]));
							charcounter=next;
							break;
						}else{
							printf("~%02d, %s/%02d",1+timechart(inputstring[i][next-1]),day[id],timechart(inputstring[i][next]));
							nextc=inputstring[i][next]+1;
							next+=1;
						}
					}
					if(inputstring[i][next] == '\0'){
						charcounter=next;
					}
				}else{
					charcounter+=1;
				}
			}
			printf("~%02d\n",1+timechart(inputstring[i][charcounter-1]));
		}
	}

	return 0;
}

