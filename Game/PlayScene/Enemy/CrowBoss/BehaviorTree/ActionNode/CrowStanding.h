//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			CrowStanding.h
// <�T�v>			�G�l�~�[�̗������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"
#include"Game/CommonResources.h"
class Crow;

class CrowStanding : public NakashiLib::ActionNode
{


public:
	// �R���X�g���N�^
	CrowStanding(Crow* crow);
	// ���s����
	bool Execute() override;

private:
	// �G�l�~�[�擾
	Crow* m_crow;
	CommonResources* m_commonResources;

	float m_timeExit;
	const float EXITTIME = 10;

	void MoveParts();
	void MoveHand();
};