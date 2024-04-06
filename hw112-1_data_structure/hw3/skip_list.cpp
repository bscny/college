#include "skip_list.h"
#include <cstdlib>
#include <ctime>
#include <cstring>

Node_v::Node_v(){
	value = -1;
	arr_next.resize(1, nullptr);
}

Node_v::Node_v(int v, int h){
	value = v;
	arr_next.resize(h+1, nullptr);
}


Skip_List_v::Skip_List_v() : probability(0.5) {
	current_height = 0;
	head = new Node_v(-1, current_height);  // at start only base level needed
	srand(time(NULL));
}

int Skip_List_v::get_Random_height() const {
	double p = double(rand()) / RAND_MAX;
	int h = 0;

	while(p > probability){
		h ++;
		p = double(rand()) / RAND_MAX;
	}

	return h;
}

void Skip_List_v::insert(int target){
	Node_v *cur = head;  // start from sentinel

	// start inserting
	int tar_height = get_Random_height();
	Node_v *tar_node;
	tar_node = new Node_v(target, tar_height);
	int cp_height = current_height;
	if(current_height > tar_height){
		cp_height = tar_height;
	}

	// finding the correct position to insert and assinging the old lv
	for(int lv = current_height; lv >= 0; lv --){
		while( (cur->arr_next[lv] != nullptr) && (cur->arr_next[lv]->value < target)){
			cur = cur->arr_next[lv];
		}

		if(lv <= cp_height){
			tar_node->arr_next[lv] = cur->arr_next[lv];
			cur->arr_next[lv] = tar_node;
		}

	}

	// creating new lv
	if(tar_height > current_height){  // have to change sentinel's height
		for(int new_lv = current_height + 1; new_lv <= tar_height; new_lv ++){
			head->arr_next.push_back(tar_node);
		}

		current_height = tar_height;
	}

}

void Skip_List_v::range_query(int small, int big, vector<int> &multiset) const {
	if(head->arr_next[0] == nullptr){
		cout << "Empty ds\n";
		return ;
	}

	if(multiset.size() != 0){
		//reset multiset
		multiset.clear();
	}

	//finding start
	Node_v *start = head;

	for(int lv = current_height; lv >= 0; lv --){
		while( (start->arr_next[lv] != nullptr) && (start->arr_next[lv]->value < small) ){
			start = start->arr_next[lv];
		}
	}
	if(start->arr_next[0] == nullptr){
		return ;
	}
	start = start->arr_next[0];

	while(start != nullptr){
		if(start->value <= big){
			multiset.push_back(start->value);

			start = start->arr_next[0];
		}else{
			break;
		}

	}

}

int Skip_List_v::travel_bottom(){
	int sum = 0;
	Node_v *temp = head->arr_next[0];
	while(temp != nullptr){
		sum += temp->value;
		temp = temp->arr_next[0];
	}
	return sum;
}

Skip_List_v::~Skip_List_v(){
	Node_v *temp, *kill;

	temp = head;
	while(temp != nullptr){
		kill = temp;
		temp = temp->arr_next[0];
		delete kill;
	}

}

// for compare usage, because Skip_List is tooooo slow, make sure it's pointer's fault
// implementing two other version, one is pure pointer, one is pure vector

// p stand for pointer
Node_p::Node_p(){
	value = -1;
	next = nullptr;
	down = nullptr;
}

Node_p::Node_p(int v){
	value = v;
	next = nullptr;
	down = nullptr;
}


Skip_List_p::Skip_List_p() : probability(0.5) {
	current_height = 0;   // at start, only base level needed
	head = new Node_p(-1);  // start from top left
	srand(time(NULL));
}

int Skip_List_p::get_Random_height() const {
	double p = double(rand()) / RAND_MAX;
	int h = 0;

	while(p > probability){
		h ++;
		p = double(rand()) / RAND_MAX;
	}

	return h;
}

void Skip_List_p::insert(int target){
	Node_p *cur = head;  // start from sentinel

	//start insert
	int tar_height = get_Random_height();
	Node_p *tar_node = nullptr;
	Node_p *tar_up_node = nullptr, *tar_down_node = nullptr;
	int cp_height = current_height;
	if(current_height > tar_height){
		cp_height = tar_height;
	}

	// creating new lv if needed
	if(tar_height > current_height){
		for(int new_lv = current_height + 1; new_lv <= tar_height; new_lv ++){
			tar_down_node = tar_node;
			tar_node = new Node_p(target);
			Node_p *temp = new Node_p(-1);   //  adding a sentinel

			if(tar_up_node == nullptr){
				tar_up_node = tar_node;  // because all node created here are "new" nodes so we remember
				                         // the first created one as the tar_up_node of latter code
			}

			temp->next = tar_node;
			temp->down = head;
			head = temp;
			if(tar_down_node != nullptr){
				tar_node->down = tar_down_node;
			}
		}

	}

	tar_node = tar_up_node;  // back to the first created node if there are

	// finding the correct position to insert and assinging the old lv
	for(int lv = current_height; lv >= 0; lv --){
		while( (cur->next != nullptr) && (cur->next->value < target) ){
			cur = cur->next;
		}

		if(lv <= cp_height){
			tar_up_node = tar_node;
			tar_node = new Node_p(target);

			tar_node->next = cur->next;
			cur->next = tar_node;
			if(tar_up_node != nullptr){   //  already has an upper node
				tar_up_node->down = tar_node;
			}
		}

		cur = cur->down;
	}

	if(tar_height > current_height){
		current_height = tar_height;
	}

}

