#include<iostream>
#include<cstdlib>
using namespace std;

#define   feasible   1
#define   unfeasible   0

int compare(const void *a,const void *b){
	return *(int*)b - *(int*)a;
}

int fill_in_table(int days,int restriction,int *bags,int array_lenth){
	int increase_weight=0;
	int counter=0,minus=0,current=0;

	while(bags[current]>minus && increase_weight<restriction){
		increase_weight+=(bags[current]-minus);
		if(current==array_lenth){
			break;
		}

		counter+=1;
		current+=1;
		if((counter%days) == 0){
			minus+=1;
			counter=0;
		}
	}

	if(increase_weight<restriction){
		return unfeasible;
	}else{
		return feasible;
	}
}

int main(int argc,char **argv){
	int restriction,bagnum;
	//scanf("%d%d",&bagnum,&restriction);
	cin>>bagnum>>restriction;
	int bags[bagnum];
	for(int i=0;i<bagnum;i++){
		//scanf("%d",&bags[i]);
		cin>>bags[i];
	}
	qsort((void*)bags,bagnum,sizeof(int),compare);
	int left=1,right=bagnum;
	int mid;
	int ans=-1;


	while(left<=right){
		mid=(left+right)/2;

		if(fill_in_table(mid,restriction,bags,bagnum-1) == feasible){
			ans=mid;
			right=mid-1;
		}else{
			left=mid+1;
		}
	}
	//printf("%d",ans);
	cout<<ans;

	return 0;
}
