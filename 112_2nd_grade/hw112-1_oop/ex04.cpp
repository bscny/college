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

typedef class room{
	public:
		int ID;
		string name;
		int pos[2];
		string description;
		string forwhom;
	private:
	protected:
}tRoom;

int main(int argc,char **argv){
	int data_num;
	cin >> data_num;
	tRoom rooms[data_num];
	char movement;
	int max_n = 0, max_s = 0, max_e = 0, max_w = 0;
	int current_x = 0, current_y = 0;

	for(int i = 0; i < data_num; i++){
		cin >> rooms[i].ID;
		cin >> rooms[i].name;
		cin >> rooms[i].pos[0];
		cin >> rooms[i].pos[1];
		cin >> rooms[i].description;
		cin >> rooms[i].forwhom;

		if(max_n < rooms[i].pos[1]){
			max_n = rooms[i].pos[1];
		}
		if(max_s > rooms[i].pos[1]){
			max_s = rooms[i].pos[1];
		}
		if(max_e < rooms[i].pos[0]){
			max_e = rooms[i].pos[0];
		}
		if(max_w > rooms[i].pos[0]){
			max_w = rooms[i].pos[0];
		}
	}

	for(int i = 0; i < data_num; i++){
		if((rooms[i].pos[0] == 0) && (rooms[i].pos[1] == 0)){
	cout << "Room#" << rooms[i].ID << "\n";
			cout << rooms[i].name << "\n";
			cout << "(" << rooms[i].pos[0] << "," << rooms[i].pos[1] << ")" << "\n";
			cout << rooms[i].description << "\n";
			cout << rooms[i].forwhom << "\n";
			cout << "********************\n";
		}
	}

	for(int i = 0; i< 3; i++){
		cin >> movement;

		if(movement == 'n'){
			if(current_y != max_n){
				current_y += 1;
			}
		}else if(movement == 's'){
			if(current_y != max_s){
				current_y -= 1;
			}
		}else if(movement == 'e'){
			if(current_x != max_e){
				current_x += 1;
			}
		}else{
			if(current_x != max_w){
				current_x -= 1;
			}
		}

		for(int i = 0; i < data_num; i++){
			if((rooms[i].pos[0] == current_x) && (rooms[i].pos[1] == current_y)){
				cout << "Room#" << rooms[i].ID << "\n";
				cout << rooms[i].name << "\n";
				cout << "(" << rooms[i].pos[0] << "," << rooms[i].pos[1] << ")" << "\n";
				cout << rooms[i].description << "\n";
				cout << rooms[i].forwhom << "\n";
				cout << "********************\n";
			}
		}
	}


	return 0;
}
