//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/18
// <file>			StageCase.cpp
// <概要>		　　ステージの枠
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"StageCase.h"
#include"Game/CommonResources.h"
#include"Framework/DeviceResources.h"
#include "Libraries/Microsoft/DebugDraw.h"
#include"Framework/Graphics.h"
#include"Libraries/NakashiLib/ResourcesManager.h"

StageCase::StageCase()
	:
	m_stageCaseBoundingBox{}
{
	m_commonResources = CommonResources::GetInstance();
	m_graphics = Graphics::GetInstance();
}

StageCase::~StageCase()
{

}

void StageCase::Initialize()
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(true);

	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPositionColor>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	m_model = m_commonResources->GetResourcesManager()->GetModel(L"Wall");
}


void StageCase::Update()
{

}

void StageCase::BoundingBoxRender()
{
	m_primitiveBatch->Begin();
	DX::Draw(m_primitiveBatch.get(), m_stageCaseBoundingBox);
	m_primitiveBatch->End();
}

void StageCase::DrawModel(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection)
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	DirectX::SimpleMath::Matrix world
		= DirectX::SimpleMath::Matrix::CreateScale(m_boxSize / 2)
		* DirectX::SimpleMath::Matrix::CreateTranslation(m_position - DirectX::SimpleMath::Vector3(0.0f, 25.0f, 0.0f));

	// モデルの描画
	m_model->Draw(context, *states, world, view, projection);
}

/// <summary>
/// バウンディングボックスを作る
/// </summary>
/// <param name="position">ポジション</param>
/// <param name="boxSize">ボックスのサイズを決める</param>
void StageCase::SetPosition(
	DirectX::SimpleMath::Vector3& position,
	DirectX::SimpleMath::Vector3& boxSize)
{

	m_position = position;
	m_boxSize = boxSize / 2;

	m_stageCaseBoundingBox
		= DirectX::BoundingBox(
			DirectX::SimpleMath::Vector3(m_position),
			DirectX::SimpleMath::Vector3(m_boxSize)
		);
}