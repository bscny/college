#include<stdio.h>

typedef struct job{
    int begin;
    int end;
}tJob;

int max(int a, int b, int c){
    if(a > b){
        if(a > c){
			return a;
		}else{
			return c;
		}
    }else{
        if(b > c){
			return b;
		}else{
			return c;
		}
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

	int table[end_free_day - start_free_day + 1];
	int d = start_free_day - 1;

	int current_end, setted = 0;
	int possible_val;

	for(int j_kind = 0; j_kind < job_num; j_kind ++){
		if(jobs[j_kind].begin < start_free_day || jobs[j_kind].end > end_free_day){ // unqualified jobs
			continue;
		}

		current_end = jobs[j_kind].end;

		if(setted == 0){
			for(int i = 0; i <= (current_end - d) - 2; i ++){
				table[i] = 0;
			}

			for(int i = current_end - d - 1; i < end_free_day - d; i ++){
				table[i] = jobs[j_kind].end - jobs[j_kind].begin;
			}

			setted = 1;
		}else{
			possible_val = table[(jobs[j_kind].begin - d - 1)] + (jobs[j_kind].end - jobs[j_kind].begin);

			if(possible_val > table[current_end - d - 1] && possible_val > table[current_end - d - 2]){ // we take consider of current job, rebuld values afterword
				table[current_end - d - 1] = possible_val;
				for(int ender = current_end - d + 1; ender <= end_free_day - d; ender ++){
					possible_val = 0;

					for(int i = 0; i < j_kind; i ++){
						if(jobs[i].end == ender + d){
							possible_val = max(table[jobs[i].begin - d - 1] + jobs[i].end - jobs[i].begin, table[ender - 2], possible_val);
						}
					}

					if(possible_val > table[ender - 2]){
						table[ender - 1] = possible_val;
					}else{
						table[ender - 1] = table[ender - 2];
					}
				}
			}

		}

		/*for(int i = 0; i <= (end_free_day - start_free_day); i ++){
			printf("%d  ", table[i]);
		}
		printf("\n");*/
	}

	printf("%d", table[end_free_day - d - 1]);


	return 0;
}
