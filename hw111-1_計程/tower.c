#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int WATER_STONE_NUM=0;
int FIRE_STONE_NUM=0;
int EARTH_STONE_NUM=0;
int LIGHT_STONE_NUM=0;
int DARK_STONE_NUM=0;
int HEALTH_STONE_NUM=0;

typedef struct hero{
	char name[80];
	char type;
	int atk_status;
	int recover_status;
	int damage;
	int recovey;
}tHero;

typedef struct stone{
	char type;
	int check_marker;
	int dele_marker;
}tStone;

typedef struct node{
	tStone stone;
	struct node *next;
}tNode;

tNode *head[6],*prev[6];

void valuecounter(char c){
	switch(c){
		case 'w':
			WATER_STONE_NUM++;
			break;
		case 'W':
			WATER_STONE_NUM+=2;
			break;
		case 'f':
			FIRE_STONE_NUM++;
			break;
		case 'F':
			FIRE_STONE_NUM+=2;
			break;
		case 'e':
			EARTH_STONE_NUM++;
			break;
		case 'E':
			EARTH_STONE_NUM+=2;
			break;
		case 'l':
			LIGHT_STONE_NUM++;
			break;
		case 'L':
			LIGHT_STONE_NUM+=2;
			break;
		case 'd':
			DARK_STONE_NUM++;
			break;
		case 'D':
			DARK_STONE_NUM+=2;
			break;
		case 'h':
			HEALTH_STONE_NUM++;
			break;
		case 'H':
			HEALTH_STONE_NUM+=2;
			break;
	}
}

int maketablefun(tStone table[5][6]){
	int counter=1,jj=0;

		for(int i=0;i<5;i++){
		counter=1;
		for(int k=0;k<6;k++){
			table[i][k].check_marker=counter;
			if(k==5){
				continue;
			}
			if(table[i][k].type==table[i][k+1].type || table[i][k].type==((table[i][k+1].type)+32) || table[i][k].type==((table[i][k+1].type)-32)){
				counter+=1;
			}else{
				counter=1;
			}
		}
	}                                         //pera set 
	for(int i=0;i<5;i++){
		for(int k=5;k>=0;k--){
			if(table[i][k].check_marker>=3){
				for(jj=0;jj<table[i][k].check_marker;jj++){
					table[i][k-jj].dele_marker=1;
				}
				k=k-jj+1;
			}
		}
	}                                        //pera dele set

	for(int i=0;i<6;i++){
		counter=1;
		for(int k=0;k<5;k++){
			table[k][i].check_marker=counter;
			if(k==4){
				continue;
			}
			if(table[k][i].type==table[k+1][i].type || table[k][i].type==((table[k+1][i].type)+32) || table[k][i].type==((table[k+1][i].type)-32)){
				counter+=1;
			}else{
				counter=1;
			}
		}
	}                                         //ver set 
	for(int i=0;i<6;i++){
		for(int k=4;k>=0;k--){
			if(table[k][i].check_marker>=3){
				for(jj=0;jj<table[k][i].check_marker;jj++){
					table[k-jj][i].dele_marker=1;
				}
				k=k-jj+1;
			}
		}
	}                                       //ver dele set

	counter=0;
	for(int i=0;i<5;i++){
		for(int k=0;k<6;k++){
			if(table[i][k].dele_marker==1){
				valuecounter(table[i][k].type);				
				table[i][k].type='0';
				counter++;
			}
		}
	}                                        //delete ok
	
	if(counter==0){
		return 0;
	}else{
		return 1;
	}
}

void switchwithnext(tStone table[5][6],int x,int y){
	if(y>0 && table[y-1][x].type=='0'){
		table[y-1][x].type=table[y][x].type;
		table[y][x].type='0';
		switchwithnext(table,x,y-1);
	}
}

