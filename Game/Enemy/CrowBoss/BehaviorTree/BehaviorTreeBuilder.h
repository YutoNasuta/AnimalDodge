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
namespace NakashiLib
{
	class IBehaviorNode;
}

class Crow;

class BehaviorTreeBuilder
{
public:
	BehaviorTreeBuilder(BlackBoard* blackboard);
	~BehaviorTreeBuilder();
	std::unique_ptr<NakashiLib::IBehaviorNode> BuildTree(Crow* crow);

	int GetNodeNumber() { return m_nodeNumber; }

private:
	// �c���[�m�[�h�̔ԍ���m��
	int m_nodeNumber;
	BlackBoard* m_blackBoard;
};