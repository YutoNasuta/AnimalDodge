//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/24
// <file>			CharacterCollision.h
// <概要>			キャラクターの当たり判定
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
	// 当たったかどうか
	bool m_isHit;

};
