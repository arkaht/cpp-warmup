#include <iostream>

#include "character.h"
#include "merchant.h"
#include "weapon.h"

int main()
{
	std::cout << "Welcome to the Arena!\n";
	
	#pragma region CharacterDef
		Character snyperh(
			std::string( "Lyhn" ),
			std::string( "the Snyperh" ),
			std::string( "Have you seen my shot? Of course not. You died before." ),
			1000,
			100,
			CharacterRace::Human,
			CharacterSpeciality::Snyperh
		);

		Character assassin(
			std::string( "Shhht" ),
			std::string( "Chhht"),
			std::string( "The most darkness crimes happen in the most absolute silence." ),
			99,
			100,
			CharacterRace::Human,
			CharacterSpeciality::Spy
		);

		Merchant merchant(
			std::string( "Atomic Kality" ),
			std::string( "A weapon dealer specialized in heavy weaponary, attracting mercenaries and hitmen. The contact is made remotely, hopefully, their connection is encrypted allowing secret transactions without a trace log." ),
			std::string( "DX" ),
			std::string( "A.K. Dealer" ),
			std::string( "What. Is. Your. Order?" ),
			100000,
			100,
			CharacterRace::Cyborg,
			CharacterSpeciality::Dealer
		);

		std::cout << std::endl;
	#pragma endregion

	#pragma region WeaponDef
		Weapon elytra_x1(
			std::string( "Elytra-X1" ),
			std::string( "One bullet and your targets will fall on the ground. One shot and your targets are already out of this world." ),
			WeaponType::PulseCharge,
			500,
			27,
			10000,
			.025f
		);

		Weapon the_blood_theft(
			std::string( "The Blood Theft" ),
			std::string( "All your victims blood will charge this dague's energy, making it more than deadly. Its power can even hurt the soul of your victims." ),
			WeaponType::Melee,
			50,
			3,
			10000,
			.025f
		);
	#pragma endregion

	#pragma region SetupCharacters
		snyperh.equip_weapon( &elytra_x1 );
		assassin.equip_weapon( &the_blood_theft );
		std::cout << std::endl;
	#pragma endregion
	
	snyperh.attack_character( &assassin );
}
