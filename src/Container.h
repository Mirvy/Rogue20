#ifndef CONTAINER_H
#define CONTAINER_H

/****************************************//*!***********
 * \brief ROOT Container Class
 *
 * This class serves as a trait for actors, allowing them
 * to hold actors in an inventory.
 ******************************************************/

class Container : public Persistent {
	public :
		int size;                    /*!< Maximum number of actors. 0=unlimited*/
		TCODList<Actor *> inventory; /*!< Holds the actors held by actor.*/

		Container(int size);
        void save(TCODZip &zip);     /*!< Saves the current state.*/
        void load(TCODZip &zip);     /*!< Loads the saved state.*/
		bool add(Actor *actor);      /*!< Places an actor into the invetory.*/
		void remove(Actor *actor);   /*!< Removes an actor from the inventory.*/
		virtual ~Container();
};
#endif
