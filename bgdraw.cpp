#include "GlobalHeader.h"
CBgdraw::CBgdraw()
{
	// Construct
	PlayScreen.top = 20;
	PlayScreen.left = 20;
	PlayScreen.right = 440;
	PlayScreen.bottom = 440;
}

void CBgdraw::draw()
{
	// 배경 그리는 곳
	DDBLTFX m_bltfx;
	m_bltfx.dwSize = sizeof(DDBLTFX);
	m_bltfx.dwFillColor = 0xFFFFFF;
	lpBackSurface->Blt(&PlayScreen, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT,
		&m_bltfx);
}

void CBgdraw::Fill()
{
	DDBLTFX m_Fill;
	m_Fill.dwSize = sizeof(DDBLTFX);
	m_Fill.dwFillColor = 0x000000;
	lpBackSurface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT,
		&m_Fill);
}

void CBgdraw::linedraw()
{
	lpBackSurface->BltFast(PlayScreen.top, PlayScreen.left, lpLineImage, NULL,
		DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
}

void CBgdraw::GameOverFill()
{
	//png 그린다.
	pngutDrawBmp2DC(GlobalDC, NULL, GameOverImg, NULL);
}
