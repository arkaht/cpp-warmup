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
		
		//  get base damage
		int damage = ( ( _inflictor->get_damage() + result ) - defense );
		
		//  get attachments damage bonuses
		auto attachments = _inflictor->get_attachments();
		auto itr = attachments->begin();
		while ( itr != attachments->end() )
		{
			IAttachment* attachment = itr->second;

			Damage info = attachment->get_damage_bonus_against( _target );
			damage += info.points;

			itr++;
		}

		_target->take_damage( _inflictor->get_damage_type(), damage, _attacker);
		
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
