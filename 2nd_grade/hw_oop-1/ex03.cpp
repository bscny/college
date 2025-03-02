#include<iostream>
#include<string>
#include<cstdarg>
using namespace std;

//DEBUG SETTINGS
#define   Debug   //THE SWITCH IS HERE

#define L0(fmt, args...)
#define L1(fmt, args...)        log_print("\033[1;31m", fmt, ## args)
#define L2(fmt, args...)        log_print("\033[1;33m", fmt, ## args)
#define L3(fmt, args...)        log_print("\033[1;34m", fmt, ## args)
#define L4(fmt, args...)        log_print("\033[1;35m", fmt, ## args)
void log_print(string color,const char *fmt, ...) {
#ifdef Debug
	va_list ap;
	unsigned int len=0;
	char buf[200], *p=NULL;
	va_start(ap, fmt);
	len = vsnprintf(buf, sizeof(buf), fmt, ap);
	if(len < sizeof(buf)) { // enough buf
		p = buf;
		if(len > 0) buf[len] = '\0';
	} else {
		p = new char[len+1];
		if(p) {
			vsnprintf(p, len, fmt, ap);
			if(len > 0) p[len] = '\0';
		} else printf("%s:error. new %dB\n", __func__, len+1);
	}
	if(len > 0) cout<<color<<p<<"\033[m";
	va_end(ap);
	if(p != buf) delete [] p;
#endif
}
//END OF DEBUG SETTINGS

void ans_calculator(int &ans, int value){
	ans += value;
}

int main(int argc,char **argv){
	int num_movement;
	cin >> num_movement;
	int table[5][5];
	int last;
	int ans = 0;
	
	for(int i = 0; i < num_movement; i++){ // do num_movement times
		ans = 0;
		for(int k = 0; k < 5; k++){
			for(int j = 0; j < 5; j++){
				last = table[k][j];
				cin  >> table[k][j];
				if(i != 0){ //skip first time
					if(last == 8){ // were standing
						if(table[k][j] == 8){ //become standing
							// add 5
							ans_calculator(ans, 5);
						}else{ //become sitting
							// add 2 
							ans_calculator(ans, 2);
						}
					}else{ // were sitting
						if(table[k][j] == 8){ //become standing
							// add 7
							ans_calculator(ans, 7);
						}else{ //become sitting
							// add 1
							ans_calculator(ans, 1);
						}
					}
				}
			}
		}
		if(i != 0){
			cout << ans << "\n";
		}
	}


	return 0;
}
