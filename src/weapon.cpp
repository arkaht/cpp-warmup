#include "weapon.h"
#include "character.h"

#include <iostream>

Weapon::Weapon( std::string name, std::string description, WeaponType type,
				int damage, int weight, int price, float durability_per_use )
	: _name( name ), _description( description ), _type( type ), _damage( damage ),
	  _weight( weight ), _price( price ), _durability_per_use( durability_per_use ),
	  _durability( 1.0f ), _owner( nullptr )
{}

void Weapon::print_state()
{
	std::cout << "'" << _name << "' ( "
		<< _damage << " damage, " << _weight << "kg, "
		<< _price << "$, " << _durability * 100 << "% durability ) : '"
		<< _description << "'" << std::endl;
}

void Weapon::attack( Character* target )
{
	if ( !target->is_alive() ) return;

	target->take_damage( _damage, _owner, this );

	//  decrement durability
	if ( ( _durability -= _durability_per_use ) <= 0.0f )
	{
		std::cout << "'" << _name << "' broke up from continous use." << std::endl;
		_owner->drop_weapon();
	}
}

void Weapon::set_owner( Character* owner )
{
	_owner = owner;
}
