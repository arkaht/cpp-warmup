#pragma once

#include <src/items/item.h>
#include "barrel_attachment.hpp"

class SuppressorAttachment : public BarrelAttachment
{
public:
	SuppressorAttachment( const char* name, const char* description, int weight, int price, float durability, int damage_bonus )
		: BarrelAttachment( name, description, weight, price, durability, damage_bonus )
	{}

	bool can_attach_to( Weapon* weapon ) override
	{
		WeaponType type = weapon->get_weapon_type();
		return type == WeaponType::RIFLE || type == WeaponType::PISTOL;
	}
};