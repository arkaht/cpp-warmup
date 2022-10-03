#pragma once

#include "character.h"
#include <vector>

class Merchant : Character
{
private:
	std::string _shop_name;
	std::string _description;

	std::vector<Weapon*> _inventory;
public:
	Merchant( std::string shop_name, std::string description, std::string first_name, std::string last_name, std::string catch_phrase, int money, int health, CharacterRace race, CharacterSpeciality speciality );

	bool buy_weapon_from( Weapon* weapon, Character* seller );
	bool sell_weapon_to( Weapon* weapon, Character* buyer );
};

