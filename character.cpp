#include "character.h"
#include "weapon.h"

#include <iostream>

Character::Character( std::string first_name, std::string last_name, std::string catch_phrase, 
					  int money, int health, CharacterRace race, CharacterSpeciality speciality )
	: _first_name( first_name ), _last_name( last_name ), _catch_phrase( catch_phrase ),
	  _money( money ), _health( health ), _race( race ), _speciality( speciality ),
	  _weapon( nullptr )
{
	introduce();
}

void Character::introduce()
{
	std::cout << get_full_name() << " is a " << _race << " specialized as a " << _speciality << "! '" << _catch_phrase << "'" << std::endl;
}

void Character::equip_weapon( Weapon* weapon )
{
	_weapon = weapon;
	weapon->set_owner( this );

	std::cout << get_full_name() << " equipped '" << weapon->get_name() << "' ( "
		<< weapon->get_damage() << " damage, " << weapon->get_weight() << "kg, "
		<< weapon->get_price() << "$, " << weapon->get_durability() * 100 << "% durability ) : '"
		<< weapon->get_description() << "'" << std::endl;
}

void Character::drop_weapon()
{
	if ( _weapon == nullptr ) return;

	std::cout << get_full_name() << " dropped the weapon '" << _weapon->get_name() << "'" << std::endl;
	
	_weapon->set_owner( nullptr );
	_weapon = nullptr;
}

void Character::attack_character( Character* target )
{
	if ( _weapon == nullptr )
	{
		printf( "%s wants to attack %s but doesn't have a weapon! Give him one!\n", get_full_name().c_str(), target->get_full_name().c_str() );
		return;
	}

	if ( !target->is_alive() ) return;

	_weapon->attack( target );
}

void Character::take_damage( int damages, Character* attacker, Weapon* used_weapon )
{
	if ( !is_alive() ) return;

	auto this_name = get_full_name();
	auto attacker_name = attacker->get_full_name();

	_health -= damages;
	std::cout << attacker_name << " dealt " << damages << " damages to " << this_name << " using '" << used_weapon->get_name() << "'" << std::endl;

	if ( _health <= 0 )
	{
		std::cout << this_name << " was killed by " << attacker_name << std::endl;

		drop_weapon();
		attacker->loot_character( this );
	}
}

void Character::loot_character( Character* looted )
{
	auto this_name = get_full_name();
	auto looted_name = looted->get_full_name();

	//  loot money
	int money = looted->get_money();
	set_money( _money + money );
	looted->set_money( 0 );
	std::cout << this_name << " loot " << money << "$ on " << looted_name << "'s corpse" << std::endl;

	//  loot weapon
	Weapon* weapon = looted->get_weapon();
	if ( weapon != nullptr && _weapon->get_damage() > weapon->get_damage() )
	{
		equip_weapon( weapon );
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

	equip_weapon( weapon );

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

	std::cout << get_full_name() << " paid " << amount << "$ to " << target->get_full_name() << ".";
}
