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

int solve(int kid_num, int remove_sequnce){
	if(kid_num == 1){ //only one kid
		return 1;
	}

	if(remove_sequnce <= (kid_num+1)/2){ //able to gain the ans in the first cycle
		if(2*remove_sequnce > kid_num){
			return 2*remove_sequnce%kid_num;
		}else{
			return 2*remove_sequnce;
		}
	}

	int x = solve(kid_num/2, remove_sequnce - (kid_num+1)/2);

	if(kid_num & 1){
		return 2*x + 1;
	}else{
		return 2*x - 1;
	}
}

int main(int argc,char **argv){
	int data_num;
	scanf("%d", &data_num);
	int kid_num, remove_sequnce;
	int ans;

	for(int i = 0; i < data_num; i++){
		scanf("%d%d", &kid_num, &remove_sequnce);

		ans = solve(kid_num, remove_sequnce);

		printf("%d\n", ans);
	}

	return 0;
}
