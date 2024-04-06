#ifndef _WORLD_H
#define _WORLD_H

#include "Env_def.h"
#include "Creature.h"
#include "Goat.h"
#include "Grass.h"
#include "RandomNum.h"

//#define   WORLD_WIDTH   35
//#define   WORLD_LENTH   20

struct tCell{
	char type;
	Grass grass;
	Goat goat;
};

class World{
	public:
		World(int n_p, int r_s);
		void mainLoop(int d_i);
		void show_map() const;
		void is_a_goat();
		void is_a_grass();
		bool available_cell(int x, int y) const;
		bool cell_with_no_goat(int x, int y) const;

	private:
		tCell map[WORLD_LENTH][WORLD_WIDTH];
		int num_pass;
		int display_interval;
		int current_pass;
		RandomNum rand_obj;
		int current_x;
		int current_y;
		bool current_acted_differ;

};

#endif
