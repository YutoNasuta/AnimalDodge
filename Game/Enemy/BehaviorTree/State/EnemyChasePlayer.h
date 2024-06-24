//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/21
// <file>			EnemyStanding.h
// <概要>			エネミーがプレイヤーを追う
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"
#include"Game/CommonResources.h"
class Enemy;
class BlackBoard;

class EnemyChase : public NakashiLib::ActionNode
{


public:
	// コンストラクタ
	EnemyChase(Enemy* enemy , BlackBoard* blackboard);
	// 実行する
	bool Execute() override;

private:
	// エネミー取得
	Enemy* m_enemy;
	CommonResources* m_commonResources;
	BlackBoard* m_blackBoard;

	float m_timeExit;
	const float EXITTIME = 10;

	void MoveParts();
	void MoveHand();
	void Chase();
};
