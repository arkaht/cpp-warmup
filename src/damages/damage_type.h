#pragma once

enum class DamageType
{
	SLASHING,
	PIERCING,
	BURNING,
};

struct Damage
{
	DamageType type;
	int points;

	Damage( DamageType type, int points ) : type( type ), points( points ) {}
};