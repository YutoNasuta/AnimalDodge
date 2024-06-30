//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			CrowHead.h
// <�T�v>			�v���C���[�̓��̃p�[�c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Game/PlayScene/Enemy/CrowBoss/CrowBase.h"
#include"Framework/DeviceResources.h"

// �O���錾
class CommonResources;
class CrowRightWing;
class CrowLeftWing;
class CrowLeftLeg;
class CrowRightLeg;

class CrowHead : public CrowBase
{
public:

	// ���݂̈ʒu���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	// ���݂̈ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; }
	// ���݂̉�]�p���擾����
	DirectX::SimpleMath::Quaternion GetQuaternion() const  override { return m_quaternion; }
	// ���݂̉�]�p��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion) override { m_quaternion = quaternion; }
	// ���ʂ��擾
	float GetMass() const override { return m_mass; }
	// ���ʂ�ݒ�
	void SetMass(const float& mass) override { m_mass = mass; }


	DirectX::Model* GetModel() override { return m_model; }

	// ���x�擾
	DirectX::SimpleMath::Vector3 GetVelocity()const {return m_velocity;};
	// ���x�ݒ�
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }

	void SetAddQuaternion(const DirectX::SimpleMath::Quaternion& quaternion) { m_addQuaternion = quaternion; }
	DirectX::SimpleMath::Quaternion GetAddQuaternion() const { return m_addQuaternion; }


	// �q�擾�p
	CrowRightWing* GetRightWing() const { return m_rightWing; }
	CrowLeftWing* GetLeftWing() const { return m_leftWing; }
	CrowLeftLeg* GetLeftLeg() const { return m_leftLeg; }
	CrowRightLeg* GetRightLeg() const { return m_rightLeg; }

public:
	// �R���X�g���N�^
	CrowHead(IComponent* parent, 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion);
	// �f�X�g���N�^
	 ~CrowHead() ;
	// ����������
	void Initialize() override;
	// �q�p�[�c�������p
	void ChildInitialize();
	void ModelInitialize();
	// �X�V����
	void Update(
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion) override;
	// �`�悷��
	void Render(const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection) override;
	// �㏈�����s��
	void Finalize();
	
private:
	// ����
	CommonResources* m_commonResources;
	// ���iID
	int m_partID;
	// ���f��
	DirectX::Model* m_model;	
	// ���݂̈ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ���݂̉�]�p
	DirectX::SimpleMath::Quaternion m_quaternion;
	// ����
	float m_mass;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �ǉ��̃N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_addQuaternion;
	// �m�[�h�ԍ�
	int m_nodeNumber;


	// body�̎q�擾�p
	CrowRightWing* m_rightWing;
	CrowLeftWing* m_leftWing;
	CrowLeftLeg* m_leftLeg;
	CrowRightLeg* m_rightLeg;
	
};