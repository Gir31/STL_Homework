#include "PLAYER.h"
#include <iostream>
#include <fstream>
#include <string>
#include <print>
#include <iomanip>
#include <algorithm>

//===========================================================================
// ������
Player::Player() = default;
// ���̳ʸ� ���Ͽ��� �о�� ��ü�� �ִ� �ڵ�
void Player::read(std::istream& is) 
{
	size_t trash;								// ������ ���� �ֱ����� ����

	is.read((char*)&name, sizeof(std::string));
	is.read((char*)&score, sizeof(int));
	is.read((char*)&trash, sizeof(int));		// int�� size_t ������ ����Ʈ�� ������� �ڵ�

	is.read((char*)&id, sizeof(size_t));
	is.read((char*)&num, sizeof(size_t));

	is.read((char*)&trash, sizeof(size_t));		// pointer�� p�� �� ������ ����Ʈ�� ������� �ڵ�

	p.reset();
	p = std::make_unique<char[]>(num);
	is.read(p.get(), num);
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
	std::cout << "----------------------------------------------------------------------------" << std::endl;
	std::print("�̸�:{:>15} | ���̵�:{:>8} | ����:{:>15} | �ڿ���:{:>4}",
		name, id, score, num);
	std::cout << std::endl;

	std::cout << "����� ����" << std::endl;
	for (int i = 0; i < num; ++i)
		std::cout << p[i];

	std::cout <<  std::endl;
	std::cout << "----------------------------------------------------------------------------" << std::endl;
}

// p ����
void Player::sortChar() const
{
	std::sort(p.get(), p.get() + num);
}

// p ���� a ���� count
bool Player::aCountChar() const
{
	int count = std::count(p.get(), p.get() + num, 'a');

	return count > 9;
}

// ��ü�� score���� �������� �ڵ�
int Player::getScore() const
{
	return score;
}
// ��ü�� id���� �������� �ڵ�
size_t Player::getId() const
{
	return id;
}
//===========================================================================

//===========================================================================
// 
std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os 
		<< std::left << std::setw(20) << player.name << player.id << '\n';
}