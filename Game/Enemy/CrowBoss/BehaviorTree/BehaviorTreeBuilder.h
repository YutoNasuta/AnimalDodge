//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			PlayerTreeBuilder.h
// <概要>			ビヘイビアツリーを作るクラス
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
	// ツリーノードの番号を知る
	int m_nodeNumber;
	BlackBoard* m_blackBoard;
};