#include <stdio.h>

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

void qsort_hoar(tJob *jobs, int start_index, int end_index){
	if(start_index >= end_index){
		return;
	}

	int pivot = jobs[start_index].end;
	int smaller = start_index, bigger = end_index;
	tJob temp;

	while(1){
		while(jobs[smaller].end < pivot){
			smaller ++;
		}

		while(jobs[bigger].end > pivot){
			bigger --;
		}

		if(smaller >= bigger){
			break;
		}

		temp.begin = jobs[smaller].begin;
		temp.end = jobs[smaller].end;
		jobs[smaller].begin = jobs[bigger].begin;
		jobs[smaller].end = jobs[bigger].end;
		jobs[bigger].begin = temp.begin;
		jobs[bigger].end = temp.end;

		smaller ++;
		bigger --;
	}

	qsort_hoar(jobs, start_index, bigger);
	qsort_hoar(jobs, bigger + 1, end_index);
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

	qsort_hoar(jobs, 0, job_num - 1);

    int table[job_num + 1];
	table[0] = 0;

	int closest_no_conflict_job;

	for(int current_job = 1; current_job <= job_num; current_job ++){
		if(jobs[current_job - 1].begin < start_free_day || jobs[current_job - 1].end > end_free_day){  //unqualified
			table[current_job] = table[current_job - 1];
			continue;
		}

		if(current_job == 1 || (jobs[current_job - 1].begin >= jobs[current_job - 2].end)){  //dont have to compare, just take it
			table[current_job] = table[current_job - 1] + (jobs[current_job - 1].end - jobs[current_job - 1].begin);
		}else{
			closest_no_conflict_job = current_job - 2;

			while(closest_no_conflict_job != 0 && (jobs[current_job - 1].begin < jobs[closest_no_conflict_job - 1].end)){
				closest_no_conflict_job --;
			}

			table[current_job] = max(table[current_job - 1], table[closest_no_conflict_job] + (jobs[current_job - 1].end - jobs[current_job - 1].begin));
		}
	}

	printf("%d", table[job_num]);

	return 0;
}
