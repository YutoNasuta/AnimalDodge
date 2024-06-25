//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			Enemy.cpp
// <�T�v>			�G�l�~�[�̒��S�j
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include "Enemy.h"
#include"Game/Enemy/Parts/EnemyBody.h"
#include "Game/CommonResources.h"
#include "Libraries/NakashiLib/InputManager.h"
#include"Game/Enemy/BehaviorTree/BehaviorTreeBuilder.h"
#include"Game/Enemy/BehaviorTree/BehaviorTreeExecute.h"
#include"Game/BlackBoard.h"

Enemy::Enemy(IComponent* parent,
    const DirectX::SimpleMath::Vector3& position,
    const DirectX::SimpleMath::Quaternion& quaternion,
    BlackBoard* blackboard
)
    :
    EnemyBase(parent , position , quaternion),
    m_commonResources{},
    m_partID{EnemyBase::PartID::ROOT} ,
    m_position{position},
    m_velocity{},
    Number{ 1 }, 
    Debug{ 1 },
    m_ballTaking{},
    m_body{},
    m_mass{}
{
    m_commonResources = CommonResources::GetInstance();
    m_blackBoard = blackboard;
}

Enemy::~Enemy()
{

}

void Enemy::Initialize() 
{


    EnemyBase::Initialize();				// �x�[�X�̏��������Ă�

    auto body = std::make_unique<EnemyBody>(				// �v���C���[�{�f�B���쐬
        this,
        DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
        DirectX::SimpleMath::Quaternion::Identity
    );
    m_body = body.get();									// �Ăяo���pbody�Ɋi�[
    SetChild(std::move(body));					// �v���C���[�̎q��body��ݒ�

    m_behaviorTreeBuilder = std::make_unique<BehaviorTreeBuilder>(m_blackBoard);
    auto tree =  m_behaviorTreeBuilder->BuildTree(this);
    m_behaviorExecutor = std::make_unique<BehaviorTreeExecute>(std::move(tree));

    m_enemyBoundingSphere = CreateBoundingSphere(1.0f);	// ���E���̍쐬
}

void Enemy::Update(
 
    const DirectX::SimpleMath::Vector3& position,
    const DirectX::SimpleMath::Quaternion& quaternion
)
{
    EnemyBase::Update(
      
        m_position + GetInitialPosition(),
        m_quaternion
    );

    m_behaviorExecutor->Update();
 
    m_enemyBoundingSphere.Center = m_position;
}


void Enemy::Render(
    const DirectX::SimpleMath::Matrix& view,
    const DirectX::SimpleMath::Matrix& projection
)
{
    EnemyBase::Render(view, projection);
}

DirectX::BoundingSphere Enemy::CreateBoundingSphere(const float& radius)
{
    // ���E����錾����
    DirectX::BoundingSphere turretBoundingSphere;
    // ���E���̔��a��ݒ肷��
    turretBoundingSphere.Radius = radius;
    // ���E����Ԃ�
    return turretBoundingSphere;
}