#include "item.h"

#include <iostream>

Item::Item( const char* name, const char* description, int weight, 
			int price, float durability )
	: _name( name ), _description( description ), _weight( weight ),
	  _price( price ), _durability( durability )
{}

void Item::print_state()
{
	std::cout << "'" << _name << "' ( "
		<< _weight << "kg, "
		<< _price << "$, " << _durability * 100 << "% durability ) : '"
		<< _description << "'" << std::endl;
}
