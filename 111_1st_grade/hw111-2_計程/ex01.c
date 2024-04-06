#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdarg.h>

#define L0(fmt, arg...)

void L1(char *fmt, ...){
	va_list ap;
	char buffer[80];
	int len;

	va_start(ap,fmt);
	len=vsprintf(buffer,fmt,ap);
	if(len>0){
		buffer[len-1]='\0';
	}else{
		buffer[0]='\0';
	}
	printf("%s\n",buffer);
	va_end(ap);
}

void L2(char *fmt, ...){
	printf("check\n");
}

//debug func---

typedef struct build_block{
	int blockID;
	struct build_block *next;
}tBuild_block;

int find_the_belonging_tower(int blocknum,tBuild_block **p_heads,int blockID){
	tBuild_block *target_head,*temp;

	for(int i=0;i<blocknum;i++){
		target_head=*(p_heads+i);
		temp=target_head;
		while(temp!=NULL){
			if(temp->blockID != blockID){
				temp=temp->next;
			}else{
				return i;
			}
		}
	}
	return -1;
}

void show_all_blocks(int blocknum,tBuild_block **p_heads){
	tBuild_block *temp,*kill;

	for(int i=0;i<blocknum;i++){
		printf("%d: ",i);
		temp=*(p_heads+i);
		while(temp!=NULL){
			printf("%d ",temp->blockID);
			kill=temp;
			temp=temp->next;
			free(kill);
		}
		printf("\n");
	}
}

void reset_a_tower(tBuild_block **p_heads,tBuild_block *main_target){
	tBuild_block *sub_target,*ptr;
	
	while(main_target->next!=NULL){
		sub_target=main_target->next;
		if(*(p_heads+(sub_target->blockID)) == NULL){  //destination is empty
			*(p_heads+(sub_target->blockID))=sub_target;
			main_target->next=sub_target->next;
			sub_target->next=NULL;
		}else{                                         //destination has a head
			ptr=*(p_heads+(sub_target->blockID));

			while(ptr->next!=NULL){
				ptr=ptr->next;
			}
			ptr->next=sub_target;
			main_target->next=sub_target->next;
			sub_target->next=NULL;
		}
		L0("%d ",main_target->blockID);
	}
}

void move_onto(tBuild_block **p_heads,int index_of_tower_a,int index_of_tower_b,int block_a_ID,int block_b_ID){
	tBuild_block *main_target_a=*(p_heads+index_of_tower_a),*main_target_b=*(p_heads+index_of_tower_b);
	tBuild_block *prev_of_mainT_a=NULL;

	//finding main targets
	while(main_target_a->blockID!=block_a_ID){
		prev_of_mainT_a=main_target_a;
		main_target_a=main_target_a->next;
	}
	while(main_target_b->blockID!=block_b_ID){
		main_target_b=main_target_b->next;
	}

	//reset tower a
	reset_a_tower(p_heads,main_target_a);

	//reset tower b
	reset_a_tower(p_heads,main_target_b);
	
	//move a onto b
	if(main_target_a == *(p_heads+(index_of_tower_a))){ //killing the head
		*(p_heads+(index_of_tower_a))=NULL;
		main_target_b->next=main_target_a;
	}else{
		prev_of_mainT_a->next=NULL;
		main_target_b->next=main_target_a;
	}
}

void move_over(tBuild_block **p_heads,int index_of_tower_a,int index_of_tower_b,int block_a_ID,int block_b_ID){
	tBuild_block *main_target_a=*(p_heads+index_of_tower_a),*main_target_b=*(p_heads+index_of_tower_b);
	//tBuild_block *prev_of_mainT_a=*(p_heads+index_of_tower_a);
	tBuild_block *prev_of_mainT_a=NULL;

	//finding main targets
	while(main_target_a->blockID != block_a_ID){
		prev_of_mainT_a = main_target_a;
		main_target_a=main_target_a->next;		
	}	
	while(main_target_b->next!=NULL){
		main_target_b=main_target_b->next;
	}

	//reset tower a
	reset_a_tower(p_heads,main_target_a);
	
	//move a over b
	if(main_target_a == *(p_heads+(index_of_tower_a))){ //killing the head
		*(p_heads+(index_of_tower_a))=NULL;
	}else{
		prev_of_mainT_a->next=NULL;
	}
	main_target_b->next=main_target_a;
}

