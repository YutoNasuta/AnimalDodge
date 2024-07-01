//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/07/01
// <file>			UserInterface.h
// <�T�v>			���[�U�[�C���^�[�t�F�[�X�N���X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"UserInterface.h"
#include"BinaryFile.h"

/// <summary>
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> NakashiLib::UserInterface::INPUT_LAYOUT =
{
	{"POSITION" , 0 , DXGI_FORMAT_R32G32B32_FLOAT , 0 , 0 , D3D11_INPUT_PER_VERTEX_DATA, 0},
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
NakashiLib::UserInterface::UserInterface()
	:
	m_pDR(nullptr),
	m_windowHeight(0),
	m_windowWidth(0),
	m_textureHeight(0),
	m_textureWidth(0),
	m_texture(nullptr),
	m_res(nullptr),
	m_scale(DirectX::SimpleMath::Vector2::One),
	m_position(DirectX::SimpleMath::Vector2::Zero),
	m_anchor(ANCHOR::TOP_LEFT),
	m_renderRatio(1.0f),
	m_renderRatioOffset(0.0f)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NakashiLib::UserInterface::~UserInterface()
{

}

/// <summary>
/// �e�N�X�`�����\�[�X�ǂݍ���
/// </summary>
/// <param name="path">���΃p�X</param>
void NakashiLib::UserInterface::LoadTexture(const wchar_t* path)
{
	// �摜�ǂݍ��ݗp
	HRESULT result;

	// �w�肳�ꂽ�摜��ǂݍ���
	result = DirectX::CreateWICTextureFromFile(
		m_pDR->GetD3DDevice(), 
		path, 
		m_res.ReleaseAndGetAddressOf(), 
		m_texture.ReleaseAndGetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(m_res.As(&tex));

	// �ǂݍ��񂾉摜�̏����擾
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	// �ǂݍ��񂾉摜�̃T�C�Y���擾
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;
}

/// <summary>
/// �����֐�
/// </summary>
/// <param name="pDR">�f�o�C�X�擾</param>
/// <param name="path">���΃p�X�擾</param>
/// <param name="position">�ʒu�擾</param>
/// <param name="scale">�傫���擾</param>
/// <param name="anchor">�A���J�[�擾</param>
void NakashiLib::UserInterface::Create(DX::DeviceResources* pDR, 
	const wchar_t* path, 
	DirectX::SimpleMath::Vector2 position, 
	DirectX::SimpleMath::Vector2 scale,
	ANCHOR anchor)
{
	//���\�[�X�̎擾
	m_pDR = pDR;
	auto device = pDR->GetD3DDevice();
	m_position = position;
	m_baseScale = m_scale = scale;
	m_anchor = anchor;

	// �V�F�[�_�̍쐬
	CreateShader();

	// �摜�̓ǂݍ���
	LoadTexture(path);

	// �v���~�e�B�u�o�b�`�̍쐬
	m_batch = 
		std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(pDR->GetD3DDeviceContext());

	m_states = std::make_unique<DirectX::CommonStates>(device);
}


void NakashiLib::UserInterface::CreateShader()
{
	auto device = m_pDR->GetD3DDevice();

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	NakashiLib::BinaryFile VSData = NakashiLib::BinaryFile::LoadFile(L"Resources/Shaders/UIVS.cso");
	NakashiLib::BinaryFile GSData = NakashiLib::BinaryFile::LoadFile(L"Resources/Shaders/UIGS.cso");
	NakashiLib::BinaryFile PSData = NakashiLib::BinaryFile::LoadFile(L"Resources/Shaders/UIPS.cso");

	// �C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(
		&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(),
		VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	// ���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		// �G���[
		MessageBox(0, L"���_�V�F�[�_�ŃG���[", NULL, MB_OK);
		return;
	}

	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{
		// �G���[
		MessageBox(0, L"�W�I���g���V�F�[�_�ŃG���[", NULL, MB_OK);
		return;
	}

	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{
		// �G���[
		MessageBox(0, L"�s�N�Z���V�F�[�_�ŃG���[", NULL, MB_OK);
		return;
	}

	// �V�F�[�_�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(ConstBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	device->CreateBuffer(&bufferDesc, nullptr, &m_cBuffer);
}

/// <summary>
/// �`��
/// </summary>
void NakashiLib::UserInterface::Render()
{
	auto context = m_pDR->GetD3DDeviceContext();

	//���_���
	// Position.xy	: �g���X�P�[��		Position.z	: �A���J�[�^�C�v
	// Color.xy		: �A���J�[���W		Color.zw	: �摜�T�C�Y
	// Tex.xy		: �E�B���h�E�T�C�Y
	DirectX::VertexPositionColorTexture vertex[1] =
	{
		DirectX::VertexPositionColorTexture(
			DirectX::SimpleMath::Vector3(m_scale.x , m_scale.y , static_cast<float>(m_anchor)),
			DirectX::SimpleMath::Vector4(m_position.x , m_position.y , static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight)),
			DirectX::SimpleMath::Vector2(m_renderRatio - m_renderRatioOffset ,0))
	};

	// �V�F�[�_�ɓn���ǉ��̃o�b�t�@�쐬
	ConstBuffer cBuffer;
	cBuffer.windowSize =
		DirectX::SimpleMath::Vector4(static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 1, 1);

	// �󂯓n���p�o�b�t�@�̓��e�X�V
	context->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &cBuffer, 0, 0);

	// �V�F�[�_�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	// �摜�p����Ԃ�[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	�������`��w��
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	�������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	�J�����O�͍�����
	context->RSSetState(m_states->CullNone());
	//	�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());


	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//	�|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}