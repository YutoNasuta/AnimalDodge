//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/30
// <file>			CrowUpperBeak.h
// <概要>		　　エネミーの上嘴
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CrowUpperBeak.h"
#include"Interface/IComponent.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
#include"Game/CommonResources.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
CrowUpperBeak::CrowUpperBeak(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& quaternion
)
	: CrowBase(parent, position, quaternion),
	m_commonResources{},
	m_partID{ CrowBase::PartID::BEAK_UPPER },
	m_model{},
	m_position{},
	m_velocity{},
	m_quaternion{},
	m_mass{},
	m_worldMatrix{},
	m_nodeNumber{ 1 }
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
CrowUpperBeak::~CrowUpperBeak()
{
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="resources"></param>
void CrowUpperBeak::Initialize()
{
	m_model = m_commonResources->GetResourcesManager()->GetModel(L"CrowUpperBeak");	//モデル取得

	CrowBase::Initialize(m_nodeNumber, m_model);	// 基底クラスのInitialize呼び出し
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">時間</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
void CrowUpperBeak::Update(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& quaternion)
{

	DirectX::SimpleMath::Vector3 localPosition = position;
	DirectX::SimpleMath::Quaternion localQuaternion = quaternion;

	localPosition += m_velocity;
	m_position = localPosition;

	m_quaternion = quaternion;			// 現在の回転角を更新する

	CrowBase::Update(			//ベースを更新
		m_position,
		m_quaternion);

	m_worldMatrix 				//行列の変更
		= DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, -0.5f, 0.0f))
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_addQuaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(GetInitialPosition())
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_quaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(m_position);


}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">カメラのビュー</param>
/// <param name="projection">カメラの投影</param>
void CrowUpperBeak::Render(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	CrowBase::Render(m_worldMatrix, view, projection);
}

/// <summary>
/// 後処理
/// </summary>
void CrowUpperBeak::Finalize()
{

}