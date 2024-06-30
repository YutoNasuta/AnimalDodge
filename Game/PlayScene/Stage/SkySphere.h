//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/30
// <file>			SkySphere.h
// <�T�v>		�@�@�X�e�[�W�̋�����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
// �O���錾
class CommonResources;

class SkySphere
{

private:
	// ���ʃX�e�[�g
	CommonResources* m_commonResources;
	// ���f���擾�p
	DirectX::Model* m_model;

public:
	SkySphere();
	~SkySphere();

	void SkyRender(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection);
};