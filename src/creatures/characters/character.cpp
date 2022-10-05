#include "character.h"

#include <iostream>

const char* CharacterRaceStr[]
{
	"Human",
	"Cyborg",
};
const char* CharacterSpecialityStr[]
{
	"Spy",
	"Snyperh",
	"Dealer",
};

Character::Character( const char* name, const char* description, const char* catch_phrase, 
					  int money, int health, int defense, CharacterRace race, CharacterSpeciality speciality )
	: Creature( name, description, health, defense ), _catch_phrase( catch_phrase ),
	  _money( money ), _race( race ), _speciality( speciality )
{}

void Character::introduce()
{
	std::cout << _name << " is a " << CharacterRaceStr[_race] << " specialized as a " << CharacterSpecialityStr[_speciality] << "! '" << _catch_phrase << "'" << std::endl
			  << "\t(" << _health << " HP, " << _defense << " DEF) '" << _description << "'" << std::endl;
}

void Character::loot( Creature* looted )
{
	auto this_name = _name;
	auto looted_name = looted->get_name();

	if ( auto character = dynamic_cast<Character*>( looted ) )
	{
		//  loot money
		int money = character->get_money();
		set_money( _money + money );
		character->set_money( 0 );
		std::cout << this_name << " loot " << money << "$ on " << looted_name << "'s corpse" << std::endl;
	}

	//  loot inventory
	auto inventory = looted->get_inventory();
	for ( auto itr = inventory->begin(); itr < inventory->end(); itr++ )
	{
		Item* item = *itr;
		store_item( item );
		std::cout << this_name << " loot the item '" << item->get_name() << "'" << std::endl;
	}
	inventory->clear();

	//  loot weapon
	Weapon* weapon = looted->get_weapon();
	if ( weapon != nullptr )
	{
		looted->drop_weapon();

		if ( get_weapon()->get_damage() < weapon->get_damage() )
		{
			equip_weapon( weapon );
		}
		else
		{
			store_item( weapon );
		}

		std::cout << this_name << " loot the weapon '" << weapon->get_name() << "' from " << looted_name << std::endl;
	}
}

bool Character::buy_weapon_from( Weapon* weapon, Character* merchant )
{
	int price = weapon->get_buy_price();
	if ( price > _money )
		return false;

	//  pay merchant
	pay( merchant, price );
	//std::cout << get_full_name() << " bought " << weapon->get_name() << " from " << merchant->get_full_name() << " for " << price << "$.";

	//  equip if no active weapon
	if ( _weapon == nullptr )
	{
		equip_weapon( weapon );
	}

	return true;
}

bool Character::sell_weapon_to( Weapon* weapon, Character* merchant )
{
	return false;
}

void Character::pay( Character* target, int amount )
{
	target->set_money( target->get_money() + amount );
	set_money( _money - amount );

	std::cout << _name << " paid " << amount << "$ to " << target->get_name() << "." << std::endl;
}
