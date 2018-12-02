#include "core.h"
#include "Persistent.h"
#include <fstream>
#include <string.h>

void Actor::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    int r,g,b;
    r = col->r;
    g = col->g;
    b = col->b;
    ar & x;
    ar & y;
    ar & ch;
    ar & r;
    ar & g;
    ar & b;
    ar & (std::strlen(name));
    for(unsigned int i = 0;i<std::strlen(name);++i){
        ar & name[i];
    }
    ar & blocks; 
    ar & (attacker != NULL);
    ar & (destructible != NULL);
    ar & (ai != NULL);
    ar & (pickable != NULL);
    ar & (container != NULL);

    if(attacker) attacker->save(ar,version);
    if(destructible) destructible->save(ar,version);
    if(ai) ai->save(ar,version);
    if(pickable) pickable->save(ar,version);
    if(container) container->save(ar,version);
}
void Actor::load(boost::archive::text_iarchive &ar, const unsigned int version) {
    int r,g,b,cc;
    ar & x;
    ar & y;
    ar & ch;
    ar & r;
    ar & g;
    ar & b;
    col = Persistent::assignTCODColor(r,g,b);
    ar & cc;
    char *tmp = new char[cc+1];
    for(unsigned int i = 0;i<cc;++i){
        ar & tmp[i];
    }
    tmp[cc] = '\0';
    name = tmp;    
    ar & blocks;
    bool hasAttacker;
    bool hasDestructible;
    bool hasAi;
    bool hasPickable;
    bool hasContainer;

    ar & hasAttacker;
    ar & hasDestructible;
    ar & hasAi;
    ar & hasPickable;
    ar & hasContainer;

    if(hasAttacker) {
        attacker = new Attacker(0.0f);
        attacker->load(ar,version);
    }
    if(hasDestructible) {
        destructible = Destructible::create(ar);
    }
    if(hasAi) {
        ai = Ai::create(ar);
    }
    if(hasPickable) {
        pickable = Pickable::create(ar);
    }
    if(hasContainer) {
        container = new Container(0);
        container->load(ar,version);
    }
}


Ai *Ai::create(boost::archive::text_iarchive &ar) {
    AiType type;
    ar & type;
    Ai *ai = NULL;
    switch(type) {
        case PLAYER : ai = new PlayerAi(); break;
        case MONSTER : ai = new MonsterAi(); break;
        case CONFUSED_MONSTER : ai = new ConfusedMonsterAi(0,NULL); break;
    }
    ai->load(ar,0);
    return ai;
}


void PlayerAi::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & (int)PLAYER;
}

void PlayerAi::load(boost::archive::text_iarchive &ar, const unsigned int version) {
}

void MonsterAi::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & (int)MONSTER;
    ar & moveCount;
}

void MonsterAi::load(boost::archive::text_iarchive &ar, const unsigned int version) {
    ar & moveCount;
}

void ConfusedMonsterAi::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & (int)CONFUSED_MONSTER;
    ar & nbTurns;
    oldAi->save(ar,version);
}

void ConfusedMonsterAi::load(boost::archive::text_iarchive &ar, const unsigned int version) {
    ar & nbTurns;
    oldAi = Ai::create(ar);
}


void Attacker::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & power;
}

void Attacker::load(boost::archive::text_iarchive &ar, const unsigned int version) {
    ar & power;
}


void Container::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & size;
    ar & inventory.size();
    for(Actor **it = inventory.begin(); it != inventory.end(); it++) {
        (*it)->save(ar,version);
    }
}

void Container::load(boost::archive::text_iarchive &ar, const unsigned int version) {
    int nbActors = 0;
    ar & size;
    ar & nbActors;
    while(nbActors > 0) {
        Actor *actor = new Actor(0,0,0,NULL,&TCODColor::white);
        actor->load(ar,version);
        inventory.push(actor);
        nbActors--;
    }
}

Destructible *Destructible::create(boost::archive::text_iarchive &ar) {
    DestructibleType type;
    ar & type;
    Destructible *destructible = NULL;
    switch(type) {
        case MONSTER : destructible = new MonsterDestructible(0,0,NULL); break;
        case PLAYER : destructible = new PlayerDestructible(0,0,NULL); break;
    }
    destructible->load(ar,0);
    return destructible;
}

void Destructible::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & maxHp;
    ar & hp;
    ar & defense;
    ar & (std::strlen(corpseName));
    for(unsigned int i = 0;i< std::strlen(corpseName);++i){
        ar & corpseName[i];
    }
}

void Destructible::load(boost::archive::text_iarchive &ar, const unsigned int version) {
    int cc;
    ar & maxHp;
    ar & hp;
    ar & defense;
    ar & cc;
    char *tmp = new char[cc+1];
    for(unsigned int i = 0; i < cc; ++i) {
        ar & tmp[i];
    }
    tmp[cc] = '\0';
    corpseName = tmp;
}

void MonsterDestructible::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & (int)MONSTER;
    this->Destructible::save(ar,version);
}

void PlayerDestructible::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & (int)PLAYER;
    this->Destructible::save(ar,version);
}


