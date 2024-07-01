//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/07/01
// <file>			CrowAttackPlayer.cpp
// <�T�v>			�J���X���v���C���[���U������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CrowAttackPlayer.h"
#include"Game/PlayScene/Enemy/CrowBoss/Crow.h"
#include"Game/PlayScene/BlackBoard.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowHead.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowLeftWing.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowRightWing.h"


/// <summary>
/// �C�j�V�����C�Y
/// </summary>
/// <param name="crow">�J���X</param>
/// <param name="blackBoard">����</param>
CrowAttackPlayer::CrowAttackPlayer(Crow* crow, BlackBoard* blackBoard)
{
	m_crow = crow;
	m_commonResources = CommonResources::GetInstance();
	m_timeExit = 0;
	m_blackBoard = blackBoard;
    m_startTime = -1;
}

/// <summary>
/// ���s
/// </summary>
/// <returns></returns>
bool CrowAttackPlayer::Execute()
{
    auto Timer = m_commonResources->GetStepTimer();
    float currentTime = Timer->GetTotalSeconds();

    // �N�[���_�E�����Ԓ��͍U�����Ȃ�
    if (currentTime < m_crow->GetLastAttackTime() + m_crow->GetAttackCoolDown())
    {
        return false;
    }

    // �U�����J�n
    if (m_startTime < 0) {
        m_crow->SetAttackNormal(true); // �U���J�n
        m_startTime = currentTime; // �J�n���Ԃ��L�^

        
    }

    MoveParts();

    // �U�����I�������ꍇ
    if (currentTime >= m_startTime + 1.0f + 0.5f) // preparationTime + attackTime
    {
        m_crow->SetAttackNormal(false);  // �U���I��
        m_crow->SetLastAttackTime(currentTime); // �U���I�����Ԃ��L�^
        m_startTime = -1; // ���Z�b�g
    }

    return true;
}


/// <summary>
/// �J���X�̃p�[�c�𓮂���
/// </summary>
void CrowAttackPlayer::MoveParts()
{
	// ��𓮂���
	MoveHand();
}


/// <summary>
/// ��̓���
/// </summary>
void CrowAttackPlayer::MoveHand()
{
    auto Timer = m_commonResources->GetStepTimer();
    float currentTime = Timer->GetTotalSeconds();

    auto rightHand = m_crow->GetHead()->GetRightWing();
    auto leftHand = m_crow->GetHead()->GetLeftWing();

    const float preparationTime = 1.0f;
    const float attackTime = 0.5f;
    float elapsedTime = currentTime - m_startTime;

    DirectX::SimpleMath::Quaternion prepareRightQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(-1.0f, 0.0f, 0.5f);
    DirectX::SimpleMath::Quaternion prepareLeftQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f, 0.0f, -0.5f);

    DirectX::SimpleMath::Quaternion attackRightQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(2.0f, 0.0f, 1.0f);
    DirectX::SimpleMath::Quaternion attackLeftQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(-2.0f, 0.0f, -1.0f);

    DirectX::SimpleMath::Quaternion currentRightRotation;
    DirectX::SimpleMath::Quaternion currentLeftRotation;

    if (elapsedTime < preparationTime) {
        float t = elapsedTime / preparationTime;
        currentRightRotation = DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQuaternion(), prepareRightQuaternion, t);
        currentLeftRotation = DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQuaternion(), prepareLeftQuaternion, t);
    }
    else if (elapsedTime < preparationTime + attackTime) {
        float t = (elapsedTime - preparationTime) / attackTime;
        currentRightRotation = DirectX::SimpleMath::Quaternion::Slerp(prepareRightQuaternion, attackRightQuaternion, t);
        currentLeftRotation = DirectX::SimpleMath::Quaternion::Slerp(prepareLeftQuaternion, attackLeftQuaternion, t);
    }

    rightHand->SetAddQuaternion(currentRightRotation);
    leftHand->SetAddQuaternion(currentLeftRotation);
}