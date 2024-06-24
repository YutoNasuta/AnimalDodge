//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			PlayerTreeExecute.cpp
// <概要>			ビヘイビアツリーを実行する
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"BehaviorTreeExecute.h"

/// <summary>
/// Builderのノードを格納する
/// </summary>
/// <param name="root">ノード</param>
BehaviorTreeExecute::BehaviorTreeExecute(
	std::unique_ptr<NakashiLib::IBehaviorNode> root)
		: 
	behaviorTreeRoot(std::move(root)) 
{

}

/// <summary>
/// 実行する
/// </summary>
void BehaviorTreeExecute::Update() 
{
	if (behaviorTreeRoot) {
		behaviorTreeRoot->Execute();
	}
}

/// <summary>
/// リセットする
/// </summary>
/// <param name="newRoot">新しいノード</param>
void BehaviorTreeExecute::Reset(
	std::unique_ptr<NakashiLib::IBehaviorNode> newRoot
)
{
	behaviorTreeRoot = std::move(newRoot);
}

