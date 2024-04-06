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

int priority_calaulator(char operator){
	switch(operator){
		case '+': case '-':
			return 1;
			break;
		case '*': case '/':
			return 2;
			break;
		default:
			return 0;
			break;
	}
}

int main(int argc,char **argv){
	char infix_str[100000];
	gets(infix_str);
	int current_index = 0;
	char operator_stack[10000];
	int tail_operator_stack = -1;

	while(infix_str[current_index] != '\0'){
		switch(infix_str[current_index]){
			case '(':
				//store into operator_stack[] instantly
				tail_operator_stack += 1;
				operator_stack[tail_operator_stack] = infix_str[current_index];
				
				break;
			case ')':
				//pop values in operator_stack[] until seeing (
				while(operator_stack[tail_operator_stack] != '('){
					printf("%c", operator_stack[tail_operator_stack]);

					tail_operator_stack -= 1;
				}
				tail_operator_stack -= 1;
				
				break;
			case '+': case '-': case '*': case '/':
				//com[are the piority and store, print the operator_stack[]
				while(priority_calaulator(operator_stack[tail_operator_stack]) >= priority_calaulator(infix_str[current_index])){
					printf("%c", operator_stack[tail_operator_stack]);
					
					tail_operator_stack -= 1;
					if(tail_operator_stack == -1){
						break;
					}
				}

				tail_operator_stack += 1;
				operator_stack[tail_operator_stack] = infix_str[current_index];

				break;
			default:
				//printf out the varibles
				printf("%c", infix_str[current_index]);
			
				break;
		}

		current_index += 1;
	}

	while(tail_operator_stack != -1){
		printf("%c", operator_stack[tail_operator_stack]);

		tail_operator_stack -= 1;
	}


	return 0;
}
