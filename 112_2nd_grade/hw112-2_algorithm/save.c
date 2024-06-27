#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "backtrace.h"

#define   N   1001
#define   INF   2147483640

typedef struct node{
	int name;
	char by_route[3];
	int edge_length;
	struct node *next;
}tNode;

// h stand for heap
typedef struct h_node{
	int key;
	int vertice_name;
}tH_node;

void bottom_up_heap(tH_node *heap, tH_node **p_addr_nodes_in_heap, int target_index){
	while(target_index > 0 && heap[target_index].key < heap[(target_index - 1) / 2].key){
		int name1 = heap[target_index].vertice_name, name2 = heap[(target_index - 1) / 2].vertice_name;

		tH_node temp = heap[target_index];
		heap[target_index] = heap[(target_index - 1) / 2];
		heap[(target_index - 1) / 2] = temp;

		tH_node *temp_addr = p_addr_nodes_in_heap[name1];
		p_addr_nodes_in_heap[name1] = p_addr_nodes_in_heap[name2];
		p_addr_nodes_in_heap[name2] = temp_addr;

		target_index = (target_index - 1) / 2;
	}
}

void top_down_heap(tH_node *heap, tH_node **p_addr_nodes_in_heap, int top){
	int target_index = 0;
	while(target_index < top){
		int swap_index;

		/*if((target_index + 1) * 2 < top && heap[target_index].key > heap[(target_index + 1) * 2].key ){
			swap_index = (target_index + 1) * 2;
		}else if( ((target_index + 1) * 2 - 1) < top && heap[target_index].key > heap[((target_index + 1) * 2) - 1].key ){
			swap_index = ((target_index + 1) * 2) - 1;
		}else{
			break;
		}*/

		if((target_index + 1) * 2 < top){
			if(heap[(target_index + 1) * 2].key > heap[((target_index + 1) * 2) - 1].key){
				swap_index = ((target_index + 1) * 2) - 1;
			}else{
				swap_index = (target_index + 1) * 2;
			}
		}else if( ((target_index + 1) * 2 - 1) < top && heap[target_index].key > heap[((target_index + 1) * 2) - 1].key ){
			swap_index = ((target_index + 1) * 2) - 1;
		}else{
			break;
		}

		int name1 = heap[target_index].vertice_name, name2 = heap[swap_index].vertice_name;

		tH_node temp = heap[target_index];
		heap[target_index] = heap[swap_index];
		heap[swap_index] = temp;

		tH_node *temp_addr = p_addr_nodes_in_heap[name1];
		p_addr_nodes_in_heap[name1] = p_addr_nodes_in_heap[name2];
		p_addr_nodes_in_heap[name2] = temp_addr;

		target_index = swap_index;
	}
}

void find_all_node_in_the_route(int head_name, tNode *cur_vertice, int accumulated_val, char *mother_routes, char *current_DFS_check,
	   	                        int *ans_distance, tH_node **addr_nodes_in_heap, char vehicle_to_node[N][3], tH_node *heap, tNode **adj_list){
	if(head_name == cur_vertice->name){
		return;
	}


	if(strcmp(current_DFS_check, mother_routes) == 0){
		accumulated_val += cur_vertice->edge_length;
	}else{
		if(strlen(current_DFS_check) == 2){  // transfer to another bus
			accumulated_val += 5;
			accumulated_val += cur_vertice->edge_length;
		}else if(strlen(current_DFS_check) == 1){
			if(atoi(current_DFS_check) == 0){  // transfer to another MRT
				accumulated_val += 10;
			}else{                      // transfer to another bus
				accumulated_val += 5;
			}
			accumulated_val += cur_vertice->edge_length;
		}
	}

	if(ans_distance[cur_vertice->name] == 0){  // not marked yet
		//  update heap
		if(accumulated_val < (addr_nodes_in_heap[cur_vertice->name])->key){
			(addr_nodes_in_heap[cur_vertice->name])->key = accumulated_val;
			strcpy(vehicle_to_node[cur_vertice->name], current_DFS_check);

			bottom_up_heap(heap, addr_nodes_in_heap, (addr_nodes_in_heap[cur_vertice->name] - heap));
		}
	}

	// recusion to find the route
	tNode *temp = adj_list[cur_vertice->name];
	while(temp != NULL){
		if(strcmp(temp->by_route, current_DFS_check) == 0){
			find_all_node_in_the_route(head_name, temp, accumulated_val, current_DFS_check, current_DFS_check,
									   ans_distance, addr_nodes_in_heap, vehicle_to_node, heap, adj_list);
		}

		temp = temp->next;
	}
}

