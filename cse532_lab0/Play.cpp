#include "stdafx.h"
#include "Play.h"

Play::Play(std::string name)
{
	_name = name;
}

Play::~Play()
{

}

Play & Play::operator<<(const Container & c)
{
	std::lock_guard<std::mutex> lock(_m);
	_map.insert(std::pair<int, Container>(c._num, c));
	return *this;
}

void Play::Print(std::ostream & _os)
{
	std::lock_guard<std::mutex> lock(_m);
	std::for_each(_map.begin(), _map.end(), []( std::pair<int, Container> n) {std::cout << n.second._name << "-Line Num " << n.second._num << ": " << n.second._txt << std::endl; });
}

void Play::Print()
{
	std::lock_guard<std::mutex> lock(_m);
	std::string cur_character = "";
	if (_map.size() != 0)
	{
		std::pair<int, Container> first_c = *(_map.begin());
		cur_character = first_c.second._name;
		std::cout << std::endl << cur_character << "." << std::endl;
	}
	std::for_each(_map.begin(), _map.end(), [&cur_character](std::pair<int, Container> n) 
	{
		if (n.second._name.compare(cur_character) != 0)
		{
			cur_character = n.second._name;
			std::cout << std::endl << cur_character << "." << std::endl;
		}
		std::cout << n.second._name << " " << n.second._num << ": " << n.second._txt << std::endl; 
	});
}

void Play::Alert(std::string & bad_file)
{
	std::lock_guard<std::mutex> lock(_m);
	std::cout << "The program was unable to open up the following file: " << bad_file << std::endl;
}