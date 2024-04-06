#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>

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

typedef struct kid{
	int id;
	struct kid *next;
}tKid;

void push_list(tKid **p_head, tKid **p_tail, int id){
	tKid *temp;

	temp = malloc(1*sizeof(tKid));
	temp->id = id;

	if(*p_head == NULL){
		temp->next = temp;
		*p_head = temp;
		*p_tail = temp;
	}else{
		(*p_tail)->next = temp;
		temp->next = *(p_head);
		*p_tail = temp;
	}
}

int kill_kid(tKid *target, tKid *prev_target){
	int value;

	prev_target->next = target->next;

	value = target->id;
	free(target);

	return value;
}

int main(int argc,char **argv){
	int data_num;
	scanf("%d", &data_num);
	int kid_num, remove_sequnce;
	tKid *head, *tail, *current, *temp;
	int ans;

	for(int i = 0; i < data_num; i++){
		scanf("%d%d", &kid_num, &remove_sequnce);
		head = NULL;
		tail = NULL;

		//make the circular list
		for(int kk = 1; kk <= kid_num; kk++){
			push_list(&head, &tail, kk);
		}

		//deleting kids
		current = head;
		for(int j = 0; j<remove_sequnce; j++){
			tail = current;
			current = current->next;
			temp = current->next;
			ans = kill_kid(current, tail);
			current = temp;
		}

		//free space
		while(current != temp){
			tail = current;
			current = current->next;
			free(tail);
		}

		printf("%d\n", ans);
	}

	return 0;
}
