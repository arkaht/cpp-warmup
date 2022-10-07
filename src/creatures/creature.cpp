#include <iostream>

#include "creature.h"
#include "src/items/weapon.h"
#include "src/creatures/characters/character.h"

Creature::Creature( const char* name, const char* description, int health, int defense )
	: _name( name ), _description( description ), _health( health ), 
	  _defense( defense ), _weapon( nullptr )
{}

void Creature::introduce()
{
	std::cout << get_name() << " is a creature (" << _health << " HP, " << _defense << " DEF) '" << _description << "'" << std::endl;
}

void Creature::take_damage( Damage damage, Creature* attacker )
{
	if ( !is_alive() ) return;

	auto this_name = get_name();

	if ( damage.points > 0 )
	{
		_health -= damage.points;
		std::cout << this_name << " lost " << damage.points << "HP." << std::endl;
	}
	else
	{
		std::cout << this_name << " deflected the damages." << std::endl;
	}

	//  killed
	if ( _health <= 0 )
	{
		std::cout << this_name << " died from wounds." << std::endl;
	}
}

void Creature::attack( Creature* target )
{
	if ( !target->is_alive() ) return;
	if ( _weapon == nullptr )
	{
		std::cout << get_name() << " wants to attack " << target->get_name() << " but doesn't have a weapon! Give him one!" << std::endl;
		return;
	}

	_weapon->attack( target );
}

void Creature::heal( int health )
{
	_health += health;
}

void Creature::equip_weapon( Weapon* weapon )
{
	_weapon = weapon;
	weapon->set_owner( this );

	std::cout << _name << " equipped ";
	weapon->print_state();
}

void Creature::drop_weapon()
{
	if ( _weapon == nullptr ) return;

	std::cout << get_name() << " dropped the weapon '" << _weapon->get_name() << "'" << std::endl;

	_weapon->set_owner( nullptr );
	_weapon = nullptr;
}

void Creature::store_item( Item* item )
{
	_inventory.push_back( item );
}