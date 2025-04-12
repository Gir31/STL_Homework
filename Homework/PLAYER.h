#pragma once
#include <iostream>
#include <string>

class Player {
private:
	std::string name;
	int score;
	size_t id;
	size_t num;
	std::unique_ptr<char[]> p;
};