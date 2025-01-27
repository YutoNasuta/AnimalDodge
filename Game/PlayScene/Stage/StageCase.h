//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/18
// <file>			StageCase.h
// <概要>		　　ステージの枠
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

class CommonResources;
class Graphics;
class StageCase
{
private:
	// 共通ステート
	CommonResources* m_commonResources;
	Graphics* m_graphics;
	// バウンディングボックス
	DirectX::BoundingBox m_stageCaseBoundingBox;

	// 描画用
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// 壁のモデル取得
	DirectX::Model* m_model;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_boxSize;

public:
	// コンストラクタとデストラクタ
	StageCase();
	~StageCase();

	void Initialize();
	void Update();
	void BoundingBoxRender();
	void DrawModel(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection);
	

	void SetPosition(
		DirectX::SimpleMath::Vector3& position, 
		DirectX::SimpleMath::Vector3& boxSize);



	DirectX::BoundingBox GetBoundingBox() const { return m_stageCaseBoundingBox; }

	
};