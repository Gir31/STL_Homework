#include <iostream>
#include <fstream>
#include <array>
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

	std::string name;
	int score;
	size_t id;
	size_t num;
	std::unique_ptr<char[]> p{};


	int a{ 0 };
	while (true) {
		switch (a % 5) {
		case 0:
			std::cout << a / 5 << "번째 객체" << std::endl;
			in.read((char*)&name, sizeof(std::string));
			std::cout << "name : " << name << std::endl;
			break;
		case 1:
			in.read((char*)&score, sizeof(int));
			std::cout << "score : " << score << std::endl;
			break;
		case 2:
			in.read((char*)&id, sizeof(size_t));
			std::cout << "id : " << id << std::endl;
			break;
		case 3:
			in.read((char*)&num, sizeof(size_t));
			std::cout << "num : " << num << std::endl;
			break;
		case 4:
			p.reset();
			p = std::make_unique<char[]>(num);
			in.read(p.get(), num);

			for (int i = 0; i < num; ++i)
				std::cout << p[i];

			std::cout << std::endl;
			break;
		}
		++a;
	}
}