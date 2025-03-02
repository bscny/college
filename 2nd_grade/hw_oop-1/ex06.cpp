#include<iostream>
#include<string>
#include<cstdarg>
#include<cstdlib>
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

typedef struct pitcher{
	char name[200];
	int wins;
	int loses;
	double era;
}tPitcher;

typedef struct batter{
	char name[200];
	int hrs;
	int rs;
	double avg;
}tBatter;

int compare_pitchers(const void* a, const void* b){
	const tPitcher* x = (tPitcher*) a;
	const tPitcher* y = (tPitcher*) b;

	if (x->wins < y->wins){
		return 1;
	}else if (x->wins > y->wins){
		return -1;
	}else{
		if(x->loses < y->loses){
			return -1;
		}else if(x->loses > y->loses){
			return 1;
		}else{
			if(x->era < y->era){
				return -1;
			}else{
				return 1;
			}
		}
	}

    return 0;
}

int compare_batters(const void* a, const void* b){
	const tBatter* x = (tBatter*) a;
	const tBatter* y = (tBatter*) b;

	if (x->hrs < y->hrs){
		return 1;
	}else if (x->hrs > y->hrs){
		return -1;
	}else{
		if(x->rs < y->rs){
			return 1;
		}else if(x->rs > y->rs){
			return -1;
		}else{
			if(x->avg < y->avg){
				return 1;
			}else{
				return -1;
			}
		}
	}

    return 0;
}

int main(int argc,char **argv){
	int data_num, player_num;
	//tPitcher *pitchers;
	//tBatter *batters;
	tPitcher pitchers[1001];
	tBatter batters[1001];
	int num_of_pitchers = 0, num_of_batters = 0;
	char type;

	cin >> data_num;
	for(int ii = 0; ii < data_num; ii++){
		cin >> player_num;
		num_of_pitchers = 0;
		num_of_batters = 0;
		//pitchers = new tPitcher[player_num];
		//batters = new tBatter[player_num];
		for(int kk = 0; kk < player_num; kk++){
			cin >> type;

			if(type == 'P'){
				cin >> pitchers[num_of_pitchers].name;
				cin >> pitchers[num_of_pitchers].wins;
				cin >> pitchers[num_of_pitchers].loses;
				cin >> pitchers[num_of_pitchers].era;
				num_of_pitchers ++;
			}else{
				cin >> batters[num_of_batters].name;
				cin >> batters[num_of_batters].hrs;
				cin >> batters[num_of_batters].rs;
				cin >> batters[num_of_batters].avg;
				num_of_batters ++;
			}
		}

		//call func
		if(num_of_pitchers > 0){
			qsort(pitchers, num_of_pitchers, sizeof(tPitcher), compare_pitchers);
		}
		if(num_of_batters > 0){
			qsort(batters, num_of_batters, sizeof(tBatter), compare_batters);
		}

		for(int i = 0; i < num_of_pitchers; i++){
			cout << "P " << pitchers[i].name << "\n";
		}
		for(int i = 0; i < num_of_batters; i++){
			cout << "B " << batters[i].name << "\n";
		}
		if(ii != data_num - 1){
			cout << "=====\n";
		}

		//delete [] pitchers;
		//delete [] batters;

	}

	return 0;
}
