//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/19
// <file>			Graphics.h
// <�T�v>		�@�@�`�揈���ɕK�v�Ȃ��̂܂Ƃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Graphics.h"
#include"Game/CommonResources.h"

std::unique_ptr<Graphics> Graphics::m_graphics = nullptr;

/// <summary>
/// �O���t�B�b�N�X�̃C���X�^���X��Ԃ�
/// </summary>
Graphics* const Graphics::GetInstance()
{
	if (m_graphics == nullptr)
	{
		// �O���t�B�b�N�X�̃C���X�^���X�𐶐�����
		m_graphics.reset(new Graphics());
	}
	// �C���X�^���X��Ԃ�
	return m_graphics.get();
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Graphics::Graphics()
	:
	m_deviceResources{},
	m_commonStates{},
	m_spriteBatch{},
	m_spriteFont{},
	m_basicEffect{},
	m_primitiveBatch{},
	m_rasterrizerState{},
	m_effectFactory{},
	m_inputLayout{},
	m_screenW(0),
	m_screenH(0),
	m_view{},
	m_projection{},
	m_device{},
	m_context{}
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Graphics::~Graphics()
{
}

void Graphics::Initialize()
{
	// �f�o�C�X�擾
	m_device = m_deviceResources->GetD3DDevice();
	// �f�o�C�X�R���e�L�X�g���擾����
	m_context = m_deviceResources->GetD3DDeviceContext();

	// �R�����X�e�[�g�𐶐�����
	m_commonStates = std::make_unique<DirectX::CommonStates>(m_device);
	// �X�v���C�g�o�b�`�𐶐�����
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_context);
	// �x�[�V�b�N�G�t�F�N�g�𐶐�����
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(m_device);
	// �X�v���C�g�t�H���g�𐶐�����
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_device, L"resources\\font\\SegoeUI_18.spritefont");
	// �v���~�e�B�u�o�b�`�𐶐�����
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(m_context);
	// ���_�J���[��L���ɂ���
	m_basicEffect->SetVertexColorEnabled(true);
	// �e�N�X�`���𖳌��ɂ���
	m_basicEffect->SetTextureEnabled(false);
	void const* shaderByteCode;
	size_t byteCodeLength;
	// ���_�V�F�[�_�[���擾����
	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	// ���̓��C�A�E�g�𐶐�����
	m_device->CreateInputLayout(
		DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.ReleaseAndGetAddressOf()
	);
	// ���X�^���C�U�[�f�B�X�N���v�V����
	CD3D11_RASTERIZER_DESC rasterizerStateDesc(
		D3D11_FILL_SOLID, D3D11_CULL_NONE, FALSE,
		D3D11_DEFAULT_DEPTH_BIAS, D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
		D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE, FALSE, FALSE, TRUE
	);
	// ���X�^���C�Y�X�e�[�g�𐶐�����
	m_device->CreateRasterizerState(&rasterizerStateDesc, m_rasterrizerState.ReleaseAndGetAddressOf());
	// �G�t�F�N�g�t�@�N�g���𐶐�����
	m_effectFactory = std::make_unique<DirectX::EffectFactory>(m_device);
}

void Graphics::DrawPrimitiveBegin(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	// �u�����f�B���O��Ԃ�ݒ肷��
	m_context->OMSetBlendState(m_commonStates->Opaque(), nullptr, 0xFFFFFFFF);
	// �[�x�X�e���V����Ԃ�ݒ肷��
	m_context->OMSetDepthStencilState(m_commonStates->DepthNone(), 0);
	// �J�����O���s��Ȃ�
	m_context->RSSetState(m_commonStates->CullNone());
	// ���X�^���C�U�[��Ԃ�ݒ肷��
	m_context->RSSetState(m_rasterrizerState.Get());

	// �r���[�s���ݒ肷��
	m_basicEffect->SetView(view);
	// �v���W�F�N�V�����s���ݒ肷��
	m_basicEffect->SetProjection(projection);
	// ���[���h�s���ݒ肷��
	m_basicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	// �R���e�L�X�g��ݒ肷��
	m_basicEffect->Apply(m_context);
	// ���̓��C�A�E�g��ݒ肷��
	m_context->IASetInputLayout(m_inputLayout.Get());
	// �v���~�e�B�u�o�b�`���J�n����
	m_primitiveBatch->Begin();
}

// �`��v���~�e�B�u���I������
void Graphics::DrawPrimitiveEnd()
{
	// �v���~�e�B�u�o�b�`���I������
	m_primitiveBatch->End();
}