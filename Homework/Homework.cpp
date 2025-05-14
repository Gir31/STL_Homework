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

	// [���� 1]
	//
	/*{
		std::cout << "\033[31m" << "\n[���� 1] " << "\033[0m" << "���� ������ Player ���\n" << std::endl;
		(players.end() - 1)->show();
	}*/
	
	// [���� 2]
	//
	/* {
		std::cout << "\033[31m" << "\n[���� 2 - 1] " << "\033[0m" << "Player�� ��� ���\n" << std::endl;

		int maxValue{ std::numeric_limits<int>::min() };
		long long total = std::accumulate(players.begin(), players.end(), 0LL,
			[](long long sum, const Player& p) {
				return sum + p.getScore();
			});
		long long average{0};

		average = total / players.size();

		std::cout << "[���] " << average << std::endl;

		std::cout << "\033[31m" << "\n[���� 2 - 2] " << "\033[0m" << "������ ���� ū Player ���\n" << std::endl;

		// �ߺ� �ִ� ���ϱ�
		maxValue = std::max_element(players.begin(), players.end(),
			[](const Player& a, const Player& b) {
				return a.getScore() < b.getScore();
			})->getScore();

		// �ִ��� �ߺ��Ǵ� Player�� ��� ���
		std::cout << "[�ִ� Player] " << std::endl;
		for (const Player& player : players) {
			if (player.getScore() == maxValue)
				player.show();
		}
   	}*/
	
	// [���� 3]
	//
	/* {
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

		std::cout << "\033[31m" << "\n[���� 3 - 1] " << "\033[0m" << "���� ID ��ü ã�� �ؽ�Ʈ���Ϸ� ����\n" << std::endl;

		std::ofstream out{ "�������̵�.txt", std::ios::app };

		for (Player& player : sameId)
			out << player;

		std::cout << "\033[31m" << "\n[���� 3 - 2] " << "\033[0m" << "ID ���� ��ü�� ���� ���\n" << std::endl;

		std::println("id�� ���� Player: {:8}", sameId.size());
	}*/

	// [���� 4]
	//
	/* {
		std::cout << "\033[31m" << "\n[���� 4] " << "\033[0m" << "�޸𸮿� ����� p �������� ���� �� 'a'�� 10���� �̻��� Player ���\n" << std::endl;

		int aCount{ 0 };
		for (const Player& player : players) {
			player.sortChar();
			if (player.aCountChar())
				++aCount;
		}
		std::println("�޸𸮿� ����� p�� 'a'�� 10�� �̻��� Player�� ���� : {:8}", aCount);
	} */

	// [����]
	
	{
		size_t targetId;

		std::cout << "\033[31m" << "\n[���� 5]\n" << "\033[0m" << std::endl;

		std::vector<Player*> sortById;					// id������ �̸� ����
		std::vector<Player*> sortByName;				// name������ �̸� ����
		std::vector<Player*> sortByScore;				// score������ �̸� ����

		// �� vector�� player_ptr ����
		for (Player& player : players) {
			sortById.push_back(&player); 
			sortByName.push_back(&player);
			sortByScore.push_back(&player);
		}

		// ����
		//
		std::sort(sortById.begin(), sortById.end(),
			[](const Player* a, const Player* b) {
				return a->getId() < b->getId();
			});

		std::sort(sortByName.begin(), sortByName.end(),
			[](const Player* a, const Player* b) {
				return std::lexicographical_compare
				(a->getName().begin(), a->getName().end(), b->getName().begin(), b->getName().end());
			});

		std::sort(sortByScore.begin(), sortByScore.end(),
			[](const Player* a, const Player* b) {
				return a->getScore() < b->getScore();
			});

		while (true) {
			// search
			//
			std::cout << "ã����� id �Է�: ";
			std::cin >> targetId;

			// ID �� ���� �� Target �� �յ� Player ���
			//
			std::cout << "\n\n[ID] Target Player ���" << std::endl;

			findPlayerById(sortById, targetId);

			// name �� ���� �� Target �� �յ� Player ���
			//
			std::cout << "\n\n[NAME] Target Player ���" << std::endl;
			
			findPlayerById(sortByName, targetId);

			// score �� ���� �� Target �� �յ� Player ���
			//
			std::cout << "\n\n[SCORE] Target Player ���" << std::endl;
			
			findPlayerById(sortByScore, targetId);

		}
	}
}