#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sub_loop = 0;
int num_node;

void DFS(int prev_ID, int current_ID, int *nodes, int adj_matrix[][1000]){
    nodes[current_ID - 1] = 1;

    for(int id = 1; id <= num_node; id ++){
        if(adj_matrix[current_ID - 1][id - 1] == 1){
            if(nodes[id - 1] == 0){
                DFS(current_ID, id, nodes, adj_matrix);
            }else if(id != prev_ID){
                sub_loop = 1;
            }
        }
    }

}

int main(int argc, char **argv){
    int Name_to_ID_convertor[1001] = {0};
    scanf("%d", &num_node);
    int nodes[num_node];
    int adj_matrix[1000][1000] = {0};

    // reading datas
	int count = 0;

	for(int i = 0; i < num_node; i++) {
        int fn_ID;
        scanf("%d", &fn_ID);
        char str[10000];

		if(Name_to_ID_convertor[fn_ID] == 0){
			nodes[count] = 0;
			Name_to_ID_convertor[fn_ID] = count + 1;
			fn_ID = count + 1;

			count ++;
		}else{
			fn_ID = Name_to_ID_convertor[fn_ID];
		}

        fgets(str, 5000, stdin);
        char *n = strtok(str, " ");
        while (n != NULL) {
			int v = atoi(n);

			if(Name_to_ID_convertor[v] == 0){
				nodes[count] = 0;

				Name_to_ID_convertor[v] = count + 1;

				count ++;
			}

            adj_matrix[fn_ID - 1][Name_to_ID_convertor[v] - 1] = 1;
            n = strtok(NULL, " ");
        }
    }

    // func start
    int num_connected_compo = 0;

    for(int current_ID = 1; current_ID <= num_node; current_ID ++){
        if(nodes[current_ID - 1] == 0){
            //DFS
            DFS(0, current_ID, nodes, adj_matrix);
            num_connected_compo ++;
        }
    }

    printf("%d %d", num_connected_compo - 1, sub_loop);

    return 0;
}
