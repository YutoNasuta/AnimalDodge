//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			PlayerTreeBuilder.cpp
// <概要>			ビヘイビアツリーを作るクラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"BehaviorTreeBuilder.h"
#include"State/EnemyStanding.h"
#include"State/EnemyChasePlayer.h"
#include"Game/BlackBoard.h"

BehaviorTreeBuilder::BehaviorTreeBuilder(BlackBoard* blackboard)
{
	m_blackBoard = blackboard;
}

BehaviorTreeBuilder::~BehaviorTreeBuilder()
{
	
}

std::unique_ptr<NakashiLib::IBehaviorNode> BehaviorTreeBuilder::BuildTree(Enemy* enemy)
{
	using namespace NakashiLib;		

	// 最初の条件を作る
	auto root = std::make_unique<SequenceNode>();

	root->AddChild(std::make_unique<EnemyStanding>(enemy));
	root->AddChild(std::make_unique<EnemyChase>(enemy , m_blackBoard));

	return root;

}