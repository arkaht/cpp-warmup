#include "weapon.h"
#include "character.h"

Weapon::Weapon( std::string name, std::string description, WeaponType type,
				int damage, int weight, int price, float durability_per_use )
	: _name( name ), _description( description ), _type( type ), _damage( damage ),
	  _weight( weight ), _price( price ), _durability_per_use( durability_per_use ),
	  _durability( 1.0f ), _owner( nullptr )
{}

void Weapon::attack( Character* target )
{
	if ( !target->is_alive() ) return;

	target->take_damage( _damage, _owner, this );
}

void Weapon::set_owner( Character* owner )
{
	_owner = owner;
}
