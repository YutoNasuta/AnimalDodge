//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/21
// <file>			CrowStanding.h
// <概要>			エネミーがプレイヤーを追う
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"
#include"Game/CommonResources.h"
class Crow;
class BlackBoard;

class CrowChase : public NakashiLib::ActionNode
{


public:
	// コンストラクタ
	CrowChase(Crow* Crow , BlackBoard* blackboard);
	// 実行する
	bool Execute() override;

private:
	// エネミー取得
	Crow* m_crow;
	CommonResources* m_commonResources;
	BlackBoard* m_blackBoard;

	float m_timeExit;
	const float EXITTIME = 10;

	void MoveParts();
	void MoveHand();
	void Chase();
};
