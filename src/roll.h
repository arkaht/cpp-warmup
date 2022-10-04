#pragma once
#include <iostream>

int roll( int count, int n )
{
	int result = 0;
	
	std::string text = "(";
	for ( int i = 0; i < count; i++ )
	{
		int value = rand() % n;
		text += std::to_string( value );
		if ( i != count - 1 )
		{
			text += ", ";
		}
		result += value;
	}
	text += ")";

	std::cout << "rolled " << result << text;
	return result;
}