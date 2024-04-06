#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	char value;
	struct node *left;
	struct node *right;
	struct node *parent;
}tNode;

void preorder(tNode *ptr){
	if(ptr!=NULL){
		printf("%c",ptr->value);
		preorder(ptr->left);
		preorder(ptr->right);
	}
}

int main(int argc,char **argv){
	tNode *root=NULL,*temp,*present=NULL;
	char c[200000];
	scanf("%s",c);
	int i=0;

	root=malloc(1*sizeof(tNode));
	root->left=NULL;
	root->right=NULL;
	root->parent=NULL;
	root->value='F';
	present=root;
	while(c[i]!='\0'){
		if(c[i]=='('){
			temp=malloc(1*sizeof(tNode));
			temp->left=NULL;
			temp->right=NULL;
			temp->parent=present;
			present->left=temp;
			present=temp;
		}else if((c[i]>='A'&&c[i]<='Z') || (c[i]>='a'&&c[i]<='z')){
			present->value=c[i];
			present=present->parent;
		}else if(c[i]==')'){
			present=present->parent;
		}else{
			present->value=c[i];
			temp=malloc(1*sizeof(tNode));
			temp->left=NULL;
			temp->right=NULL;
			temp->parent=present;
			present->right=temp;
			present=temp;
		}	
		i++;
	}
	preorder(root);

	return 0;
}
