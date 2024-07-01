#include"pch.h"
#include"BinaryFile.h"
#include<fstream>
#include<assert.h>

/// <summary>
/// ファイルをロードする
/// </summary>
/// <param name="fileName">ファイルパス</param>
NakashiLib::BinaryFile NakashiLib::BinaryFile::LoadFile(const wchar_t* fileName)
{
	BinaryFile binary;

	std::ifstream ifs;

	// ファイルオープン
	ifs.open(fileName, std::ios::in | std::ios::binary);
	// 読み込み失敗したら強制終了
	assert(ifs);

	// ファイルサイズを取得
	ifs.seekg(0, std::fstream::end);
	std::streamoff eofPos = ifs.tellg();
	ifs.clear();
	ifs.seekg(0, std::fstream::beg);
	std::streamoff begPos = ifs.tellg();
	binary.m_size = (unsigned int)(eofPos - begPos);

	// 読み込み用のメモリ確保
	binary.m_data.reset(new char[binary.m_size]);

	// ファイルの先頭からバッファへコピー
	ifs.read(binary.m_data.get(), binary.m_size);

	// ファイルを閉じる
	ifs.close();

	// バイナリファイルを返す
	return std::move(binary);
}

/// <summary>
/// コンストラクタ
/// </summary>
NakashiLib::BinaryFile::BinaryFile()
{
	m_size = 0;
}

/// <summary>
/// ムーブコンストラクタ
/// </summary>
NakashiLib::BinaryFile::BinaryFile(BinaryFile&& in)
{
	m_data = std::move(in.m_data);
	m_size = in.m_size;
}