//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/18
// <file>			StageCase.h
// <�T�v>		�@�@�X�e�[�W�̘g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

class CommonResources;
class Graphics;
class StageCase
{
private:
	// ���ʃX�e�[�g
	CommonResources* m_commonResources;
	Graphics* m_graphics;
	// �o�E���f�B���O�{�b�N�X
	DirectX::BoundingBox m_stageCaseBoundingBox;

	// �`��p
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// �ǂ̃��f���擾
	DirectX::Model* m_model;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_boxSize;

public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	StageCase();
	~StageCase();

	void Initialize();
	void Update();
	void BoundingBoxRender();
	void DrawModel(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection);
	

	void SetPosition(
		DirectX::SimpleMath::Vector3& position, 
		DirectX::SimpleMath::Vector3& boxSize);



	DirectX::BoundingBox GetBoundingBox() const { return m_stageCaseBoundingBox; }

	
};