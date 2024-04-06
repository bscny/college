#ifndef _GRASS_H
#define _GRASS_H

#include "RandomNum.h"

class Grass : public Creature{
	public:
		//big 3
		Grass();
		Grass(const Grass &in);
		Grass operator= (const Grass &in);

		Grass give_birth() const;

		virtual bool is_dead() const;
		virtual bool can_have_baby() const;
		virtual void wanted_baby_coordinate(int current_x, int current_y);
		virtual int get_Baby_x_coordinate() const;
		virtual int get_Baby_y_coordinate() const;

	private:
		const int age_start_reproduce;
		const int age_stop_reproduce;
		const int age_limit;
		const int distance_from_baby;

		int x_baby;
		int y_baby;
		RandomNum rand_obj;
	protected:
};

#endif
