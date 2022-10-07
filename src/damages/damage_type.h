#pragma once

#include <stdint.h>

namespace DamageType
{
	typedef uint8_t Flag;
	//using Flag = std::uint8_t;

	enum Flags
	{
		NONE = 0,
		SOUL = 1 << 0,
		CARCASS = 1 << 1,
		VIRAL = 1 << 2,
		FIRE = 1 << 3,
		WATER = 1 << 4,
		ELECTRICITY = 1 << 5,
		SLICING = 1 << 6,
		BLOOD = 1 << 7,
	};

	static const char* get_name( Flag type )
	{
		switch ( type )
		{
			case SOUL:
				return "SOUL";
			case CARCASS:
				return "CARCASS";
			case VIRAL:
				return "VIRAL";
			case FIRE:
				return "FIRE";
			case WATER:
				return "WATER";
			case ELECTRICITY:
				return "ELECTRICITY";
			case SLICING:
				return "SLICING";
			case BLOOD:
				return "BLOOD";
		}

		return "NONE";
	}

	namespace Immunity
	{
		const Flag HUMAN = NONE;
		const Flag CYBORG = BLOOD | VIRAL | SOUL;
	}

	namespace Critical
	{
		const Flag HUMAN = SOUL | BLOOD;
		const Flag CYBORG = ELECTRICITY | WATER;
	}

	//const Flag FIREARM = SLICING | CARCASS;
}

struct Damage
{
	DamageType::Flag type;
	int points;

	Damage( DamageType::Flag type, int points ) : type( type ), points( points ) {}
};