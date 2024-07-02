//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/07/01
// <file>			CrowAttackPlayer.cpp
// <�T�v>			�J���X���v���C���[���U������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "pch.h"
#include "CrowAttackPlayer.h"
#include "Game/PlayScene/Enemy/CrowBoss/Crow.h"
#include "Game/PlayScene/BlackBoard.h"
#include "Game/PlayScene/Enemy/CrowBoss/Parts/CrowHead.h"
#include "Game/PlayScene/Enemy/CrowBoss/Parts/CrowLeftWing.h"
#include "Game/PlayScene/Enemy/CrowBoss/Parts/CrowRightWing.h"
#include "Game/PlayScene/Enemy/CrowBoss/AttackInformation/CrowAttackParameter.h"

CrowAttackPlayer::CrowAttackPlayer(Crow* crow, BlackBoard* blackBoard)
{
    m_crow = crow;
    m_commonResources = CommonResources::GetInstance();
    m_timeExit = 0;
    m_blackBoard = blackBoard;
    m_startTime = -1;
}

bool CrowAttackPlayer::Execute()
{
    auto Timer = m_commonResources->GetStepTimer();
    float currentTime = Timer->GetTotalSeconds();

    // �N�[���_�E�����Ԓ��͍U�����Ȃ�
    if (currentTime < m_crow->GetAttackParameter()->GetLastAttack1Time() + CrowAttackParameter::m_attack1Cooldown)
    {
        return false;
    }

    // �U�����J�n
    if (m_startTime < 0) {
        m_crow->GetAttackParameter()->SetAttack1(true); // �U��1�J�n
        m_startTime = currentTime; // �J�n���Ԃ��L�^
    }

    MoveParts();

    // �U�����I�������ꍇ
    if (currentTime >= m_startTime + 1.0f + 0.5f) // preparationTime + attackTime
    {
        m_crow->GetAttackParameter()->SetAttack1(false); // �U��1�I��
        m_crow->GetAttackParameter()->SetLastAttack1Time(currentTime); // �U���I�����Ԃ��L�^
        m_startTime = -1; // ���Z�b�g
    }

    return true;
}

void CrowAttackPlayer::MoveParts()
{
    MoveHand();
}

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
