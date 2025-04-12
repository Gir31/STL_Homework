#include "PLAYER.h"
#include <iostream>
#include <fstream>
#include <string>
#include <print>

//===========================================================================
// 생성자
Player::Player() = default;
// 바이너리 파일에서 읽어와 객체에 넣는 코드
void Player::read(std::istream& is) 
{
	size_t trash;								// 쓰레기 값을 넣기위한 변수

	is.read((char*)&name, sizeof(std::string));
	is.read((char*)&score, sizeof(int));
	is.read((char*)&trash, sizeof(int));		// int와 size_t 사이의 바이트를 잡기위한 코드

	is.read((char*)&id, sizeof(size_t));
	is.read((char*)&num, sizeof(size_t));

	is.read((char*)&trash, sizeof(size_t));		// pointer와 p의 값 사이의 바이트를 잡기위한 코드

	p.reset();
	p = std::make_unique<char[]>(num);
	is.read(p.get(), num);
}

// 복사 생성자 & 복사할당연산자
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


// 객체 정보를 보여주는 코드
void Player::show() const
{
	std::cout << "----------------------------------------------------------------------------" << std::endl;
	std::print("이름:{:>15} | 아이디:{:>8} | 점수:{:>15} | 자원수:{:>4}",
		name, id, score, num);
	std::cout << std::endl;

	std::cout << "저장된 글자" << std::endl;
	for (int i = 0; i < num; ++i)
		std::cout << p[i];

	std::cout <<  std::endl;
	std::cout << "----------------------------------------------------------------------------" << std::endl;
}

// 객체의 score값을 가져오는 코드
int Player::getScore() const
{
	return score;
}
// 객체의 id값을 가져오는 코드
size_t Player::getId() const
{
	return id;
}
//===========================================================================

//===========================================================================
// 
std::ostream& operator<<(std::ostream& os, const Player& player)
{

}