//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/24
// <file>			CharacterCollision.h
// <�T�v>			�L�����N�^�[�̓����蔻��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

class Player;
class Enemy;

class CharacterCollision
{
public:
	CharacterCollision();
	~CharacterCollision();
	void CheckHit(Player* player , Enemy* enemy);

private:
	// �����������ǂ���
	bool m_isHit;

};
