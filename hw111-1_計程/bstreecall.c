#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node{
	char phonenum[9];
	int value;
	struct node *left;
	struct node *right;
}tNode;

int corresponding(char c){
	switch(c){
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		default:
			return 9;
	}
}

int value_calculator(char *phonenum){
	int value=0,i=0;
	int transfer_array[9]={0};
	while(phonenum[i] != '\0'){
		transfer_array[i]=corresponding(phonenum[i]);
		i++;
	}
	transfer_array[i]=-1;
	if(transfer_array[i-1]%2 == 0){
		value+=20;
	}
	i=0;
	while(transfer_array[i] != -1){
		value+=transfer_array[i];
		if(transfer_array[i]%2 == 0){
			value+=1;
		}
		if(transfer_array[i]==1 || transfer_array[i]==8){
			value-=3;
		}
		i++;
	}

	return value;
}

int compare(char *current,char *target){
	int i=0,digitc=0,digitt=0;
	while(current[i] != '\0'){
		digitc+=1;
		i++;
	}
	i=0;
	while(target[i] != '\0'){
		digitt+=1;
		i++;
	}
	if(digitc<digitt){
		return 1;
	}else if(digitc>digitt){
		return 0;
	}
	i=0;
	while(current[i] != '\0'){
		if(current[i] < target[i]){
			return 1;
		}else if(current[i] > target[i]){
			return 0;
		}
		i++;
	}
	return 0;
}

void inorder(tNode *ptr){
	if(ptr!=NULL){
		inorder(ptr->right);
		printf("%s ",ptr->phonenum);
		inorder(ptr->left);
	}
}

int main(int argc,char **argv){
	tNode *root=NULL,*ptr,*temp;
	int datanum;
	scanf("%d",&datanum);
	for(int i=0;i<datanum;i++){
		if(root==NULL){
			root=malloc(1*sizeof(tNode));
			scanf("%s",root->phonenum);
			root->value=value_calculator(root->phonenum);
			root->left=NULL;
			root->right=NULL;
		}else{
			temp=malloc(1*sizeof(tNode));
			scanf("%s",temp->phonenum);
			temp->value=value_calculator(temp->phonenum);
			temp->left=NULL;
			temp->right=NULL;
			ptr=root;
			while(1){
				if(temp->value > ptr->value){
					if(ptr->right == NULL){
						ptr->right=temp;
						break;
					}else{
						ptr=ptr->right;
					}
				}else if(temp->value==ptr->value && compare(temp->phonenum,ptr->phonenum)==1){
					if(ptr->right == NULL){
						ptr->right=temp;
						break;
					}else{
						ptr=ptr->right;
					}
				}else{
					if(ptr->left == NULL){
						ptr->left=temp;
						break;
					}else{
						ptr=ptr->left;
					}
				}
			}
		}
	}
	inorder(root);

	return 0;
}
