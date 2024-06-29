//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/29
// <file>			NearPlayerCheck.h
// <�T�v>			�߂��Ƀv���C���[�����邩�ǂ�������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"

// �O���錾
class Crow;
class BlackBoard;

class NearPlayerCheck : public NakashiLib::ConditionNode
{
public:
	// �R���X�g���N�^
	NearPlayerCheck(Crow* Crow, BlackBoard* blackboard);
	// �f�X�g���N�^
	~NearPlayerCheck();
	// �v���C���[���߂��ɂ��邩�ǂ�����Ԃ�
	bool CheckNearPlayer();

private:


	// �G�l�~�[�擾
	Crow* m_crow;
	// �u���b�N�{�[�h�̎擾
	BlackBoard* m_blackBoard;
};