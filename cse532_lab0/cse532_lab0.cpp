// cse532_lab0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <tuple>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>


#include "Play.h"
#include "Container.h"
#include "ThreadProtector.h"

enum ReturnValues{ SUCCESS, INCORRECT_ARGS, FILE_OPEN_ERROR};

int main(int argc, char * argv[])
{
	if (argc < 2 || argc > 2)
	{
		auto ErrorMessage = [&]() -> int
		{
			std::cout << "Incorrect number of arguments" << std::endl;
			std::cout << "Usage: " << argv[0] <<  " <configuration_file_name>" << std::endl;
			return INCORRECT_ARGS; 
		};
		return ErrorMessage();
	}

	std::string name;
	std::ifstream stream;
	std::vector<std::tuple<std::string, std::string>> name_file_vec;
	stream.open(argv[1], std::ifstream::in);

	if (stream.is_open())
	{
		int count = 0;
		std::string config_line;
		while (std::getline(stream, config_line))
		{
			std::istringstream iss_config(config_line);
			if (count == 0)
			{
				if (!config_line.empty())
				{	
					name = config_line;
					count++;
				}
			}
			else
			{
				std::string char_name, file_name;
				if (iss_config >> char_name >> file_name)
				{
					name_file_vec.push_back(std::make_tuple(char_name, file_name));
				}	
				else
				{
					//Need some sort of error message
				}
			}
		}
	}
	else
	{
		auto ArgErrorMessage = []() -> int
		{
			std::cout << "Unable to open file" << std::endl;
			return FILE_OPEN_ERROR;
		};
		return ArgErrorMessage();
	}

	Play p(name);
	ThreadProtector t_p;
	for_each(name_file_vec.begin(), name_file_vec.end(), [&](std::tuple<std::string, std::string> & t)
	{
		t_p << std::thread([&t, &p]()
		{
			std::ifstream script;
			script.open(std::get<1>(t), std::ifstream::in);
			const std::string character_name = std::get<0>(t);
			if (script.is_open())
			{
				std::string line;
				while (std::getline(script, line))
				{
					std::istringstream iss(line);
					int line_num;
					while (iss >> line_num)
					{
						std::string rest_of_line;
						std::getline(iss, rest_of_line);
						if (!rest_of_line.empty())
						{
							Container c(line_num, character_name, rest_of_line);
							p << c;
						}
					}
				}
				script.close();
			}
			else
			{
				p.Alert(std::get<1>(t));
			}
		});
	});
	t_p();
	p.Print();
	return SUCCESS;
}
/*
std::ifstream script;
script.open(std::get<1>(t), std::ifstream::in);
if (script.is_open())
{
script.close();
const std::string character_name = std::get<0>(t);
const std::string script_name = std::get<1>(t);
t_p << std::thread([script_name , character_name, &p]()
{
std::string line;
std::ifstream thread_script;
thread_script.open(script_name, std::ifstream::in);
while (std::getline(thread_script, line))
{
std::istringstream iss(line);
int line_num;
while (iss >> line_num)
{
std::string rest_of_line;
std::getline(iss, rest_of_line);
if (!rest_of_line.empty())
{
Container c(line_num, character_name, rest_of_line);
p << c;
}
}
}
thread_script.close();
});
}
else
{

}
*/