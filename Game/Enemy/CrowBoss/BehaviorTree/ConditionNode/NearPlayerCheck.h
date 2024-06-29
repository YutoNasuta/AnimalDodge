//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/29
// <file>			NearPlayerCheck.h
// <概要>			近くにプレイヤーがいるかどうか判定
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"

// 前方宣言
class Crow;
class BlackBoard;

class NearPlayerCheck : public NakashiLib::ConditionNode
{
public:
	// コンストラクタ
	NearPlayerCheck(Crow* Crow, BlackBoard* blackboard);
	// デストラクタ
	~NearPlayerCheck();
	// プレイヤーが近くにいるかどうかを返す
	bool CheckNearPlayer();

private:


	// エネミー取得
	Crow* m_crow;
	// ブラックボードの取得
	BlackBoard* m_blackBoard;
};