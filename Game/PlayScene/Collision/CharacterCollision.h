//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/24
// <file>			CharacterCollision.h
// <概要>			キャラクターの当たり判定
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
	// 当たったかどうか
	bool m_isEnemyHit;
	bool m_isWallHit;

	// 当たったステージケース番号格納用
	int m_stageCaseNumber;

};
