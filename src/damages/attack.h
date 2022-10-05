#pragma once

#include "damage_type.h"

#include "src/items/weapon.fwd.h"
#include "src/creatures/creature.fwd.h"

class Attack
{
private:
	Creature* _attacker;
	Creature* _target;

	Weapon* _inflictor;

	int _bonus;
public:
	Attack( Creature* attacker, Creature* target, Weapon* inflictor, int bonus );

	bool resolve();
};

