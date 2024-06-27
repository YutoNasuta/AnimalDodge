//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/21
// <file>			PlayerAttack.h
// <�T�v>		�@�@�v���C���[�U�����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include"pch.h"
#include"PlayerAttack.h"
#include"Game/CommonResources.h"
#include"framework/DeviceResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"
#include"Game/Player/PlayerPart/PlayerTail.h"
#include"Game/Player/PlayerPart/PlayerHead.h"
PlayerAttack::PlayerAttack(Player* player)
	:
	m_player(player),
    m_attackDuration(0.2f)
{
	m_commonResources = CommonResources::GetInstance();
    m_attackSpeed = 2.0f;
}

PlayerAttack::~PlayerAttack()
{

}

void PlayerAttack::OnEnter()
{
    // �_�b�V�����J�n�������Ԃ��L�^
    m_attackStartTime = m_commonResources->GetStepTimer()->GetTotalSeconds();
    // ������
    m_differenceTime = 0;
}

void PlayerAttack::OnExit()
{

}

void PlayerAttack::Initialize()
{

}

void PlayerAttack::Update()
{
  
    double currentTime = m_commonResources->GetStepTimer()->GetTotalSeconds();

    m_differenceTime = m_attackStartTime - currentTime;
    if (currentTime - m_attackStartTime >= m_attackDuration)
    {
        // �v���C���[���X�^���f�B���O��ԂɕύX
        m_player->ChangeState(m_player->GetStanding());
    }
    else
    {
        MoveChild();
        MovePlayer();
    }
}

void PlayerAttack::Render()
{

}

void PlayerAttack::Finalize()
{

}


void PlayerAttack::MoveChild()
{
	MoveHand();
    MoveBody();
    MoveHead();
}

/// <summary>
/// ��̓���
/// </summary>
void PlayerAttack::MoveHand()
{
    auto rightHand = m_player->GetBody()->GetRightHand();
    auto leftHand = m_player->GetBody()->GetLeftHand();

    // ��]�̐ݒ�
    static float rotationAngle = 0.0f;
    rotationAngle += 0.1f;

    DirectX::SimpleMath::Quaternion TakePointRightQuaternion =
        DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle + 1), -1.0f * cos(rotationAngle ), 1.0f);

    DirectX::SimpleMath::Quaternion TakePointLeftQuaternion =
        DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle + 1), 1.0f * cos(rotationAngle), -1.0f);

    DirectX::SimpleMath::Quaternion slerpRotationRight =
        DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), TakePointRightQuaternion, 0.1f);
    DirectX::SimpleMath::Quaternion slerpRotationLeft =
        DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), TakePointLeftQuaternion, 0.1f);

    rightHand->SetAddQuaternion(slerpRotationRight);
    leftHand->SetAddQuaternion(slerpRotationLeft);

}

void PlayerAttack::MoveBody()
{
    auto body = m_player->GetBody();
    // ��]�̐ݒ�
    static float rotationAngle = 0.0f;
    rotationAngle += 0.1f;

    DirectX::SimpleMath::Quaternion PointBodyQuaternion =
        DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle), 0.0f , 0.0f );

    DirectX::SimpleMath::Quaternion slerpRotationBody =
        DirectX::SimpleMath::Quaternion::Slerp(body->GetQuaternion(), PointBodyQuaternion , 0.1f);

    body->SetAddQuaternion(slerpRotationBody);

}

void PlayerAttack::MoveHead()
{
    auto head = m_player->GetBody()->GetHead();
    // ��]�̐ݒ�
    static float rotationAngle = 0.0f;
    rotationAngle += 0.1f;

    DirectX::SimpleMath::Quaternion PointBodyQuaternion =
        DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.3f * sin(rotationAngle), 0.0f, 0.0f);

    DirectX::SimpleMath::Quaternion slerpRotationBody =
        DirectX::SimpleMath::Quaternion::Slerp(head->GetAddQuaternion(), PointBodyQuaternion, 0.1f);

    head->SetAddQuaternion(slerpRotationBody);

}

void PlayerAttack::MoveTail()
{

}

void PlayerAttack::MovePlayer()
{
    DirectX::SimpleMath::Vector3 direction = m_player->GetVelocity() * 0.15f;		// ��~����

    direction.y = 0.0f;			// y���������[����

    direction.Normalize();		// �ړ��ʂ̐��K��

    // �W�����v�̍���������
    float jumpHeight = 1.0f;  // �W�����v�̍�����ݒ�i�K�X�����j
    float jumpDuration = 0.5f;  // �W�����v�̎������ԁi�K�X�����j

    // ���Ԍo�߂Ɋ�Â��W�����v�̍����̕��
    double elapsedTime = m_commonResources->GetStepTimer()->GetTotalSeconds() - m_attackStartTime;
    float normalizedTime = static_cast<float>(elapsedTime / jumpDuration);

    if (normalizedTime > 0.5f)
    {
        normalizedTime = 0.5f;  // �������Ԃ��߂�����1�ɌŒ�
    }

    // �W�����v�̍������v�Z�i�������^���j
    float heightOffset = jumpHeight * (1 - 4 * (normalizedTime) * (normalizedTime ));

    // �W�����v�ƈړ�����������
    DirectX::SimpleMath::Vector3 velocity = direction * m_attackSpeed;
    velocity.y = heightOffset;

    



    m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());		//�|�W�V�����̕ύX
    m_player->SetVelocity(velocity );				//���x�̕ύX

    SlerpRotate(direction);		//�v���C���[�̈ړ��Ɗp�x����⊮������
}

void PlayerAttack::SlerpRotate(DirectX::SimpleMath::Vector3 direction)
{
    if (direction.LengthSquared() < 1e-2f) { return; }			// �ړ��ʂ��قƂ�ǂȂ��Ȃ�v�Z���Ȃ�( 1��10-2��ȉ� )

    DirectX::SimpleMath::Quaternion targetRotation =
        DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(atan2f(direction.x, direction.z), 0.0f, 0.0f);	// �ړ������x�N�g������ڕW�̃N�H�[�^�j�I�����v�Z

    DirectX::SimpleMath::Quaternion slerpRotation =
        DirectX::SimpleMath::Quaternion::Slerp(m_player->GetQuaternion(), targetRotation, 0.2f);			// ���`�⊮����

    slerpRotation.Normalize();				//�m�[�}���C�Y����

    m_player->SetAngle(slerpRotation);			// ���݂̊p�x���v���C���[�̃N�H�[�^�j�I���ɂ����
}