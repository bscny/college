#ifndef _GRASS_H
#define _GRASS_H

#include "Env_def.h"
#include "RandomNum.h"

class Grass : public Creature{
	public:
		friend class World;

		//big 3
		Grass();
		Grass(const Grass &in);
		Grass operator= (const Grass &in);

		Grass give_birth() const;
		void wanted_baby_coordinate(int current_x, int current_y);
		
		virtual void action(Creature *map[WORLD_LENTH][WORLD_WIDTH], bool current_acted_differ, int current_x, int current_y);
		virtual char get_ID() const;
		virtual void show_ID();


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
