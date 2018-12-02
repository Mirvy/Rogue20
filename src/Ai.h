#ifndef AI_H
#define AI_H

/***************************************//*!***********
 * \brief ROOT AI Class
 *
 * This class serves as the root class for all AI.
 * ***************************************************/

class Ai : public Persistent {
	public :
		virtual void save(boost::archive::text_oarchive &ar, const unsigned int version); /*!< Implemented by descendants to save state. */
        virtual void load(boost::archive::text_iarchive &ar, const unsigned int version); /*!< Implemented by descendants to load states. */
        static Ai *create(boost::archive::text_iarchive &ar);      /*!< Facilitates polymorphism when loading game states.*/
        virtual void update(Actor *owner) = 0;
		virtual ~Ai() {} 
    protected :

        /****************************//*!*********
         * \brief Key for Polymorphism
         *
         * A key used in the choice of which 
         * descendant will be instantiated.
         ****************************************/

        enum AiType {
            MONSTER,CONFUSED_MONSTER,PLAYER
        };

};

/**************************************//*!***********
 * \brief Player AI
 *
 * This AI class is used to control the player actor.
 * **************************************************/

class PlayerAi : public Ai {
	public :
		virtual void save(boost::archive::text_oarchive &ar, const unsigned int version); /*!< Implemented by descendants to save state. */
        virtual void load(boost::archive::text_iarchive &ar, const unsigned int version); /*!< Implemented by descendants to load states. */
		void update(Actor *owner);            /*!< Takes user inputs and updates actor position/state*/
	protected :
		bool moveOrAttack(Actor *owner, int targetx, int targety); /*!< Moves of attacks based on whats present.*/
		void handleActionKey(Actor *owner, int ascii);             /*!< Handles specific player key inputs.*/
		Actor *choseFromInventory(Actor *owner);                   /*!< Facilitates interaction with inventory.*/
        
};

/*************************************//*!************
 * \brief Monster AI
 *
 * This AI class is used to control monster actors.
 * **************************************************/

class MonsterAi : public Ai {
	public :
        MonsterAi();
		virtual void save(boost::archive::text_oarchive &ar, const unsigned int version); /*!< Implemented by descendants to save state. */
        virtual void load(boost::archive::text_iarchive &ar, const unsigned int version); /*!< Implemented by descendants to load states. */
		void update(Actor *owner);                            /*!< Processes monster's ai. */
	protected :
		int moveCount;                                        /*!< Controls how long monsters move once out of sight.*/
		void moveOrAttack(Actor *owner, int targetx, int targety); /*!<Moves or attacks based on whats present.*/
        
};

/***************************************//*!**********
 * \brief ConfusedMonster AI
 *
 * This AI class is used to control monsters when they
 * lost control of themselves.
 * **************************************************/

class ConfusedMonsterAi : public Ai {
	public :
		ConfusedMonsterAi(int nbTurns, Ai *oldAi);
		virtual void save(boost::archive::text_oarchive &ar, const unsigned int version); /*!< Implemented by descendants to save state. */
        virtual void load(boost::archive::text_iarchive &ar, const unsigned int version); /*!< Implemented by descendants to load states. */
		void update(Actor *owner);                            /*!< Process monster's modified ai.*/
	protected :
		int nbTurns;                      /*!< Number of turns the ai persists.*/
		Ai *oldAi;                        /*!< Stores the monsters default ai.*/
        
};



#endif
