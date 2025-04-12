#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Player {
public:
	// ������
	Player();

	// ���Ͽ��� ����
	void read(std::istream&);

	// ���� ������ & �����Ҵ翬����
	Player(const Player&);
	Player& operator=(const Player&);

	// �̵� ������ & �̵��Ҵ翬����
	Player(Player&&);
	Player& operator=(Player&&);

	// ȭ�� ���
	void show() const;

	// ���� ��������
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