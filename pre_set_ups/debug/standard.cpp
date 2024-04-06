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

int main(int argc,char **argv){


	return 0;
}
