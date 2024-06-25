//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/24
// <file>			BallCollision.h
// <概要>			ボールの当たり判定
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
	// 壁とボールの当たり判定検出用
	void DetectCollisionBallToWall(Ball* ball , GenerateStage* stage);

private:
	// 当たったか検出する用
	bool m_isHit;	
	// 当たったステージケース番号格納用
	int m_stageCaseNumber;
};