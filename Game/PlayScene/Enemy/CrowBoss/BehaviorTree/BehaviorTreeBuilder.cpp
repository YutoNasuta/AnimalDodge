//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			PlayerTreeBuilder.cpp
// <�T�v>			�r�w�C�r�A�c���[�����N���X
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
	using namespace NakashiLib;

	// �\���𑝂₷
	auto sequence = std::make_unique<SequenceNode>();

	auto persistentRandomSelector = std::make_unique<PersistentRandomSelectorNode>();

	persistentRandomSelector->AddChild(std::make_unique<CrowChase>(m_crow, m_blackBoard));
	persistentRandomSelector->AddChild(std::make_unique<CrowAttackPlayer>(m_crow, m_blackBoard));

	sequence->AddChild(std::move(persistentRandomSelector));

	return sequence;
	
}

/// <summary>
/// �v���C���[���߂��ɂ��Ȃ�
/// </summary>
std::unique_ptr<NakashiLib::IBehaviorNode> BehaviorTreeBuilder::NotCloseByPlayer()
{
	// �\���𑝂₷
	auto sequence = std::make_unique<NakashiLib::SequenceNode>();
	// �ҋ@����
	sequence->AddChild(std::make_unique<CrowStanding>(m_crow));

	return sequence;
}