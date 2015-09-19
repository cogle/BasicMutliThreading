#pragma once
#include <string>

struct Container
{
	Container(int line_num, std::string character_name, std::string text)
	{
		_num  = line_num;
		_name = character_name;
		_txt = text;
	}
	int _num;
	std::string _name, _txt;
};