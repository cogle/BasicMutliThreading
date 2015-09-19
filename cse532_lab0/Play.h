#pragma once

#include <map>
#include <mutex>
#include <string>
#include <utility>
#include <iostream>
#include <algorithm>
#include "Container.h"


class Play
{
public:
	Play(std::string play_name);
	~Play();
	Play & operator<<(const Container & c);
	void Alert(std::string & bad_file);
	void Print(std::ostream & _os);
	void Print();

private:
	std::mutex _m;
	std::string _name;
	std::map<int, Container> _map;
};