void Skip_List_p::range_query(int small, int big, vector<int> &multiset) const {
	if(head->next == nullptr){
		cout << "Empty ds\n";
		return ;
	}

	if(multiset.size() != 0){
		//reset multiset
		multiset.clear();
	}

	//finding start
	Node_p *start = head;

	for(int lv = current_height; lv >= 0; lv --){
		while( (start->next != nullptr) && (start->next->value <small) ){
			start = start->next;
		}

		if(start->down != nullptr){
			start = start->down;
		}
	}

	if(start->next == nullptr){
		return ;
	}
	start = start->next;

	while(start != nullptr){
		if(start->value <= big){
			multiset.push_back(start->value);

			start = start->next;
		}else{
			break;
		}

	}

}

void Skip_List_p::set_bottom_head(){
	bottom_head = head;
	while(bottom_head->down != nullptr){
		bottom_head = bottom_head->down;
	}
}

int Skip_List_p::travel_bottom(){
	int sum = 0;
	Node_p *temp = bottom_head->next;
	while(temp != nullptr){
		sum += temp->value;
		temp = temp->next;
	}
	return sum;
}

Skip_List_p::~Skip_List_p(){
	Node_p *temp = head;
	Node_p *kill;
	Node_p *h_per_lv = head;

	for(int lv = current_height; lv >= 0; lv --){
		temp = h_per_lv->next;
		while(temp != nullptr){
			kill = temp;
			temp = temp->next;

			delete kill;
		}

		kill = h_per_lv;
		delete kill;
		h_per_lv = h_per_lv->down;
	}
}


// give a cheating test

// c stand for cheating v stand for vector
Node_c_v::Node_c_v(){
	value = -1;
	repeated_num = 0;
	arr_next.resize(1, nullptr);
}

Node_c_v::Node_c_v(int v, int h){
	value = v;
	repeated_num = 0;
	arr_next.resize(h+1, nullptr);
}


Skip_List_c_v::Skip_List_c_v() : probability(0.5) {
	current_height = 0;
	head = new Node_c_v(-1, current_height);  // at start only base level needed
	srand(time(NULL));
}

int Skip_List_c_v::get_Random_height() const {
	double p = double(rand()) / RAND_MAX;
	int h = 0;

	while(p > probability){
		h ++;
		p = double(rand()) / RAND_MAX;
	}

	return h;
}

void Skip_List_c_v::insert(int target){
	Node_c_v *cur = head;  // start from sentinel

	// start inserting
	Node_c_v *prev_tar_node[current_height + 1];

	// finding the correct position to insert and assinging the old lv
	for(int lv = current_height; lv >= 0; lv --){
		while( (cur->arr_next[lv] != nullptr) && (cur->arr_next[lv]->value < target)){
			cur = cur->arr_next[lv];
		}

		prev_tar_node[lv] = cur;

	}

	if( (cur->arr_next[0] != nullptr) && (cur->arr_next[0]->value == target) ){
		cur->arr_next[0]->repeated_num ++;
		return ;
	}

	Node_c_v *tar_node;
	int tar_height = get_Random_height();
	tar_node = new Node_c_v(target, tar_height);
	int cp_height = current_height;
	if(tar_height < current_height){
		cp_height = tar_height;
	}

	// linking prev_tar_node and tar_node
	for(int lv = 0; lv <= cp_height; lv ++){
		tar_node->arr_next[lv] = prev_tar_node[lv]->arr_next[lv];
		prev_tar_node[lv]->arr_next[lv] = tar_node;
	}

	// creating new lv
	if(tar_height > current_height){  // have to change sentinel's height
		for(int new_lv = current_height + 1; new_lv <= tar_height; new_lv ++){
			head->arr_next.push_back(tar_node);
		}

		current_height = tar_height;
	}

}

void Skip_List_c_v::range_query(int small, int big, vector<int> &multiset) const {
	if(head->arr_next[0] == nullptr){
		cout << "Empty ds\n";
		return ;
	}

	if(multiset.size() != 0){
		//reset multiset
		multiset.clear();
	}

	//finding start
	Node_c_v *start = head;

	for(int lv = current_height; lv >= 0; lv --){
		while( (start->arr_next[lv] != nullptr) && (start->arr_next[lv]->value < small) ){
			start = start->arr_next[lv];
		}
	}
	if(start->arr_next[0] == nullptr){
		return ;
	}
	start = start->arr_next[0];

	while(start != nullptr){
		if(start->value <= big){
			for(int r = start->repeated_num; r >= 0; r --){
				multiset.push_back(start->value);
			}

			start = start->arr_next[0];
		}else{
			break;
		}

	}

}

int Skip_List_c_v::travel_bottom(){
	int sum = 0;
	Node_c_v *temp = head->arr_next[0];
	while(temp != nullptr){
		for(int r = temp->repeated_num; r >= 0; r --){
			sum += temp->value;
		}
		temp = temp->arr_next[0];
	}
	return sum;
}

Skip_List_c_v::~Skip_List_c_v(){
	Node_c_v *temp, *kill;

	temp = head;
	while(temp != nullptr){
		kill = temp;
		temp = temp->arr_next[0];
		delete kill;
	}

}
