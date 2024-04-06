#include <stdio.h>
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
	if(len > 0) printf("%s%s%s\n", color, p, "\033[m");
	va_end(ap);
	if(p != buf) free(p);
#endif
}
//END OF DEBUG SETTINGS

int cmpfunc (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

int main(int argc, char **argv){
	int arr[2000000];
	int fir_len, len=0;

	while(scanf("%d", &fir_len) != EOF){
		for(int i=len ; i<(fir_len+len) ; i++){
			scanf("%d", &arr[i]);
		}

		len += fir_len;
	}

	qsort(arr, len, sizeof(int), cmpfunc);

	for(int i=0 ; i<len ; i++){
		printf("%d ", arr[i]);
	}

	return 0;
}
