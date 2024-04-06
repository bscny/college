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

typedef struct node{
	char name[100];
	struct node *next;
	struct node *prev;
}tNode;

void push_list(tNode **p_head, char *temp_name){
	tNode *temp = *p_head, *new;
	
	if(*p_head == NULL){
		*p_head = malloc(1*sizeof(tNode));
		strcpy((*p_head)->name, temp_name);
		(*p_head)->next = NULL;
		(*p_head)->prev = NULL;
	}else{
		while(temp->next != NULL){
			temp = temp->next;
		}
		new = malloc(1*sizeof(tNode));
		strcpy(new->name, temp_name);
		new->next = NULL;
		new->prev = temp;
		temp->next = new;
	}
}

void pop_list(tNode **p_head){
	if(*p_head == NULL){
		return;
	}
	tNode *kill = *p_head, *prev_kill;

	while(kill->next != NULL){
		kill = kill->next;
	}
	if(kill == *p_head){
		free(kill);
		*p_head = NULL;
		return;
	}
	prev_kill = kill->prev;
	prev_kill->next = NULL;
	free(kill);
}

void show_list(tNode *ptr){
	if(ptr == NULL){
		printf("/");
	}

	while(ptr != NULL){
		printf("/%s", ptr->name);
		ptr = ptr->next;
	}
}

int main(int argc,char **argv){
	char temp_name[100];
	char input;
	int there_is_word = 0, index = 0;
	tNode *head=NULL;

	//scanf("%*c");
	while(scanf("%c", &input) != EOF){
		if(input != '/'){
			if(there_is_word == 0){
				there_is_word = 1;
			}
			there_is_word = 1;
			temp_name[index] = input;
			index += 1;
		}else if((input == '/') && (there_is_word == 0)){
			continue;
		}else if((input == '/') && (there_is_word == 1)){
			temp_name[index] = '\0';
			there_is_word = 0;
			index = 0;

			//word segment catch, start to call funcs
			if(strcmp(temp_name, ".") == 0){
				continue;
			}else if(strcmp(temp_name, "..") == 0){
				//pop
				pop_list(&head);
			}else{
				//push
				push_list(&head, temp_name);
			}
		}
	}

	index -= 1;
	if(index != 0){
		temp_name[index] = '\0';
		if(strcmp(temp_name, ".") == 0){
			//dont do anything
		}else if(strcmp(temp_name, "..") == 0){
			//pop
			pop_list(&head);
		}else{
			//push
			push_list(&head, temp_name);
		}

	}

	show_list(head);

	return 0;
}
