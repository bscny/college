#ifndef _CREATURE_H
#define _CREATURE_H

#include "Env_def.h"

class Creature{
	public:
		friend class World;

		//big 3
		Creature();
		Creature(const Creature &in);
		void operator= (const Creature &in);

		void grow_older();

		virtual void action(Creature *map[WORLD_LENTH][WORLD_WIDTH], bool current_acted_differ, int current_x, int current_y) = 0;
		virtual char get_ID() const = 0;
		virtual void show_ID() = 0;

	private:
	protected:
		int age;
		bool has_acted;
};

#endif
