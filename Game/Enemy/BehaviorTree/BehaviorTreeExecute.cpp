//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			PlayerTreeExecute.cpp
// <�T�v>			�r�w�C�r�A�c���[�����s����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"BehaviorTreeExecute.h"

/// <summary>
/// Builder�̃m�[�h���i�[����
/// </summary>
/// <param name="root">�m�[�h</param>
BehaviorTreeExecute::BehaviorTreeExecute(
	std::unique_ptr<NakashiLib::IBehaviorNode> root)
		: 
	behaviorTreeRoot(std::move(root)) 
{

}

/// <summary>
/// ���s����
/// </summary>
void BehaviorTreeExecute::Update() 
{
	if (behaviorTreeRoot) {
		behaviorTreeRoot->Execute();
	}
}

/// <summary>
/// ���Z�b�g����
/// </summary>
/// <param name="newRoot">�V�����m�[�h</param>
void BehaviorTreeExecute::Reset(
	std::unique_ptr<NakashiLib::IBehaviorNode> newRoot
)
{
	behaviorTreeRoot = std::move(newRoot);
}

