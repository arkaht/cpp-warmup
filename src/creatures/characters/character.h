#pragma once
#include <string>

#include "character.fwd.h"

#include "src/creatures/creature.h"
#include "src/items/weapon.h"

enum CharacterRace
{
	HUMAN,
	CYBORG,
};

enum CharacterSpeciality
{
	SPY,
	SNYPERH,
	DEALER,
};

class Character : public Creature
{
protected:
	const char* _catch_phrase;

	int _money;

	CharacterRace _race;
	CharacterSpeciality _speciality;
public:
	Character( const char* name, const char* description, const char* catch_phrase, int money, int health, int defense, CharacterRace race, CharacterSpeciality speciality );

	void introduce() override;

	bool can_loot() override { return true; }
	void loot( Creature* looted ) override;

	virtual bool buy_weapon_from( Weapon* weapon, Character* merchant );
	virtual bool sell_weapon_to( Weapon* weapon, Character* merchant );

	void set_money( int money ) { _money = money; }
	int get_money() { return _money; }
	void pay( Character* target, int amount );
};