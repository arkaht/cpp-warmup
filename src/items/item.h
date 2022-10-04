#pragma once

class Item
{
protected:
	const char* _name;
	const char* _description;

	int _weight;
	int _price;

	float _durability;  //  0.0f to 1.0f
public:
	Item( const char* name, const char* description, int weight, int price, int durability );

	virtual void print_state();

	const char* get_name() { return _name; }
	const char* get_description() { return _description; }
	int get_weight() { return _weight; }
	float get_durability() { return _durability; }
	int get_price() { return _price; }
	int get_buy_price() { return (int) ( _price * ( 1.0f + _durability ) ); };
	int get_sell_price() { return (int) ( _price * _durability ); };
};

