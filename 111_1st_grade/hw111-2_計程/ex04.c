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

int min_func(int a, int b){
	if(a>b){
		return b;
	}else{
		return a;
	}
}

int main(int argc,char **argv){
	int target;
	scanf("%d", &target);
	int square_nums[1000], index_tail;
	int num=0;

	//get the range of square_nums
	for(int i=0 ; i<1001 ; i++){
		num = (i+1)*(i+1);
		if(num > target){
			index_tail = i-1;
			break;
		}

		square_nums[i] = num;
	}

	int table[target];

	//only using 1
	for(int i=0 ; i<target ; i++){
		table[i] = i+1;
	}

	//using 4 9 16 ...
	for(int i=1 ; i<(index_tail+1) ; i++){
		table[square_nums[i]-1] = 1;
		for(int k=square_nums[i] ; k<target ; k++){
			//target num = k+1
			table[k] = min_func(table[k], 1+table[k-square_nums[i]]);
		}
	}

	printf("%d", table[target-1]);

	return 0;
}
