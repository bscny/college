#include "Creature.h"
#include "Grass.h"
#include "AnsiPrint.h"

Grass::Grass() : age_start_reproduce(3), age_stop_reproduce(5), age_limit(6), distance_from_baby(1){
}

Grass::Grass(const Grass &in) : Creature(in), age_start_reproduce(3), age_stop_reproduce(5), age_limit(6), distance_from_baby(1){
}

Grass Grass::operator= (const Grass &in){
	Creature::operator= (in);

	return *this;
}

Grass Grass::give_birth() const {
	Grass baby;

	baby.has_acted = !has_acted;

	return baby;
}

void Grass::action(Creature *map[WORLD_LENTH][WORLD_WIDTH], bool current_acted_differ, int current_x, int current_y){
	if(has_acted == current_acted_differ){ // has_acted
		return;
	}

	grow_older();

	if(age >= age_limit){ //too old
		delete [] map[current_y][current_x];
		map[current_y][current_x] = NULL;
		return;
	}

	if( (age >= age_start_reproduce) && (age <= age_stop_reproduce) ){  // could have baby
		wanted_baby_coordinate(current_x, current_y);

		if( (x_baby < 0) || (x_baby >= WORLD_WIDTH) || (y_baby < 0) || (y_baby >= WORLD_LENTH) ){  // out of border
			has_acted = current_acted_differ;
			return;
		}else if(map[y_baby][x_baby] != NULL){  // already have creature
			has_acted = current_acted_differ;
			return;
		}
		
		map[y_baby][x_baby] = new Grass[1];
		*(map[y_baby][x_baby]) = give_birth();

	}

	has_acted = current_acted_differ;
}

char Grass::get_ID() const {
	return 'I';
}

void Grass::show_ID(){
	AnsiPrint("I", green, nochange, false, false);
}

void Grass::wanted_baby_coordinate(int current_x, int current_y){
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
