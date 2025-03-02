#ifndef _CREATURE_H
#define _CREATURE_H

#include "Env_def.h"

/*#define   UP   0
#define   DOWN   1
#define   LEFT   2
#define   RIGHT   3*/

class Creature{
	public:
		//big 3
		Creature();
		Creature(const Creature &in);
		//Creature operator= (const Creature &in);
		void operator= (const Creature &in);

		void grow_older();
		void set_Has_acted(bool in);

		bool actable(bool cur) const;

		virtual bool is_dead() const = 0;
		virtual bool can_have_baby() const = 0;
		virtual void wanted_baby_coordinate(int current_x, int current_y) = 0;
		virtual int get_Baby_x_coordinate() const = 0;
		virtual int get_Baby_y_coordinate() const = 0;
		//give_birth() const;

	private:
	protected:
		int age;
		bool has_acted;
};

#endif
