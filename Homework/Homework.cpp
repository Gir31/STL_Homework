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
		std::cout << "\033[31m" << "\n[문제 1]" << "\033[0m" << "가장 마지막 Player 출력\n" << std::endl;
		(players.end() - 1)->show();
	}
	
	{
		std::cout << "\033[31m" << "\n[문제 2 - 1]" << "\033[0m" << "Player의 평균 출력\n" << std::endl;

		int maxValue{ std::numeric_limits<int>::min() };
		long long total = std::accumulate(players.begin(), players.end(), 0LL,
			[](long long sum, const Player& p) {
				return sum + p.getScore();
			});
		long long average{0};

		std::cout << "총합 - " << total << std::endl;

		average = total / players.size();

		std::cout << "평균 - " << average << std::endl;

		std::cout << "\033[31m" << "\n[문제 2 - 2]" << "\033[0m" << "점수가 가장 큰 Player 출력\n" << std::endl;

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

		std::cout << "\033[31m" << "\n[문제 3 - 1]" << "\033[0m" << "동일 ID 객체 찾아 텍스트파일로 저장\n" << std::endl;

		std::ofstream out{ "같은아이디.txt", std::ios::app };

		for (Player& player : sameId)
			out << player;

		std::cout << "\033[31m" << "\n[문제 3 - 2]" << "\033[0m" << "ID 같은 객체의 개수 출력\n" << std::endl;

		std::println("id가 같은 Player: {:8}", sameId.size());


	}

	{
		std::cout << "\033[31m" << "\n[문제 4]" << "\033[0m" << "메모리에 저장된 p 오름차순 정렬 후 'a'가 10글자 이상인 Player 출력\n" << std::endl;

		int aCount{ 0 };
		for (const Player& player : players) {
			player.sortChar();
			if (player.aCountChar())
				++aCount;
		}
		std::println("메모리에 저장된 p중 'a'가 10개 이상인 Player: {:8}", aCount);
	}

	
	{
		size_t targetId;
		std::vector<Player> targetPlayer;										// 찾아낸 Player
		std::vector<Player> frontPlayer;										// targetPlayer 앞의 Player
		std::vector<Player> backPlayer;											// targetPlayer 뒤의 Player

		std::cout << "\033[31m" << "\n[문제 5]\n" << "\033[0m" << std::endl;

		while (true) {
			// vector 리셋
			targetPlayer.clear();												
			frontPlayer.clear();
			backPlayer.clear();

			// search
			std::cout << "찾고싶은 id 입력: ";
			std::cin >> targetId;

			auto startTime = std::chrono::high_resolution_clock::now();
			// 측정하고 싶은 코드--------------------------------------
			//

			// ID 순 정렬 후 Target 및 앞뒤 Player 출력
			//
			std::cout << "\n\nid 정렬 후 Target Player 출력" << std::endl;
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

			// name 순 정렬 후 Target 및 앞뒤 Player 출력
			//
			std::cout << "\n\nname 정렬 후 Target Player 출력" << std::endl;
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

			// score 순 정렬 후 Target 및 앞뒤 Player 출력
			//
			std::cout << "\n\nscore 정렬 후 Target Player 출력" << std::endl;
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
			std::cout << "걸린시간: " << endTime - startTime << std::endl;
		}
	}
}