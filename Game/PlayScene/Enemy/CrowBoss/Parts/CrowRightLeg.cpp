//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			CrowRightLeg.cpp
// <概要>		　　プレイヤーの足パーツ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CrowRightLeg.h"
#include"Interface/IComponent.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
#include"Game/CommonResources.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
CrowRightLeg::CrowRightLeg(
	IComponent* parent, 
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& quaternion
)
	: CrowBase(parent , position ,quaternion),
	m_commonResources{},
	m_partID{CrowBase::PartID::LEG_RIGHT},
	m_model{},
	m_position{},
	m_velocity{},
	m_quaternion{},
	m_mass{},
	m_worldMatrix{},
	m_nodeNumber{1}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
CrowRightLeg::~CrowRightLeg()
{
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="resources">共通リソース</param>
void CrowRightLeg::Initialize()
{


	m_model = m_commonResources->GetResourcesManager()->GetModel(L"CrowLeg");


	// 基底クラスのInitialize呼び出し
	CrowBase::Initialize(m_nodeNumber , m_model);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">時間</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
void CrowRightLeg::Update(
	const DirectX::SimpleMath::Vector3& position , 
	const DirectX::SimpleMath::Quaternion& quaternion)
{

	DirectX::SimpleMath::Vector3 localPosition = position;
	DirectX::SimpleMath::Quaternion localQuaternion = m_quaternion;

	localPosition += m_velocity;
	m_position = localPosition;

	m_quaternion = quaternion;			// 現在の回転角を更新する

	CrowBase::Update(
		m_position,
		m_quaternion);

	m_worldMatrix 				//行列の変更
		= DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_addQuaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(GetInitialPosition())
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_quaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">カメラのビュー</param>
/// <param name="projection">カメラの投影</param>
void CrowRightLeg::Render(
const DirectX::SimpleMath::Matrix& view ,
const DirectX::SimpleMath::Matrix& projection
)
{
	CrowBase::Render(m_worldMatrix, view, projection);
}

/// <summary>
/// 後処理
/// </summary>
void CrowRightLeg::Finalize()
{
}