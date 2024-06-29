//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			Enemy.cpp
// <概要>			エネミーの中心核
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include "Crow.h"
#include"Game/Enemy/CrowBoss/Parts/CrowHead.h"
#include "Game/CommonResources.h"
#include "Libraries/NakashiLib/InputManager.h"
#include"Game/Enemy/CrowBoss/BehaviorTree/BehaviorTreeBuilder.h"
#include"Game/Enemy/CrowBoss/BehaviorTree/BehaviorTreeExecute.h"
#include"Game/BlackBoard.h"

Crow::Crow(IComponent* parent,
    const DirectX::SimpleMath::Vector3& position,
    const DirectX::SimpleMath::Quaternion& quaternion,
    BlackBoard* blackboard
)
    :
    CrowBase(parent , position , quaternion),
    m_commonResources{},
    m_partID{CrowBase::PartID::ROOT} ,
    m_position{position},
    m_velocity{},
    Number{ 1 }, 
    Debug{ 1 },
    m_head{},
    m_mass{}
{
    m_commonResources = CommonResources::GetInstance();
    m_blackBoard = blackboard;
}

Crow::~Crow()
{

}

void Crow::Initialize()
{


    CrowBase::Initialize();				// ベースの初期化を呼ぶ

    auto head = std::make_unique<CrowHead>(				// プレイヤーボディを作成
        this,
        DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
        DirectX::SimpleMath::Quaternion::Identity
    );
    m_head = head.get();									// 呼び出し用bodyに格納
    SetChild(std::move(head));					// プレイヤーの子にbodyを設定

    m_behaviorTreeBuilder = std::make_unique<BehaviorTreeBuilder>(m_blackBoard , this);
    auto tree =  m_behaviorTreeBuilder->BuildTree();
    m_behaviorExecutor = std::make_unique<BehaviorTreeExecute>(std::move(tree));

    m_crowBoundingSphere = CreateBoundingSphere(1.0f);	// 境界球の作成
}

void Crow::Update(
 
    const DirectX::SimpleMath::Vector3& position,
    const DirectX::SimpleMath::Quaternion& quaternion
)
{
    CrowBase::Update(
      
        m_position + GetInitialPosition(),
        m_quaternion
    );

    m_behaviorExecutor->Update();
 
    m_crowBoundingSphere.Center = m_position;

    Number = m_behaviorTreeBuilder->GetNodeNumber();
}


void Crow::Render(
    const DirectX::SimpleMath::Matrix& view,
    const DirectX::SimpleMath::Matrix& projection
)
{
    CrowBase::Render(view, projection);
}

DirectX::BoundingSphere Crow::CreateBoundingSphere(const float& radius)
{
    // 境界球を宣言する
    DirectX::BoundingSphere turretBoundingSphere;
    // 境界球の半径を設定する
    turretBoundingSphere.Radius = radius;
    // 境界球を返す
    return turretBoundingSphere;
}