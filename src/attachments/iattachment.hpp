#pragma once

#include <src/damages/damage_type.h>
#include <src/items/weapon.fwd.h>
#include <src/creatures/creature.h>

enum AttachmentType
{
	BARREL,
	SCOPE,
	CROSS,
};

class IAttachment
{
public:
	virtual ~IAttachment() {};

	virtual bool can_attach_to( Weapon* weapon ) = 0;

	virtual AttachmentType get_attachment_type() = 0;
	virtual Damage get_damage_bonus_against( Creature* character ) = 0;
};