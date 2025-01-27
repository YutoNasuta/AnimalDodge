//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			PlayerBody.cpp
// <概要>			プレイヤーの胴体パーツ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerBody.h"
#include"Interface/IComponent.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
#include"Game/CommonResources.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerHead.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerRightHand.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerLeg.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerTail.h"
#include"Game/PlayScene/Factory/PlayerFactory.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
PlayerBody::PlayerBody(
	IComponent* parent, 
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& quaternion
)
	: PlayerBase(parent , position ,quaternion),
	m_commonResources{},
	m_partID{PlayerBase::PartID::BODY},
	m_model{},
	m_position{},
	m_velocity{},
	m_quaternion{},
	m_mass{},
	m_worldMatrix{},
	m_rightHand{},
	m_leftHand{},
	m_leg{},
	m_head{},
	m_tail{},
	m_addQuaternion{},
	m_nodeNumber{0}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerBody::~PlayerBody()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void PlayerBody::Initialize()
{

	ModelInitialize();
	ChildInitialize();

	// 基底クラスのInitialize呼び出し
	PlayerBase::Initialize(m_nodeNumber , m_model);
}

/// <summary>
/// 子供の初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void PlayerBody::ChildInitialize()
{
	
	// 右腕を子オブジェクトに
	auto rightHand = std::make_unique<PlayerRightHand>(
		this,
		DirectX::SimpleMath::Vector3(-1.0f, 0.5f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity);
	m_rightHand =(rightHand.get());
	SetChild(std::move(rightHand));

	auto leftHand =
		std::make_unique<PlayerLeftHand>(
			this,
			DirectX::SimpleMath::Vector3(1.0f, 0.5f, 0.0f),
			DirectX::SimpleMath::Quaternion::Identity);
	m_leftHand = leftHand.get();
	SetChild(std::move(leftHand));

	// 足を子オブジェクトに
	auto leg = std::make_unique<PlayerLeg>(
		this,
		DirectX::SimpleMath::Vector3(0.0f, -0.6f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity);
	m_leg = leg.get();
	SetChild(std::move(leg));

	// 頭を子オブジェクトに
	auto Head = std::make_unique<PlayerHead>(
		this,
		DirectX::SimpleMath::Vector3(0.0f, 0.9f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity);

	m_head = Head.get();
	SetChild(std::move(Head));

	// しっぽを子オブジェクトに
	auto Tail = std::make_unique<PlayerTail>(
		this,
		DirectX::SimpleMath::Vector3(0.0f, -0.5f, -0.8f),
		DirectX::SimpleMath::Quaternion::Identity);
	m_tail = Tail.get();
	SetChild(std::move(Tail));
}

/// <summary>
/// モデルの初期化
/// </summary>
void PlayerBody::ModelInitialize()
{
	m_model = m_commonResources->GetResourcesManager()->GetModel(L"PlayerBody");
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">時間</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
void PlayerBody::Update(
	const DirectX::SimpleMath::Vector3& position , 
	const DirectX::SimpleMath::Quaternion& quaternion)
{


	DirectX::SimpleMath::Vector3 localPosition = position;
	DirectX::SimpleMath::Quaternion localQuaternion = m_quaternion;

	localPosition += m_velocity;
	m_position = localPosition;

	m_quaternion = quaternion;			// 現在の回転角を更新する

	PlayerBase::Update(
		m_position,
		m_quaternion);

	m_worldMatrix =
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_addQuaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(GetInitialPosition())
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(quaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(position)
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetInitialQuaternion());
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">カメラのビュー</param>
/// <param name="projection">カメラの投影</param>
void PlayerBody::Render(
const DirectX::SimpleMath::Matrix& view ,
const DirectX::SimpleMath::Matrix& projection
)
{
	PlayerBase::Render(m_worldMatrix, view, projection);
}

/// <summary>
/// 後処理
/// </summary>
void PlayerBody::Finalize()
{
}

