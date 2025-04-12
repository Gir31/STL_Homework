#include "PLAYER.h"
#include <iostream>
#include <fstream>
#include <string>
#include <print>

//===========================================================================
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

void Player::show()
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
//===========================================================================

//===========================================================================
// 
std::ostream& operator<<(std::ostream& os, const Player& player)
{

}