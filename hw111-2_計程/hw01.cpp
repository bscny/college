#include<iostream>
#include<string>
using namespace std;

#define   added_successfully   0
#define   added_failed   1

typedef class node_course{
	public:
		friend class list;
	private:
		string courseID;
		int day;
		double start_time;
		double end_time;
		class node_course *next;
	protected:
}tNode_course;

typedef class node_conflict{
	public:
		friend class list;
	private:
		string courseID;
		class node_conflict *next;
	protected:
}tNode_conflict;

typedef class list{
	public:
		void make_daily_list();
		list(){
			for(int i=0;i<7;i++){
				head[i]=NULL;
			}
			conflicts=0;
			head_conflict=NULL;
		}
		void check_time_conflict();
		int make_conflict_list();
		/*void printlist(){
			for(int i=0;i<7;i++){
				temp=head[i];
				while(temp!=NULL){
					cout<<temp->courseID<<" "<<temp->start_time<<endl;
					temp=temp->next;
				}
			}
		}*/
		void dislay_conflicts(){
			cout<<conflicts;
		}
	private:
		int coursenum;
		int segament;
		string courseID;
		char turn;
		tNode_course *head[7];
		tNode_course *temp;
		tNode_course *ptr;
		int conflicts;
		double timeperiod;
		int counter;
		int checksum[10];
		int determinator;
		int j;
		tNode_conflict *head_conflict;
		tNode_conflict *temp_conflict;
		tNode_conflict *ptr_conflict;
		tNode_conflict *prev_conflict;
		string courseID_discovered;
	protected:
}tList;

void list::make_daily_list(){
	cin>>coursenum;
	for(int i=0;i<coursenum;i++){
		cin>>segament>>courseID;
		for(int k=0;k<segament;k++){
			temp=new tNode_course[1];
			cin>>temp->day>>turn>>temp->start_time>>turn>>temp->end_time;
			temp->courseID=courseID;
			temp->next=NULL;

			if(head[temp->day-1] == NULL){
				head[temp->day-1]=temp;
			}else{
				ptr=head[temp->day-1];
				while(ptr->next!=NULL){
					ptr=ptr->next;
				}
				ptr->next=temp;
			}
		}
	}
}

int list::make_conflict_list(){
	if(head_conflict==NULL){
		head_conflict=new tNode_conflict[1];
		head_conflict->next=NULL;
		head_conflict->courseID=courseID_discovered;

		return added_successfully;
	}else{
		ptr_conflict=head_conflict;

		while(ptr_conflict!=NULL){
			if(ptr_conflict->courseID == courseID_discovered){
				return added_failed;
			}
			prev_conflict=ptr_conflict;
			ptr_conflict=ptr_conflict->next;
		}

		temp_conflict=new tNode_conflict[1];
		temp_conflict->courseID=courseID_discovered;
		temp_conflict->next=NULL;
		prev_conflict->next=temp_conflict;

		return added_successfully;
	}
}

void list::check_time_conflict(){
	for(int i=0;i<7;i++){
		timeperiod=6.5;

		for(int k=0;k<15;k++){
			temp=head[i];
			counter=0;
			j=0;
			for(int ii=0;ii<10;ii++){
				checksum[ii]=0;
			}
			determinator=0;

			while(temp!=NULL){
				if(timeperiod>temp->start_time && timeperiod<temp->end_time){
					counter+=1;
					if(counter>1){
						//add to conflict list
						checksum[j]+=make_conflict_list();
						courseID_discovered=temp->courseID;
						checksum[j]+=make_conflict_list();
						j+=1;
					}else{
						courseID_discovered=temp->courseID;
					}
				}
				temp=temp->next;
			}

			for(int l=0;l<10;l++){
				if(checksum[l]!=0){
					determinator=1;
				}
			}

			if(determinator==0 && counter>1){
				conflicts+=1;
			}

			timeperiod+=1;
		}
	}
}

int main(int argc,char **argv){
	tList run;
	
	run.make_daily_list();
	//run.printlist();
	run.check_time_conflict();
	run.dislay_conflicts();

	return 0;
}