void Engine::save() {
	if(player->destructible->isDead()) {
		TCODSystem::deleteFile("game.sav");
	}else{
        std::ofstream ofs("game.sav");
        boost::archive::text_oarchive ar(ofs);
        // save the map first
            ar & map->width;
            ar & map->height;
        map->save(ar,0);
        // then the player
        player->save(ar,0);
        // then all the other actors
        ar & (actors.size()-1);
        for(Actor **iterator = actors.begin();iterator != actors.end();iterator++) {
            if(*iterator != player) {
                (*iterator)->save(ar,0);
            }
        }
        // finally the message log
        gui->save(ar,0);
	}
}

void Engine::load() {
    std::ifstream ifs("game.sav");
    if(ifs) {
        boost::archive::text_iarchive ar(ifs);
        // load the map
            int width;
            int height;
            ar & width;
            ar & height;
            map = new Map(width,height);
        map->load(ar,0);
        // then the player
        player = new Actor(0,0,0,NULL,&TCODColor::white);
        player->load(ar,0);
        actors.push(player);
        // then all the other actors
        int nbActors;
        ar & nbActors;
        while(nbActors > 0) {
            Actor *actor = new Actor(0,0,0,NULL,&TCODColor::white);
            actor->load(ar,0);
            actors.push(actor);
            nbActors--;
        } 
        // finally the message log
        gui->load(ar,0);
    }else{
            engine.init();
    }
}


void Gui::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & log.size();
    int r,g,b;
    for(Message **it = log.begin(); it != log.end(); it++) {
        ar & std::strlen((*it)->text);
        for(unsigned int i = 0; i < std::strlen((*it)->text);++i) {
            ar & (*it)->text[i];
        }
        r = (*it)->col->r;
        g = (*it)->col->g;
        b = (*it)->col->b;
        ar & r;
        ar & g;
        ar & b;
    }
}

void Gui::load(boost::archive::text_iarchive &ar, const unsigned int version) {
    int nbMessages;
    int r,g,b,cc;
    const char *text;
    char *tmp;
    const TCODColor *col;
    ar & nbMessages;
    while(nbMessages > 0) {
        ar & cc;
        tmp = new char[cc+1];
        for(unsigned int i = 0; i < cc; ++i) {
            ar & tmp[i];
        }
        tmp[cc] = '\0';
        text = tmp;
        ar & r;
        ar & g;
        ar & b;
        col = Persistent::assignTCODColor(r,g,b);
        message(col,text);
        nbMessages--;
    }
}


void Map::save(boost::archive::text_oarchive &ar, const unsigned int version) { 
    ar & seed;
    for(int i = 0; i < width*height; i++) {
        ar & tiles[i].explored;
    }
}

void Map::load(boost::archive::text_iarchive &ar, const unsigned int version) {
    ar & seed;
    init(false);
    for(int i = 0; i < width*height; i++) {
        ar & tiles[i].explored;
    }
}


const TCODColor *Persistent::assignTCODColor(int r, int g, int b) {
    const TCODColor *col;
    if(r == 0 && g == 128 && b == 0) col = &TCODColor::darkerGreen;
    if(r == 64 && g == 128 && b == 64) col = &TCODColor::desaturatedGreen;
    if(r == 127 && g == 0 && b == 255) col = &TCODColor::violet;
    if(r == 159 && g == 159 && b == 159) col = &TCODColor::lightGrey;
    if(r == 255 && g == 0 && b == 0) col = &TCODColor::red;
    if(r == 255 && g == 255 && b == 115) col = &TCODColor::lightYellow;
    if(r == 255 && g == 255 && b == 255){ col = &TCODColor::white; }
    return col;    
}

Pickable *Pickable::create(boost::archive::text_iarchive &ar) {
    PickableType type;
    int ntype;
    ar & ntype;
    type = (PickableType)ntype;
    Pickable *pickable = NULL;
    switch(type) {
        case HEALER : pickable = new Healer(0); break;
        case LIGHTNING_BOLT : pickable = new LightningBolt(0,0); break;
        case CONFUSER : pickable = new Confuser(0,0); break;
        case FIREBALL : pickable = new Fireball(0,0); break;
    }
    pickable->load(ar,0);
    return pickable;
}

void Healer::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & (int)HEALER;
    ar & amount;
}

void Healer::load(boost::archive::text_iarchive &ar, const unsigned int version) {
    ar & amount;
}

void LightningBolt::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & (int)LIGHTNING_BOLT;
    ar & range;
    ar & damage;
}

void LightningBolt::load(boost::archive::text_iarchive &ar, const unsigned int version) {
    ar & range;
    ar & damage;
}

void Fireball::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & (int)FIREBALL;
    ar & range;
    ar & damage;
}

void Confuser::save(boost::archive::text_oarchive &ar, const unsigned int version) {
    ar & (int)CONFUSER;
    ar & nbTurns;
    ar & range;
}

void Confuser::load(boost::archive::text_iarchive &ar, const unsigned int version) {
    ar & nbTurns;
    ar & range;
}
