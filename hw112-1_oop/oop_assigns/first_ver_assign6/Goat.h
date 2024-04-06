#ifndef _GOAT_H
#define _GOAT_H

#include "Env_def.h"
#include "RandomNum.h"

class Goat : public Creature{
	public:
		//big 3
		Goat();
		Goat(const Goat &in);
		Goat operator= (const Goat &in);

		void become_hungry();
		Goat give_birth(char destination_type);
		Goat move(char destination_type);
		void eating();
		void wanted_future_coordinate(int current_x, int current_y);
		int get_Future_x_coordinate() const;
		int get_Future_y_coordinate() const;

		virtual bool is_dead() const;
		virtual bool can_have_baby() const;
		virtual void wanted_baby_coordinate(int current_x, int current_y);
		virtual int get_Baby_x_coordinate() const;
		virtual int get_Baby_y_coordinate() const;

	private:
		int food_point;

		const int age_start_reproduce;
		const int age_stop_reproduce;
		const int age_limit;
		const int distance_from_baby;
		const int distance_moving;

		int x_baby;
		int y_baby;
		int x_future;
		int y_future;
		RandomNum rand_obj;
	protected:
};

#endif
