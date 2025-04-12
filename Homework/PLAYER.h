#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Player {
public:
	void read(std::istream&);
	void show();
	int getScore() const;
private:
	std::string name;
	int score;
	size_t id;
	size_t num;
	std::unique_ptr<char[]> p;

	friend std::ostream& operator<<(std::ostream&, const Player&);
};