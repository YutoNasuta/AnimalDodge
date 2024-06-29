//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			CrowHead.cpp
// <概要>			プレイヤーの胴体パーツ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CrowHead.h"
#include"Interface/IComponent.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
#include"Game/CommonResources.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowLeftWing.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowRightWing.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowLeftLeg.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowRightLeg.h"
#include"Libraries/NakashiLib/InputManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
CrowHead::CrowHead(
	IComponent* parent, 
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& quaternion
)
	: CrowBase(parent , position ,quaternion),
	m_commonResources{},
	m_partID{CrowBase::PartID::BODY},
	m_model{},
	m_position{},
	m_velocity{},
	m_quaternion{},
	m_mass{},
	m_worldMatrix{},
	m_rightWing{},
	m_leftWing{},
	m_rightLeg{},
	m_leftLeg{},
	m_addQuaternion{},
	m_nodeNumber{1}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
CrowHead::~CrowHead()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void CrowHead::Initialize()
{

	ModelInitialize();
	ChildInitialize();

	// 基底クラスのInitialize呼び出し
	CrowBase::Initialize(m_nodeNumber , m_model);
}

/// <summary>
/// 子供の初期化
/// </summary>
void CrowHead::ChildInitialize()
{
	// 羽を子オブジェクトに
	auto rightWing =
		std::make_unique<CrowRightWing>(
			this,
			DirectX::SimpleMath::Vector3(-5.0f, 5.0f, 0.0f),
			DirectX::SimpleMath::Quaternion::Identity);
	m_rightWing = rightWing.get();
	SetChild(std::move(rightWing));

	auto leftWing =
		std::make_unique<CrowLeftWing>(
			this,
			DirectX::SimpleMath::Vector3(5.0f, 5.0f, 0.0f),
			DirectX::SimpleMath::Quaternion::Identity);
	m_leftWing = leftWing.get();
	SetChild(std::move(leftWing));

	// 足を子オブジェクトに
	auto rightLeg = std::make_unique<CrowRightLeg>(
		this,
		DirectX::SimpleMath::Vector3(-2.0f, 0.0f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity);
	m_rightLeg = rightLeg.get();
	SetChild(std::move(rightLeg));

	auto leftLeg = std::make_unique<CrowLeftLeg>(
		this,
		DirectX::SimpleMath::Vector3(2.0f, 0.0f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity);
	m_leftLeg = leftLeg.get();
	SetChild(std::move(leftLeg));
}

/// <summary>
/// モデルの初期化
/// </summary>
void CrowHead::ModelInitialize()
{
	//m_commonResources->GetResourcesManager()->CreateModel(L"CrowHead", L"CrowHead.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyLeftHand", L"EnemyLeftHand.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"CrowHead", L"CrowHead.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyLeg", L"EnemyLeg.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyRightHand", L"EnemyRightHand.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyTail", L"EnemyTail.cmo");
	m_model = m_commonResources->GetResourcesManager()->GetModel(L"CrowHead");
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">時間</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
void CrowHead::Update(
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

	m_worldMatrix =
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_addQuaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(GetInitialPosition())
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_quaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(m_position)
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetInitialQuaternion());
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">カメラのビュー</param>
/// <param name="projection">カメラの投影</param>
void CrowHead::Render(
const DirectX::SimpleMath::Matrix& view ,
const DirectX::SimpleMath::Matrix& projection
)
{
	CrowBase::Render(m_worldMatrix, view, projection);
}

/// <summary>
/// 後処理
/// </summary>
void CrowHead::Finalize()
{
}

