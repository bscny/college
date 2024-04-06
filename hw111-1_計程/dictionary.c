#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int counter=1;
char teller='A';

typedef struct node{
	char word[500];
	char start;
	int sequence;
	struct node *left;
	struct node *right;
}tNode;

tNode *input(tNode *root,char cut[500]){
	tNode *temp,*current;

	temp=malloc(1*sizeof(tNode));
	temp->left=NULL;
	temp->right=NULL;
	strcpy(temp->word,cut);
	current=root;

	if(root == NULL){
		return temp;
	}else{
		while(current!=NULL){
			if(strcmp(temp->word,current->word) < 0){
				if(current->left==NULL){
					current->left=temp;
					return root;
				}else{
					current=current->left;
				}
			}else{
				if(current->right==NULL){
					current->right=temp;
					return root;
				}else{
					current=current->right;
				}
			}
		}
		return root;
	}
}

void inorder(tNode *ptr){
	char c[500];
	if(ptr!=NULL){
		inorder(ptr->left);
		strcpy(c,ptr->word);
		ptr->start=c[0]-32;
		if(teller != ptr->start){
			counter=1;
		}
		teller=ptr->start;
		ptr->sequence=counter;
		counter+=1;
		inorder(ptr->right);
	}
}

void searchfun(tNode *root,char target[500]){
	tNode *temp;
	temp=root;

	if(temp == NULL){
		printf("NOT FOUND\n");
		return;
	}
	while(temp!=NULL){
		if(strcmp(temp->word,target) == 0){
			printf("%c %d\n",temp->start,temp->sequence);
			break;			
		}else if(strcmp(temp->word,target) < 0){
			temp=temp->right;
		}else{
			temp=temp->left;
		}
	}
	if(temp==NULL){
		printf("NOT FOUND\n");
	}
}

int main(int argc,char **argv){
	char total[10000],cut[500];
	scanf("%s",total);
	tNode *root=NULL;
	int now=0,i=0;
	char target[500];

	while(1){
		if(total[now]!=',' && total[now]!='\0'){
			cut[i]=total[now];
			i+=1;
		}else{
			cut[i]='\0';
			root=input(root,cut);
			i=0;
		}
		if(total[now] == '\0'){
			break;
		}
		now+=1;
	}
	inorder(root);
	while(scanf("%s",target) != EOF){
		searchfun(root,target);
	}

	return 0;
}
