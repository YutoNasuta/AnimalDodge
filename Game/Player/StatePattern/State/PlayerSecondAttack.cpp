//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/26
// <file>			PlayerSecondAttack.h
// <�T�v>		�@�@�ŏ��̍U��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerSecondAttack.h"
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


PlayerSecondAttack::PlayerSecondAttack(Player* player)
	:
	m_player(player),
	m_deriveTime(10.0f),
	m_elapsedTime(0.0f),
	m_hasRotateFlag(false),
	m_rotateAngle(0.0f)
{
	m_commonResources = CommonResources::GetInstance();
}

PlayerSecondAttack::~PlayerSecondAttack()
{

}

void PlayerSecondAttack::OnEnter()
{
	m_elapsedTime = 0.0f;
	m_hasRotateFlag = false;
	m_rotateAngle = 0.0f;
}

void PlayerSecondAttack::OnExit()
{

}

void PlayerSecondAttack::Initialize()
{

}

void PlayerSecondAttack::Update()
{
	m_elapsedTime += m_commonResources->GetStepTimer()->GetElapsedSeconds();
	MoveChild();
	MovePlayer();
	ChangeState();
}

void PlayerSecondAttack::Render()
{

}

void PlayerSecondAttack::Finalize()
{

}

void PlayerSecondAttack::MoveChild()
{
	MoveHand();
	MoveBody();
	MoveHead();
}

void PlayerSecondAttack::MoveHand()
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

void PlayerSecondAttack::MoveBody()
{

}

void PlayerSecondAttack::MoveHead()
{

}

void PlayerSecondAttack::MovePlayer()
{
	if (m_hasRotateFlag) {
		// ���]�����ꍇ�A�������~�߂�
		return;
	}
	const float rotationSpeed = 0.3f; // ��]���x

	m_rotateAngle += rotationSpeed;

	// �v���C���[�̑O�i���鑬�x
	float forwardSpeed = 0.4f;

	// �v���C���[�̌��݂̃N�H�[�^�j�I������]�s��ɕϊ�
	DirectX::SimpleMath::Matrix rotationMatrix = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_player->GetQuaternion());

	// �O�����x�N�g�����擾
	DirectX::SimpleMath::Vector3 forwardDirection = rotationMatrix.Forward();

	

	// ��]���v�Z
	DirectX::SimpleMath::Quaternion currentRotation = m_player->GetQuaternion();
	DirectX::SimpleMath::Quaternion rotationIncrement = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(rotationSpeed,0.0f , 0.0f);
	DirectX::SimpleMath::Quaternion newRotation = currentRotation * rotationIncrement;

	m_player->SetAngle(newRotation);

	// ��]�p�x��360�x�𒴂����瓮�����~�߂�
	if (m_rotateAngle >= DirectX::XM_2PI) {
		m_hasRotateFlag = true;
	}
}

void PlayerSecondAttack::ChangeState()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();
	auto mouseStateTracker = m_commonResources->GetInputManager()->GetMouseState();

	if (m_hasRotateFlag)
	{
		if (m_elapsedTime <= m_deriveTime)
		{
			// m_deriveTime�ȓ��ɂ�����x���N���b�N���ꂽ�ꍇ�AsecondAttack�ɑJ��
			if (mouseStateTracker.leftButton) {
				m_player->ChangeState(m_player->GetThirdAttack());
			}
		}
		if (m_elapsedTime > m_deriveTime)
		{
			// m_deriveTime���߂����ꍇ�AStanding��ԂɑJ��
			m_player->ChangeState(m_player->GetStanding());
		}
		if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::D) ||
			keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::A) ||
			keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::W) ||
			keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::S)) {
			// �L�[�̊J���ŁAStanding�ɑJ��
			m_player->ChangeState(m_player->GetStanding());
		}
	}


}