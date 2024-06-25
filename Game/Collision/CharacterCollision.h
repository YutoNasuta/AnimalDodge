//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/24
// <file>			CharacterCollision.h
// <概要>			キャラクターのコリジョン
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
	// 当たったかどうか
	bool m_isHit;
	// 当たった位置
	DirectX::SimpleMath::Vector3 m_hitPosition;
};
