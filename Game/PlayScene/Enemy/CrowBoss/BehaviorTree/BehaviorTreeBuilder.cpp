//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			PlayerTreeBuilder.cpp
// <概要>			ビヘイビアツリーを作るクラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"BehaviorTreeBuilder.h"
#include"Game/PlayScene/Enemy/CrowBoss/Crow.h"
#include"ActionNode/CrowStanding.h"
#include"ActionNode/CrowChasePlayer.h"
#include"Game/PlayScene/BlackBoard.h"
#include"ConditionNode/NearPlayerCheck.h"
#include"ActionNode/CrowAttackPlayer.h"
#include"Game/CommonResources.h"
#include"Framework/StepTimer.h"
BehaviorTreeBuilder::BehaviorTreeBuilder(BlackBoard* blackboard , Crow* crow)
	:
	m_nodeNumber{},
	m_attackInProgress(false)
{
	m_blackBoard = blackboard;
	m_crow = crow;
	m_commonResources = CommonResources::GetInstance();
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
	using namespace NakashiLib;

	// 構造を増やす
	auto sequence = std::make_unique<SequenceNode>();

	auto persistentRandomSelector = std::make_unique<PersistentRandomSelectorNode>();

	persistentRandomSelector->AddChild(std::make_unique<CrowChase>(m_crow, m_blackBoard));
	persistentRandomSelector->AddChild(std::make_unique<CrowAttackPlayer>(m_crow, m_blackBoard));

	sequence->AddChild(std::move(persistentRandomSelector));

	return sequence;
	
}

/// <summary>
/// プレイヤーが近くにいない
/// </summary>
std::unique_ptr<NakashiLib::IBehaviorNode> BehaviorTreeBuilder::NotCloseByPlayer()
{
	// 構造を増やす
	auto sequence = std::make_unique<NakashiLib::SequenceNode>();
	// 待機する
	sequence->AddChild(std::make_unique<CrowStanding>(m_crow));

	return sequence;
}