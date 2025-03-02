#ifndef _GOAT_H
#define _GOAT_H

#include "Env_def.h"
#include "RandomNum.h"

class Goat : public Creature{
	public:
		friend class World;

		//big 3
		Goat();
		Goat(const Goat &in);
		Goat operator= (const Goat &in);

		void become_hungry();
		Goat give_birth();

		virtual void action(Creature *map[WORLD_LENTH][WORLD_WIDTH], bool current_acted_differ, int current_x, int current_y);
		virtual char get_ID() const;
		virtual void show_ID();

		void eating();
		void wanted_future_coordinate(int current_x, int current_y);
		void wanted_baby_coordinate(int current_x, int current_y);

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
