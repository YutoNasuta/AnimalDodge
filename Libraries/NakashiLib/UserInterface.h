//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/07/01
// <file>			UserInterface.h
// <�T�v>			���[�U�[�C���^�[�t�F�[�X�N���X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

#include"pch.h"
#include"Framework/DeviceResources.h"
#include"Framework/StepTimer.h"


namespace NakashiLib
{
	// UI�̃A���J�[�|�C���g
	enum ANCHOR
	{
		TOP_LEFT = 0,
		TOP_CENTER = 1,
		TOP_RIGHT = 2,

		MIDDLE_LEFT = 3,
		MIDDLE_CENTER = 4,
		MIDDLE_RIGHT = 5,

		BOTTOM_LEFT = 6,
		BOTTOM_CENTER = 7,
		BOTTOM_RIGHT = 8
	};

	class UserInterface
	{
	public:
		// �f�[�^�̎󂯓n���p�R���X�^���g�o�b�t�@
		struct ConstBuffer
		{
			DirectX::SimpleMath::Vector4 windowSize;
		};

	private:
		// �f�o�C�X�擾
		DX::DeviceResources* m_pDR;
		// �o�b�t�@�擾
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_cBuffer;
		// �^�C�}�[�擾
		DX::StepTimer	m_timer;
		// ���̓��C�A�E�g
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		// �v���~�e�B�u�o�b�`
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
		// �R�����X�e�[�g
		std::unique_ptr<DirectX::CommonStates> m_states;
		// �e�N�X�`���n���h��
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		Microsoft::WRL::ComPtr<ID3D11Resource> m_res;
		// ���_�V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		// �s�N�Z���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		// �W�I���g���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
		// �E�B���h�E�̃T�C�Y
		int m_windowWidth, m_windowHeight;
		// �e�N�X�`���̃T�C�Y
		int m_textureWidth, m_textureHeight;
		// �傫��
		DirectX::SimpleMath::Vector2 m_scale;
		// ���̑傫��
		DirectX::SimpleMath::Vector2 m_baseScale;
		// �ʒu
		DirectX::SimpleMath::Vector2 m_position;

		ANCHOR m_anchor;

		float m_renderRatio;
		float m_renderRatioOffset;

	public:
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

		UserInterface();
		~UserInterface();

		void LoadTexture(const wchar_t* path);
		void Create(
			DX::DeviceResources* pDR,
			const wchar_t* path,
			DirectX::SimpleMath::Vector2 position,
			DirectX::SimpleMath::Vector2 scale,
			ANCHOR anchor);

		void Render();

		void SetWindowSize(const int& width, const int& height) { m_windowWidth = width; m_windowHeight = height; }

		void SetScale(DirectX::SimpleMath::Vector2 scale) { m_scale = scale; }

		DirectX::SimpleMath::Vector2 GetScale() { return m_scale; }

		DirectX::SimpleMath::Vector2 GetBaseScale() { return m_baseScale; }

		void SetPosition(DirectX::SimpleMath::Vector2 position) { m_position = position; }

		DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }

		void SetAnchor(NakashiLib::ANCHOR anchor);

		NakashiLib::ANCHOR GetAnchor() { return m_anchor; }

		void SetRenderRatio(float ratio) { m_renderRatio = ratio; }
		float GetRenderRatio() { return m_renderRatio; }

		void SetRenderRatioOffset(float offset) { m_renderRatioOffset = offset; }
		float GetRenderRatioOffset() { return m_renderRatioOffset; }

	private:
		void CreateShader();
	};
}