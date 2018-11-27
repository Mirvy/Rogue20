#ifndef ENGINE_H
#define ENGINE_H

/******************************************//*!**************
 * \brief Core Game Engine
 *
 * Class controls the games core operations and flow.
 * *********************************************************/

class Engine {
	public :

		/************************************//*!*****
		 * \brief Game States
		 *
		 * Used to set the game into different states.
		 * ******************************************/

		enum GameStatus {
			STARTUP,
			IDLE,
			NEW_TURN,
			VICTORY,
			DEFEAT
		} gameStatus;	          /*!< Games current status.*/
	
		int fovRadius;            /*!< Radius of player's FOV.*/
		int screenWidth;          /*!< Game screen width.*/
		int screenHeight;         /*!< Game screen height.*/
		Actor *player;            /*!< Actor representing the player.*/
		Map *map;                 /*!< Game's current map.*/
		Gui *gui;                 /*!< Game's current user interface.*/
		TCODList<Actor *> actors; /*!< Game's current actors.*/
		TCOD_key_t lastKey;       /*!< Last keyboard character entered.*/
		TCOD_mouse_t mouse;       /*!< Last mouse information stored(location,button).*/

		Engine(int screenWidth, int screenHeight);
		void init(); 						  /*!< Initialiases the game engine.*/
		void load(); 						  /*!< Loads the stored game state.*/
		void save(); 						  /*!< Saves the current game state.*/
		void update();                                            /*!< Calls update() for map and actors.*/
		void render();                                            /*!< Calls render() for map gui and actors.*/
		void sendToBack(Actor *actor);                            /*!< Moves actors to the front so they are buried.*/
		bool pickATile(int *x, int *y, float maxRange = 0.0f);    /*!< Allows the user to select an x,y coords.*/ 
		Actor *getClosestMonster(int x, int y, float range) const;/*!< Gets the closest monster to x,y within range.*/
		Actor *getActor(int x, int y) const;                      /*!< Gets the actor at x,y coords.*/
		~Engine();
};

extern Engine engine;
#endif