int survay(tNode **adj_list, int max_name, int target_from, int target_to){
	if(target_from == target_to){
		return 0;
	}
	
	//init time
	tH_node *addr_nodes_in_heap[N] = {0};
	char vehicle_to_node[N][3];
	int ans_distance[N] = {0};
	ans_distance[target_from] = 1;  // mark the target_from for DFS use
	// the heap
	int top = 0;
	tH_node heap[max_name];

	tNode *temp = adj_list[target_from];
	while(temp != NULL){  // init visible nodes
		heap[top].vertice_name = temp->name;
		heap[top].key = temp->edge_length;

		addr_nodes_in_heap[temp->name] = &heap[top];

		strcpy(vehicle_to_node[temp->name], temp->by_route);

		bottom_up_heap(heap, addr_nodes_in_heap, top);

		top ++;
		temp = temp->next;
	}

	//printf("%d\n\n", max_name);
	for(int i = 1; i <= max_name; i ++){
		if(i == target_from){
			continue;
		}else if(addr_nodes_in_heap[i] != NULL){
			continue;
		}
		/*tNode *temp = adj_list[i];
		if(temp == NULL){
			continue;
		}*/

		//  init unvisible nodes
		heap[top].vertice_name = i;
		heap[top].key = INF;

		addr_nodes_in_heap[i] = &heap[top];

		top ++;
	}
	//  init over

	/*for(int i = 0; i < top; i ++){
		printf("%d(%d)  ", heap[i].key, heap[i].vertice_name);
	}
	printf("\n");

	for(int i = 1; i <= max_name; i ++){
		printf("%d:%s  ", i, vehicle_to_node[i]); //debug
	}
	printf("\n");*/


	//pop from heap and DFS through the route
	while(top > 0){   // each ans_distance
		if(heap[0].key == INF){
			return -1;
		}else if(heap[0].vertice_name == target_to){
			return heap[0].key;
		}

		int current_node = heap[0].vertice_name;
		ans_distance[current_node] = heap[0].key;
		
		/*if(top == 3){
			return 0;
		}
		if(top == 4){
			printf("heap pop: %d(%d)\n", current_node, ans_distance[current_node]); //debug
		}*/
		
		top --;
		addr_nodes_in_heap[heap[top].vertice_name] = &heap[0];
		heap[0] = heap[top];
		top_down_heap(heap, addr_nodes_in_heap, top);

		tNode *each_adj_node = adj_list[current_node];
		while(each_adj_node != NULL){
			find_all_node_in_the_route(current_node, each_adj_node, ans_distance[current_node], vehicle_to_node[current_node], each_adj_node->by_route,
									   ans_distance, addr_nodes_in_heap, vehicle_to_node, heap, adj_list);

			each_adj_node = each_adj_node->next;

			/*for(int i = 1; i <= max_name; i ++){
				printf("%d:%s  ", i, vehicle_to_node[i]); //debug
			}
			printf("\n");*/
		}

		/*if(top == 3){
			for(int i = 0; i < top; i ++){
				printf("%d(%d)  ", heap[i].key, heap[i].vertice_name);
			}
			printf("\n");

			for(int i = 1; i <= max_name; i ++){
				printf("%d:%s  ", i, vehicle_to_node[i]); //debug
			}
			printf("\n");

			for(int i = 1; i <= max_name; i ++){
				printf("%d:%d  ", i, ans_distance[i]); //debug
			}
			printf("\n");

		}*/

	}

	/*for(int i = 0; i < top; i ++){
		printf("%d(%d)  ", heap[i].key, heap[i].vertice_name);
	}
	printf("\n");

	for(int i = 1; i <= max_name; i ++){
		printf("%d:%s  ", i, vehicle_to_node[i]); //debug
	}
	printf("\n");*/


	return -1;
}

int main(int argc, char **argv){
	set_signal_handler();
	tNode *adj_list[N] = {0};
	int max_name = 0;
	
	while(1){
		char mode;
		scanf("%c", &mode);

		if(mode == 'E'){  // finish reading datas
			break;
		}else if(mode == 'Q'){
			//  each survay
			int target_from, target_to;
			scanf("%d%d", &target_from, &target_to);

			//  dijasktra + DFS time
			printf("%d\n", survay(adj_list, max_name, target_from, target_to));
			//survay(adj_list, max_name, target_from, target_to);
		}else if(mode == 'L'){
			//  each route
			char route_name[3];
			int num_stops;
			scanf("%s%d", route_name, &num_stops);

			for(int i = 0; i < num_stops; i ++){
				int from, to, val;
				scanf("%d%d%d", &from, &to, &val);
				if(max_name < from){
					max_name = from;
				}else if(max_name < to){
					max_name = to;
				}

				tNode *new = malloc(1*sizeof(tNode));
				new->name = to;
				new->edge_length = val;
				new->next = NULL;
				strcpy(new->by_route, route_name);

				if(adj_list[from] == NULL){
					adj_list[from] = new;
				}else{
					tNode *temp = adj_list[from];
					while(temp->next != NULL){
						temp = temp->next;
					}

					temp->next = new;
				}
			}

		}
	}

	/*for(int i = 1; i <= 7; i ++){
		tNode *temp = adj_list[i];
		printf("%d: ", i);
		while(temp != NULL){
			printf("%d(%d, %s)  ", temp->name, temp->edge_length, temp->by_route);
			temp = temp->next;
		}
		printf("\n");
	}*/

	return 0;
}
