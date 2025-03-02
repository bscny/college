#include<iostream>
#include<string>
#include<cstdarg>
#include <iomanip>
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

double trans(char a){
	char sample[10] = {'0','1','2','3','4','5','6','7','8','9'};

	for(int i = 0; i < 10; i ++){
		if(a == sample[i]){
			return double(i);
		}
	}
}

template<typename T1, typename T2>
double add_func(T1 a, T2 b){
	return a+b;
}

void adjust(double &tar){
	int compare = 10*tar;
	compare *= 10;
	int temp = 100*tar;
	
	if(temp > compare){
		compare += 10;
	}

	tar = double(compare) / 100;
}

int main(int argc,char **argv){
	string in_type_1, in_type_2;
	int val_int_1, val_int_2;
	char val_char_1, val_char_2;
	double val_float_1, val_float_2;
	double ans;

	while(true){
		cin >> in_type_1;
		if(in_type_1 == "-1"){
			break;
		}
		
		if(in_type_1 == "char"){
			cin >> val_char_1;
			cin >> in_type_2;

			if(in_type_2 == "char"){
				cin >> val_char_2;
				ans = add_func(trans(val_char_1), trans(val_char_2));

			}else if(in_type_2 == "int"){
				cin >> val_int_2;
				ans = add_func(trans(val_char_1), val_int_2);

			}else{
				cin >> val_float_2;
				ans = add_func(trans(val_char_1), val_float_2);

			}

		}else if(in_type_1 == "int"){
			cin >> val_int_1;
			cin >> in_type_2;

			if(in_type_2 == "char"){
				cin >> val_char_2;
				ans = add_func(val_int_1, trans(val_char_2));

			}else if(in_type_2 == "int"){
				cin >> val_int_2;
				ans = add_func(val_int_1, val_int_2);

			}else{
				cin >> val_float_2;
				ans = add_func(val_int_1, val_float_2);

			}

		}else{
			cin >> val_float_1;
			cin >> in_type_2;

			if(in_type_2 == "char"){
				cin >> val_char_2;
				ans = add_func(val_float_1, trans(val_char_2));

			}else if(in_type_2 == "int"){
				cin >> val_int_2;
				ans = add_func(val_float_1, val_int_2);

			}else{
				cin >> val_float_2;
				ans = add_func(val_float_1, val_float_2);

			}

		}

		adjust(ans);
		cout << "Sum: " << ans << "\n";

	}

	return 0;
}
