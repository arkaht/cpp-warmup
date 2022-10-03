#include "merchant.h"
#include "weapon.h"

#include <iostream>

Merchant::Merchant( std::string shop_name, std::string description, std::string first_name, std::string last_name, std::string catch_phrase, int money, int health, CharacterRace race, CharacterSpeciality speciality )
	: _shop_name( shop_name ), _description( description ),
	  Character( first_name, last_name, catch_phrase, money, health, race, speciality )
{}

bool Merchant::sell_weapon_to( Weapon* weapon, Character* buyer )
{
	auto iterator = std::find( _inventory.begin(), _inventory.end(), weapon );
	if ( iterator == _inventory.end() ) return false;
	if ( !buyer->buy_weapon_from( weapon, this ) ) return false;

	_inventory.erase( iterator );
	
	std::cout << get_full_name() << " sell '" << weapon->get_name() << "' to " << buyer->get_full_name() << std::endl;
	return true;
}

bool Merchant::buy_weapon_from( Weapon* weapon, Character* seller )
{
	if ( !seller->sell_weapon_to( weapon, this ) ) return false;

	_inventory.push_back( weapon );

	std::cout << get_full_name() << " bought '" << weapon->get_name() << "' from " << seller->get_full_name() << std::endl;
	return true;
}
