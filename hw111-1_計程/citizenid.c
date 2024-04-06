#include <stdio.h>

int convertfunc(char c){
	int list[26] = {1, 0, 9, 8, 7, 6, 5, 4, 9, 3, 2, 2, 1, 0, 8, 9, 8, 7, 6, 5, 4, 3, 1, 3, 2, 0};

	return(list[c-'A']);
}

int main(int argc,char **argv) {
	int datanum=0;
	scanf("%d",&datanum);
	char firstword[datanum+1];
	char container[datanum][11];
	int id[datanum][9];
	int counter[datanum];
	for(int i=0;i<datanum;i++){
		counter[i]=0;
	}
	int determinater=0;

	for(int i=0;i<datanum;i++){
		scanf("%s",container[i]);
	}

	/*if(container[0][10]=='\0'){
	  printf("%c\n",container[0][9]);
	  }*/

	for(int i=0;i<datanum;i++){
		firstword[i]=container[i][0];
		for(int k=0;k<9;k++){
			switch(container[i][k+1]){
				case '0':
					id[i][k]=0;
					break;
				case '1':
					id[i][k]=1;
					break;
				case '2':
					id[i][k]=2;
					break;
				case '3':
					id[i][k]=3;
					break;
				case '4':
					id[i][k]=4;
					break;
				case '5':
					id[i][k]=5;
					break;
				case '6':
					id[i][k]=6;
					break;
				case '7':
					id[i][k]=7;
					break;
				case '8':
					id[i][k]=8;
					break;
				case '9':
					id[i][k]=9;
					break;
				default:
					counter[i]+=1;
			}
		}
		//printf("%c%d%d%d%d%d%d%d%d%d\n",firstword[i],id[i][0],id[i][1],id[i][2],id[i][3],id[i][4],id[i][5],id[i][6],id[i][7],id[i][8]);

		if(counter[i]!=0){
			printf("Invalid\n");
			continue;
		}
		if(firstword[i] > 'Z' || firstword[i] < 'A'){
			printf("Invalid\n");
			continue;
		}
		if(id[i][0]!=1 && id[i][0]!=2){
			printf("Invalid\n");
			continue;
		}
		determinater=convertfunc(firstword[i])+(8*id[i][0])+(7*id[i][1])+(6*id[i][2])+(5*id[i][3])+(4*id[i][4])+(3*id[i][5])+(2*id[i][6])+(1*id[i][7])+(1*id[i][8]);
		if((determinater%10) != 0){
			printf("Invalid\n");
		}else{
			printf("Valid\n");
		}
	}


	return 0;
}

