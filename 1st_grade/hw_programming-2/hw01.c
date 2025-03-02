#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define   added_successfully   0
#define   added_failed   1

int conflict=0;

typedef struct node_course{
	char courseID[10];
	double start_time;
	double end_time;
	struct node_course *next;
}tNode_course;

typedef struct node_conflict{
	char courseID[10];
	struct node_conflict *next;
}tNode_conflict;

void input_to_dailylist(tNode_course **phead,char courseID[10],double start_time,double end_time){
	tNode_course *head,*temp,*ptr;
	head=*phead;

	temp=malloc(1*sizeof(tNode_course));
	temp->start_time=start_time;
	temp->end_time=end_time;
	strcpy(temp->courseID,courseID);
	temp->next=NULL;

	if(head==NULL){
		*phead=temp;
	}else{
		ptr=head;
		while(ptr->next!=NULL){
			ptr=ptr->next;
		}
		ptr->next=temp;
	}
}

int making_conflict_list(tNode_conflict **phead_conflict_course,char courseID[10]){
	tNode_conflict *head_conflict_course,*temp_conflct_course,*ptr_conflict_course,*prev;
	head_conflict_course=*phead_conflict_course;

	if(head_conflict_course==NULL){
		temp_conflct_course=malloc(1*sizeof(tNode_conflict));
		temp_conflct_course->next=NULL;
		strcpy(temp_conflct_course->courseID,courseID);
		
		*phead_conflict_course=temp_conflct_course;
		return added_successfully;
	}else{
		ptr_conflict_course=head_conflict_course;
		
		while(ptr_conflict_course!=NULL){
			if(strcmp(ptr_conflict_course->courseID,courseID)==0){
				return added_failed;
			}
			prev=ptr_conflict_course;
			ptr_conflict_course=ptr_conflict_course->next;
		}

		temp_conflct_course=malloc(1*sizeof(tNode_conflict));
		temp_conflct_course->next=NULL;
		strcpy(temp_conflct_course->courseID,courseID);
		prev->next=temp_conflct_course;

		return added_successfully;
	}
}

void checking_time_conflict(tNode_course *head,tNode_conflict **phead_conflict_course){
	double timeperiod=6.5;
	tNode_course *temp;
	int counter=0;
	int checksum[10],j=0,determinator=0;
	char courseID[10];

	for(int i=0;i<15;i++){
		temp=head;
		counter=0;
		j=0;
		memset(checksum,0,10*sizeof(int));
		determinator=0;

		while(temp!=NULL){
			if(timeperiod>temp->start_time && timeperiod<temp->end_time){
				counter+=1;
				if(counter>1){
					//add to conflict list

					checksum[j]=making_conflict_list(phead_conflict_course,temp->courseID)+making_conflict_list(phead_conflict_course,courseID);
					j+=1;
					/*if(checksum==0){
						conflict+=1;
					}*/
				}else{
					strcpy(courseID,temp->courseID);
				}
			}
			temp=temp->next;
		}

		for(int k=0;k<10;k++){
			if(checksum[k]!=0){
				determinator=1;
			}
		}

		if(determinator==0 && counter>1){
			conflict+=1;
		}

		timeperiod+=1;
	}
}

int main(int argc,char **argv){
	int coursenum=0,segaments=0,day=0;
	double start_time=0,end_time=0;
	char courseID[10];
	tNode_course *head_week[7];
	for(int i=0;i<7;i++){
		head_week[i]=NULL;
	}

	tNode_conflict *head_conflict_course=NULL;

	//preparing the daily list
	scanf("%d%*c",&coursenum);
	for(int i=0;i<coursenum;i++){
		scanf("%d%*c%s%*c",&segaments,courseID);
		for(int k=0;k<segaments;k++){
			scanf("%d%*c%*c%lf%*c%*c%lf%*c",&day,&start_time,&end_time);
			switch(day){
				case 1:
					//Monday list
					input_to_dailylist(&head_week[0],courseID,start_time,end_time);
					break;
				case 2:
					//Tuesday list
					input_to_dailylist(&head_week[1],courseID,start_time,end_time);
					break;
				case 3:
					//Wednesday list
					input_to_dailylist(&head_week[2],courseID,start_time,end_time);
					break;
				case 4:
					//Thursday list
					input_to_dailylist(&head_week[3],courseID,start_time,end_time);
					break;
				case 5:
					//Friday list
					input_to_dailylist(&head_week[4],courseID,start_time,end_time);
					break;
				case 6:
					//Saturday list
					input_to_dailylist(&head_week[5],courseID,start_time,end_time);
					break;
				case 7:
					//Sunday list
					input_to_dailylist(&head_week[6],courseID,start_time,end_time);
					break;
			}
		}
	}
	//daily list completed
	
	//calculating...
	for(int i=0;i<7;i++){
		checking_time_conflict(head_week[i],&head_conflict_course);
	}

	printf("%d",conflict);

	/*for(int i=0;i<7;i++){
		while(head_week[i]!=NULL){
			printf("%s, ",head_week[i]->courseID);
			head_week[i]=head_week[i]->next;
		}
		printf("\n");
	}*/

	return 0;
}
