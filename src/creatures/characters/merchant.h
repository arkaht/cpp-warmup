#pragma once
#include <vector>

#include "character.h"

class Merchant : public Character
{
private:
	std::string _shop_name;
	std::string _description;
public:
	Merchant( const char* shop_name, const char* description, const char* name, const char* catch_phrase, int money, int health, int defense, CharacterRace race, CharacterSpeciality speciality );

	bool buy_weapon_from( Weapon* weapon, Character* seller );
	bool sell_weapon_to( Weapon* weapon, Character* buyer );
};

