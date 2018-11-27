#ifndef PERSISTENT_H
#define PERSISTENT_H

/***************************************//*!**********
 * \brief INTERFACE - Save/Load
 *
 *
 * This interface allows for game elements to be saved
 * using TCODZip.
 ****************************************************/

class Persistent {
	public :
		virtual void load(TCODZip &zip) = 0; /*!< Loads states.*/
		virtual void save(TCODZip &zip) = 0; /*!< Saves state. */
        virtual ~Persistent() {} 
};

#endif
