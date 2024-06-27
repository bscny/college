#include <stdio.h>
#include <stdlib.h>

#define   N   1000

typedef struct wood{
	int head;
	int tail;
}tWood;

typedef struct node{
	int ID;
	struct node *next;
}tNode;

int cmpfunc(const void *a, const void *b){
   return ( ((tWood*)a)->head - ((tWood*)b)->head );
}

int find_start_index(tWood *woods, int wood_num, tWood start_wood){
	int left = 0, right = wood_num - 1;
	int mid, temp;

	while(left <= right){
		mid = (left + right)/2;

		if(woods[mid].head > start_wood.head){
			right = mid - 1;
		}else if(woods[mid].head < start_wood.head){
			left = mid + 1;
		}else{
			if(woods[mid].tail == start_wood.tail){
				return mid;
			}

			temp = mid;
			while(temp > 0 && woods[temp].head == woods[temp - 1].head){
				if(woods[temp - 1].tail == start_wood.tail){
					return temp - 1;
				}

				temp --;
			}
			
			temp = mid;
			while(temp < wood_num - 1 && woods[temp].head == woods[temp + 1].head){
				if(woods[temp + 1].tail == start_wood.tail){
					return temp + 1;
				}

				temp ++;
			}
		}
	}

	printf("ERROR\n");
	return -1;
}

int BFS(int *marker, tNode *adj_list, int num_valuable_woods){
	int ID_queue[N];
	int bottom = 0, top = 0;
	marker[0] = 1;
	ID_queue[0] = 0;
	
	int current_node_ID;

	while(bottom <= top){
		current_node_ID = ID_queue[bottom++];

		tNode *temp = adj_list[current_node_ID].next;
		while(temp != NULL){
			if(marker[temp->ID] == 0 && temp->ID < num_valuable_woods){
				//enqueue ID
				ID_queue[++top] = temp->ID;
				marker[temp->ID] = marker[current_node_ID] + 1;

				if(temp->ID == num_valuable_woods - 1){
					return marker[num_valuable_woods - 1] - 1;
				}
			}

			temp = temp->next;
		}
	}

	return 0;
}

int main(int argc, char **argv){
	int wood_num;
	scanf("%d", &wood_num);

	tWood woods[wood_num];
	tWood start_wood, end_wood;

	// reading datas
	for(int i = 0; i < wood_num; i ++){
		scanf("%d%d", &woods[i].head, &woods[i].tail);

		if(i == 0){
			start_wood.head = woods[0].head;
			start_wood.tail = woods[0].tail;
		}else if(i == wood_num - 1){
			end_wood.head = woods[i].head;
			end_wood.tail = woods[i].tail;
		}
	}

	if(start_wood.tail > end_wood.head){
    	printf("1");
      	return 0;
    }

	//sort according to head
	qsort(woods, wood_num, sizeof(tWood), cmpfunc);

	// building adj_list & marker
	int start_index = find_start_index(woods, wood_num, start_wood);
	int marker[N] = {0};
	tNode adj_list[N];
	int curr_ID = 0;
	int num_valuable_woods;

	for(int curr_index = start_index; curr_index < wood_num; curr_index ++){
		adj_list[curr_ID].next = NULL;

		if(woods[curr_index].head == end_wood.head && woods[curr_index].tail == end_wood.tail){ // find the target_ID
			num_valuable_woods = curr_index - start_index + 1;
			break;
		}

		int next_index = curr_index + 1;
		tNode *temp_tail = &adj_list[curr_ID];

		while(next_index < wood_num && woods[curr_index].tail > woods[next_index].head){
			tNode *temp = malloc(1*sizeof(tNode));
			temp->ID = curr_ID + (next_index - curr_index);
			temp->next = NULL;

			temp_tail->next = temp;
			temp_tail = temp;

			next_index ++;
		}

		curr_ID ++;
	}

	/*printf("%d\n", num_valuable_woods);
	for(int i = 0; i < num_valuable_woods; i ++){
		tNode *temp = adj_list[i].next;
		while(temp != NULL){
			printf("%d ", temp->ID);

			temp = temp->next;
		}
		printf("\n");
	}*/

	//BFS time
	printf("%d", BFS(marker, adj_list, num_valuable_woods));

	return 0;
}
