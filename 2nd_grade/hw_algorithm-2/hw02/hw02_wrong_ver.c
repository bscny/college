#include<stdio.h>

typedef struct job{
	int begin;
	int end;
}tJob;

int max(int a, int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}

int main(int argc, char **argv){
	int job_num;
	scanf("%d", &job_num);
	int start_free_day, end_free_day;

	tJob jobs[job_num];
	for(int i = 0; i < job_num; i++){
		scanf("%d %d", &jobs[i].begin, &jobs[i].end);
	}
	scanf("%d %d", &start_free_day, &end_free_day);

	int table[end_free_day - start_free_day][end_free_day - start_free_day];
	int d = start_free_day - 1;
	int front, tail;
	int setted = 0;

	for(int j_kind = 0; j_kind < job_num; j_kind++){
		if(jobs[j_kind].begin < start_free_day || jobs[j_kind].end > end_free_day){  // unqualified
			continue;
		}

		if(setted == 0){
			// init the table
			for(int layer_begin = 1; layer_begin < end_free_day - d; layer_begin ++){
				for(int layer_end = layer_begin + 1; layer_end <= end_free_day - d; layer_end ++){
					if( (layer_begin + d) > jobs[0].begin || (layer_end + d) < jobs[0].end ){ // dont consider current job
						table[layer_begin - 1][layer_end - 2] = 0;
					}else{                                                                    //cuz initiallizing, just set value
						table[layer_begin - 1][layer_end - 2] = jobs[j_kind].end - jobs[j_kind].begin;
					}
				}
			}

			setted = 1;
		}else{
			// every blank after init
			for(int layer_begin = 1; layer_begin <= jobs[j_kind].begin - d; layer_begin ++){
				for(int layer_end = jobs[j_kind].end - d; layer_end <= end_free_day - d; layer_end ++){
					if( (layer_begin + d) == jobs[j_kind].begin){
						front = 0;
					}else{
						front = table[layer_begin - 1][(jobs[j_kind].begin - d) - 2];
					}

					if( (layer_end + d) == jobs[j_kind].end){
						tail = 0;
					}else{
						tail = table[(jobs[j_kind].end - d) - 1][layer_end - 2];
					}

					table[layer_begin - 1][layer_end - 2] = max(table[layer_begin - 1][layer_end - 2], (front + jobs[j_kind].end - jobs[j_kind].begin + tail));

				}
			}
		}
	}

	printf("%d", table[0][end_free_day - d - 2]);

	return 0;
}
