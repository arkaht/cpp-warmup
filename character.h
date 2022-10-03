#pragma once
#include <string>

#include "character.fwd.h"
#include "weapon.fwd.h"

enum CharacterRace
{
	Human,
	Cyborg,
};

enum CharacterSpeciality
{
	Spy,
	Snyperh,
	Dealer,
};

class Character
{
private:
	std::string _first_name;
	std::string _last_name;
	std::string _catch_phrase;

	int _money;
	int _health;

	Weapon* _weapon;

	CharacterRace _race;
	CharacterSpeciality _speciality;

public:
	Character( std::string first_name, std::string last_name, std::string catch_phrase, int money, int health, CharacterRace race, CharacterSpeciality speciality );

	void introduce();

	void equip_weapon( Weapon* weapon );
	void drop_weapon();
	Weapon* get_weapon() { return _weapon; }

	void attack_character( Character* target );
	void take_damage( int damages, Character* attacker, Weapon* used_weapon );
	void loot_character( Character* target );

	virtual bool buy_weapon_from( Weapon* weapon, Character* merchant );
	virtual bool sell_weapon_to( Weapon* weapon, Character* merchant );

	void set_money( int money ) { _money = money; }
	int get_money() { return _money; }
	void pay( Character* target, int amount );

	bool is_alive() { return _health > 0; }

	std::string get_first_name() { return _first_name; };
	std::string get_last_name() { return _last_name; };
	std::string get_full_name() { return _first_name + " " + _last_name; }
};