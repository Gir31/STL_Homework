#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <algorithm>
#include <print>
#include <vector>
#include <chrono>
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

	std::cout << "[����]		Player ��ü�� �޸� ����" << std::endl;
	for (Player& player : players)
		player.read(in);

	
	{
		std::cout << "[���� 1]���� ������ Player ���" << std::endl;
		(players.end() - 1)->show();
	}
	
	{
		std::cout << "[���� 2 - 1]Player�� ��� ���" << std::endl;

		int maxValue{ std::numeric_limits<int>::min() };
		long long total = std::accumulate(players.begin(), players.end(), 0LL,
			[](long long sum, const Player& p) {
				return sum + p.getScore();
			});
		long long average{0};

		std::cout << "���� - " << total << std::endl;

		average = total / players.size();

		std::cout << "��� - " << average << std::endl;

		// ���� ���� ���� �ִ� ���ϱ�
		/*auto pos = std::max_element(players.begin(), players.end(),
			[](const Player& a, const Player& b) {
				return a.getScore() < b.getScore();
			});
		
		if (pos != players.end())
			pos->show();*/

		std::cout << "[���� 2 - 2]������ ���� ū Player ���" << std::endl;

		// �ߺ� �ִ� ���ϱ�
		maxValue = std::max_element(players.begin(), players.end(),
			[](const Player& a, const Player& b) {
				return a.getScore() < b.getScore();
			})->getScore();

		for (const Player& player : players) {
			if (player.getScore() == maxValue)
				player.show();
		}
	}
	
	{
		std::sort(players.begin(), players.end(),
			[](const Player& a, const Player& b) {
				return a.getId() < b.getId();
			});

		std::vector<Player> sameId;

		for (size_t i = 0; i < players.size() - 1; ++i) {
			if (players[i].getId() == players[i + 1].getId()) {
				if (sameId.empty() || sameId.back().getId() != players[i].getId()) 
					sameId.push_back(players[i]);
				sameId.push_back(players[i + 1]);
			}
		}

		/*for (Player& player : sameId)
			player.show();*/

		std::cout << "[���� 3 - 1]���� ID ��ü ã�� �ؽ�Ʈ���Ϸ� ����" << std::endl;

		std::ofstream out{ "�������̵�.txt", std::ios::app };

		for (Player& player : sameId)
			out << player;

		std::cout << "[���� 3 - 2]ID ���� ��ü�� ���� ���" << std::endl;

	}

	{
		std::cout << "[���� 4 - 1]�޸𸮿� ����� p �������� ����" << std::endl;

		int aCount{ 0 };
		auto b = std::chrono::high_resolution_clock::now();
		for (const Player& player : players) {
			player.sortChar();
			if (player.aCountChar())
				++aCount;
		}
		auto e = std::chrono::high_resolution_clock::now();

		std::cout << "�ɸ��ð� : " << e - b << " / " << aCount << std::endl;

		aCount = 0 ;
		b = std::chrono::high_resolution_clock::now();
		for (const Player& player : players) {
			player.sortChar();
			if (player.aCountChar2())
				++aCount;
		}
		e = std::chrono::high_resolution_clock::now();

		std::cout << "�ɸ��ð� : " << e - b << " / " << aCount << std::endl;
	}
	
}