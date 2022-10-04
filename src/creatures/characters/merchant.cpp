#include "merchant.h"

#include <iostream>

Merchant::Merchant( const char* shop_name, const char* description, const char* name,
					const char* catch_phrase, int money, int health, int defense, 
					CharacterRace race, CharacterSpeciality speciality )
	: _shop_name( shop_name ), 
	  Character( name, description, catch_phrase, money, health, defense, race, speciality )
{}

bool Merchant::sell_weapon_to( Weapon* weapon, Character* buyer )
{
	auto iterator = std::find( _inventory.begin(), _inventory.end(), weapon );
	if ( iterator == _inventory.end() ) return false;
	if ( !buyer->buy_weapon_from( weapon, this ) ) return false;

	_inventory.erase( iterator );
	
	std::cout << _name << " sell '" << weapon->get_name() << "' to " << buyer->get_name() << std::endl;
	return true;
}

bool Merchant::buy_weapon_from( Weapon* weapon, Character* seller )
{
	if ( !seller->sell_weapon_to( weapon, this ) ) return false;

	_inventory.push_back( weapon );

	std::cout << _name << " bought '" << weapon->get_name() << "' from " << seller->get_name() << std::endl;
	return true;
}

