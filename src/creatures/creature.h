#pragma once
#include <string>
#include <vector>

#include "creature.fwd.h"

#include "src/damages/attack.h"
#include "src/items/weapon.h"

class Creature
{
protected:
	const char* _name;
	const char* _description;
	
	std::vector<Attack> _attacks;  //  why?
	Weapon* _weapon;

	DamageType::Flag _damages_immunity;
	DamageType::Flag _damages_critical;

	std::vector<Item*> _inventory;

	int _health;
	int _defense = 1;  //  1 to 20
public:
	Creature( const char* name, const char* description, int health, int defense );
	virtual ~Creature() = default;

	virtual void introduce();

	void take_damage( Damage damage, Creature* attacker );
	void attack( Creature* target );
	void heal( int health );

	void set_damages_immunity( DamageType::Flag immunity ) { _damages_immunity = immunity; }
	void set_damages_critical( DamageType::Flag critical ) { _damages_critical = critical; }

	DamageType::Flag get_damages_immunity() { return _damages_immunity; }
	DamageType::Flag get_damages_critical() { return _damages_critical; }

	void equip_weapon( Weapon* weapon );
	void drop_weapon();

	void store_item( Item* item );
	std::vector<Item*>* get_inventory() { return &_inventory; }

	virtual bool can_loot() { return false; }
	virtual void loot( Creature* looted ) {}

	bool is_alive() { return _health > 0; }

	int get_defense() { return _defense; }
	Weapon* get_weapon() { return _weapon; }

	const char* get_name() { return _name; }
	const char* get_description() { return _name; }
};

