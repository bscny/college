#include<stdio.h>

#define   draw   0
#define   blackwin   1
#define   whitewin   2

int winteller(int move[225][2],int x,int y,int step){
	int counter=0,teller=0;
	int target,target2;

	if(step%2 == 0){                       //black
		target=x-4;
		counter=0;
		for(int i=0;i<9;i++){
			teller=0;
			for(int k=0;k<=step;k+=2){
				if(move[k][0]==target && move[k][1]==y){
					teller=1;
					break;
				}
			}
			target+=1;
			if(teller==1){
				counter+=1;
			}else{
				counter=0;
			}
			if(counter==5){
				return blackwin;
			}
		}                                                     //horizontal situation over

		target=y-4;
		counter=0;
		for(int i=0;i<9;i++){
			teller=0;
			for(int k=0;k<=step;k+=2){
				if(move[k][0]==x && move[k][1]==target){
					teller=1;
					break;
				}
			}
			target+=1;
			if(teller==1){
				counter+=1;
			}else{
				counter=0;
			}
			if(counter==5){
				return blackwin;
			}
		}                                                     //vertical situation over

		target=x-4;
		target2=y-4;
		counter=0;
		for(int i=0;i<9;i++){
			teller=0;
			for(int k=0;k<=step;k+=2){
				if(move[k][0]==target && move[k][1]==target2){
					teller=1;
					break;
				}
			}
			target+=1;
			target2+=1;
			if(teller==1){
				counter+=1;
			}else{
				counter=0;
			}
			if(counter==5){
				return blackwin;
			}
		}                                                    //y=x situation over

		target=x+4;
		target2=y-4;
		counter=0;
		for(int i=0;i<9;i++){
			teller=0;
			for(int k=0;k<=step;k+=2){
				if(move[k][0]==target && move[k][1]==target2){
					teller=1;
					break;
				}
			}
			target-=1;
			target2+=1;
			if(teller==1){
				counter+=1;
			}else{
				counter=0;
			}
			if(counter==5){
				return blackwin;
			}
		}                                                  //y=-x situation over
	}else{                          //white
		target=x-4;
		counter=0;
		for(int i=0;i<9;i++){
			teller=0;
			for(int k=1;k<=step;k+=2){
				if(move[k][0]==target && move[k][1]==y){
					teller=1;
					break;
				}
			}
			target+=1;
			if(teller==1){
				counter+=1;
			}else{
				counter=0;
			}
			if(counter==5){
				return whitewin;
			}
		}                                                     //horizontal situation over

		target=y-4;
		counter=0;
		for(int i=0;i<9;i++){
			teller=0;
			for(int k=1;k<=step;k+=2){
				if(move[k][0]==x && move[k][1]==target){
					teller=1;
					break;
				}
			}
			target+=1;
			if(teller==1){
				counter+=1;
			}else{
				counter=0;
			}
			if(counter==5){
				return whitewin;
			}
		}                                                     //vertical situation over

		target=x-4;
		target2=y-4;
		counter=0;
		for(int i=0;i<9;i++){
			teller=0;
			for(int k=1;k<=step;k+=2){
				if(move[k][0]==target && move[k][1]==target2){
					teller=1;
					break;
				}
			}
			target+=1;
			target2+=1;
			if(teller==1){
				counter+=1;
			}else{
				counter=0;
			}
			if(counter==5){
				return whitewin;
			}
		}                                                    //y=x situation over

		target=x+4;
		target2=y-4;
		counter=0;
		for(int i=0;i<9;i++){
			teller=0;
			for(int k=1;k<=step;k+=2){
				if(move[k][0]==target && move[k][1]==target2){
					teller=1;
					break;
				}
			}
			target-=1;
			target2+=1;
			if(teller==1){
				counter+=1;
			}else{
				counter=0;
			}
			if(counter==5){
				return whitewin;
			}
		}
	}
	return draw;
}

int main(int argc,char **argv){
	int move[225][2];
	char y,turn;
	int step=0;
	int invalidmove=-1,winner=0;
	for(int i=0;i<225;i++){
		move[i][0]='0';
		move[i][1]='0';
	}

	while(scanf("%c%c%d%c",&y,&turn,&move[step][1],&turn)!=EOF){
		move[step][0] = (y-'A'+1);
		if(15<move[step][0] || move[step][0]<1){
			invalidmove=step;
			break;
		}
		if(15<move[step][1] || move[step][1]<1){
			invalidmove=step;
			break;
		}
		for(int k=0;k<step;k++){
			if(move[step][0]==move[k][0] && move[step][1]==move[k][1]){
				invalidmove=step;
				break;
			}
		}
		if(invalidmove != -1){
			break;
		}
		if(winner==0){
			winner=winteller(move,move[step][0],move[step][1],step);
		}
		if(winner!=0){
			break;
		}
		if(step>=225){
			break;
		}
		step+=1;
	}

	if(invalidmove != -1){
		printf("Invalid move at step %d.",(invalidmove+1));
	}else{
		if(winner==blackwin){
			printf("The winner is black.");
		}else if(winner==whitewin){
			printf("The winner is white.");
		}else if(winner==draw){
			printf("The game is tie.");
		}
	}

	return 0;
}

