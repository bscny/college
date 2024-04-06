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

class App {
    public:
        App(int d) { download = d; }

        ~App(){};

        int getDownload() { return download; }

        void increaseDownload() { ++download; }
    private:
        int download;
};

class Jjbox : public App{
	public:
		Jjbox(int d, int s_num);
		int get_song_num(){
			return song_num;
		}

		void renew(){
			int temp;

			temp = getDownload();

			song_num = 5*temp;
		}
	private:
		int song_num;
};

Jjbox::Jjbox (int d, int s_num) : App(d), song_num(s_num){

}

class Nosebook : public App{
	public:
		Nosebook(int d, int f_num);
		int get_friend_num(){
			return friend_num;
		}

		void renew(){
			int temp;

			temp = getDownload();

			friend_num = 3*temp + 5;
		}
	private:
		int friend_num;
};

Nosebook::Nosebook(int d, int f_num) : App(d), friend_num(f_num){

}


int main(int argc,char **argv){
	int mode = 1;
	int temp;
	cin >> temp;
	Jjbox jjb(temp, (temp*5) );
	cin >> temp;
	Nosebook nb(temp, (temp*3 + 5));

	while(mode){
		cin >> mode;
		switch(mode){
			case 1:
				jjb.increaseDownload();
				break;
			case 2:
				nb.increaseDownload();
				break;
			case 3:
				jjb.increaseDownload();
				nb.increaseDownload();
				break;
			case 4:
				jjb.renew();
				break;
			case 5:
				nb.renew();
				break;
			default:
				mode = 0;
				break;
		}

		if(mode != 0){
			cout << "JJBox now has " << (jjb.get_song_num() ) << " songs.\n";
			cout << "NoseBook now has " << (nb.get_friend_num() ) << " friends.\n";
			cout << "==========\n";
		}
	}

	return 0;
}
