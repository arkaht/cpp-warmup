#include "attack.h"

#include "src/creatures/creature.h"
#include "src/roll.h"

#include <random>
#include <iostream>

Attack::Attack( Creature* attacker, Creature* target, Weapon* inflictor, int bonus )
	: _attacker( attacker ), _target( target ), 
	  _inflictor( inflictor ), _bonus( bonus )
{}

bool Attack::resolve()
{
	int defense = _target->get_defense();

	std::cout << _attacker->get_name() << " ";

	//  roll result
	int result = roll( 3, 6 ) + 2 + _bonus;

	std::cout << ", resulting in " << result << " attack points (+" << _bonus
			  << " bonus) against " << defense << " DEF" << std::endl;

	//  perform attack
	if ( result >= defense )
	{
		std::cout << _attacker->get_name() << " attacked " << _target->get_name() << " using '" << _attacker->get_weapon()->get_name() << "'" << std::endl;
		
		//  setup
		Damage applied_damage( DamageType::NONE, 0 );

		//  get base damage
		damages_container* damages = _inflictor->get_damages();
		for ( auto itr = damages->begin(); itr < damages->end(); itr++ )
		{
			handle_damage( applied_damage, *itr, _inflictor->get_name() );
		}

		//  sub defense
		applied_damage.points -= defense;
		std::cout << "- " << _target->get_name() << ": " << -defense << " DEF" << std::endl;

		//  get attachments damage bonuses
		auto attachments = _inflictor->get_attachments();
		auto itr = attachments->begin();
		while ( itr != attachments->end() )
		{
			IAttachment* attachment = itr->second;

			handle_damage( applied_damage, attachment->get_damage_bonus_against( _target ), attachment->get_name() );

			itr++;
		}

		_target->take_damage( applied_damage, _attacker );
		
		//  loot target
		if ( _attacker->can_loot() )
		{
			_attacker->loot( _target );
		}

		return true;
	}

	std::cout << _attacker->get_name() << " miss " << _target->get_name() << "!" << std::endl;
	return false;
}

void Attack::handle_damage( Damage& damage, Damage new_damage, const char* name )
{
	const char* damage_name = DamageType::get_name( new_damage.type );
	
	//  prevent immunity damage
	if ( _target->get_damages_immunity() & new_damage.type )
	{
		std::cout << "- " << name << ": immunity! " << new_damage.points << " " << damage_name << " DMG (x0)" << std::endl;
		return;
	}

	//  critical damage
	int damages = 0;
	if ( _target->get_damages_critical() & new_damage.type )
	{
		damages = new_damage.points << 1;
		std::cout << "- " << name << ": critical! " << new_damage.points << " " << damage_name << " DMG (x2)" << std::endl;
	}
	//  normal damage
	else
	{
		damages = new_damage.points;
		std::cout << "- " << name << ": " << damages << " " << damage_name << " DMG " << std::endl;
	}

	damage.points += damages;
	damage.type |= new_damage.type;
}