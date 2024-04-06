#include<stdio.h>

int main(int argc,char **argv) {
        int x=0,y=0;
        char mode;
        int firstNum, secondNum;
        int counter=0;
        //int keepRunning=1;

        scanf("%d %d",&x,&y);

        while(scanf("%c",&mode)!=EOF) {
                if(mode=='U'){
                    scanf("%d",&firstNum);
                    if(counter>0){
                        counter-=1;
                        continue;
                    }
                    if(counter==0){
                        y += firstNum;
                    }
                }else if(mode=='D'){
                    scanf("%d",&firstNum);
                    if(counter>0){
                        counter-=1;
                        continue;
                    }
                    if(counter==0){
                        y -= firstNum;
                    }
                }else if(mode=='L'){
                    scanf("%d",&firstNum);
                    if(counter>0){
                        counter-=1;
                        continue;
                    }
                    if(counter==0){
                        x -= firstNum;
                    }
                }else if(mode=='R'){
                    scanf("%d",&firstNum);
                    if(counter>0){
                        counter-=1;
                        continue;
                    }
                    if(counter==0){
                        x += firstNum;
                    }
                }else if(mode=='S'){
                    scanf("%d",&firstNum);
                    if(counter>0){
                        counter-=1;
                        continue;
                    }
                    if(counter==0){
                        counter=firstNum;
                    }
                }else if(mode=='T'){
                    scanf("%d %d",&firstNum,&secondNum);
                    if(counter>0){
                        counter-=1;
                        continue;
                    }
                    if(counter==0){
                        x = firstNum;
                        y = secondNum;
                    }
                }
        }


        printf("(%d , %d)", x, y);
        return 0;
}

