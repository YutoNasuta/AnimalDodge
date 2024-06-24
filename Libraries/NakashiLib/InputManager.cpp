//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/16
// <file>			InputManager.cpp
// <�T�v>			�}�E�X�A�L�[�{�[�h�̓���
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include"pch.h"
#include"InputManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="window">�E�B���h�E</param>
NakashiLib::InputManager::InputManager(const HWND& window)
:
	m_mouseState{},
	m_keyboardState{}
{
	// �}�E�X���g�p�ł����Ԃɂ���
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouse->SetWindow(window);
	m_mouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();

	// �L�[�{�[�h���g�p�ł����Ԃɂ���
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
}

/// <summary>
/// ���\�[�X�̍X�V
/// </summary>
void NakashiLib::InputManager::Update()
{
	// �}�E�X�̏����X�V
	m_mouseState = m_mouse->GetState();
	m_mouseTracker->Update(m_mouseState);

	// �L�[�{�[�h�̏����X�V����
	m_keyboardState = m_keyboard->GetState();
	m_keyboardTracker->Update(m_keyboardState);
}