//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			Crow.h
// <�T�v>			�G�l�~�[�̒��S�j
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IComponent.h"
#include"Game/Enemy/CrowBoss/CrowBase.h"

class CommonResources;

class CrowHead;

class BehaviorTreeBuilder;

class BlackBoard;

class BehaviorTreeExecute;


class Crow : public CrowBase 
{
public:
    // �C���^�t�F�[�X�p++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }						// ���݂̈ʒu���擾����
    void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; }		// ���݂̈ʒu��ݒ肷��

    DirectX::SimpleMath::Quaternion GetQuaternion() const override { return m_quaternion; }						//  ���݂̉�]�p���擾����
    void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion)override { m_quaternion = quaternion; }		// ���݂̉�]�p��ݒ肷��

    float GetMass() const override { return m_mass; }				// ���ʂ�ݒ�
    void SetMass(const float& mass) override { m_mass = mass; }		// ���ʂ�ݒ�



    CrowHead* GetHead() const { return m_head; }

public: //�v���p�e�B

    DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
    void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }

    DirectX::BoundingSphere GetBoundingSphere() { return m_crowBoundingSphere; }
    void SetBoundingSphereCenter(DirectX::SimpleMath::Vector3 boundingSphere) { m_crowBoundingSphere.Center = boundingSphere; }
public:
    Crow(
        IComponent* parent,
        const DirectX::SimpleMath::Vector3& position,
        const DirectX::SimpleMath::Quaternion& quaternion,
        BlackBoard* blackboard);
    ~Crow();

    void Initialize() override;
    void Update(
   
        const DirectX::SimpleMath::Vector3& position,
        const DirectX::SimpleMath::Quaternion& quaternion) override;

    // �`�悷��
    void Render(
        const DirectX::SimpleMath::Matrix& view,
        const DirectX::SimpleMath::Matrix& projection) override;

    const float GetNumber() const { return Number; }
    void SetDebug(float value) { Debug = value; }
    const float GetDebug() const { return Debug; }

    // ���E�����쐬
    DirectX::BoundingSphere CreateBoundingSphere(const float& radius);

private:
    // ���ʃ��\�[�X
    CommonResources* m_commonResources;

    // �u���b�N�{�[�h
    BlackBoard* m_blackBoard;

    float Number;
    float Debug;

    //  �v���C���[�̏��+++++++++++++++++++++++++++++++++++++++++++
    int m_partID;								 //ID
    DirectX::SimpleMath::Vector3 m_position;	 //  ���݂̈ʒu
    DirectX::SimpleMath::Vector3 m_velocity;	 //  ���݂̑��x
    DirectX::SimpleMath::Quaternion m_quaternion;//  ���݂̉�]�p
    DirectX::SimpleMath::Matrix m_worldMatrix;   //  ���[���h�s�� 
    DirectX::SimpleMath::Vector3 m_friction;	 //�@���C
    float m_mass;								 //  ����
    DirectX::SimpleMath::Vector3 m_acceleration; //  �����x
    DirectX::SimpleMath::Vector3 m_gravity;      //�@�d��
    bool m_ballTaking;							 // �{�[���������Ă����Ԃ������Ă��Ȃ���Ԃ�
    float m_forceCharge;						 // �{�[���̃`���[�W��

    // �r�w�C�r�A�c���[�m�[�h���s�p
    std::unique_ptr<BehaviorTreeBuilder> m_behaviorTreeBuilder;
    std::unique_ptr<BehaviorTreeExecute> m_behaviorExecutor;

    CrowHead* m_head;

    DirectX::BoundingSphere m_crowBoundingSphere;			// �v���C���[�����蔻�苅
    DirectX::SimpleMath::Vector3 m_CrowCenter;			// �v���C���[�̒��S
};