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
		std::cout << "\033[31m" << "\n[���� 1]" << "\033[0m" << "���� ������ Player ���\n" << std::endl;
		(players.end() - 1)->show();
	}
	
	{
		std::cout << "\033[31m" << "\n[���� 2 - 1]" << "\033[0m" << "Player�� ��� ���\n" << std::endl;

		int maxValue{ std::numeric_limits<int>::min() };
		long long total = std::accumulate(players.begin(), players.end(), 0LL,
			[](long long sum, const Player& p) {
				return sum + p.getScore();
			});
		long long average{0};

		std::cout << "���� - " << total << std::endl;

		average = total / players.size();

		std::cout << "��� - " << average << std::endl;

		std::cout << "\033[31m" << "\n[���� 2 - 2]" << "\033[0m" << "������ ���� ū Player ���\n" << std::endl;

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

		std::cout << "\033[31m" << "\n[���� 3 - 1]" << "\033[0m" << "���� ID ��ü ã�� �ؽ�Ʈ���Ϸ� ����\n" << std::endl;

		std::ofstream out{ "�������̵�.txt", std::ios::app };

		for (Player& player : sameId)
			out << player;

		std::cout << "\033[31m" << "\n[���� 3 - 2]" << "\033[0m" << "ID ���� ��ü�� ���� ���\n" << std::endl;

		std::println("id�� ���� Player: {:8}", sameId.size());


	}

	{
		std::cout << "\033[31m" << "\n[���� 4]" << "\033[0m" << "�޸𸮿� ����� p �������� ���� �� 'a'�� 10���� �̻��� Player ���\n" << std::endl;

		int aCount{ 0 };
		for (const Player& player : players) {
			player.sortChar();
			if (player.aCountChar())
				++aCount;
		}
		std::println("�޸𸮿� ����� p�� 'a'�� 10�� �̻��� Player: {:8}", aCount);
	}

	
	{
		size_t targetId;
		std::vector<Player> targetPlayer;										// ã�Ƴ� Player
		std::vector<Player> frontPlayer;										// targetPlayer ���� Player
		std::vector<Player> backPlayer;											// targetPlayer ���� Player

		std::cout << "\033[31m" << "\n[���� 5]\n" << "\033[0m" << std::endl;

		while (true) {
			// vector ����
			targetPlayer.clear();												
			frontPlayer.clear();
			backPlayer.clear();

			// search
			std::cout << "ã����� id �Է�: ";
			std::cin >> targetId;

			auto startTime = std::chrono::high_resolution_clock::now();
			// �����ϰ� ���� �ڵ�--------------------------------------
			//

			// ID �� ���� �� Target �� �յ� Player ���
			//
			std::cout << "\n\nid ���� �� Target Player ���" << std::endl;
			std::sort(players.begin(), players.end(),
				[](const Player& a, const Player& b) {
					return a.getId() < b.getId();
				});
			
			auto it = players.begin();

			while ((it = std::find_if(it, players.end(), [targetId](const Player& player) {
				return player.getId() == targetId;
				})) != players.end()) {
				if (it != players.begin()) {
					std::cout << "\033[33m" << "[Front Player]" << std::endl;
					(it - 1)->show();
				}

				std::cout << "\033[31m" << "[Target Player]" << std::endl;
				it->show();

				if (it != players.end()) {
					std::cout << "\033[33m" << "[Back Player]" << "\033[0m" << std::endl;
					(it + 1)->show();
				}

				std::cout << std::endl;
				++it;
			}

			// name �� ���� �� Target �� �յ� Player ���
			//
			std::cout << "\n\nname ���� �� Target Player ���" << std::endl;
			std::sort(players.begin(), players.end(),
				[](const Player& a, const Player& b) {
					return std::lexicographical_compare(a.getName().begin(), a.getName().end(), b.getName().begin(), b.getName().end());
				});

			it = players.begin();

			while ((it = std::find_if(it, players.end(), [targetId](const Player& player) {
				return player.getId() == targetId;
				})) != players.end()) {
				if (it != players.begin()) {
					std::cout << "\033[33m" << "[Front Player]" << std::endl;
					(it - 1)->show();
				}

				std::cout << "\033[31m" << "[Target Player]" << std::endl;
				it->show();

				if (it != players.end()) {
					std::cout << "\033[33m" << "[Back Player]" << "\033[0m" << std::endl;
					(it + 1)->show();
				}

				std::cout << std::endl;
				++it;
			}

			// score �� ���� �� Target �� �յ� Player ���
			//
			std::cout << "\n\nscore ���� �� Target Player ���" << std::endl;
			std::sort(players.begin(), players.end(),
				[](const Player& a, const Player& b) {
					return a.getScore() < b.getScore();
				});

			it = players.begin();

			while ((it = std::find_if(it, players.end(), [targetId](const Player& player) {
				return player.getId() == targetId;
				})) != players.end()) {
				if (it != players.begin()) {
					std::cout << "\033[33m" << "[Front Player]" << std::endl;
					(it - 1)->show();
				}

				std::cout << "\033[31m" << "[Target Player]" << std::endl;
				it->show();

				if (it != players.end()) {
					std::cout << "\033[33m" << "[Back Player]" << "\033[0m" << std::endl;
					(it + 1)->show();
				}

				std::cout << std::endl;
				++it;
			}

			// 
			//---------------------------------------------------------
			auto endTime = std::chrono::high_resolution_clock::now();
			std::cout << "�ɸ��ð�: " << endTime - startTime << std::endl;
		}
	}
}