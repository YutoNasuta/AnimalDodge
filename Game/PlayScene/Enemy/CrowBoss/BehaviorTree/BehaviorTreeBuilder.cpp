//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			PlayerTreeBuilder.cpp
// <概要>			ビヘイビアツリーを作るクラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"BehaviorTreeBuilder.h"
#include"ActionNode/CrowStanding.h"
#include"ActionNode/CrowChasePlayer.h"
#include"Game/PlayScene/BlackBoard.h"
#include"ConditionNode/NearPlayerCheck.h"
BehaviorTreeBuilder::BehaviorTreeBuilder(BlackBoard* blackboard , Crow* crow)
	:
	m_nodeNumber{}
{
	m_blackBoard = blackboard;
	m_crow = crow;
}

BehaviorTreeBuilder::~BehaviorTreeBuilder()
{
	
}

std::unique_ptr<NakashiLib::IBehaviorNode> BehaviorTreeBuilder::BuildTree()
{
	using namespace NakashiLib;		

	// 最初の条件を作る
	auto root = std::make_unique<SequenceNode>();

	// プレイヤーが近くにいるかいないかを判定する
	auto isNearPlayerCheck = std::make_unique<NakashiLib::ContitionalBranchNode>(
		[this]() { return std::make_unique<NearPlayerCheck>(m_crow, m_blackBoard)->CheckNearPlayer(); },
		CloseByPlayer(),
		NotCloseByPlayer()
	);
	root->AddChild(std::move(isNearPlayerCheck));

	return root;

}

/// <summary>
/// プレイヤーが近くにいる
/// </summary>
std::unique_ptr<NakashiLib::IBehaviorNode> BehaviorTreeBuilder::CloseByPlayer()
{
	// 構造を増やす
	auto sequence = std::make_unique<NakashiLib::SequenceNode>();

	// プレイヤーを追う
	sequence->AddChild(std::make_unique<CrowChase>(m_crow, m_blackBoard));

	return sequence;
	
}

std::unique_ptr<NakashiLib::IBehaviorNode> BehaviorTreeBuilder::NotCloseByPlayer()
{

	auto sequence = std::make_unique<NakashiLib::SequenceNode>();

	sequence->AddChild(std::make_unique<CrowStanding>(m_crow));

	return sequence;
}