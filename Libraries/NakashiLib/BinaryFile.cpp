#include"pch.h"
#include"BinaryFile.h"
#include<fstream>
#include<assert.h>

/// <summary>
/// �t�@�C�������[�h����
/// </summary>
/// <param name="fileName">�t�@�C���p�X</param>
NakashiLib::BinaryFile NakashiLib::BinaryFile::LoadFile(const wchar_t* fileName)
{
	BinaryFile binary;

	std::ifstream ifs;

	// �t�@�C���I�[�v��
	ifs.open(fileName, std::ios::in | std::ios::binary);
	// �ǂݍ��ݎ��s�����狭���I��
	assert(ifs);

	// �t�@�C���T�C�Y���擾
	ifs.seekg(0, std::fstream::end);
	std::streamoff eofPos = ifs.tellg();
	ifs.clear();
	ifs.seekg(0, std::fstream::beg);
	std::streamoff begPos = ifs.tellg();
	binary.m_size = (unsigned int)(eofPos - begPos);

	// �ǂݍ��ݗp�̃������m��
	binary.m_data.reset(new char[binary.m_size]);

	// �t�@�C���̐擪����o�b�t�@�փR�s�[
	ifs.read(binary.m_data.get(), binary.m_size);

	// �t�@�C�������
	ifs.close();

	// �o�C�i���t�@�C����Ԃ�
	return std::move(binary);
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
NakashiLib::BinaryFile::BinaryFile()
{
	m_size = 0;
}

/// <summary>
/// ���[�u�R���X�g���N�^
/// </summary>
NakashiLib::BinaryFile::BinaryFile(BinaryFile&& in)
{
	m_data = std::move(in.m_data);
	m_size = in.m_size;
}