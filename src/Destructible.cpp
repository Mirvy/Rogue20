#include <stdio.h>
#include "core.h"

Destructible::Destructible(float maxHp, float defense, const char *corpseName) :
	maxHp(maxHp), hp(maxHp), defense(defense), corpseName(corpseName) {
            //this->corpseName = strdup(corpseName);
}

Destructible::~Destructible() {
    //free((char*)corpseName);
}

float Destructible::takeDamage(Actor *owner, float damage) {
	damage -= defense;
	if(damage > 0) {
		hp -= damage;
		if(hp <= 0) {
			die(owner);
		}
	}else{
		damage -= 0;
	}
	return damage;
}

float Destructible::heal(float amount) {
	hp += amount;
	if(hp > maxHp) {
		amount -= hp - maxHp;
		hp = maxHp;
	}
	return amount;
}

void Destructible::die(Actor *owner) {
	// transform the actor into a corpse!
	owner->ch = '%';
	owner->col = &TCODColor::darkRed;
	owner->name = corpseName;
	owner->blocks = false;
	// make sure corpses are drawn before living actors
	engine.sendToBack(owner);
}

MonsterDestructible::MonsterDestructible(float maxHp, float defense, const char *corpseName) :
	Destructible(maxHp,defense,corpseName) {
}

void MonsterDestructible::die(Actor *owner) {
	// transform it into a nasty corpse! it doesn't block, can't be
	// attacked and desn't move
	engine.gui->message(&TCODColor::lightGrey,"%s is dead\n",owner->name);
	Destructible::die(owner);
}

PlayerDestructible::PlayerDestructible(float maxHp, float defense, const char *corpseName) :
	Destructible(maxHp,defense,corpseName) {
}

void PlayerDestructible::die(Actor *owner) {
	engine.gui->message(&TCODColor::red,"You died!\n");
	Destructible::die(owner);
	engine.gameStatus = Engine::DEFEAT;
}
