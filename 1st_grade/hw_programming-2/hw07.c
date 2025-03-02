#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>

//DEBUG SETTINGS
#define   Debug   //THE SWITCH IS HERE

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
	if(len > 0) printf("%s%s%s", color, p, "\033[m");
	va_end(ap);
	if(p != buf) free(p);
#endif
}
//END OF DEBUG SETTINGS

int main(int argc,char **argv){
	double **currency_table;
	int country_num;
	double recorder[24][24][24];
	int index_change;
	double temp_max_profit, max_profit, valid_profit;
	int start, end;
	int mid_path[24][24][24][24];
	int steps;
	int arbitrarge;

	while(scanf("%d", &country_num) != EOF){
		//set the currency_table
		temp_max_profit = 0;
		max_profit = 0;
		valid_profit = 0;
		steps = 0;
		arbitrarge = 0;
		currency_table = malloc(country_num*sizeof(double));

		for(int i=0 ; i<country_num ; i++){
			currency_table[i] = malloc(country_num*sizeof(double));

			for(int j=0 ; j<country_num ; j++){
				if(i==j){
					continue;
				}
				scanf("%lf", &currency_table[i][j]);
			}
		}

		//set the recorder
		for(int i=0 ; i<country_num ; i++){
			for(int j=0 ; j<country_num ; j++){
				if(i == j){
					continue;
				}
				recorder[i][j][0] = currency_table[i][j];
				temp_max_profit = recorder[i][j][0]*currency_table[j][i];
				if((valid_profit < temp_max_profit) && (temp_max_profit >= 1.01)){
					arbitrarge = 1;
					valid_profit = temp_max_profit;
					start = i;
					end = j;
				}
			}
		}

		//two changes
		if(arbitrarge == 1){
			printf("%d %d %d\n", start+1, end+1, start+1);
			for(int i=0 ; i<country_num ; i++){
				free(currency_table[i]);
			}
			free(currency_table);
			continue; //read next data
		}

		//calculation on more than 2 changes
		index_change = 1;
		while(index_change < 24){
			for(int i=0 ; i<country_num ; i++){
				for(int j=0 ; j<country_num ; j++){ //fill in the blank
					if(i == j){
						continue;
					}

					//init data
					max_profit = 0;

					for(int k=0 ; k<country_num ; k++){ //do country_num-2 times to find the max & mid_path in the blank
						if((k == i) || (k == j)){
							continue; //skip the two
						}

						temp_max_profit = recorder[i][k][index_change - 1]*recorder[k][j][0];
						if(temp_max_profit > max_profit){ //change the max_profit & mid_path in the blank
							//change the max_profit
							max_profit = temp_max_profit;

							//change the mid_path
							if(index_change != 1){ //there are mid_path to inherit
								for(int h=0 ; h<(index_change-1) ; h++){
									mid_path[i][j][index_change][h] = mid_path[i][k][index_change - 1][h];
								}
							}
							mid_path[i][j][index_change][index_change-1] = k;
						}
					}
					//set the blank
					recorder[i][j][index_change] = max_profit;

					//test valid or not
					temp_max_profit = recorder[i][j][index_change]*recorder[j][i][0];
					if((valid_profit < temp_max_profit) && (temp_max_profit >= 1.01)){
						arbitrarge = 1;
						valid_profit = temp_max_profit;
						steps = index_change;
						start = i;
						end = j;
					}
				}
			}

			//find the ans
			if(arbitrarge == 1){
				printf("%d ", start+1);
				for(int i=0 ; i<steps ; i++){
					printf("%d ", mid_path[start][end][steps][i]+1);
				}
				printf("%d %d\n", end+1, start+1);

				break; //read next data
			}

			index_change += 1;
		}

		if(arbitrarge == 0){
			printf("no arbitrage sequence exists\n");
		}

		//free the space
		for(int i=0 ; i<country_num ; i++){
			free(currency_table[i]);
		}
		free(currency_table);
	}

	return 0;
}
