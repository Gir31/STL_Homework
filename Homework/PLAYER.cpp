#include "PLAYER.h"
#include <iostream>
#include <fstream>
#include <string>
#include <print>
#include <iomanip>
#include <algorithm>
#include <vector>

//===========================================================================
// ������
Player::Player() = default;
// ���̳ʸ� ���Ͽ��� �о�� ��ü�� �ִ� �ڵ�
void Player::read(std::istream& is) 
{
	size_t trash;								// ������ ���� �ֱ����� ����

	is.read((char*)&name, sizeof(std::string));
	is.read((char*)&score, sizeof(int));
	// is.read((char*)&trash, sizeof(int));		// int�� size_t ������ ����Ʈ�� ������� �ڵ�
	is.seekg(4, std::ios::cur);					// 4����Ʈ ��ŵ

	is.read((char*)&id, sizeof(size_t));
	is.read((char*)&num, sizeof(size_t));

	// is.read((char*)&trash, sizeof(size_t));		// pointer�� p�� �� ������ ����Ʈ�� ������� �ڵ�
	is.seekg(8, std::ios::cur);						// 8����Ʈ ��ŵ

	p.reset();
	p = std::make_unique<char[]>(num);
	is.read(p.get(), num);

	//is.read((char*)this, sizeof(Player));

	//p.release();
	//p = std::make_unique<char[]>(num);
	//is.read(p.get(), num);
}

// ���� ������ & �����Ҵ翬����
Player::Player(const Player& other) 
	: name{other.name}, score{ other.score }, id{ other.id }, num {other.num}
{
	p.reset();
	p = std::make_unique<char[]>(num);
	memcpy(p.get(), other.p.get(), num);
}

Player& Player::operator=(const Player& other)
{
	if (this == &other)
		return *this;

	name = other.name;
	score = other.score;
	id = other.id;
	num = other.num;

	p.reset();
	p = std::make_unique<char[]>(num);
	memcpy(p.get(), other.p.get(), num);

	return *this;
}

// �̵� ������ & �̵��Ҵ翬����
Player::Player(Player&& other)
	: name{ other.name }, score{ other.score }, id{ other.id }, num{ other.num }
{
	p.reset(other.p.release());
	other.num = 0;
}

Player& Player::operator=(Player&& other)
{
	if (this == &other)
		return *this;

	name = other.name;
	score = other.score;
	id = other.id;
	num = other.num;

	p.reset(other.p.release());
	other.num = 0;

	return *this;
}


// ��ü ������ �����ִ� �ڵ�
void Player::show() const
{
	std::cout << "\033[32m" << "----------------------------------------------------------------------------" << "\033[0m" << std::endl;
	std::print("�̸�:{:>15} | ���̵�:{:>8} | ����:{:>15} | �ڿ���:{:>4}",
		name, id, score, num);
	std::cout << std::endl;

	std::cout << "\033[32m" << "����� ����" << "\033[0m";
	for (int i = 0; i < num; ++i) {
		if (i % 75 == 0)
			std::cout << std::endl;
		std::cout << p[i];
	}

	std::cout <<  std::endl;
	std::cout << "\033[32m" << "----------------------------------------------------------------------------" << "\033[0m" << std::endl;
}

// p ����
void Player::sortChar() const
{
	std::sort(p.get(), p.get() + num);
}

// p ���� a ���� count
bool Player::aCountChar() const
{
	return (std::count(p.get(), p.get() + num, 'a') > 9) ;
}


// ��ü�� score���� �������� �ڵ�
const int Player::getScore() const
{
	return score;
}
// ��ü�� id���� �������� �ڵ�
const size_t Player::getId() const
{
	return id;
}
// ��ü�� name���� �������� �ڵ�
const std::string Player::getName() const
{
	return name;
}
//
//===========================================================================

//===========================================================================
// 
std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os 
		<< std::left << std::setw(20) << player.name << player.id << '\n';
}
//
//===========================================================================

//===========================================================================
//
// id�� ���ؼ� player�� ã�� ����ϴ� �Լ�
void findPlayerById(const std::vector<Player*>& v, const size_t& targetId)
{
	for (const Player* player : v) {
		if (player->getId() == targetId) {

			if (*v.begin() != player) {
				std::cout << "\033[33m" << "[Front Player]" << std::endl;
				(player - 1)->show();
			}

			std::cout << "\033[31m" << "[Target Player]" << std::endl;
			player->show();

			if (*(v.end()-1) != player) {
				std::cout << "\033[33m" << "[Back Player]" << "\033[0m" << std::endl;
				(player + 1)->show();
			}

			std::cout << std::endl;
		}
	}
}