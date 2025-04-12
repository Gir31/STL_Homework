#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <algorithm>
#include <print>
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

	for (Player& player : players)
		player.read(in);

	{
		int maxValue{ std::numeric_limits<int>::min() };
		long long sum {std::numeric_limits<int>::min()};
		long long average{0};

		for (Player& player : players)
			sum += player.getScore();

		std::cout << "���� - " << sum << std::endl;

		average = sum / players.size();

		std::cout << "��� - " << average << std::endl;

		auto pos = std::max_element(players.begin(), players.end(), 
			[](const Player& a, const Player& b) {
				return a.getScore() < b.getScore();
			});
		
		if (pos != players.end())
			pos->show();
	}
}