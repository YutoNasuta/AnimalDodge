//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			CrowStanding.h
// <概要>			エネミーの立ち状態
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"
#include"Game/CommonResources.h"
class Crow;

class CrowStanding : public NakashiLib::ActionNode
{


public:
	// コンストラクタ
	CrowStanding(Crow* crow);
	// 実行する
	bool Execute() override;

private:
	// エネミー取得
	Crow* m_crow;
	CommonResources* m_commonResources;

	float m_timeExit;
	const float EXITTIME = 10;

	void MoveParts();
	void MoveHand();
};