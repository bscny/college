#include<iostream>
#include<string>
#include<cstdarg>
#include <vector>
#include <algorithm>
#include <cmath>
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

class Instrument{
	public:
		void set_P_num(int n){
			num_performancer = n;
		}
		void set_S_num(int n){
			sheet_num = n;
		}
		void plus_S_num(){
			sheet_num ++;
		}

		int get_P_num(){
			return num_performancer;
		}
		double get_ans(){
			return ((double)num_performancer / (double)sheet_num);
		}

		Instrument operator= (const Instrument &in){
			num_performancer = in.num_performancer;
			sheet_num = in.sheet_num;

			return *this;
		}
	private:
		int num_performancer;
		int sheet_num;
};

bool cmpfunc(Instrument &a, Instrument &b){
	return (a.get_ans() > b.get_ans() );
}

int main(int argc,char **argv){
	vector<Instrument> band;
	int total_sheet, total_ins;
	int temp;
	int target_index;

	while(cin >> total_sheet){
		cin >> total_ins;

		band.resize(total_ins);
		for(int i = 0; i < total_ins; i++){
			cin >> temp;
			band[i].set_P_num(temp);
			band[i].set_S_num(1);
		}
		total_sheet -= total_ins;
		//sort(band.begin(), band.end(), cmpfunc);

		while(total_sheet){
			target_index = 0;
			for(int i = 1; i < total_ins; i++){
				if(band[i].get_ans() > band[target_index].get_ans() ){
					target_index = i;
				}
			}
			band[target_index].plus_S_num();
			//sort(band.begin(), band.end(), cmpfunc);

			total_sheet --;
		}

		target_index = 0;
		for(int i = 1; i < total_ins; i++){
			if(band[i].get_ans() > band[target_index].get_ans() ){
				target_index = i;
			}
		}

		cout << floor(band[target_index].get_ans() ) << "\n";

		band.clear();
	}

	return 0;
}