void pile_onto(tBuild_block **p_heads,int index_of_tower_a,int index_of_tower_b,int block_a_ID,int block_b_ID){
	tBuild_block *main_target_a=*(p_heads+index_of_tower_a),*main_target_b=*(p_heads+index_of_tower_b);
	tBuild_block *prev_of_mainT_a=NULL;

	//finding main targets
	while(main_target_a->blockID!=block_a_ID){
		prev_of_mainT_a=main_target_a;
		main_target_a=main_target_a->next;
	}
	while(main_target_b->blockID!=block_b_ID){
		main_target_b=main_target_b->next;
	}

	//reset tower b
	reset_a_tower(p_heads,main_target_b);
	
	//pile a onto b
	if(main_target_a == *(p_heads+(index_of_tower_a))){ //killing the head
		*(p_heads+(index_of_tower_a))=NULL;
		main_target_b->next=main_target_a;
	}else{
		prev_of_mainT_a->next=NULL;
		main_target_b->next=main_target_a;
	}
}

void pile_over(tBuild_block **p_heads,int index_of_tower_a,int index_of_tower_b,int block_a_ID,int block_b_ID){
	tBuild_block *main_target_a=*(p_heads+index_of_tower_a),*main_target_b=*(p_heads+index_of_tower_b);
	tBuild_block *prev_of_mainT_a=NULL;

	//finding main targets
	while(main_target_a->blockID!=block_a_ID){
		prev_of_mainT_a=main_target_a;
		main_target_a=main_target_a->next;
	}
	while(main_target_b->next!=NULL){
		main_target_b=main_target_b->next;
	}
	
	//pile a over b
	if(main_target_a == *(p_heads+(index_of_tower_a))){ //killing the head
		*(p_heads+(index_of_tower_a))=NULL;
		main_target_b->next=main_target_a;
	}else{
		prev_of_mainT_a->next=NULL;
		main_target_b->next=main_target_a;
	}
}

int main(int argc,char **argv){
	int blocknum=0;
	int block_a_ID,block_b_ID;
	char first_instruction[5],second_instruction[5];
	tBuild_block *heads[25];
	int index_of_tower_a=NULL,index_of_tower_b=NULL;

	while(scanf("%d",&blocknum)!=EOF){
		for(int i=0;i<blocknum;i++){
			heads[i]=NULL;
			heads[i]=malloc(1*sizeof(tBuild_block));
			heads[i]->blockID=i;
			heads[i]->next=NULL;
		}
		while(1){
			scanf("%s",first_instruction);
			if(strcmp(first_instruction,"quit")==0){
				break;
			}
			scanf("%d%s%d",&block_a_ID,second_instruction,&block_b_ID);
			//find the tower of a&b
			index_of_tower_a=find_the_belonging_tower(blocknum,&heads[0],block_a_ID);
			index_of_tower_b=find_the_belonging_tower(blocknum,&heads[0],block_b_ID);
			//recongnize the instructions
			if((block_a_ID==block_b_ID) || (index_of_tower_a==index_of_tower_b)){
				continue;
			}

			if(first_instruction[0]=='m'){
				if(second_instruction[1]=='n'){
					//MOVE ONTO
					move_onto(&heads[0],index_of_tower_a,index_of_tower_b,block_a_ID,block_b_ID);
				}else{
					//MOVE OVER
					move_over(&heads[0],index_of_tower_a,index_of_tower_b,block_a_ID,block_b_ID);
				}
			}else{
				if(second_instruction[1]=='n'){
					//PILE ONTO
					pile_onto(&heads[0],index_of_tower_a,index_of_tower_b,block_a_ID,block_b_ID);
				}else{
					//PILE OVER
					pile_over(&heads[0],index_of_tower_a,index_of_tower_b,block_a_ID,block_b_ID);
				}
			}
		}

		show_all_blocks(blocknum,&heads[0]);
		for(int i=0;i<blocknum;i++){
			heads[i]=NULL;
		}
	}

	return 0;
}
