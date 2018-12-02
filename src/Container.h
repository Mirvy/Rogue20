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
                void save(boost::archive::text_oarchive &ar, const unsigned int version); /*!< Saves the current state.*/
                void load(boost::archive::text_iarchive &ar, const unsigned int version); /*!< Loads the saved state.*/
                bool add(Actor *actor);      /*!< Places an actor into the invetory.*/
                void remove(Actor *actor);   /*!< Removes an actor from the inventory.*/
                virtual ~Container();
};

#endif
