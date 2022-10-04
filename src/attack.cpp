#include "attack.h"
#include "creatures/creature.h"
#include "roll.h"

#include <random>
#include <iostream>

Attack::Attack( Creature* attacker, Creature* target, int damage, DamageType damage_type, int bonus )
	: _attacker( attacker ), _target( target ), 
	  _damage( damage ), _damage_type(damage_type),
	  _bonus( bonus )
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
		_target->take_damage( _damage_type, ( _damage + result ) - defense, _attacker );
		
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
