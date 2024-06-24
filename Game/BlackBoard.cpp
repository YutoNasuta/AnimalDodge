//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/23
// <file>			BlackBoard.cpp
// <概要>		　　シーンで扱う、データの集まり
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"BlackBoard.h"

BlackBoard::BlackBoard()
	:
	m_acceleration{},
	m_ballPosition{},
	m_enemyPosition{},
	m_gameTime{},
	m_gravity{},
	m_playerPosition{}
{

}

BlackBoard::~BlackBoard()
{

}

