//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/07/01
// <file>			CrowAttackPlayer.h
// <�T�v>			�J���X���v���C���[���U������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"
#include"Game/CommonResources.h"

class Crow;
class BlackBoard;

class CrowAttackPlayer : public NakashiLib::ActionNode
{
public:
	// �R���X�g���N�^
	CrowAttackPlayer(Crow* crow, BlackBoard* blackBoard);
	// ���s����
	bool Execute() override;

private:
	// �J���X�擾
	Crow* m_crow;
	CommonResources* m_commonResources;
	BlackBoard* m_blackBoard;

	float m_timeExit;
	const float EXITTIME = 10;

	float m_startTime;

	void MoveParts();
	void MoveHand();

};