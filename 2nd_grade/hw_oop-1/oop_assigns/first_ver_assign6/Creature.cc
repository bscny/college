#include "Creature.h"
#include <iostream>
using namespace std;

Creature::Creature(){
	age = 0;
	has_acted = false;
}

Creature::Creature(const Creature &in){
	age = in.age;
	has_acted = in.has_acted;
}

/*Creature Creature::operator= (const Creature &in){
	age = in.age;
	has_acted = in.has_acted;

	return *this;
}*/

void Creature::operator= (const Creature &in){
	age = in.age;
	has_acted = in.has_acted;
}

void Creature::grow_older(){
	age ++;
}

void Creature::set_Has_acted(bool in){
	has_acted = in;
}

bool Creature::actable(bool cur) const {
	if(has_acted != cur){
		return true;
	}else{
		return false;
	}
}
