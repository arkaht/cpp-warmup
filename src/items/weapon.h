#pragma once
#include <string>

#include "item.h"
#include "weapon.fwd.h"
#include "../creatures/creature.fwd.h"
#include "../damage_type.h"

enum class WeaponType
{
	PULSE_CHARGE,
	FIREARM,
	MELEE,
};

class Weapon : public Item
{
private:
	std::string _name;
	std::string _description;

	WeaponType _type;
	Creature* _owner;

	DamageType _damage_type;

	int _damage;

	float _durability_per_use;
public:
	Weapon( const char* name, const char* description, WeaponType type,
		int damage, DamageType damage_type, int weight, int price,
		float durability, float durability_per_use );

	void print_state() override;

	void attack( Creature* target );
	void set_owner( Creature* owner );

	int get_damage() { return _damage; }
};