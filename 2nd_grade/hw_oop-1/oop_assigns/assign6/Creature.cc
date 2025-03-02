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

void Creature::operator= (const Creature &in){
	age = in.age;
	has_acted = in.has_acted;
}

void Creature::grow_older(){
	age ++;
}
