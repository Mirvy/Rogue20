#ifndef CONTAINER_H
#define CONTAINER_H
#include "core.h"

/****************************************//*!***********
 * \brief ROOT Container Class
 *
 * This class serves as a trait for actors, allowing them
 * to hold actors in an inventory.
 ******************************************************/

class Container {
	public :
		int size;                    /*!< Maximum number of actors. 0=unlimited*/
		TCODList<Actor *> inventory; /*!< Holds the actors held by actor.*/

		Container(int size);
		bool add(Actor *actor);      /*!< Places an actor into the invetory.*/
		void remove(Actor *actor);   /*!< Removes an actor from the inventory.*/
		~Container();
};
#endif
