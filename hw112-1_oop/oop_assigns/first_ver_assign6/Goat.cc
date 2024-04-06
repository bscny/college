#include "Creature.h"
#include "Goat.h"

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

Goat Goat::give_birth(char destination_type){
	Goat baby;

	baby.has_acted = !has_acted;

	if(destination_type == 'I'){
		eating();
	}

	return baby;
}

Goat Goat::move(char destination_type){
	if(destination_type == 'I'){
		eating();
	}

	has_acted = !has_acted;

	return *this;
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

int Goat::get_Future_x_coordinate() const {
	return x_future;
}

int Goat::get_Future_y_coordinate() const {
	return y_future;
}


bool Goat::is_dead() const {
	if( (age >= age_limit) || (food_point <= 0) ){
		return true;
	}else{
		return false;
	}
}

bool Goat::can_have_baby() const {
	if( (age >= age_start_reproduce) && (age <= age_stop_reproduce) ){
		return true;
	}else{
		return false;
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

int Goat::get_Baby_x_coordinate() const {
	return x_baby;
}

int Goat::get_Baby_y_coordinate() const {
	return y_baby;
}
