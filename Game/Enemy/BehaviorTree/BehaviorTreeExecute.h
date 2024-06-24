//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			PlayerTreeExecute.h
// <�T�v>			�r�w�C�r�A�c���[�����s����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"


class BehaviorTreeExecute
{
public:
	// �R���X�g���N�^
	BehaviorTreeExecute(std::unique_ptr<NakashiLib::IBehaviorNode> root);
		
	// ���s����
	void Update();

	// ���Z�b�g����
	void Reset(std::unique_ptr<NakashiLib::IBehaviorNode> newRoot);

private:
	std::unique_ptr<NakashiLib::IBehaviorNode> behaviorTreeRoot;
};