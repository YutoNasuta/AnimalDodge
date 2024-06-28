//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			PlayerTreeBuilder.cpp
// <概要>			ビヘイビアツリーを作るクラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"BehaviorTreeBuilder.h"
#include"State/CrowStanding.h"
#include"State/CrowChasePlayer.h"
#include"Game/BlackBoard.h"

BehaviorTreeBuilder::BehaviorTreeBuilder(BlackBoard* blackboard)
	:
	m_nodeNumber{}
{
	m_blackBoard = blackboard;
}

BehaviorTreeBuilder::~BehaviorTreeBuilder()
{
	
}

std::unique_ptr<NakashiLib::IBehaviorNode> BehaviorTreeBuilder::BuildTree(Crow* crow)
{
	using namespace NakashiLib;		

	// 最初の条件を作る
	auto root = std::make_unique<SequenceNode>();

	root->AddChild(std::make_unique<CrowStanding>(crow));
	root->AddChild(std::make_unique<CrowChase>(crow , m_blackBoard));

	return root;

}