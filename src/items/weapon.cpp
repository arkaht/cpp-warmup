#include "weapon.h"
#include "src/creatures/characters/character.h"

#include <iostream>

Weapon::Weapon( const char* name, const char* description, WeaponType type,
				int weight, int price, float durability, float durability_per_use )
	: Item( name, description, weight, price, durability ), _type( type ),
	  _durability_per_use( durability_per_use ), _owner( nullptr )
{}

void Weapon::print_state()
{
	std::cout << "'" << _name << "' ( " 
		<< _weight << "kg, "
		<< _price << "$, " << _durability * 100 << "% durability ) : '"
		<< _description << "'" << std::endl;
}

void Weapon::attack( Creature* target )
{
	if ( !target->is_alive() ) return;

	Attack attack( _owner, target, this, rand() % 5 );
	attack.resolve();

	//  decrease durability
	if ( ( _durability -= _durability_per_use ) <= 0.0f )
	{
		std::cout << "'" << _name << "' broke up from continous use." << std::endl;
		_owner->drop_weapon();
	}
}

void Weapon::set_owner( Creature* owner )
{
	_owner = owner;
}


bool Weapon::attach( IAttachment* attachment )
{
	auto itr = _attachments.find( attachment->get_attachment_type() );
	if ( itr != _attachments.end() ) return false;
	if ( !attachment->can_attach_to( this ) ) return false;

	//  register
	_attachments[attachment->get_attachment_type()] = attachment;

	//  notify
	std::cout << "'" << attachment->get_name() << "' has been attached to '" << _name << "'" << std::endl;

	return true;
}

bool Weapon::unattach( IAttachment* attachment )
{
	auto itr = _attachments.find( attachment->get_attachment_type() );
	if ( itr == _attachments.end() ) return false;
	if ( _attachments.at( attachment->get_attachment_type() ) != attachment ) return false;

	//  un-register
	_attachments.erase( itr );

	//  notify
	std::cout << "'" << attachment->get_name() << "' has been un-attached from '" << _name << "'" << std::endl;

	return true;
}