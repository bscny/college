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
			map[i][j].type = ' ';
		}
	}
	int x, y, temp;

	//initialize 5 goat
	temp = 0;
	while(temp < 5){
		x = rand_obj.getRandomNum(0, WORLD_WIDTH - 1);
		y = rand_obj.getRandomNum(0, WORLD_LENTH - 1);
		if(map[y][x].type == ' '){
			map[y][x].type = 'X';
			temp ++;
		}
	}

	//initialize 10 grass
	temp = 0;
	while(temp < 10){
		x = rand_obj.getRandomNum(0, WORLD_WIDTH - 1);
		y = rand_obj.getRandomNum(0, WORLD_LENTH - 1);
		if(map[y][x].type == ' '){
			map[y][x].type = 'I';
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
				if(map[current_y][current_x].type == ' '){
					continue;
				}else if(map[current_y][current_x].type == 'I'){
					is_a_grass();
				}else{
					is_a_goat();
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

void World::is_a_grass(){
	Grass &target_grass = map[current_y][current_x].grass;

	if(target_grass.actable(current_acted_differ) == false){ // has_acted before
		return ;
	}

	target_grass.grow_older();
	if(target_grass.is_dead() == true){ // kill it
		map[current_y][current_x].type = ' ';
		return ;
	}

	if(target_grass.can_have_baby() == true){ // give_birth
		int x_baby, y_baby;
		target_grass.wanted_baby_coordinate(current_x, current_y);
		x_baby = target_grass.get_Baby_x_coordinate();
		y_baby = target_grass.get_Baby_y_coordinate();
		
		if(available_cell(x_baby, y_baby) == true){
			map[y_baby][x_baby].grass = target_grass.give_birth();
			map[y_baby][x_baby].type = 'I';
		}

	}

	target_grass.set_Has_acted(current_acted_differ); // become has_acted

}

void World::is_a_goat(){
	Goat &target_goat = map[current_y][current_x].goat;

	if(target_goat.actable(current_acted_differ) == false){ // has_acted before
		return ;
	}

	target_goat.grow_older();
	target_goat.become_hungry();
	if(target_goat.is_dead() == true){ // kill it
		map[current_y][current_x].type = ' ';
		return ;
	}

	if(target_goat.can_have_baby() == true){ // give_birth
		int x_baby, y_baby;
		target_goat.wanted_baby_coordinate(current_x, current_y);
		x_baby = target_goat.get_Baby_x_coordinate();
		y_baby = target_goat.get_Baby_y_coordinate();

		if(cell_with_no_goat(x_baby, y_baby) == true){
			map[y_baby][x_baby].goat = target_goat.give_birth(map[y_baby][x_baby].type);
			map[y_baby][x_baby].type = 'X';
		}
		
	}else{ // moveable
		int x_future, y_future;
		target_goat.wanted_future_coordinate(current_x, current_y);
		x_future = target_goat.get_Future_x_coordinate();
		y_future = target_goat.get_Future_y_coordinate();

		if(cell_with_no_goat(x_future, y_future) == true){
			map[y_future][x_future].goat = target_goat.move(map[y_future][x_future].type);
			map[y_future][x_future].type = 'X';

			map[current_y][current_x].type = ' ';  // because moved, so kill the original
		}

	}

	target_goat.set_Has_acted(current_acted_differ);

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
					if(map[i][j].type == 'X'){
						AnsiPrint("X ", red, nochange, false, false);
					}else if(map[i][j].type == 'I'){
						AnsiPrint("I ", green, nochange, false, false);
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

bool World::available_cell(int x, int y) const {
	if( (x < 0) || (x >= WORLD_WIDTH) || (y < 0) || (y >= WORLD_LENTH) ){
		return false;
	}

	if(map[y][x].type == ' '){
		return true;
	}else{
		return false;
	}
}

bool World::cell_with_no_goat(int x, int y) const {
	if( (x < 0) || (x >= WORLD_WIDTH) || (y < 0) || (y >= WORLD_LENTH) ){
		return false;
	}

	if(map[y][x].type == 'X'){
		return false;
	}else{
		return true;
	}
}
