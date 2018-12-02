#ifndef DESTRUCTIBLE_H
#define DESTRUCTIBLE_H


/*****************************************//*!**********
 * \brief ROOT Class for Destructibles
 *
 * This class is the ROOT ancesestor for all entities
 * which can be destroyed or take damage.
 * ****************************************************/

class Destructible : public Persistent {
	public :
		float maxHp;            /*!< Maximum health points.*/
		float hp;               /*!< Current health points.*/
		float defense;          /*!< Damage deflected.*/
		const char *corpseName; /*!< The actor's name once dead/destroyed.*/
		
		Destructible(float maxHp, float defense, const char* corpseName);
        void save(boost::archive::text_oarchive &ar, const unsigned int version);
        void load(boost::archive::text_iarchive &ar, const unsigned int version);
        static Destructible *create(boost::archive::text_iarchive &ar);
		inline bool isDead() { return hp <= 0; }     /*!< Determines if an actor is dead.*/
		float takeDamage(Actor *owner, float damage);/*!< Applies damage to owner.*/
		float heal(float amount);                    /*!< Heals for amount.*/
		virtual void die(Actor *owner);              /*!< Kills the actor; turns them into corpse.*/
		virtual ~Destructible();
    protected :

        /*******************//*!********
         * \brief Polymorphism Key
         *
         * Provides a key for save/load
         * to determine what type of
         * descendant to instantiate.
         ******************************/

        enum DestructibleType {
            MONSTER,PLAYER
        };

};

/************************************//*!*************
 * \brief Trait - Destructible Monsters
 *
 * This class serves as a trait which allows actors to
 * take damage, heal, and die.
 * **************************************************/

class MonsterDestructible : public Destructible {
	public : 
		MonsterDestructible(float maxHp, float defense, const char *corpseName);
		void die(Actor *owner);                   /*!< Kills the monster; turns it into a corpse.*/
    protected :
        void save(boost::archive::text_oarchive &ar, const unsigned int version);
};

/*****************************************//*!*******
 * \brief Trait - Destructible Player
 *
 * This class serves as a trait which allow the player
 * to take damage, heal and die.
 * *************************************************/

class PlayerDestructible : public Destructible {
	public :
		PlayerDestructible(float maxHp, float defense, const char * corpseName);
		void die(Actor *owner);                  /*!< Kills the player; turns it into a corpse.*/
    protected :
        void save(boost::archive::text_oarchive &ar, const unsigned int version);
};


#endif
