#ifndef ATTACKER_H
#define ATTACKER_H
#include "core.h"

/****************************************//*!***********
 * \brief ROOT Attacker Class
 *
 * This class serves as a ROOT trait which allows actors
 * to deal damage to other actors.
 * ****************************************************/

class Attacker {
	public :
		float power;                             /*!< Hit points given.*/
		Attacker(float power);
		void attack(Actor *owner, Actor *target);/*!< Performs the attach against target.*/
};
#endif
