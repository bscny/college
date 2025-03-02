#include<stdio.h>

typedef struct vec{
	int x;
	int y;
	int z;
}tVec;

void plus(tVec firstv,tVec secondv){
	printf("<%d, %d, %d>\n",firstv.x+secondv.x,firstv.y+secondv.y,firstv.z+secondv.z);
}

void minus(tVec firstv,tVec secondv){
	printf("<%d, %d, %d>\n",firstv.x-secondv.x,firstv.y-secondv.y,firstv.z-secondv.z);
}

void dot(tVec firstv,tVec secondv){
	int value=0;

	value=(firstv.x*secondv.x)+(firstv.y*secondv.y)+(firstv.z*secondv.z);
	if(value>0){
		printf("+");
	}
	printf("%d\n",value);
}

void cross(tVec firstv,tVec secondv){
	tVec newv;

	newv.x=(firstv.y*secondv.z)-(firstv.z*secondv.y);
	newv.y=(firstv.z*secondv.x)-(firstv.x*secondv.z);
	newv.z=(firstv.x*secondv.y)-(firstv.y*secondv.x);
	printf("<%d, %d, %d>\n",newv.x,newv.y,newv.z);
}

int main(int argc,char **argv){
	int num=0,first=0,second=0;
	char turn,mode;
	scanf("%d%c",&num,&turn);
	tVec vec[num];

	for(int i=0;i<num;i++){
		scanf("%c%d%c%c%d%c%c%d%c%c",&turn,&vec[i].x,&turn,&turn,&vec[i].y,&turn,&turn,&vec[i].z,&turn,&turn);
	}
	while(scanf("%d%c%c%c%d%c",&first,&turn,&mode,&turn,&second,&turn) != EOF){
		switch(mode){
			case '+':
				plus(vec[first-1],vec[second-1]);
				break;
			case '-':
				minus(vec[first-1],vec[second-1]);
				break;
			case '.':
				dot(vec[first-1],vec[second-1]);
				break;
			case 'x':
				cross(vec[first-1],vec[second-1]);
				break;
		}
	}

	return 0;
}
