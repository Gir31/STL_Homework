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
	std::cout << "[파일]2025 STL 과제 파일 - 2021184002 읽기" << std::endl;
	std::ifstream in{ "2025 STL 과제 파일 - 2021184002", std::ios::binary };
	if (not in) {
		std::cout << "[파일]	파일 읽기 실패" << std::endl;
		return 2021184002;
	}
	std::cout << "[파일]	파일 읽기 성공" << std::endl;

	std::cout << "[저장]		Player 객체에 메모리 저장" << std::endl;
	for (Player& player : players)
		player.read(in);

	
	{
		std::cout << "[문제 1]가장 마지막 Player 출력" << std::endl;
		(players.end() - 1)->show();
	}
	
	{
		std::cout << "[문제 2 - 1]Player의 평균 출력" << std::endl;

		int maxValue{ std::numeric_limits<int>::min() };
		long long total = std::accumulate(players.begin(), players.end(), 0LL,
			[](long long sum, const Player& p) {
				return sum + p.getScore();
			});
		long long average{0};

		std::cout << "총합 - " << total << std::endl;

		average = total / players.size();

		std::cout << "평균 - " << average << std::endl;

		// 제일 먼저 나온 최댓값 구하기
		/*auto pos = std::max_element(players.begin(), players.end(),
			[](const Player& a, const Player& b) {
				return a.getScore() < b.getScore();
			});
		
		if (pos != players.end())
			pos->show();*/

		std::cout << "[문제 2 - 2]점수가 가장 큰 Player 출력" << std::endl;

		// 중복 최댓값 구하기
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
		std::unordered_set<size_t> handledIds;		// 중복 방지
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

		std::cout << "[문제 3 - 1]동일 ID 객체 찾아 텍스트파일로 저장" << std::endl;

		std::cout << "[문제 3 - 2]ID 같은 객체의 개수 출력" << std::endl;

	}
	
}