#include "Creature.h"
#include "Goat.h"
#include "AnsiPrint.h"

Goat::Goat() : age_start_reproduce(50), age_stop_reproduce(55), age_limit(70), distance_from_baby(2), distance_moving(1) {
	food_point = 20;
}

Goat::Goat(const Goat &in) : Creature(in), age_start_reproduce(50), age_stop_reproduce(55), age_limit(70), distance_from_baby(2), distance_moving(1) {
	food_point = in.food_point;
}

Goat Goat::operator= (const Goat &in){
	Creature::operator= (in);
	food_point = in.food_point;

	return *this;
}

void Goat::become_hungry(){
	food_point --;
}

Goat Goat::give_birth(){
	Goat baby;

	baby.has_acted = !has_acted;

	return baby;
}

void Goat::action(Creature *map[WORLD_LENTH][WORLD_WIDTH], bool current_acted_differ, int current_x, int current_y){
	if(has_acted == current_acted_differ){ //has_acted
		return;
	}

	grow_older();
	become_hungry();
	if( (age >= age_limit) || (food_point <= 0) ){  // too old or too hungry
		delete [] map[current_y][current_x];
		map[current_y][current_x] = NULL;
		return;
	}

	if( (age >= age_start_reproduce) && (age <= age_stop_reproduce) ){ // could have baby
		wanted_baby_coordinate(current_x, current_y);

		if( (x_baby < 0) || (x_baby >= WORLD_WIDTH) || (y_baby < 0) || (y_baby >= WORLD_LENTH) ){  // out of border
			has_acted = current_acted_differ;
			return;
		}else if(map[y_baby][x_baby] != NULL){
			if(map[y_baby][x_baby]->get_ID() == 'X'){ // already occupied
				has_acted = current_acted_differ;
				return;
			}else{         // baby find grass
				eating();
				delete [] map[y_baby][x_baby]; // kill the grass
			}
		}

		map[y_baby][x_baby] = new Goat[1];
		*(map[y_baby][x_baby]) = give_birth();

		has_acted = current_acted_differ;

	}else{         // movable
		wanted_future_coordinate(current_x, current_y);

		if( (x_future < 0) || (x_future >= WORLD_WIDTH) || (y_future < 0) || (y_future >= WORLD_LENTH) ){  // out of border
            has_acted = current_acted_differ;
            return;
        }else if(map[y_future][x_future] != NULL){  // already have creature
			if(map[y_future][x_future]->get_ID() == 'X'){  // already occupied
				has_acted = current_acted_differ;
				return;
			}else{        // destination has grass
				eating();
				delete [] map[y_future][x_future]; // kill the grass
			}
		}

		// move
		map[y_future][x_future] = map[current_y][current_x];
		map[current_y][current_x] = NULL;

		has_acted = current_acted_differ;

	}

}

char Goat::get_ID() const {
	return 'X';
}

void Goat::show_ID(){
	AnsiPrint("X", red, nochange, false, false);
}

void Goat::eating(){
	food_point += 5;
}

void Goat::wanted_future_coordinate(int current_x, int current_y){
	int direction = rand_obj.getRandomNum(UP, RIGHT);

	switch(direction){
		case UP:
			x_future = current_x;
			y_future = current_y - distance_moving;
			break;
		case DOWN:
			x_future = current_x;
			y_future = current_y + distance_moving;
			break;
		case LEFT:
			x_future = current_x - distance_moving;
			y_future = current_y;
			break;
		case RIGHT:
			x_future = current_x + distance_moving;
			y_future = current_y;
			break;
	}

}

void Goat::wanted_baby_coordinate(int current_x, int current_y){
	int direction = rand_obj.getRandomNum(UP, RIGHT);

	switch(direction){
		case UP:
			x_baby = current_x;
			y_baby = current_y - distance_from_baby;
			break;
		case DOWN:
			x_baby = current_x;
			y_baby = current_y + distance_from_baby;
			break;
		case LEFT:
			x_baby = current_x - distance_from_baby;
			y_baby = current_y;
			break;
		case RIGHT:
			x_baby = current_x + distance_from_baby;
			y_baby = current_y;
			break;
	}
}
