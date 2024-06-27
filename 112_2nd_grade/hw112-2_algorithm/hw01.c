#include <stdio.h>

int main(int argc, char **argv){
    int arr[1000000];

    int current, sum = 0;
    int max = 0;
    int buff = 0, start_index_buff = -1;
    int i = 0;

	int min = 0;
	int potential_min = 0;

    while(scanf("%d", &current) != EOF){
        arr[i] = current;
		sum += current;

        if((current + buff) >= 0){
            if(start_index_buff == -1){
                start_index_buff = i;
            }

            buff += current;
            if(buff > max){
                max = buff;
            }
        }else{
            buff = 0;
            start_index_buff = -1;
        }

		if((current + potential_min) <= 0){
			potential_min += current;

			if(potential_min < min){
				min = potential_min;
			}
		}else{
			potential_min = 0;
		}

        i++;
    }

    for(int k = 0; k < start_index_buff; k++){
        current = arr[k];

        if((current + buff) >= 0){
            buff += current;
            if(buff > max){
                max = buff;
            }
        }else{
            buff = 0;
			break;
        }

    }

	if(max < (sum - min)){
		max = sum - min;
	}

    printf("%d", max);

    return 0;
}
