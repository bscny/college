#include "World.h"
#include "Creature.h"
#include "Goat.h"
#include "Grass.h"
#include "RandomNum.h"
#include <iostream>
#include "AnsiPrint.h"
#include <unistd.h>
using namespace std;

#define   DELAY_MIN_SEC   50

World::World(int n_p, int r_s) : rand_obj(r_s) {
	num_pass = n_p;
	display_interval = 1;
	current_pass = 0;
	current_acted_differ = true;
	for(int i = 0; i < WORLD_LENTH; i++){
		for(int j = 0; j < WORLD_WIDTH; j++){
			map[i][j] = NULL;
		}
	}
	int x, y, temp;

	//initialize 5 goat
	temp = 0;
	while(temp < 5){
		x = rand_obj.getRandomNum(0, WORLD_WIDTH - 1);
		y = rand_obj.getRandomNum(0, WORLD_LENTH - 1);
		if(map[y][x] == NULL){
			map[y][x] = new Goat[1];
			temp ++;
		}
	}

	//initialize 10 grass
	temp = 0;
	while(temp < 10){
		x = rand_obj.getRandomNum(0, WORLD_WIDTH - 1);
		y = rand_obj.getRandomNum(0, WORLD_LENTH - 1);
		if(map[y][x] == NULL){
			map[y][x] = new Grass[1];
			temp ++;
		}
	}

}

void World::mainLoop(int d_i){
	if(d_i < 1){
		cout << "ERROR interval needs to > 0\n";
		return;
	}
	display_interval = d_i;

	show_map();

	int time_to_display = display_interval;

	for(current_pass = 1; current_pass <= num_pass; current_pass++){
		//each pass
		for(current_y = 0; current_y < WORLD_LENTH; current_y++){
			for(current_x = 0; current_x < WORLD_WIDTH; current_x++){
				if(map[current_y][current_x] == NULL){
					continue;
				}else{
					map[current_y][current_x]->action(map, current_acted_differ, current_x, current_y);
				}

			}
		}
		current_acted_differ = !current_acted_differ;

		// to print??
		time_to_display --;
		if(time_to_display == 0){
			show_map();
			usleep(1000 * DELAY_MIN_SEC);
			time_to_display = display_interval;
		}

	}

}

void World::show_map() const{
	system("clear");

	cout << "[   " << current_pass << "]\n";
	for(int i = -1; i <= WORLD_LENTH; i++){
		for(int j = -1; j < WORLD_WIDTH; j++){
			if(i == -1){
				// first line
				if(j == -1){
					// first line first blank
					cout << "  ";
				}else{
					cout << (j % 10) << " ";
				}
			}else if(i == WORLD_LENTH){
				// last line
				cout << "--";
			}else{
				if(j == -1){
					//first blank for each line
					cout << (i % 10) << " ";
				}else{
					if(map[i][j] != NULL){
						map[i][j]->show_ID();
						cout << " ";
					}else{
						cout << "  ";
					}
				}
			}

		}

		cout << "\n";
	}

	cout << flush;
}
