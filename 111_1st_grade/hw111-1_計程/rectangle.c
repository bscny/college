#include<stdio.h>

int main(int argc,char **argv){
	double rectangle_1[4][2],rectangle_2[4][2];
	double vector_1[2][2],vector_2[2][2];
	double value_1=0,value_2=0;

	scanf("(%lf, %lf), (%lf, %lf), (%lf, %lf), (%lf, %lf)\n",
			&rectangle_1[0][0],&rectangle_1[0][1],
			&rectangle_1[1][0],&rectangle_1[1][1],
			&rectangle_1[2][0],&rectangle_1[2][1],
			&rectangle_1[3][0],&rectangle_1[3][1]);

	scanf("(%lf, %lf), (%lf, %lf), (%lf, %lf), (%lf, %lf)",
			&rectangle_2[0][0],&rectangle_2[0][1],
			&rectangle_2[1][0],&rectangle_2[1][1],
			&rectangle_2[2][0],&rectangle_2[2][1],
			&rectangle_2[3][0],&rectangle_2[3][1]);

	//printf("\n");

	vector_1[0][0]=rectangle_1[1][0]-rectangle_1[0][0];
	vector_1[0][1]=rectangle_1[1][1]-rectangle_1[0][1];
	vector_1[1][0]=rectangle_1[3][0]-rectangle_1[0][0];
	vector_1[1][1]=rectangle_1[3][1]-rectangle_1[0][1];

	vector_2[0][0]=rectangle_2[1][0]-rectangle_2[0][0];
	vector_2[0][1]=rectangle_2[1][1]-rectangle_2[0][1];
	vector_2[1][0]=rectangle_2[3][0]-rectangle_2[0][0];
	vector_2[1][1]=rectangle_2[3][1]-rectangle_2[0][1];

	value_1=(vector_1[0][0]*vector_1[1][1])-(vector_1[1][0]*vector_1[0][1]);
	if(value_1 < 0){
		value_1*=-1;
	}
	value_2=(vector_2[0][0]*vector_2[1][1])-(vector_2[1][0]*vector_2[0][1]);
	if(value_2 < 0){
		value_2*=-1;
	}

	if(value_1 == (unsigned long)value_1){
		printf("%ld\n",(unsigned long)value_1);
	}else if((value_1*10) == ((unsigned long)(value_1*10))){
		printf("%.1f\n",value_1);
	}else{
		printf("%.2f\n",value_1);
	}

	if(value_2 == (unsigned long)value_2){
		printf("%ld\n",(unsigned long)value_2);
	}else if((value_2*10) == ((unsigned long)(value_2*10))){
		printf("%.1f\n",value_2);
	}else{
		printf("%.2f\n",value_2);
	}

	if(value_1 < value_2){
		printf("A < B");
	}else if(value_1 > value_2){
		printf("A > B");
	}else{
		printf("A = B");
	}

	return 0;
}


