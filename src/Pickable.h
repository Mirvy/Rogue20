#ifndef PICKABLE_H
#define PICKABLE_H

/**********************************************//*!***********
 * \brief ROOT of Carryable Things
 *
 * This class is the ROOT ancestor of all entities which can
 * be physically manipulated in the game world(Take,Carry,etc.)
 * ***********************************************************/

class Pickable : public Persistent {
	public :
		virtual ~Pickable() {}
		bool pick(Actor *owner, Actor *wearer);        /*!< Allows wearer to hold owner, taken from the world. */
		virtual bool use(Actor *owner, Actor *wearer); /*!< Exhausts the actor be removing it. */
		void drop(Actor *owner, Actor *wearer);        /*!< Allows current wearer to place owner in the world. */
        static Pickable *create(boost::archive::text_iarchive &ar); /*!< Faciliates state loading polymorphism */
    protected :

        /*******************************//*!********
         * \brief Key for Polymorphism
         *
         * Key used to determine which descendant to
         * instantiate upon state loading.
         ******************************************/

        enum PickableType {
            HEALER,LIGHTNING_BOLT,CONFUSER,FIREBALL
        };
};

/*********************************************//*!************
 * \brief Basic Healing Class
 *
 * This class is a basic implementation of some entity which
 * can heal actors which hold the destructible trait.
 * **********************************************************/

class Healer : public Pickable {
	public :
		float amount;                          /*!< Amount of hp which will be restored. */
		Healer(float amount);
		bool use(Actor *owner, Actor *wearer); /*!< Performs the entities functions */
        void save(boost::archive::text_oarchive &ar, const unsigned int version); /*!< Saves the current state. */
        void load(boost::archive::text_iarchive &ar, const unsigned int version); /*!< Loads the saved state. */
};

/*******************************************//*!*************
 * \brief Basic Damage Class
 *
 * This class is a basic implementation of some entity which
 * can deal damage to an actor which holds the destructible
 * trait.
 * **********************************************************/

class LightningBolt : public Pickable {
	public :
		float range;                              /*!< Distance from the source in which actors can be affected.*/
		float damage;                             /*!< Damage the entity deals to destructible traited actor */
		LightningBolt(float range, float damage);
		bool use(Actor *owner, Actor *wearer);    /*!< Performs the entities functions */
        void save(boost::archive::text_oarchive &ar, const unsigned int version); /*!< Saves the current state. */
        void load(boost::archive::text_iarchive &ar, const unsigned int version); /*!< Loads the saved state. */
};

/*!****************************************//*!*************
 * \brief Spell - Fireball
 *
 * A basic spell which does damage to all actors in range.
 * ********************************************************/

class Fireball : public LightningBolt {
	public :
		Fireball(float range, float damage);
		bool use(Actor *owner, Actor *wearer);    /*!< Performs the entities functions */
        void save(boost::archive::text_oarchive &ar, const unsigned int version); /*!< Saves the current state. */
};

/*!***************************************//*!*************
 * \brief Basic Ai-Manipulator Class
 *
 * This class is a basic implementation of some entity which
 * can alter the current AI of an actor. After n turns, the
 * original AI is restored.
 *********************************************************/

class Confuser : public Pickable {
	public :
		int nbTurns;                           /*!< Number of turns the AI will be changed. */
		float range;                           /*!< Distance from the source in which actors can be affected */
		Confuser(int nbTurns, float range);
		bool use(Actor *owner, Actor *wearer); /*!< Performs the entities functions */
        void save(boost::archive::text_oarchive &ar, const unsigned int version); /*!< Saves the current state. */
        void load(boost::archive::text_iarchive &ar, const unsigned int version); /*!< Loads the saved state. */
};

#endif
