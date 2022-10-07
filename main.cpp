#include <iostream>
#include <functional>

#include "src/creatures/monster.h"
#include "src/creatures/characters/merchant.h"
#include "src/items/weapon.h"
#include "src/attachments/suppressor_attachment.hpp"

using lambda = std::function<void()>;

struct UserAction
{
	const char* name;
	lambda callback;
	
	UserAction( const char* name, lambda callback ) 
		: name( name ), callback( callback ) {};
};

void user_action_from( UserAction* actions, size_t len )
{
	//  print actions
	for ( int i = 0; i < len; i++ )
	{
		UserAction action = actions[i];
		std::cout << i + 1 << " - " << action.name << std::endl;
	}

	//  read action input
	int action_id;
	do
	{
		std::cin >> action_id;
		action_id--;
	}
	while ( action_id < 0 || action_id >= len );

	std::cout << std::endl;

	//  invoke callback
	actions[action_id].callback();
}

int main()
{
	std::cout << "Welcome to the Arena!\n";

	//  init random
	srand( time( NULL ) );
	
	//  characters def
	Monster alien(
		"Alien",
		"Veniminous & dangerous creature",
		250,
		8
	);
	alien.set_damages_immunity( DamageType::VIRAL | DamageType::WATER | DamageType::CARCASS );
	alien.set_damages_critical( DamageType::BLOOD | DamageType::FIRE );
	alien.introduce();

	Character snyperh(
		"Lyhn the Snyperh",
		"Hidden in a Ghillie suit.",
		"Have you seen my shot? Of course not. You died before.",
		10000,
		100,
		4,
		CharacterRace::HUMAN,
		CharacterSpeciality::SNYPERH
	);
	snyperh.introduce();

	Character assassin(
		"Shhht",
		"Chhht",
		"The most darkness crimes happen in the most absolute silence.",
		99,
		100,
		3,
		CharacterRace::HUMAN,
		CharacterSpeciality::SPY
	);
	assassin.introduce();

	Merchant merchant(
		"Atomic Kality",
		"A weapon dealer specialized in heavy weaponary, attracting mercenaries and hitmen. The contact is made remotely, hopefully, their connection is encrypted allowing secret transactions without a trace log.",
		"DX-A.K. Dealer",
		"What. Is. Your. Order?",
		100000,
		100,
		10,
		CharacterRace::CYBORG,
		CharacterSpeciality::DEALER
	);
	merchant.introduce();

	std::cout << std::endl;

	//  item def
	Weapon elyte_x1(
		"Elyte-X1",
		"One bullet and your targets will fall on the ground. One shot and your targets are already out of this world.",
		WeaponType::RIFLE,
		27,
		10000,
		1.0f,
		.025f
	);
	elyte_x1.add_damages(
		Damage( DamageType::SLICING, 400 ),
		Damage( DamageType::FIRE, 25 ),
		Damage( DamageType::CARCASS, 50 )
	);

	Weapon the_blood_theft(
		"The Blood Theft",
		"All your victims blood will charge this dague's energy, making it more than deadly. Its power can even hurt the soul of your victims.",
		WeaponType::MELEE,
		1,
		10000,
		1.0f,
		.025f
	);
	the_blood_theft.add_damages(
		Damage( DamageType::SLICING, 50 ),
		Damage( DamageType::BLOOD, 20 ),
		Damage( DamageType::SOUL, 10 )
	);

	Weapon deagle(
		"Deagle",
		"Boum.",
		WeaponType::PISTOL,
		3,
		5000,
		1.0f,
		.15f
	);
	deagle.add_damages(
		Damage( DamageType::SLICING, 50 ),
		Damage( DamageType::CARCASS, 25 )
	);

	Weapon poisonous_dart(
		"Poisonous Dart",
		"Slash your enemies to deal them poison.",
		WeaponType::MELEE,
		3,
		5000,
		1.0f,
		.15f
	);
	poisonous_dart.add_damages(
		Damage( DamageType::SLICING, 50 ),
		Damage( DamageType::VIRAL, 20 )
	);

	Item tokiwoka(
		"Toki-Woka",
		"Used for communicating with others Toki-Wokas",
		1,
		100,
		1.0f
	);

	SuppressorAttachment suppressor(
		"Suppressor",
		"Minimize the sound the gun emits but decreases its damage too",
		1,
		99,
		1.0f,
		-15
	);
	poisonous_dart.attach( &suppressor );  //  successfully fails
	elyte_x1.attach( &suppressor );
	for ( auto pair : *elyte_x1.get_attachments() )
	{
		std::cout << pair.first << " - " << pair.second << std::endl;
	}
	//elyte_x1.unattach( &suppressor );

	//  setup characters
	alien.equip_weapon( &poisonous_dart );
	alien.store_item( &tokiwoka );
	merchant.store_item( &deagle );
	snyperh.equip_weapon( &elyte_x1 );
	assassin.equip_weapon( &the_blood_theft );
	std::cout << std::endl;
	
	//tokiwoka.print_state();

	//std::cout << "sell: " << elyte_x1.get_sell_price() << "$ buy: " << elyte_x1.get_buy_price() << "$" << std::endl;
	alien.attack( &assassin );
	snyperh.attack( &alien );
	//std::cout << "sell: " << elyte_x1.get_sell_price() << "$ buy: " << elyte_x1.get_buy_price() << "$" << std::endl;
	std::cout << std::endl;

	UserAction actions[] {
		UserAction( "Walk", 
			[&]
			{
				std::cout << "wok" << std::endl;
			} 
		),
		UserAction( "Call Weapon Dealer", 
			[&]
			{
				merchant.introduce();
				std::cout << "I can sell you these:" << std::endl;

				int i = 0;
				auto inventory = merchant.get_inventory();
				for ( auto itr = inventory->begin(); itr < inventory->end(); itr++ )
				{
					Item* item = *itr;
					std::cout << ++i << " - ";
					item->print_state();
				}
			}
		)
	};

	do
	{
		std::cout << "What do you do?" << std::endl;
		user_action_from( actions, 2 );

		std::cout << std::endl;
	}
	while ( true );
	
	//merchant.store_weapon( &deagle );
	//merchant.sell_weapon_to( &deagle, &snyperh );
}