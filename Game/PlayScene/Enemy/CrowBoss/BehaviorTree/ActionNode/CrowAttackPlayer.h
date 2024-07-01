//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/07/01
// <file>			CrowAttackPlayer.h
// <概要>			カラスがプレイヤーを攻撃する
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"
#include"Game/CommonResources.h"

class Crow;
class BlackBoard;

class CrowAttackPlayer : public NakashiLib::ActionNode
{
public:
	// コンストラクタ
	CrowAttackPlayer(Crow* crow, BlackBoard* blackBoard);
	// 実行する
	bool Execute() override;

private:
	// カラス取得
	Crow* m_crow;
	CommonResources* m_commonResources;
	BlackBoard* m_blackBoard;

	float m_timeExit;
	const float EXITTIME = 10;

	float m_startTime;

	void MoveParts();
	void MoveHand();

};