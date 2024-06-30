//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/30
// <file>			SkySphere.h
// <概要>		　　ステージの空を作る
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
// 前方宣言
class CommonResources;

class SkySphere
{

private:
	// 共通ステート
	CommonResources* m_commonResources;
	// モデル取得用
	DirectX::Model* m_model;

public:
	SkySphere();
	~SkySphere();

	void SkyRender(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection);
};