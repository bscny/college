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

int cmpfunc (const void * a, const void * b){
	return ( *(int*)a - *(int*)b );
}

int main(int argc,char **argv){
	int test_case;
	scanf("%d", &test_case);
	int seq_num;
	int *sequences;
	int target, index_substrction;
	int element_gainable, sequences_valid;

	for(int jj=0 ; jj<test_case ; jj++){ //each test case
		scanf("%d", &seq_num);
		sequences = malloc(seq_num*(sizeof(int)));
		for(int i=0 ; i<seq_num ; i++){
			scanf("%d", &sequences[i]);
		}
		qsort(sequences, seq_num, sizeof(int), cmpfunc);
		sequences_valid = 1;
		//data init over
		
		//special situation (no 1s)
		if(sequences[0] != 1){
			printf("NO\n");
			continue;  // go to the next test case
		}

		//start from the first element, check if its poosible to be gained from the prev elements
		for(int i=0 ; i<seq_num ; i++){ //each element
			if(sequences[i] == 1){
				continue;  // go to the next element
			}else{
				//check prev
				
				target = sequences[i];
				index_substrction = i-1;
				element_gainable = 0;
				//init over

				while(index_substrction != -1){
					if(sequences[index_substrction] <= target){
						target -= sequences[index_substrction];
					}

					if(target == 0){
						element_gainable = 1;
						break;
					}

					index_substrction -= 1;
				}

				if(element_gainable == 0){
					sequences_valid = 0;
					break;
				}
			}
		}

		if(sequences_valid == 1){
			printf("YES\n");
		}else{
			printf("NO\n");
		}

		free(sequences);
	}

	return 0;
}
