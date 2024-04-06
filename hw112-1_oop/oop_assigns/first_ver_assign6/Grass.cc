#include "Creature.h"
#include "Grass.h"

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


bool Grass::is_dead() const {
	if(age >= age_limit){
		return true;
	}else{
		return false;
	}
}

bool Grass::can_have_baby() const {
	if( (age >= age_start_reproduce) && (age <= age_stop_reproduce) ){
		return true;
	}else{
		return false;
	}
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

int Grass::get_Baby_x_coordinate() const {
	return x_baby;
}

int Grass::get_Baby_y_coordinate() const {
	return y_baby;
}
