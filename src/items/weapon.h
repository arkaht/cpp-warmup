#pragma once
#include <string>
#include <unordered_map>

#include "item.h"
#include "weapon.fwd.h"

#include <src/creatures/creature.fwd.h>
#include <src/attachments/iattachment.hpp>

typedef std::vector<Damage> damages_container;
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

	damages_container _damages;
	attachments_container _attachments;

	float _durability_per_use;
public:
	Weapon( const char* name, const char* description, WeaponType type,
		int weight, int price, float durability, float durability_per_use );

	void print_state() override;

	void attack( Creature* target );
	void set_owner( Creature* owner );

	WeaponType get_weapon_type() { return _type; }

	void add_damages( Damage damage ) { _damages.push_back( damage ); }
	template <class... Args>
	void add_damages( Args... args )
	{
		damages_container new_damages = { args... };
		for ( auto itr = new_damages.begin(); itr < new_damages.end(); itr++ )
		{
			_damages.push_back( *itr );
		}
	}
	damages_container* get_damages() { return &_damages; }

	bool attach( IAttachment* attachment );
	bool unattach( IAttachment* attachment );
	attachments_container* get_attachments() { return &_attachments; };
};