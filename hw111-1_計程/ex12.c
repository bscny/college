#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct pokemon{
	int seq;
	char name[11];
	int atk;
	int def;
	int health;
	struct pokemon *left;
	struct pokemon *right;
}tPokemon;

void inputfunc(tPokemon **proot,int seq,char *name,int atk,int def,int health){
	tPokemon *temp,*present;
	tPokemon *root=(*proot);
	present=root;
	temp=malloc(1*sizeof(tPokemon));
	temp->seq=seq;
	strcpy(temp->name,name);
	temp->atk=atk;
	temp->def=def;
	temp->health=health;
	temp->left=NULL;
	temp->right=NULL;

	if(root==NULL){
		*proot=temp;
		return;
	}else{
		while(present!=NULL){
			if(temp->atk < present->atk){        //layer1
				if(present->left != NULL){
					present=present->left;
				}else{
					present->left=temp;
					return;
				}
			}else if(temp->atk > present->atk){  //layer1
				if(present->right != NULL){
					present=present->right;
				}else{
					present->right=temp;
					return;
				}
			}else{                               //layer1
				if(temp->def < present->def){                //layer2        
					if(present->left != NULL){
						present=present->left;
					}else{
						present->left=temp;
						return;
					}
				}else if(temp->def > present->def){          //layer2
					if(present->right != NULL){
						present=present->right;
					}else{
						present->right=temp;
						return;
					}
				}else{                                       //layer2
					if(strlen(temp->name) < strlen(present->name)){        //layer3
						if(present->left != NULL){
							present=present->left;
						}else{
							present->left=temp;
							return;
						}
					}else if(strlen(temp->name) > strlen(present->name)){  //layer3
						if(present->right != NULL){
							present=present->right;
						}else{
							present->right=temp;
							return;
						}
					}else{                                                 //layer3
						if(strcmp(temp->name,present->name) < 0){                               //layer4
							if(present->left != NULL){
								present=present->left;
							}else{
								present->left=temp;
								return;
							}
						}else{                                                     //layer4
							if(present->right != NULL){
								present=present->right;
							}else{
								present->right=temp;
								return;
							}
						}
					}
				}
			}
		}
	}
}

void preorder(tPokemon *ptr){
	if(ptr!=NULL){
		preorder(ptr->right);
		printf("%03d %-10s %-3d %-3d %d\n",ptr->seq,ptr->name,ptr->atk,ptr->def,ptr->health);
		preorder(ptr->left);
	}
}

int main(int argc,char **argv){
	char linereader[80],*seg;
	char name[11];
	int seq=0,atk=0,def=0,health=0;
	int counter=0;
	tPokemon *root=NULL;

	while(gets(linereader) != NULL){
		counter=0;
		seg=strtok(linereader," ");
		while(seg!=NULL){
			switch(counter){
				case 0:
					seq=atoi(seg);
					break;
				case 1:
					strcpy(name,seg);
					break;
				case 2:
					atk=atoi(seg);
					break;
				case 3:
					def=atoi(seg);
					break;
				case 4:
					health=atoi(seg);
					break;
			}
			seg=strtok(NULL," ");
			counter+=1;
		}
		inputfunc(&root,seq,name,atk,def,health);
	}

	preorder(root);

	return 0;
}
