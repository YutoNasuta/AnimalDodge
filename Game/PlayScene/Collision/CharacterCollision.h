//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/24
// <file>			CharacterCollision.h
// <�T�v>			�L�����N�^�[�̓����蔻��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

class Player;
class Crow;
class GenerateStage;

class CharacterCollision
{
public:
	CharacterCollision();
	~CharacterCollision();
	void DetectCollisionPlayerToEnemy(Player* player , Crow* crowBoss);

	void DetectCollisionPlayerToWall(Player* player, GenerateStage* stage);

private:
	// �����������ǂ���
	bool m_isEnemyHit;
	bool m_isWallHit;

	// ���������X�e�[�W�P�[�X�ԍ��i�[�p
	int m_stageCaseNumber;

};
