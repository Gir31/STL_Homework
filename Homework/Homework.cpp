#include <iostream>
#include <fstream>
#include <array>
#include "PLAYER.h"

std::array<Player, 250'0000> players;

int main()
{
	std::cout << "[����]2025 STL ���� ���� - 2021184002 �б�" << std::endl;
	std::ifstream in{ "2025 STL ���� ���� - 2021184002", std::ios::binary };
	if (not in) {
		std::cout << "[����]	���� �б� ����" << std::endl;
		return 2021184002;
	}
	std::cout << "[����]	���� �б� ����" << std::endl;

	std::string name;
	int score;
	int trash_4;
	size_t id;
	size_t num;
	size_t trash_8;
	std::unique_ptr<char[]> p{};


	for (Player& player : players)
		player.read(in);

	for (int i = 0; i < 100; ++i)
		players[i].show();
}