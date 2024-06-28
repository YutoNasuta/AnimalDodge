//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			PlayerTreeBuilder.cpp
// <�T�v>			�r�w�C�r�A�c���[�����N���X
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

	// �ŏ��̏��������
	auto root = std::make_unique<SequenceNode>();

	root->AddChild(std::make_unique<CrowStanding>(crow));
	root->AddChild(std::make_unique<CrowChase>(crow , m_blackBoard));

	return root;

}