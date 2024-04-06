#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>

//DEBUG SETTINGS
//#define   Debug   //THE SWITCH IS HERE

#define L0(fmt, args...)
#define L1(fmt, args...)        log_print("\033[1;31m", fmt, ## args)
#define L2(fmt, args...)        log_print("\033[1;33m", fmt, ## args)
#define L3(fmt, args...)        log_print("\033[1;34m", fmt, ## args)
#define L4(fmt, args...)        log_print("\033[1;35m", fmt, ## args)
void log_print(const char *color,const char *fmt, ...) {
#ifdef Debug
	va_list ap;
	int len=0;
	char buf[200], *p=NULL;
	va_start(ap, fmt);
	len = vsnprintf(buf, sizeof(buf), fmt, ap);
	if(len < sizeof(buf)) { // enough buf
		p = buf;
		if(len > 0) buf[len] = '\0';
	} else {
		p = malloc(len+1);
		if(p) {
			vsnprintf(p, len, fmt, ap);
			if(len > 0) p[len] = '\0';
		} else printf("%s:error. malloc %dB\n", __func__, len+1);
	}
	if(len > 0) printf("%s%s%s\n", color, p, "\033[m");
	va_end(ap);
	if(p != buf) free(p);
#endif
}
//END OF DEBUG SETTINGS

#define  conflict_happens  1
#define  conflict_didnt_happens  0

int max_stone_calculator(int mine_num, int *U_mines, int *Zn_mines, int *stones_of_U, int *stones_of_Zn){
	int index_of_max_of_U=0, index_of_max_of_Zn=0;
	int index_of_2ndmax_of_U=0, index_of_2ndmax_of_Zn=0;

	for(int i=1 ; i<mine_num ; i++){
		//Uranium
		if(U_mines[index_of_max_of_U] > U_mines[i]){ //check if to change 2nd only
			if(i == 1){
				index_of_2ndmax_of_U = 1;
			}else{
				if(U_mines[index_of_2ndmax_of_U] < U_mines[i]){ //changed 2nd
					index_of_2ndmax_of_U = i;
				}
			}
		}else if(U_mines[index_of_max_of_U] < U_mines[i]){ //change 1st and 2nd
			index_of_2ndmax_of_U = index_of_max_of_U;
			index_of_max_of_U = i;
		}

		//Zinc
		if(Zn_mines[index_of_max_of_Zn] > Zn_mines[i]){ //check if to chnage 2nd only
			if(i == 1){
				index_of_2ndmax_of_Zn = 1;
			}else{
				if(Zn_mines[index_of_2ndmax_of_Zn] < Zn_mines[i]){ //changed 2nd
					index_of_2ndmax_of_Zn = i;
				}
			}
		}else if(Zn_mines[index_of_max_of_Zn] < Zn_mines[i]){ //change 1st and 2nd
			index_of_2ndmax_of_Zn = index_of_max_of_Zn;
			index_of_max_of_Zn = i;
		}
		//conflict check Uranium
		if(U_mines[index_of_max_of_U] == U_mines[i]){ //possible to change i
			if(index_of_max_of_Zn == index_of_max_of_U){ //conflict exist EXCHANGE i
				index_of_max_of_U = i;
			}
		}
		//conflict check Zinc
		if(Zn_mines[index_of_max_of_Zn] == Zn_mines[i]){ //possible to change i
			if(index_of_max_of_Zn == index_of_max_of_U){ //conflict exist EXCHANGE i
				index_of_max_of_Zn = i;
			}
		}
	}

	stones_of_U[0] = U_mines[index_of_max_of_U];
	stones_of_U[1] = U_mines[index_of_2ndmax_of_U];
	stones_of_Zn[0] = Zn_mines[index_of_max_of_Zn];
	stones_of_Zn[1] = Zn_mines[index_of_2ndmax_of_Zn];

	if(index_of_max_of_Zn == index_of_max_of_U){
		return conflict_happens;
	}else{
		return conflict_didnt_happens;
	}
}

long long int profit_calculator(int usage_of_U, int usage_of_Zn, int price_per_M, int stones_of_U, int stones_of_Zn, long long int profit){
	long long int money=0;
	long long int num_of_product=0;
	
	L0("BEFORE stones_of_U:%d  stones_of_Zn:%d",stones_of_U, stones_of_Zn);
	while(1){
		if((stones_of_U - usage_of_U)<0 || (stones_of_Zn - usage_of_Zn)<0){
			break;
		}
		stones_of_U -= usage_of_U;
		stones_of_Zn -= usage_of_Zn;
		num_of_product += 1;
	}

	L0("num of product %lld", num_of_product);

	money = (num_of_product)*(price_per_M)*(usage_of_U*92 + usage_of_Zn*30);
	L0("use of U:%d  use of Zn:%d  price per M:%d  profit:%lld  money:%lld\n", usage_of_U, usage_of_Zn, price_per_M, profit, money);
	if(money > profit){
		return money;	
	}else{
		return profit;
	}
}

int main(int argc,char **argv){
	int mine_num, merch_num;
	scanf("%d%d", &mine_num, &merch_num);
	int Zn_mines[mine_num], U_mines[mine_num];
	for(int i=0 ; i<mine_num ; i++){
		scanf("%d%d", &U_mines[i], &Zn_mines[i]);
	}
	int stones_of_U[2],stones_of_Zn[2];
	
	int usage_of_U, usage_of_Zn;
	int price_per_M;
	long long int profit=0;



	//calculate the max stone for each
	if(max_stone_calculator(mine_num, U_mines, Zn_mines, stones_of_U, stones_of_Zn) == conflict_didnt_happens){
		L1("no conflict %d %d %d %d", stones_of_U[0], stones_of_U[1], stones_of_Zn[0], stones_of_Zn[1]);
		for(int i=0 ; i<merch_num ; i++){
			scanf("%d%d%d", &usage_of_U, &usage_of_Zn, &price_per_M);
			//calculate the profit
			profit = profit_calculator(usage_of_U, usage_of_Zn, price_per_M, stones_of_U[0], stones_of_Zn[0], profit);
		}
	}else{
		L1("conflict %d %d %d %d", stones_of_U[0], stones_of_U[1], stones_of_Zn[0], stones_of_Zn[1]);
		for(int i=0 ; i<merch_num ; i++){
			scanf("%d%d%d", &usage_of_U, &usage_of_Zn, &price_per_M);
			//calculate the profit
			profit = profit_calculator(usage_of_U, usage_of_Zn, price_per_M, stones_of_U[0], stones_of_Zn[1], profit);
			profit = profit_calculator(usage_of_U, usage_of_Zn, price_per_M, stones_of_U[1], stones_of_Zn[0], profit);
		}
	}

	printf("%lld", profit);

	return 0;
}
