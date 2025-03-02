#include<iostream>
#include<string>
#include<cstdarg>
#include<cstring>
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

//int people_num = 3;

typedef struct person{
	string name;
	int ID;
}tPerson;

typedef struct blank{
	int point_feeling;
	int times_of_joke;
}tBlank;

void Chatting(tBlank **feeling_table, int a_ID, int b_ID){
	feeling_table[a_ID][b_ID].point_feeling += 2;
	feeling_table[b_ID][a_ID].point_feeling += 2;
}

void Field_Game(tBlank **feeling_table, int a_ID, int b_ID){
	feeling_table[a_ID][b_ID].point_feeling += 3;
	feeling_table[b_ID][a_ID].point_feeling += 3;
}

void Night_Education(tBlank **feeling_table, int a_ID, int b_ID){
	feeling_table[a_ID][b_ID].point_feeling += 5;
	feeling_table[b_ID][a_ID].point_feeling += 5;
}

void Cheesy_Joke(tBlank **feeling_table, int a_ID, int b_ID){
	feeling_table[a_ID][b_ID].point_feeling += 2;
	feeling_table[b_ID][a_ID].times_of_joke += 1;

	if(feeling_table[b_ID][a_ID].times_of_joke == 3){
		feeling_table[b_ID][a_ID].point_feeling = 0;
		feeling_table[b_ID][a_ID].times_of_joke = 0;
	}
}

int main(int argc,char **argv){
	int people_num;
	cin >> people_num;
	tPerson people[people_num];
	tBlank *feeling_table[people_num];
	memset(feeling_table, 0, sizeof(feeling_table));
	for(int i=0; i<people_num; i++){
		feeling_table[i] = new tBlank[people_num];

		cin >> people[i].name;
		people[i].ID = i;
	}
	string movement;
	tPerson personA, personB;
	int find = 2;
	//int a_ID, b_ID;

	while(cin >> movement){
		cin >> personA.name;
		cin >> personB.name;
		find = 2;

		//find id of A B
		for(int i=0; i<people_num; i++){ //fin both
			if(find == 0){
				break;
			}

			if(personA.name == people[i].name){ //find A
				personA = people[i];
				find--;
				continue;
			}
			if(personB.name == people[i].name){ //find B
				personB = people[i];
				find--;
				continue;
			}
		}

		L0("%d %d\n", personA.ID, personB.ID);
		//a_ID = personA.ID;
		//b_ID = personB.ID;

		if(movement == "Chatting"){ //add 2 to both
			//call func
			Chatting(feeling_table, personA.ID, personB.ID);
			/*feeling_table[a_ID][b_ID].point_feeling += 2;
			feeling_table[b_ID][a_ID].point_feeling += 2;*/
		}else if(movement == "Field_Game"){ //add 3 to both
			//call func
			Field_Game(feeling_table, personA.ID, personB.ID);
			/*feeling_table[a_ID][b_ID].point_feeling += 3;
			feeling_table[b_ID][a_ID].point_feeling += 3;*/
		}else if(movement == "Night_Education"){ //add 5 to both
			//call func
			Night_Education(feeling_table, personA.ID, personB.ID);
			/*feeling_table[a_ID][b_ID].point_feeling += 5;
			feeling_table[b_ID][a_ID].point_feeling += 5;*/
		}else if(movement == "Cheesy_Joke"){ //add 2 to A set counter
			//call func
			Cheesy_Joke(feeling_table, personA.ID, personB.ID);
			/*feeling_table[a_ID][b_ID].point_feeling += 2;
			feeling_table[b_ID][a_ID].times_of_joke += 1;

			if(feeling_table[b_ID][a_ID].times_of_joke == 3){
				feeling_table[b_ID][a_ID].point_feeling = 0;
				feeling_table[b_ID][a_ID].times_of_joke = 0;
			}*/
		}

		if((feeling_table[personA.ID][personB.ID].point_feeling >= 10) && (feeling_table[personB.ID][personA.ID].point_feeling >= 10)){ //find the ans
			if(personA.name < personB.name){
				cout << personA.name << " " << personB.name;
			}else{
				cout << personB.name << " " << personA.name;
			}

			break;
		}
	}

	return 0;
}
