//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/07/01
// <file>			UserInterface.h
// <概要>			ユーザーインターフェースクラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"UserInterface.h"
#include"BinaryFile.h"

/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> NakashiLib::UserInterface::INPUT_LAYOUT =
{
	{"POSITION" , 0 , DXGI_FORMAT_R32G32B32_FLOAT , 0 , 0 , D3D11_INPUT_PER_VERTEX_DATA, 0},
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
NakashiLib::UserInterface::~UserInterface()
{

}

/// <summary>
/// テクスチャリソース読み込み
/// </summary>
/// <param name="path">相対パス</param>
void NakashiLib::UserInterface::LoadTexture(const wchar_t* path)
{
	// 画像読み込み用
	HRESULT result;

	// 指定された画像を読み込む
	result = DirectX::CreateWICTextureFromFile(
		m_pDR->GetD3DDevice(), 
		path, 
		m_res.ReleaseAndGetAddressOf(), 
		m_texture.ReleaseAndGetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(m_res.As(&tex));

	// 読み込んだ画像の情報を取得
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	// 読み込んだ画像のサイズを取得
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;
}

/// <summary>
/// 生成関数
/// </summary>
/// <param name="pDR">デバイス取得</param>
/// <param name="path">相対パス取得</param>
/// <param name="position">位置取得</param>
/// <param name="scale">大きさ取得</param>
/// <param name="anchor">アンカー取得</param>
void NakashiLib::UserInterface::Create(DX::DeviceResources* pDR, 
	const wchar_t* path, 
	DirectX::SimpleMath::Vector2 position, 
	DirectX::SimpleMath::Vector2 scale,
	ANCHOR anchor)
{
	//リソースの取得
	m_pDR = pDR;
	auto device = pDR->GetD3DDevice();
	m_position = position;
	m_baseScale = m_scale = scale;
	m_anchor = anchor;

	// シェーダの作成
	CreateShader();

	// 画像の読み込み
	LoadTexture(path);

	// プリミティブバッチの作成
	m_batch = 
		std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(pDR->GetD3DDeviceContext());

	m_states = std::make_unique<DirectX::CommonStates>(device);
}


void NakashiLib::UserInterface::CreateShader()
{
	auto device = m_pDR->GetD3DDevice();

	// コンパイルされたシェーダファイルを読み込み
	NakashiLib::BinaryFile VSData = NakashiLib::BinaryFile::LoadFile(L"Resources/Shaders/UIVS.cso");
	NakashiLib::BinaryFile GSData = NakashiLib::BinaryFile::LoadFile(L"Resources/Shaders/UIGS.cso");
	NakashiLib::BinaryFile PSData = NakashiLib::BinaryFile::LoadFile(L"Resources/Shaders/UIPS.cso");

	// インプットレイアウトの作成
	device->CreateInputLayout(
		&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(),
		VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	// 頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		// エラー
		MessageBox(0, L"頂点シェーダでエラー", NULL, MB_OK);
		return;
	}

	// ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{
		// エラー
		MessageBox(0, L"ジオメトリシェーダでエラー", NULL, MB_OK);
		return;
	}

	// ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{
		// エラー
		MessageBox(0, L"ピクセルシェーダでエラー", NULL, MB_OK);
		return;
	}

	// シェーダにデータを渡すためのコンスタントバッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(ConstBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	device->CreateBuffer(&bufferDesc, nullptr, &m_cBuffer);
}

/// <summary>
/// 描画
/// </summary>
void NakashiLib::UserInterface::Render()
{
	auto context = m_pDR->GetD3DDeviceContext();

	//頂点情報
	// Position.xy	: 拡張スケール		Position.z	: アンカータイプ
	// Color.xy		: アンカー座標		Color.zw	: 画像サイズ
	// Tex.xy		: ウィンドウサイズ
	DirectX::VertexPositionColorTexture vertex[1] =
	{
		DirectX::VertexPositionColorTexture(
			DirectX::SimpleMath::Vector3(m_scale.x , m_scale.y , static_cast<float>(m_anchor)),
			DirectX::SimpleMath::Vector4(m_position.x , m_position.y , static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight)),
			DirectX::SimpleMath::Vector2(m_renderRatio - m_renderRatioOffset ,0))
	};

	// シェーダに渡す追加のバッファ作成
	ConstBuffer cBuffer;
	cBuffer.windowSize =
		DirectX::SimpleMath::Vector4(static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 1, 1);

	// 受け渡し用バッファの内容更新
	context->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &cBuffer, 0, 0);

	// シェーダにバッファを渡す
	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	// 画像用さんぶらーの登録
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	半透明描画指定
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	カリングは左周り
	context->RSSetState(m_states->CullNone());
	//	シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());


	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//	板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}