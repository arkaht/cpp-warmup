#include "weapon.h"
#include "../creatures/characters/character.h"

#include <iostream>

Weapon::Weapon( const char* name, const char* description, WeaponType type,
				int damage, DamageType damage_type, int weight, int price, 
				float durability, float durability_per_use )
	: Item( name, description, weight, price, durability ), _type(type),
	  _damage( damage ), _damage_type( damage_type ), 
	  _durability_per_use( durability_per_use ), _owner( nullptr )
{}

void Weapon::print_state()
{
	std::cout << "'" << _name << "' ( "
		<< _damage << " damage, " << _weight << "kg, "
		<< _price << "$, " << _durability * 100 << "% durability ) : '"
		<< _description << "'" << std::endl;
}

void Weapon::attack( Creature* target )
{
	if ( !target->is_alive() ) return;

	Attack attack( _owner, target, _damage, _damage_type, rand() % 5 );
	attack.resolve();

	//  decrement durability
	if ( ( _durability -= _durability_per_use ) <= 0.0f )
	{
		std::cout << "'" << _name << "' broke up from continous use." << std::endl;
		_owner->drop_weapon();
	}
}

void Weapon::set_owner( Creature* owner )
{
	_owner = owner;
}
