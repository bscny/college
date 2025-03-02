#include<iostream>
#include<string>
#include<cstdarg>
using namespace std;

//DEBUG SETTINGS
//#define   Debug   //THE SWITCH IS HERE

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
	if(len > 0) cout<<color<<p<<"\033[m"<<"\n";
	va_end(ap);
	if(p != buf) delete [] p;
#endif
}
//END OF DEBUG SETTINGS

typedef class block{
	public:
		friend class movement;
	private:
		int blockID;
		class block *next;
	protected:
}tBlock;

typedef class movement{
	public:
		movement(){
			temp=NULL;
			counter=0;
		}
		void instruction_center(int bn);
		void finding_targeted_lists();
		void reseting_targeted_a_lists();
		void reseting_targeted_b_lists();

		void move_onto();
		void move_over();
		void pile_over();
		void pile_onto();

		void show_blocks();
	private:
		int block_num;
		string fir_instruction;
		string sec_instruction;
		tBlock **heads;
		int block_a_ID;
		int block_b_ID;
		int index_of_head_of_target_list_a;
		int index_of_head_of_target_list_b;
		tBlock *temp;
		tBlock *ptr;
		tBlock *kill;
		tBlock *target_a;
		tBlock *target_b;
		tBlock *prev_of_Ta;
		int counter;
	protected:
}tMovement;

void movement::instruction_center(int bn){
	block_num=bn;
	heads=new tBlock*[block_num];
	for(int i=0;i<block_num;i++){
		heads[i]=new tBlock[1];
		heads[i]->blockID=i;
		heads[i]->next=NULL;
	}
	while(1){
		cin>>fir_instruction;
		if(fir_instruction=="quit"){
			return;
		}

		cin>>block_a_ID>>sec_instruction>>block_b_ID;
	
	L1("%d",block_num);	
		finding_targeted_lists();
		L1("instruct 1");
		if((index_of_head_of_target_list_a == index_of_head_of_target_list_b) || (block_a_ID == block_b_ID)){
			continue;
		}
		L1("instruct 2");

		if(fir_instruction=="move"){
			if(sec_instruction=="onto"){
				move_onto();
			}else{
				move_over();
			}
		}else{
			if(sec_instruction=="onto"){
				pile_onto();
			}else{
				pile_over();
			}
		}

		L1("instruct 3");
	}
}

void movement::finding_targeted_lists(){
	counter=0;
	
	for(int i=0;i<block_num;i++){
		temp=heads[i];

			L0("finding target func check %d %d",temp->blockID,block_a_ID);
		while(temp!=NULL){
			if(counter==2){
	L3("finding target func check %d %d",target_a->blockID,target_b->blockID);
				return;
			}
			
			if(temp->blockID == block_a_ID){
				index_of_head_of_target_list_a=i;
				target_a=temp;
				counter+=1;
			}else if(temp->blockID == block_b_ID){
				index_of_head_of_target_list_b=i;
				target_b=temp;  //not decide yet
				counter+=1;
			}

			temp=temp->next;
		}
	}
}

void movement::reseting_targeted_a_lists(){
	while(target_a->next!=NULL){
		temp=target_a->next;
		if(heads[temp->blockID]==NULL){ //destination is empty
			heads[temp->blockID]=temp;
		}else{                          //destination has a head 
			ptr=heads[temp->blockID];

			while(ptr->next!=NULL){
				ptr=ptr->next;
			}
			ptr->next=temp;
		}
		target_a->next=temp->next;
		temp->next=NULL;
	}
}

void movement::reseting_targeted_b_lists(){
	while(target_b->next!=NULL){
		temp=target_b->next;
		if(heads[temp->blockID]==NULL){ //destination is empty
			heads[temp->blockID]=temp;
		}else{                          //destination has a head 
			ptr=heads[temp->blockID];

			while(ptr->next!=NULL){
				ptr=ptr->next;
			}
			ptr->next=temp;
		}
		target_b->next=temp->next;
		temp->next=NULL;
	}
}

void movement::move_onto(){
	//adjust target b & prev of a
	prev_of_Ta=NULL;
	L3("move onto func check %d",target_a->blockID);
	if(target_a != heads[index_of_head_of_target_list_a]){
		prev_of_Ta=heads[index_of_head_of_target_list_a];

		while(prev_of_Ta->next != target_a){
			prev_of_Ta=prev_of_Ta->next;
		}
	}
	//adjust over
	reseting_targeted_a_lists();
	reseting_targeted_b_lists();


	if(prev_of_Ta==NULL){
		heads[index_of_head_of_target_list_a]=NULL;
	}else{
		prev_of_Ta->next=NULL;
	}
	target_b->next=target_a;
}

void movement::move_over(){
	//adjust target b & prev of a
	prev_of_Ta=NULL;
	if(target_a != heads[index_of_head_of_target_list_a]){
		prev_of_Ta=heads[index_of_head_of_target_list_a];

		while(prev_of_Ta->next != target_a){
			prev_of_Ta=prev_of_Ta->next;
		}
	}

	while(target_b->next!=NULL){
		target_b=target_b->next;
	}
	//adjust over
	reseting_targeted_a_lists();

	if(prev_of_Ta==NULL){
		heads[index_of_head_of_target_list_a]=NULL;
	}else{
		prev_of_Ta->next=NULL;
	}
	target_b->next=target_a;
}

void movement::pile_onto(){
	//adjust target b & prev of a
	prev_of_Ta=NULL;
	if(target_a != heads[index_of_head_of_target_list_a]){
		prev_of_Ta=heads[index_of_head_of_target_list_a];

		while(prev_of_Ta->next != target_a){
			prev_of_Ta=prev_of_Ta->next;
		}
	}
	//adjust over
	reseting_targeted_b_lists();

	if(prev_of_Ta==NULL){
		heads[index_of_head_of_target_list_a]=NULL;
	}else{
		prev_of_Ta->next=NULL;
	}
	target_b->next=target_a;
}

void movement::pile_over(){
	//adjust target b & prev of a
	prev_of_Ta=NULL;
	if(target_a != heads[index_of_head_of_target_list_a]){
		prev_of_Ta=heads[index_of_head_of_target_list_a];

		while(prev_of_Ta->next != target_a){
			prev_of_Ta=prev_of_Ta->next;
		}
	}

	while(target_b->next != NULL){
		target_b=target_b->next;
	}
	//adjust over

	if(prev_of_Ta==NULL){
		heads[index_of_head_of_target_list_a]=NULL;
	}else{
		prev_of_Ta->next=NULL;
	}
	target_b->next=target_a;
}

void movement::show_blocks(){
	for(int i=0;i<block_num;i++){
		cout<<i<<": ";
		temp=heads[i];
		while(temp!=NULL){
			cout<<temp->blockID<<" ";
			kill=temp;
			temp=temp->next;
			delete [] kill;
		}
		cout<<"\n";
	}
L3("show");
	delete [] heads;
}

int main(int argc,char **argv){
	int block_num;
	tMovement robot_arm;

	while(cin>>block_num){
		//class time
		robot_arm.instruction_center(block_num);
		robot_arm.show_blocks();
	}

	return 0;
}
