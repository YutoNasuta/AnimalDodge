//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/30
// <file>			SkySphere.h
// <概要>		　　ステージの空を作る
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"SkySphere.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
#include "Framework/DeviceResources.h"

/// <summary>
/// コンストラクタ
/// </summary>
SkySphere::SkySphere()
{
	m_commonResources = CommonResources::GetInstance();
	m_model = m_commonResources->GetResourcesManager()->GetModel(L"Sky");
}

/// <summary>
/// デストラクタ
/// </summary>
SkySphere::~SkySphere()
{

}

void SkySphere::SkyRender(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection)
{

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	m_model->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ベーシックエフェクトの設定
			DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				// 個別ライトの無効化
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// モデルを自発光させる
				basicEffect->SetEmissiveColor(DirectX::Colors::White);
			}
		});

	// ワールド行列の更新
	DirectX::SimpleMath::Matrix world 
		= DirectX::SimpleMath::Matrix::Identity
		* DirectX::SimpleMath::Matrix::CreateScale(5);

	// モデルの描画
	m_model->Draw(context, *states, world, view, projection);

}
