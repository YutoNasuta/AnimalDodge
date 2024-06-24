//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			PlayerTreeExecute.h
// <概要>			ビヘイビアツリーを実行する
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"


class BehaviorTreeExecute
{
public:
	// コンストラクタ
	BehaviorTreeExecute(std::unique_ptr<NakashiLib::IBehaviorNode> root);
		
	// 実行する
	void Update();

	// リセットする
	void Reset(std::unique_ptr<NakashiLib::IBehaviorNode> newRoot);

private:
	std::unique_ptr<NakashiLib::IBehaviorNode> behaviorTreeRoot;
};