//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/21
// <file>			CrowStanding.h
// <�T�v>			�G�l�~�[���v���C���[��ǂ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"
#include"Game/CommonResources.h"
class Crow;
class BlackBoard;

class CrowChase : public NakashiLib::ActionNode
{


public:
	// �R���X�g���N�^
	CrowChase(Crow* Crow , BlackBoard* blackboard);
	// ���s����
	bool Execute() override;

private:
	// �G�l�~�[�擾
	Crow* m_crow;
	CommonResources* m_commonResources;
	BlackBoard* m_blackBoard;

	float m_timeExit;
	const float EXITTIME = 10;

	void MoveParts();
	void MoveHand();
	void Chase();
};
