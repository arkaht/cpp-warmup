#pragma once
#include "creature.h"

//  you are useless bro
class Monster : public Creature
{
public:
	Monster( const char* name, const char* description, int health, int defense );
};

