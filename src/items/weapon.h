#pragma once
#include <string>
#include <unordered_map>

#include "item.h"
#include "weapon.fwd.h"

#include <src/creatures/creature.fwd.h>
#include <src/attachments/iattachment.hpp>

typedef std::unordered_map<AttachmentType, IAttachment*> attachments_container;

enum class WeaponType
{
	RIFLE,
	PISTOL,
	MELEE,
};

class Weapon : public Item
{
private:
	WeaponType _type;
	Creature* _owner;

	DamageType _damage_type;
	attachments_container _attachments;

	int _damage;

	float _durability_per_use;
public:
	Weapon( const char* name, const char* description, WeaponType type,
		int damage, DamageType damage_type, int weight, int price,
		float durability, float durability_per_use );

	void print_state() override;

	void attack( Creature* target );
	void set_owner( Creature* owner );

	WeaponType get_weapon_type() { return _type; }
	DamageType get_damage_type() { return _damage_type; }
	int get_damage() { return _damage; }

	bool attach( IAttachment* attachment );
	bool unattach( IAttachment* attachment );
	attachments_container* get_attachments() { return &_attachments; };
};