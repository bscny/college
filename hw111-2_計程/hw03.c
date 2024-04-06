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
	if(len > 0) printf("%s%s%s\n", color, p, "\033[m");
	va_end(ap);
	if(p != buf) free(p);
#endif
}
//END OF DEBUG SETTINGS

int visable_tower_calaulator(int *towers,int tower_num,int target_index){
	int ans=0;
	int max_height=towers[target_index],hightest_height=0;
	int i=1;

	while(hightest_height<max_height){
		if((target_index+i) >= tower_num){
			return ans;
		}
		
		if(towers[target_index+i] >= hightest_height){
			ans+=1;
			hightest_height=towers[target_index+i];
		}

		i+=1;
	}

	return ans;
}

int main(int argc,char **argv){
	int tower_num;
	scanf("%d",&tower_num);
	int towers[tower_num];
	for(int i=0;i<tower_num;i++){
		scanf("%d",&towers[i]);
	}

	for(int i=0;i<tower_num;i++){
		printf("%d ",visable_tower_calaulator(towers,tower_num,i));
	}

	L0("%d %d %d",towers[2],towers[4],towers[6]);

	return 0;
}
