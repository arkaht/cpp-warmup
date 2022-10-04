#pragma once

#include "items/weapon.fwd.h"
#include "damage_type.h"

#include "creatures/creature.fwd.h"

class Attack
{
private:
	Creature* _attacker;
	Creature* _target;

	DamageType _damage_type;
	int _damage;
	int _bonus; //  0 to 5
public:
	Attack( Creature* attacker, Creature* target, int damage, DamageType damage_type, int bonus );

	bool resolve();
};

