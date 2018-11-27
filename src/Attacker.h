#ifndef ATTACKER_H
#define ATTACKER_H

/****************************************//*!***********
 * \brief ROOT Attacker Class
 *
 * This class serves as a ROOT trait which allows actors
 * to deal damage to other actors.
 * ****************************************************/

class Attacker : public Persistent {
	public :
		float power;                             /*!< Hit points given.*/
		Attacker(float power);
        void save(TCODZip &zip);                             /*!< Saves the current state.*/
        void load(TCODZip &zip);                             /*!< Loads the saved state.*/
		void attack(Actor *owner, Actor *target);/*!< Performs the attach against target.*/
};
#endif
