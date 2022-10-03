#pragma once
#include <string>

#include "weapon.fwd.h"
#include "character.fwd.h"

enum WeaponType {
	PulseCharge,
	Firearm,
	Melee,
};

class Weapon {
private:
	std::string _name;
	std::string _description;

	WeaponType _type;
	Character* _owner;

	int _weight;
	int _damage;
	int _price;

	float _durability;  //  0.0f to 1.0f
	float _durability_per_use;
public:
	Weapon( std::string name, std::string description, WeaponType type, int damage, int weight, int price, float durability_per_use );

	void print_state();

	void attack( Character* target );
	void set_owner( Character* owner );

	std::string get_name() { return _name; }
	std::string get_description() { return _description; }
	int get_damage() { return _damage; }
	int get_weight() { return _weight; }
	float get_durability() { return _durability; }

	int get_price() { return _price; }
	int get_buy_price() { return (int) ( _price * ( 1.0f + _durability ) ); };
	int get_sell_price() { return (int) ( _price * _durability ); };
};