//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/24
// <file>			CharacterCollision.h
// <�T�v>			�L�����N�^�[�̃R���W����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

class Player;
class Enemy;

class CharacterCollision
{
public:
	bool CheckHit(Player* player , Enemy* enemy);

private:
	// �����������ǂ���
	bool m_isHit;
	// ���������ʒu
	DirectX::SimpleMath::Vector3 m_hitPosition;
};
