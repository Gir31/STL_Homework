#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include "PLAYER.h"

std::array<Player, 250'0000> players;

int main()
{
	std::cout << "[파일]2025 STL 과제 파일 - 2021184002 읽기" << std::endl;
	std::ifstream in{ "2025 STL 과제 파일 - 2021184002", std::ios::binary };
	if (not in) {
		std::cout << "[파일]	파일 읽기 실패" << std::endl;
		return 2021184002;
	}
	std::cout << "[파일]	파일 읽기 성공" << std::endl;

	for (Player& player : players)
		player.read(in);

	{
		long long sum {std::numeric_limits<int>::min()};
		long long average{0};

		for (Player& player : players)
			sum += player.getScore();

		std::cout << "총합 - " << sum << std::endl;

		average = sum / players.size();

		std::cout << "평균 - " << average << std::endl;
	};
}