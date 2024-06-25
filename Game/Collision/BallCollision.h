//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/24
// <file>			BallCollision.h
// <�T�v>			�{�[���̓����蔻��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
class Ball;
class GenerateStage;

class BallCollision
{
public:
	BallCollision();
	~BallCollision();
	// �ǂƃ{�[���̓����蔻�茟�o�p
	void DetectCollisionBallToWall(Ball* ball , GenerateStage* stage);

private:
	// �������������o����p
	bool m_isHit;	
	// ���������X�e�[�W�P�[�X�ԍ��i�[�p
	int m_stageCaseNumber;
};