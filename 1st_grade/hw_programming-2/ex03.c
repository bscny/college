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
	int test_case;
	scanf("%d", &test_case);
	int target;
	int seq_num;
	int *sequeces, *auxiliary_arr;
	int sum = 0;
	int determinator = 0;
	int change_auxiliray_switch = 1;

	for(int jj=0 ; jj<test_case ; jj++){
		scanf("%d%d", &target, &seq_num);
		sequeces = malloc(seq_num*(sizeof(int)));
		auxiliary_arr = malloc(seq_num*(sizeof(int)));
		for(int i=0 ; i<seq_num ; i++){
			scanf("%d", &sequeces[i]);
			auxiliary_arr[i] = 1;
		}
		//basic data set over

		//definitely feasible
		if(target == 0){
			printf("YES\n");
			continue;
		}

		//calculate every power set start from sellect all
		int x = 115000;  
		determinator = 0;
		do{
			sum = 0;
			change_auxiliray_switch = 1;
			for(int i=0 ; i<seq_num ; i++){ //each set
				L0("%d ", auxiliary_arr[i]);

				if(auxiliary_arr[i] == 1){
					sum += sequeces[i];
					if(change_auxiliray_switch == 1){
						auxiliary_arr[i] = 0;

						change_auxiliray_switch = 0;
					}
				}else{
					if(change_auxiliray_switch == 1){
						auxiliary_arr[i] = 1;
					}
				}

				if(sum == target){
					printf("YES\n");
					determinator = 1;
					break;
				}else if(sum > target){
					break;
				}

			}
			if(sum == 0){
				break;
			}

			if(determinator == 1){
				break;
			}
			L0("\n");
			x--;
		}while(x);

		if(determinator == 0){
			printf("NO\n");
		}
		/*for(int i=0 ; i<seq_num ; i++){
		  printf("%d ", sequeces[i]);
		  }*/
		free(sequeces);
	}

	return 0;
}
