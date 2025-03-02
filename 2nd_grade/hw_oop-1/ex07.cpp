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

class Complex{
	public:
		Complex(){
			real = 0;
			imagine = 0;
		}
		friend istream &operator>> (istream &in, Complex &target);
		friend ostream &operator<< (ostream &out, Complex target);
		bool operator== (Complex &target);
		bool operator< (Complex &target);
		bool operator> (Complex &target);
		Complex operator+ (Complex &target);
		Complex operator- (Complex &target);
		Complex operator* (Complex &target);
		Complex operator++ (int);
		Complex operator++ ();
		Complex operator-- (int);
		Complex operator-- ();
		Complex operator+= (Complex &target);
	private:
		double real;
		double imagine;
};

istream& operator>> (istream &in, Complex &target){
	cin >> target.real;
	cin >> target.imagine;

	return in;
}

ostream& operator<< (ostream &out, Complex target){
	cout << target.real;
	if(target.imagine < 0){
		cout << target.imagine << "i";
	}else{
		cout << "+" << target.imagine << "i";
	}

	return out;
}

bool Complex::operator== (Complex &target){
	if(real == target.real){
		if(imagine == target.imagine){
			return true;
		}
	}

	return false;
}

bool Complex::operator< (Complex &target){
	if(real < target.real){
		return true;
	}else if(real > target.real){
		return false;
	}else{
		if(imagine < target.imagine){
			return true;
		}else{
			return false;
		}
	}

	return false;
}

bool Complex::operator> (Complex &target){
	if(real > target.real){
		return true;
	}else if(real < target.real){
		return false;
	}else{
		if(imagine > target.imagine){
			return true;
		}else{
			return false;
		}
	}

	return false;
}

Complex Complex::operator+ (Complex &target){
	Complex temp;

	temp.real = real + target.real;
	temp.imagine = imagine + target.imagine;

	return temp;
}

Complex Complex::operator- (Complex &target){
	Complex temp;

	temp.real = real - target.real;
	temp.imagine = imagine - target.imagine;

	return temp;
}

Complex Complex::operator* (Complex &target){
	Complex temp;

	temp.real = (real * target.real) - (imagine * target.imagine);
	temp.imagine = (real * target.imagine) + (imagine * target.real);

	return temp;
}

Complex Complex::operator++ (int){
	Complex temp = *this;

	real+=1;
	imagine+=1;

	return temp;
}

Complex Complex::operator-- (int){
	Complex temp = *this;

	real-=1;
	imagine-=1;

	return temp;
}

Complex Complex::operator++ (){
	real+=1;
	imagine+=1;

	return *this;
}

Complex Complex::operator-- (){
	real-=1;
	imagine-=1;

	return *this;
}

Complex Complex::operator+= (Complex &target){
	real += target.real;
	imagine += target.imagine;

	return *this; 
}

int main(int argc,char **argv){
	Complex C1, C2;
    while( cin >> C1 >> C2 ) {
        cout << "C1 = " << C1 << endl;
        cout << "C2 = " << C2 << endl;

        cout << "C1==C2? " << ((C1==C2)?"true":"false") << endl;
        cout << "C1<C2?  " << ((C1<C2)?"true":"false") << endl;
        cout << "C1>C2?  " << ((C1>C2)?"true":"false") << endl;

        cout << "C1+C2 = " << C1+C2 << endl;
        cout << "C1-C2 = " << C1-C2 << endl;
        cout << "C1*C2 = " << C1*C2 << endl;
        cout << "C1++  = " << C1++ << endl;
        cout << "C1++  = " << C1++ << endl;
        cout << "++C1  = " << ++C1 << endl;
        cout << "++C1  = " << ++C1 << endl;
        cout << "C2--  = " << C2-- << endl;
        cout << "C2--  = " << C2-- << endl;
        cout << "--C2  = " << --C2 << endl;
        cout << "--C2  = " << --C2 << endl;

        C1+=C2;
        cout << "C1+=C2  " << C1 << endl;
        cout << "==============" << endl;
    }

	return 0;
}
