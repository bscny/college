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
	if(len > 0) printf("%s%s%s", color, p, "\033[m");
	va_end(ap);
	if(p != buf) free(p);
#endif
}
//END OF DEBUG SETTINGS

int main(int argc,char **argv){
	int train_len;
	int init_train[100000];
	int station[100000];
	int target_train[100000];
	int current_index;
	int target_index;
	int top_station;
	int bottom_station;
	int find;

	while(scanf("%d", &train_len) != EOF){
		for(int i=0; i<train_len; i++){
			init_train[i] = i+1;
			scanf("%d", &target_train[i]);
		}
		current_index = 0;
		target_index = 0;
		top_station = -1;
		bottom_station = 0;
		find = 1;
		//data set over

		while(1){
			if(target_index >= train_len){
				break;
			}

			if(current_index < train_len){
				if(target_train[target_index] == init_train[current_index]){
					target_index += 1;
					current_index += 1;
					continue;
				}else if(top_station != -1){
					if(station[top_station] == target_train[target_index]){
						target_index++;
						top_station--;
						continue;
					}
				}
				top_station++;
				station[top_station] = init_train[current_index];
				current_index++;
				continue;
			}else{
				if(top_station == -1 || top_station < bottom_station){
					find = 0;
					break;
				}else if(station[top_station] != target_train[target_index] && station[bottom_station] != target_train[target_index]){
					find = 0;
					break;
				}

				if(station[top_station] == target_train[target_index]){
					target_index++;
					top_station--;
					continue;
				}else if(station[bottom_station] == target_train[target_index]){
					target_index++;
					bottom_station++;
					continue;
				}

			}
		}

		if(find == 0){
			printf("NIE\n");
		}else{
			printf("TAK\n");
		}

	}

	return 0;
}
