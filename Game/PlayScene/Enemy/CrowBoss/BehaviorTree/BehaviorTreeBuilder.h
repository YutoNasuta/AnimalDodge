//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			PlayerTreeBuilder.h
// <�T�v>			�r�w�C�r�A�c���[�����N���X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include<memory>
#include"Libraries/NakashiLib/BehaviorNode.h"

class BlackBoard;
class CommonResources;
namespace NakashiLib
{
	class IBehaviorNode;
}

class Crow;

class BehaviorTreeBuilder
{
public:
	BehaviorTreeBuilder(BlackBoard* blackboard , Crow* crow);
	~BehaviorTreeBuilder();
	std::unique_ptr<NakashiLib::IBehaviorNode> BuildTree();

	int GetNodeNumber() { return m_nodeNumber; }

private:
	// �v���C���[���߂��ɂ���ꍇ
	std::unique_ptr<NakashiLib::IBehaviorNode> CloseByPlayer();
	// �v���C���[���߂��ɂ��Ȃ��ꍇ
	std::unique_ptr<NakashiLib::IBehaviorNode> NotCloseByPlayer();

private:
	// �c���[�m�[�h�̔ԍ���m��
	int m_nodeNumber;
	// �J���X�擾�p
	Crow* m_crow;
	// �u���b�N�{�[�h�̎擾�p
	BlackBoard* m_blackBoard;
	// ���ʃX�e�[�g
	CommonResources* m_commonResources;
	// �A�^�b�N���Ă��邩�ǂ����̃t���O
	bool m_attackInProgress;

};