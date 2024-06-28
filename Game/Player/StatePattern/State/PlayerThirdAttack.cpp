//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/26
// <file>			PlayerThirdAttack.h
// <�T�v>		�@�@�O��ڂ̍U��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerThirdAttack.h"
#include"Game/Player/Player.h"
#include"Game/CommonResources.h"
#include"Framework/DeviceResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include "Framework/StepTimer.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"
#include"Game/Player/PlayerPart/PlayerTail.h"
#include"Game/Player/PlayerPart/PlayerHead.h"
#include"Framework/StepTimer.h"

PlayerThirdAttack::PlayerThirdAttack(Player* player)
	:
	m_player(player),
	m_attackDuration(0.2f)
	
{
	m_commonResources = CommonResources::GetInstance();
	m_backWardSpeed = 1.5f;
}

PlayerThirdAttack::~PlayerThirdAttack()
{

}

void PlayerThirdAttack::OnEnter()
{
	m_attackStartTime = m_commonResources->GetStepTimer()->GetTotalSeconds();
}

void PlayerThirdAttack::OnExit()
{

}

void PlayerThirdAttack::Initialize()
{

}

void PlayerThirdAttack::Update()
{
	double currentTime = m_commonResources->GetStepTimer()->GetTotalSeconds();

	if (currentTime - m_attackStartTime >= m_attackDuration)
	{
		m_player->ChangeState(m_player->GetStanding());
	}
	else
	{
		MoveChild();
		MovePlayer();
	}
}

void PlayerThirdAttack::Render()
{

}

void PlayerThirdAttack::Finalize()
{

}

void PlayerThirdAttack::MoveChild()
{
	MoveHand();
	MoveBody();
	MoveHead();
}

void PlayerThirdAttack::MoveHand()
{
	//auto rightHand = m_player->GetBody()->GetRightHand();
	//auto leftHand = m_player->GetBody()->GetLeftHand();

	//static float rotationAngle = 0.0f;
	//rotationAngle += 0.1f;

	//DirectX::SimpleMath::Quaternion TakePointRightQuaternion =
	//	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle), 0.0f , 0.0f);

	//DirectX::SimpleMath::Quaternion TakePointLeftQuaternion =
	//	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle), 1.0f * sin(rotationAngle),0.0f );

	//DirectX::SimpleMath::Quaternion slerpRotationRight =
	//	DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), TakePointRightQuaternion, 0.1f);
	//DirectX::SimpleMath::Quaternion slerpRotationLeft =
	//	DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), TakePointLeftQuaternion, 0.1f);

	//rightHand->SetAddQuaternion(slerpRotationRight);
	//leftHand->SetAddQuaternion(slerpRotationLeft);
}

void PlayerThirdAttack::MoveBody()
{

}

void PlayerThirdAttack::MoveHead()
{

}

void PlayerThirdAttack::MovePlayer()
{
	//// �v���C���[�̑��x�x�N�g�����擾���A�����𔽓]������
	//DirectX::SimpleMath::Vector3 direction = -m_player->GetVelocity();

	//direction.y = 0.0f;            // y���������[����
	//direction.Normalize();        // �ړ��ʂ̐��K��

	//// �W�����v�̍���������
	//float jumpHeight = 2.0f;    // �W�����v�̍�����ݒ�i�K�X�����j
	//float jumpDuration = 1.0f;  // �W�����v�̎������ԁi�K�X�����j

	//// ���Ԍo�߂Ɋ�Â��W�����v�̍����̕��
	//double elapsedTime = m_commonResources->GetStepTimer()->GetTotalSeconds() - m_attackStartTime;
	//float normalizedTime = static_cast<float>(elapsedTime / jumpDuration);

	//if (normalizedTime > 1.0f)
	//{
	//	normalizedTime = 1.0f;  // �������Ԃ��߂�����1�ɌŒ�
	//}

	//// �W�����v�̍������v�Z�i�������^���j
	//float heightOffset = jumpHeight * (1 - 4 * (normalizedTime - 0.5f) * (normalizedTime - 0.5f));

	//// �W�����v�ƈړ�����������
	//DirectX::SimpleMath::Vector3 velocity = direction * m_backWardSpeed;
	//velocity.y = heightOffset;

	//m_player->SetVelocity(velocity);  // ���x�̕ύX
	//m_player->SetPosition(m_player->GetPosition() + velocity * m_commonResources->GetStepTimer()->GetElapsedSeconds());  // �|�W�V�����̕ύX

	//SlerpRotate(direction);  // �v���C���[�̈ړ��Ɗp�x����⊮������
}

void PlayerThirdAttack::ChangeState()
{
	//auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();
	//auto mouseStateTracker = m_commonResources->GetInputManager()->GetMouseState();
	//	
	//		// deriveTime���߂����ꍇ�AStanding��ԂɑJ��
	//	m_player->ChangeState(m_player->GetStanding());
	//	
	//	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::D) ||
	//		keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::A) ||
	//		keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::W) ||
	//		keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::S)) {
	//		// �L�[�̊J���ŁAStanding�ɑJ��
	//		m_player->ChangeState(m_player->GetStanding());
	//	}
}


void PlayerThirdAttack::SlerpRotate(DirectX::SimpleMath::Vector3 direction)
{
	if (direction.LengthSquared() < 1e-2f) { return; }	// �ړ��ʂ��قƂ�ǂȂ��Ȃ�v�Z���Ȃ�

	DirectX::SimpleMath::Quaternion targetRotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(atan2f(direction.x, direction.z), 0.0f, 0.0f);	// �ړ������x�N�g������ڕW�̃N�H�[�^�j�I�����v�Z

	DirectX::SimpleMath::Quaternion slerpRotation =
		DirectX::SimpleMath::Quaternion::Slerp(m_player->GetQuaternion(), targetRotation, 0.2f);	// ���`�⊮����

	slerpRotation.Normalize();	// �m�[�}���C�Y����

	m_player->SetAngle(slerpRotation);	// ���݂̊p�x���v���C���[�̃N�H�[�^�j�I���ɂ����
}
