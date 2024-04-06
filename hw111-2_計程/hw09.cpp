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

typedef class passenger{
	public:
		friend class elevator_list;
		friend class waiting_list;
		friend class outside_list;
		friend class command_center;
	private:
		string name;
		int weight;
		struct passenger *next;
		struct passenger *prev;
	protected:
}tPassenger;

typedef class elevator_list{
	public:
		friend class command_center;
		elevator_list(){
			head = NULL;
			tail = NULL;
		}
		tPassenger pop();
		tPassenger deque();
		void push(tPassenger input);
		void enque(tPassenger input);
	private:
		tPassenger *head;
		tPassenger *tail;
		tPassenger *temp;
		tPassenger value;
	protected:
}tElevator;

tPassenger tElevator::pop(){
	if(head == tail){ //pop the head
		value = *head;
		delete [] head;
		head = NULL;
		tail = NULL;
	}else{
		temp = tail->prev;
		value = *tail;
		delete [] tail;
		tail = temp;
		tail->next = NULL;
	}

	return value;
}

tPassenger tElevator::deque(){
	if(head == tail){ //deque the tail
		value = *tail;
		delete [] tail;
		head = NULL;
		tail = NULL;
	}else{
		value = *head;
		temp = head->next;
		temp->prev = NULL;
		delete [] head;
		head = temp;
	}

	return value;
}

void tElevator::push(tPassenger input){
	temp = new tPassenger[1];
	*temp = input;
	temp->next = NULL;
	if(head == NULL){ //add to the head
		temp->prev = NULL;
		head = temp;
		tail = head;
	}else{
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
	}
}

void tElevator::enque(tPassenger input){
	temp = new tPassenger[1];
	*temp = input;
	temp->next = NULL;
	if(head == NULL){ //add to the tail
		temp->prev = NULL;
		head = temp;
		tail = head;
	}else{
		head->prev = temp;
		temp->next = head;
		temp->prev = NULL;
		head = temp;
	}
}

typedef class waiting_list{
	public:
		friend class command_center;
		waiting_list(){
			head = NULL;
			tail = NULL;
		}
		tPassenger pop();
		tPassenger deque();
		void push(tPassenger input);
		void enque(tPassenger input);
	private:
		tPassenger *head;
		tPassenger *tail;
		tPassenger *temp;
		tPassenger value;
	protected:
}tWaiting;

tPassenger tWaiting::pop(){
	if(head == tail){ //pop the head
		value = *head;
		delete [] head;
		head = NULL;
		tail = NULL;
	}else{
		temp = tail->prev;
		value = *tail;
		delete [] tail;
		tail = temp;
		tail->next = NULL;
	}

	return value;
}

tPassenger tWaiting::deque(){
	if(head == tail){ //deque the tail
		value = *tail;
		delete [] tail;
		head = NULL;
		tail = NULL;
	}else{
		value = *head;
		temp = head->next;
		temp->prev = NULL;
		delete [] head;
		head = temp;
	}

	return value;
}

void tWaiting::push(tPassenger input){
	temp = new tPassenger[1];
	*temp = input;
	temp->next = NULL;
	if(head == NULL){ //add to the head
		temp->prev = NULL;
		head = temp;
		tail = head;
	}else{
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
	}
}

void tWaiting::enque(tPassenger input){
	temp = new tPassenger[1];
	*temp = input;
	temp->next = NULL;
	if(head == NULL){ //add to the tail
		temp->prev = NULL;
		head = temp;
		tail = head;
	}else{
		head->prev = temp;
		temp->next = head;
		temp->prev = NULL;
		head = temp;
	}
}

typedef class outside_list{
	public:
		friend class command_center;
		outside_list(){
			head = NULL;
			tail = NULL;
		}
		tPassenger pop();
		tPassenger deque();
		void push(tPassenger input);
		void enque(tPassenger input);
	private:
		tPassenger *head;
		tPassenger *tail;
		tPassenger *temp;
		tPassenger value;
	protected:
}tOutside;

tPassenger tOutside::pop(){
	if(head == tail){ //pop the head
		value = *head;
		delete [] head;
		head = NULL;
		tail = NULL;
	}else{
		temp = tail->prev;
		value = *tail;
		delete [] tail;
		tail = temp;
		tail->next = NULL;
	}

	return value;
}

tPassenger tOutside::deque(){
	if(head == tail){ //deque the tail
		value = *tail;
		delete [] tail;
		head = NULL;
		tail = NULL;
	}else{
		value = *head;
		temp = head->next;
		temp->prev = NULL;
		delete [] head;
		head = temp;
	}

	return value;
}

void tOutside::push(tPassenger input){
	temp = new tPassenger[1];
	*temp = input;
	temp->next = NULL;
	if(head == NULL){ //add to the head
		temp->prev = NULL;
		head = temp;
		tail = head;
	}else{
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
	}
}

void tOutside::enque(tPassenger input){
	temp = new tPassenger[1];
	*temp = input;
	temp->next = NULL;
	if(head == NULL){ //add to the tail
		temp->prev = NULL;
		head = temp;
		tail = head;
	}else{
		head->prev = temp;
		temp->next = head;
		temp->prev = NULL;
		head = temp;
	}
}

typedef class command_center{
	public:
		command_center(){
			Max_Weight = 400;
			Max_Passenger = 8;
			current_waiting_people_num = 0;
		}
		void input_data();
		void movement();
	private:
		int Max_Passenger;
		int Max_Weight;
		tElevator list_elevator;
		tWaiting list_waiting;
		tOutside list_outside;
		int current_waiting_people_num;
		tPassenger current_passenger;
		tPassenger ans;
	protected:
}tCommand_center;

void tCommand_center::input_data(){
	while(cin>>current_passenger.name){
		if(current_passenger.name != "-1"){
			//read data
			cin>>current_passenger.weight;

			if(current_waiting_people_num < Max_Passenger){
				//input into waiting list
				list_waiting.push(current_passenger);
				current_waiting_people_num += 1;
			}else{
				//input into outside list
				list_outside.push(current_passenger);
			}
		}else{
			//exacute a set of movement
			while(list_waiting.head != NULL){
				movement();
				while(list_elevator.head != NULL){
					ans = list_elevator.pop();
					cout<<ans.name<<" ";
				}
				cout<<"\n";
			}
			cout<<"\n";

			current_waiting_people_num = 0;
		}
	}
}

void tCommand_center::movement(){
	int current_weight = 0;
	int current_passenger_num = 0;
	tPassenger temp;

	while(list_waiting.head != NULL){
		temp = list_waiting.deque();
		if((current_passenger_num + 1  >  Max_Passenger) || (current_weight + temp.weight  >  Max_Weight)){
			list_waiting.push(temp);
			break;
		}
		current_passenger_num += 1;
		current_weight += temp.weight;
		list_elevator.push(temp);
	}
	for(int i=0 ; i<current_passenger_num ; i++){
		if(list_outside.head != NULL){
			temp = list_outside.deque();
			list_waiting.push(temp);
		}else{
			break;
		}
	}
}

int main(int argc,char **argv){
	tCommand_center location_1;

	location_1.input_data();

	return 0;
}