void fallfunc(tStone table[5][6]){
	tNode *kill;
	
	for(int i=0;i<5;i++){
		for(int k=0;k<6;k++){
			if(table[i][k].type!='0'){
				switchwithnext(table,k,i);
			}
		}
	}                                      //zero on top

	for(int i=0;i<6;i++){
		for(int k=0;k<5;k++){
			if(table[k][i].type=='0'){
				if(head[i]!=NULL){
					table[k][i]=head[i]->stone;
					kill=head[i];
					head[i]=head[i]->next;
					free(kill);
				}else{
					break;
				}
			}
		}
	}                                      //fall

	for(int i=4;i>=0;i--){
		for(int k=0;k<6;k++){
			table[i][k].dele_marker=0;
		}
	}                                      //reset table
}

void hero_output(tHero heros[6]){
	int marker;
	
	for(int i=0;i<6;i++){
		marker=0;
		switch(heros[i].type){
			case 'W':
				heros[i].damage=(WATER_STONE_NUM*heros[i].atk_status);
				break;
			case 'F':
				heros[i].damage=(FIRE_STONE_NUM*heros[i].atk_status);
				break;
			case 'E':
				heros[i].damage=(EARTH_STONE_NUM*heros[i].atk_status);
				break;
			case 'L':
				heros[i].damage=(LIGHT_STONE_NUM*heros[i].atk_status);
				break;
			case 'D':
				heros[i].damage=(DARK_STONE_NUM*heros[i].atk_status);
				break;
			case 'N':
				heros[i].damage=0;
				marker=1;
				break;
		}
		if(marker==0){
			heros[i].recovey=(HEALTH_STONE_NUM*heros[i].recover_status);
		}else{
			heros[i].recovey=0;
		}
	}
}

int comparefunc(const void *a,const void *b){
	return ((*(tHero *)b).damage - (*(tHero *)a).damage);
}

int main(int argc,char **argv){
	char linereader[80];
	int dashcounter=0;
	tHero heros[6];
	for(int i=0;i<6;i++){
		head[i]=NULL;
		prev[i]=NULL;
	}
	tStone table[5][6];
	int ii=4;
	int keep=1;

	while(gets(linereader) != NULL){
		if(linereader[0]=='-'){
			dashcounter+=1;
			continue;
		}

		if(dashcounter<=6){
			switch(linereader[0]){
				case 'N':
					strcpy(heros[dashcounter-1].name,linereader+7);
					break;
				case 'T':
					heros[dashcounter-1].type=linereader[7];
					break;
				case 'A':
					heros[dashcounter-1].atk_status=atoi(linereader+9);
					break;
				case 'R':
					heros[dashcounter-1].recover_status=atoi(linereader+11);
					heros[dashcounter-1].damage=0;
					heros[dashcounter-1].recovey=0;
					break;
			}
		}else if(dashcounter==7){
			for(int i=0;i<6;i++){
				head[i]=malloc(1*sizeof(tNode));
				head[i]->next=prev[i];
				head[i]->stone.type=linereader[i];
				head[i]->stone.check_marker=0;
				head[i]->stone.dele_marker=0;
				prev[i]=head[i];
			}
		}else{
			if(ii>=0){
				for(int i=0;i<6;i++){
					table[ii][i].type=linereader[i];
					table[ii][i].check_marker=0;
					table[ii][i].dele_marker=0;
				}
				ii--;
			}
		}
	}

	while(keep){
		keep=maketablefun(table);
		fallfunc(table);
	}
        //set hero damage
	
	hero_output(heros);

	qsort(heros,6,sizeof(tHero),comparefunc);

	/*printf("-------------------------------------------\n");
	for(int i=0;i<6;i++){
		printf("| %-40s|\n",heros[i].name);
		printf("| Damage : %-10d",heros[i].damage);
		printf("| Recovery : %-8d|\n",heros[i].recovey);
		printf("-------------------------------------------\n");
	}*/


	printf("water:%d\nfire:%d\nearth:%d\nlight:%d\ndark:%d\nhealth:%d",WATER_STONE_NUM,FIRE_STONE_NUM,EARTH_STONE_NUM,LIGHT_STONE_NUM,DARK_STONE_NUM,HEALTH_STONE_NUM);
	return 0;
}
