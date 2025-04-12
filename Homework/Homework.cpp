#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <algorithm>
#include <print>
#include <vector>
#include <unordered_set>
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
		std::unordered_set<size_t> handledIds;		// �ߺ� ����
		std::vector<Player> sameId;

		for (Player& player : players) {
			size_t targetId = player.getId();

			if (handledIds.contains(targetId)) continue;

			int count = std::count_if(players.begin(), players.end(),
				[targetId](const Player& p) { return p.getId() == targetId; });

			if (count > 1) {
				std::copy_if(players.begin(), players.end(), std::back_inserter(sameId),
					[targetId](const Player& p) {
						return p.getId() == targetId;
					});

				handledIds.insert(targetId);
			}
		}

		std::sort(sameId.begin(), sameId.end(), 
			[](const Player& a, const Player& b) {
				return a.getId() < b.getId();
			});

		for (Player& player : sameId)
			player.show();

		std::cout << "[���� 3 - 1]���� ID ��ü ã�� �ؽ�Ʈ���Ϸ� ����" << std::endl;

		std::cout << "[���� 3 - 2]ID ���� ��ü�� ���� ���" << std::endl;

	}
	
}