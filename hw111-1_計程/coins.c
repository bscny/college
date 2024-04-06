#include<stdio.h>

long long int sum=0;

void valuecounter(long long int *coin,long long int max,long long int init){
	if(*(coin+1) == -1){
		long long int temp=init+(*coin);
		if(temp<=max && temp>sum){
			sum=temp;
		}else if(init<=max && init>sum){
			sum=init;
		}
		return;
	}
	
	valuecounter(coin+1,max,init);
	valuecounter(coin+1,max,init+(*coin));
}

int main(int argc,char **argv){
	int coinnum=0;
	long long int max=0;
	scanf("%d%lld",&coinnum,&max);
	long long int coin[coinnum+1];
	for(int i=0;i<coinnum;i++){
		scanf("%lld",&coin[i]);
	}
	coin[coinnum]=-1;

	valuecounter(coin,max,0);	
	printf("%lld",sum);

	return 0;
}
