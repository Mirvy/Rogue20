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
        void save(boost::archive::text_oarchive &ar, const unsigned int version); /*!< Saves the current state.*/
        void load(boost::archive::text_iarchive &ar, const unsigned int version); /*!< Loads the saved state.*/
		void attack(Actor *owner, Actor *target);/*!< Performs the attach against target.*/
};

#endif
