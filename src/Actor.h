#ifndef ACTOR_H
#define ACTOR_H

/***********************************************//*!*********
 * \brief Entity Base
 *
 * This class forms the foundation of all non world entities.
 * The ROOT of all characters, npcs, objects, items, etc....
 * **********************************************************/

class Actor : public Persistent {
	public:
		int x;                      /*!< X Position on current map*/
        int y;                      /*!< Y Position on current map*/
		int ch;                     /*!< Ascii code representing the actor.*/
		const char *name;           /*!< The actor's name*/
		TCODColor col;              /*!< Color to be used for printed character. */
		bool blocks;                /*!< Can actor be moved through */
		Attacker *attacker;         /*!< Trait - allows for damaging actors */
		Destructible *destructible; /*!< Trait - allows actor to take damage or be destroyed */
		Pickable *pickable;         /*!< Trait - allows actor to be manipublated by actors */
		Container *container;       /*!< Trait - allows actor to hold actors */
		Ai *ai;                     /*!< Logic used to control actors */
		
		Actor(int x, int y, int ch, const char* name, const TCODColor &col);
        void save(TCODZip &zip);                 /*!< Saves the current state.*/
        void load(TCODZip &zip);                 /*!< Load the saved state.*/
		void update();                           /*!< Processes any instructions from its ai or traits */
		void render() const;                     /*!< Sets actor's current position and color. */ 
		float getDistance(int cx, int cy) const; /*!< Calculates distance between two actors. */
		~Actor();
};
#endif
