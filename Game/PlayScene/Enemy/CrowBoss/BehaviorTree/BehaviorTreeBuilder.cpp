//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			PlayerTreeBuilder.cpp
// <�T�v>			�r�w�C�r�A�c���[�����N���X
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

	// �ŏ��̏��������
	auto root = std::make_unique<SequenceNode>();

	// �v���C���[���߂��ɂ��邩���Ȃ����𔻒肷��
	auto isNearPlayerCheck = std::make_unique<NakashiLib::ContitionalBranchNode>(
		[this]() { return std::make_unique<NearPlayerCheck>(m_crow, m_blackBoard)->CheckNearPlayer(); },
		CloseByPlayer(),
		NotCloseByPlayer()
	);
	root->AddChild(std::move(isNearPlayerCheck));

	return root;

}

/// <summary>
/// �v���C���[���߂��ɂ���
/// </summary>
std::unique_ptr<NakashiLib::IBehaviorNode> BehaviorTreeBuilder::CloseByPlayer()
{
	// �\���𑝂₷
	auto sequence = std::make_unique<NakashiLib::SequenceNode>();

	// �v���C���[��ǂ�
	sequence->AddChild(std::make_unique<CrowChase>(m_crow, m_blackBoard));

	return sequence;
	
}

std::unique_ptr<NakashiLib::IBehaviorNode> BehaviorTreeBuilder::NotCloseByPlayer()
{

	auto sequence = std::make_unique<NakashiLib::SequenceNode>();

	sequence->AddChild(std::make_unique<CrowStanding>(m_crow));

	return sequence;
}