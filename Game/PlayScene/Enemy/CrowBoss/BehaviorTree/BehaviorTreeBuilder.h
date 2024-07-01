//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			PlayerTreeBuilder.h
// <概要>			ビヘイビアツリーを作るクラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include<memory>
#include"Libraries/NakashiLib/BehaviorNode.h"

class BlackBoard;
class CommonResources;
namespace NakashiLib
{
	class IBehaviorNode;
}

class Crow;

class BehaviorTreeBuilder
{
public:
	BehaviorTreeBuilder(BlackBoard* blackboard , Crow* crow);
	~BehaviorTreeBuilder();
	std::unique_ptr<NakashiLib::IBehaviorNode> BuildTree();

	int GetNodeNumber() { return m_nodeNumber; }

private:
	// プレイヤーが近くにいる場合
	std::unique_ptr<NakashiLib::IBehaviorNode> CloseByPlayer();
	// プレイヤーが近くにいない場合
	std::unique_ptr<NakashiLib::IBehaviorNode> NotCloseByPlayer();

private:
	// ツリーノードの番号を知る
	int m_nodeNumber;
	// カラス取得用
	Crow* m_crow;
	// ブラックボードの取得用
	BlackBoard* m_blackBoard;
	// 共通ステート
	CommonResources* m_commonResources;
	// アタックしているかどうかのフラグ
	bool m_attackInProgress;

};