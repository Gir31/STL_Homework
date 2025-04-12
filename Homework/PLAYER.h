#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Player {
public:
	// 생성자
	Player();

	// 파일에서 복사
	void read(std::istream&);

	// 복사 생성자 & 복사할당연산자
	Player(const Player&);
	Player& operator=(const Player&);

	// 이동 생성자 & 이동할당연산자
	Player(Player&&);
	Player& operator=(Player&&);

	// 화면 출력
	void show() const;

	// 변수 가져오기
	int getScore() const;
	size_t getId() const;
private:
	std::string name;
	int score;
	size_t id;
	size_t num;
	std::unique_ptr<char[]> p{};

	friend std::ostream& operator<<(std::ostream&, const Player&);
};