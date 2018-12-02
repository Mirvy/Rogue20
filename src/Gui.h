#ifndef GUI_H
#define GUI_H

/**************************************************//*!*******************
 * \brief GUI Framework
 *
 * Class used to serve as the framework for user interface.
 * **********************************************************************/

class Gui : public Persistent {
    	public :
                Gui();
                void save(boost::archive::text_oarchive &ar, const unsigned int version); /*!< Stores current state*/
                void load(boost::archive::text_iarchive &ar, const unsigned int version); /*!< Loads saved state.*/
                ~Gui();
                void message(const TCODColor *col, const char *text, ...); /*!< Creates messages on the game log.*/
                void render();                                             /*!< Draws the user interface.*/
            protected :

                /*****************************************//*!*********
                 * \brief Log Message
                 *
                 * Serves as messages to be used in the games activity
                 * log.
                 * ***************************************************/

                struct Message {
                    char *text;         /*!< Message text */
                    const TCODColor *col;      /*! Message color*/
                    Message(const char *text,const TCODColor *col);
                    ~Message();
                };
                TCODConsole *con;                                              /*!< Console used for the activity log*/
                TCODList<Message *> log;                                       /*!< Contains log's messages */
                void renderBar(int x, int y, int width, const char *name,
                        float value, float maxValue, const TCODColor &barColor,
                        const TCODColor &backColor);                           /*!< Draws the player's health bar*/
                void renderMouseLook();                                /*!< Draws the message for player's mouse look */
};


#endif
