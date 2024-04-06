#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
#include<string.h>

//DEBUG SETTINGS
#define   Debug   //THE SWITCH IS HERE

#define L0(fmt, args...)
#define L1(fmt, args...)        log_print("\033[1;31m", fmt, ## args)
#define L2(fmt, args...)        log_print("\033[1;33m", fmt, ## args)
#define L3(fmt, args...)        log_print("\033[1;34m", fmt, ## args)
#define L4(fmt, args...)        log_print("\033[1;35m", fmt, ## args)
void log_print(const char *color,const char *fmt, ...) {
#ifdef Debug
	va_list ap;
	int len=0;
	char buf[200], *p=NULL;
	va_start(ap, fmt);
	len = vsnprintf(buf, sizeof(buf), fmt, ap);
	if(len < sizeof(buf)) { // enough buf
		p = buf;
		if(len > 0) buf[len] = '\0';
	} else {
		p = malloc(len+1);
		if(p) {
			vsnprintf(p, len, fmt, ap);
			if(len > 0) p[len] = '\0';
		} else printf("%s:error. malloc %dB\n", __func__, len+1);
	}
	if(len > 0) printf("%s%s%s", color, p, "\033[m");
	va_end(ap);
	if(p != buf) free(p);
#endif
}
//END OF DEBUG SETTINGS

#define   Max_People   8
#define   Max_Weight   400

typedef struct passenger{
	char name[80];
	int weight;
	struct passenger *next;
}tPassenger;

void pop(tPassenger **p_ptr, tPassenger *value){
	if(*p_ptr == NULL){
		return;
	}
	tPassenger *ptr = *p_ptr, *prev_ptr = NULL;
	while(ptr->next != NULL){
		prev_ptr = ptr;
		ptr = ptr->next;
	}
	prev_ptr->next = NULL;
	//*value = *ptr;
	value->weight = ptr->weight;
	strcpy(value->name, ptr->name);
	if(*p_ptr == ptr){ //killing head
		*p_ptr = NULL;
	}
	free(ptr);
}

void deque(tPassenger **p_ptr, tPassenger *value){
	if(*p_ptr == NULL){
		return;
	}
	tPassenger *kill = *p_ptr;
	//*value = *(*p_ptr);
	value->weight = (*p_ptr)->weight;
	strcpy(value->name, (*p_ptr)->name);
	(*p_ptr) = (*p_ptr)->next;
	free(kill);
}

void push(tPassenger **p_ptr, tPassenger value){
	tPassenger *temp, *ptr;

	temp = malloc(1*sizeof(tPassenger));
	strcpy(temp->name, value.name);
	temp->weight = value.weight;
	temp->next = NULL;
	if(*p_ptr == NULL){ //add to the head
		*p_ptr = temp;
	}else{
		ptr = *p_ptr;
		while(ptr->next != NULL){
			ptr = ptr->next;
		}
		ptr->next = temp;
	}
}

void enque(tPassenger **p_ptr, tPassenger value){
	tPassenger *temp;

	temp = malloc(1*sizeof(tPassenger));
	strcpy(temp->name, value.name);
	temp->weight = value.weight;
	temp->next = *p_ptr;
	*p_ptr = temp;
}

void print_list(tPassenger *ptr){
	tPassenger *kill;
	
	while(ptr != NULL){
		printf("%s ", ptr->name);
		kill = ptr;
		ptr = ptr->next;
		free(kill);
	}
	printf("\n");
}

void movement(tPassenger **p_head_passenger_in_elevator, tPassenger **p_head_passenger_in_waiting_line, tPassenger **p_head_passenger_outside){
	tPassenger value_temp;
	int current_weight = 0, current_passenger = 0;

	while(*p_head_passenger_in_waiting_line != NULL){
		//get into the elevator
		deque(p_head_passenger_in_waiting_line, &value_temp);
		if((current_passenger + 1  >  Max_People) || (current_weight + value_temp.weight  >  Max_Weight)){ //over the limits
			//punishment
			push(p_head_passenger_in_waiting_line, value_temp);
			break;
		}
		current_passenger += 1;
		current_weight += value_temp.weight;
		enque(p_head_passenger_in_elevator, value_temp);
	}
	for(int i=0 ; i<current_passenger ; i++){
		//get into the line
		if(*p_head_passenger_outside != NULL){ //there r people hanging
			deque(p_head_passenger_outside, &value_temp);
			push(p_head_passenger_in_waiting_line, value_temp);
		}else{
			break;
		}
	}
}

int main(int argc,char **argv){
	tPassenger *head_passenger_in_waiting_line = NULL;
	tPassenger *head_passenger_in_elevator = NULL;
	tPassenger *head_passenger_outside = NULL;
	tPassenger *temp, *current_last = NULL;
	char current_name[80];
	int num_passengers_in_line = 0;

	while(scanf("%s", current_name) != EOF){
		if(strcmp(current_name, "-1") == 0){
			//start the movement
			while(head_passenger_in_waiting_line != NULL){
				movement(&head_passenger_in_elevator, &head_passenger_in_waiting_line, &head_passenger_outside);
				print_list(head_passenger_in_elevator);
				head_passenger_in_elevator = NULL;
			}
			printf("\n");

			head_passenger_in_waiting_line = NULL;
			head_passenger_outside = NULL;
			head_passenger_in_elevator = NULL;
			num_passengers_in_line = 0;
		}else{
			//read data
			temp = malloc(1*sizeof(tPassenger));
			strcpy(temp->name, current_name);
			scanf("%d", &temp->weight);
			temp->next = NULL;
			if(num_passengers_in_line < Max_People){  //read into head_passenger_in_waiting_line
				num_passengers_in_line += 1;
				if(head_passenger_in_waiting_line == NULL){
					head_passenger_in_waiting_line = temp;
					current_last = head_passenger_in_waiting_line;
				}else{
					current_last->next = temp;
					current_last = temp;
				}
			}else{ //read into head_passenger_outside
				if(head_passenger_outside == NULL){
					head_passenger_outside = temp;
					current_last = head_passenger_outside;
				}else{
					current_last->next = temp;
					current_last = temp;
				}

			}
		}
	}

	return 0;
}
