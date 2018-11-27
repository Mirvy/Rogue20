#ifndef MAP_H
#define MAP_H

/******************************************//*!************
 * \brief Represents basic world tiles.
 *
 * Used to represent the basic properties which will be
 * applied to each x,y coordinate on the map.
 * *******************************************************/

struct Tile{
	bool explored;   /*!< Player has already seen the tile? */
	Tile() : explored(false) {}
};

/*****************************************//*!************
 * \brief Tactical Map Implementation
 *
 * This class allows for the generation of the map, as well
 * as the required calls to TCOD console to draw the map.
 * *******************************************************/

class Map : public Persistent {
	public :
		int width;      /*!< Width of current map. */
		int height;     /*!< Height of current map. */
		
		Map(int width, int height);
        void save(TCODZip &zip);            /*!< Saves the current state.*/
        void load(TCODZip &zip);            /*!< Loads a saved state.*/
		void init(bool withActors);         /*!< Initialises the map state*/
		void render() const;                /*!< Renders the current map to main windows.*/
		bool isInFov(int x, int y) const;   /*!< Determines if the x,y coords are within player's FOV.*/
		bool isExplored(int x, int y)const; /*!< Determines if the x,y coords has been revealed.*/
		bool isWall (int x, int y) const;   /*!< Determines if the x,y coords is a wall.*/
		bool canWalk(int x, int y) const;   /*!< Determines if the x,y coords can be traversed by an actor.*/
		void computeFov();                  /*!< Uses TCODMap to generate players LOS */
		void addMonster(int x, int y);      /*!< Randomly generates and places a MONSTER actor.*/
		void addItem(int x, int y);         /*!< Randomly gnerates and places an ITEM actor. */
		~Map();
	protected:
		Tile *tiles;                               /*!< The colletion of tiles used to represent the game map. */
		//void setWall(int x, int y);              // Sets tile at x,y coords to a wall.*/
		TCODMap *map;                              /*!< Used to store the map used to represent the player's LOS.*/
		long seed;                                 /*!< Random Seed for TCODRandom object */
		TCODRandom *rng;			   /*!< Used for random map generation */
		void dig(int x1, int y1, int x2, int y2);                                     /*!< Carves out a room from a filled default map*/
		void createRoom(bool first, int x1, int y1, int x2, int y2, bool withActors); /*!< Used to generate random dungeon.*/
		friend class BspListener;
};
#endif
