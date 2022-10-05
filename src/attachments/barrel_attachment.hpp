#pragma once

#include <src/items/item.h>
#include "iattachment.hpp"

class BarrelAttachment : public Item, public IAttachment
{
private:
	int _damage_bonus;
public:
	BarrelAttachment( const char* name, const char* description, int weight, int price, float durability, int damage_bonus )
		: Item( name, description, weight, price, durability ), 
		  _damage_bonus( damage_bonus )
	{}

	bool can_attach_to( Weapon* weapon ) override
	{
		return weapon->get_weapon_type() == WeaponType::RIFLE;
	}

	AttachmentType get_attachment_type() override 
	{
		return AttachmentType::BARREL;
	}

	Damage get_damage_bonus_against( Creature* character ) override
	{
		return Damage( DamageType::PIERCING, _damage_bonus );
	}
};