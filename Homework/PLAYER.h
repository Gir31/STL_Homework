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

	// 복사 생성자
	Player(const Player&);

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