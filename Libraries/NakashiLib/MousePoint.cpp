//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/01/20
// <file>			MousePoint.cpp
// <�T�v>			�}�E�X�|�C���^�̎擾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"MousePoint.h"
#include "Game/Screen.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
NakashiLib::MousePoint::MousePoint()
	:
	m_previousMousePos{},
	m_currentMousePos{},
	m_deltaX{},
	m_deltaY{},
	m_mouseMove{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NakashiLib::MousePoint::~MousePoint()
{

}

/// <summary>
/// �X�V����
/// </summary>
void NakashiLib::MousePoint::Update()
{
	if (m_mouseMove == false) { return; }								//���������Ȃ�

	GetCursorPos(&m_currentMousePos);

	m_deltaX = m_currentMousePos.x - m_previousMousePos.x;					//�}�E�X���W�̍����v�Z
	m_deltaY = m_currentMousePos.y - m_previousMousePos.y;					//Y��

	POINT center = { Screen::CENTER_X , Screen::CENTER_Y };				//�}�E�X�𒆉��ɌŒ肳���邽�߂ɁA�ǂ��ɂ���̂������߂�B

	ShowCursor(FALSE);													//�J�[�\���������Ȃ��悤�ɂ���
			
	SetCursorPos(center.x, center.y);									//�}�E�X�𒆉��ɌŒ�

	m_previousMousePos = center;										//�ߋ��̃}�E�X�|�C���^�̈ʒu��ύX������

	Sleep(0);															//���t���ňړ�������̂�
}


