//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/29
// <file>			NearPlayerCheck.h
// <�T�v>			�߂��Ƀv���C���[�����邩�ǂ�������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"NearPlayerCheck.h"
#include"Game/PlayScene/Enemy/CrowBoss/Crow.h"
#include"Game/PlayScene/BlackBoard.h"
#include<cmath>
/// <summary>
///  �R���X�g���N�^
/// </summary>
/// <param name="Crow">����</param>
/// <param name="blackboard">�u���b�N�{�[�h</param>
NearPlayerCheck::NearPlayerCheck(Crow* Crow, BlackBoard* blackboard)
	:
	ConditionNode([this]() { return this->CheckNearPlayer(); })
{
	m_crow = Crow;
	m_blackBoard = blackboard;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NearPlayerCheck::~NearPlayerCheck()
{

}

/// <summary>
/// �߂��Ƀv���C���[�����邩�ǂ���
/// </summary>
bool NearPlayerCheck::CheckNearPlayer()
{
    // �J���X�ƃv���C���[�̈ʒu���擾
    auto crowPosition = m_crow->GetPosition();
    auto playerPosition = m_blackBoard->GetPlayerPosition();

    // �����̌v�Z
    float distance = std::sqrt(
        std::pow(crowPosition.x - playerPosition.x, 2) +
        std::pow(crowPosition.y - playerPosition.y, 2) +
        std::pow(crowPosition.z - playerPosition.z, 2)
    );

    // �߂��Ɣ��肷�鋗����ݒ�
    constexpr float threshold = 50.0f; 

    // ������臒l��菬�������ǂ������`�F�b�N
    return distance < threshold;
}