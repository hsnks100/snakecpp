#include "GlobalHeader.h"
#include <ddraw.h>
#pragma warning(disable:4706)
#pragma warning(disable:4100)
#pragma warning(disable:4127)
//창 모드.
RECT rcScreen;
RECT rcView;

// DD 관련...
LPDIRECTDRAWCLIPPER pClipper;
LPDIRECTDRAW7 lpDirectOBJ;
LPDIRECTDRAWSURFACE7 lpPrimarySurface;
LPDIRECTDRAWSURFACE7 lpBackSurface;
LPDIRECTDRAW lpdd;



BOOL ErrorMessage(HWND hWnd, char* str)
{
	MessageBox(hWnd, str, "축하합니다.[?]", MB_OK);
	DestroyWindow(hWnd);
	return TRUE;
}

HRESULT DeleteAll()
{
	if(lpBackSurface != NULL)
	{
		lpBackSurface->Release();
		lpBackSurface = NULL;
	}

	if(lpPrimarySurface != NULL)
	{
		lpPrimarySurface->Release();
		lpPrimarySurface = NULL;
	}

	if(lpDirectOBJ != NULL)
	{
		lpDirectOBJ->Release();
		lpDirectOBJ = NULL;
	}
	if(lpdd != NULL)
	{
		lpdd->Release();
		lpdd = NULL;
	}
	if(pClipper != NULL)
	{
		pClipper->Release();
		pClipper=NULL;
	}

	if(lpMouthImage != NULL)
	{
		lpMouthImage->Release();
		lpMouthImage = NULL;
	}

	if(lpMouthImageR != NULL)
	{
		lpMouthImageR->Release();
		lpMouthImageR = NULL;
	}

	if(lpMouthImageT != NULL)
	{
		lpMouthImageT->Release();
		lpMouthImageT = NULL;
	}
	if(lpMouthImageB != NULL)
	{
		lpMouthImageB->Release();
		lpMouthImageB = NULL;
	}
	if(lpFoodImg != NULL)
	{
		lpFoodImg->Release();
		lpFoodImg = NULL;
	}
	if(lpTailImage != NULL)
	{
		lpTailImage->Release();
		lpTailImage = NULL;
	}
	if(lpLineImage != NULL)
	{
		lpLineImage->Release();
		lpLineImage = NULL;
	}
	if(GameOverImg) //널 이 아니라면...
		DeleteObject((HGDIOBJ)GameOverImg);
	delete SnakeControl;
	return DD_OK;
}
/************************************************************************/
/* DD 생성 하는 함수.                                                   */
/************************************************************************/

HRESULT InitDirectDraw(int x, int y, int colordepth)
{
	DDSURFACEDESC2 ddsd;
	HRESULT hr;

	hr = DirectDrawCreate(NULL, &lpdd, NULL);
	if(hr != DD_OK)
		return ErrorMessage(GlobalWnd, "생성 실패");
	
	hr = lpdd->QueryInterface(IID_IDirectDraw7, (LPVOID*)&lpDirectOBJ);
	if(hr != DD_OK)
		return ErrorMessage(GlobalWnd, "쿼리 인터페이스 실패");

	hr = lpDirectOBJ->SetCooperativeLevel(GlobalWnd,
		DDSCL_NORMAL);
	if(hr != DD_OK)
		return ErrorMessage(GlobalWnd, "협력 실패");



	GetClientRect(GlobalWnd, &rcView);
	GetClientRect(GlobalWnd, &rcScreen);
	ClientToScreen(GlobalWnd, (POINT*)&rcScreen.left);
	ClientToScreen(GlobalWnd, (POINT*)&rcScreen.right);



	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS ; 
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	lpDirectOBJ->CreateSurface(&ddsd,&lpPrimarySurface,NULL);
	lpDirectOBJ->CreateClipper(0, &pClipper, NULL);
	pClipper->SetHWnd(0, GlobalWnd);
	
	lpPrimarySurface->SetClipper(pClipper);
	



	ddsd.dwFlags        = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	ddsd.dwWidth        = 640;
	ddsd.dwHeight       = 480;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	
	lpDirectOBJ->CreateSurface(&ddsd, &lpBackSurface, NULL);

	return DD_OK;
}


void Flip(void)
{
	HRESULT hRet;

	while(TRUE)
	{
		hRet = lpPrimarySurface->Blt(&rcScreen, lpBackSurface, &rcView, DDBLT_WAIT, NULL);
		
		
		if(hRet==DD_OK)
			break;

		if(hRet == DDERR_SURFACELOST)
		{
			hRet = lpPrimarySurface->Restore();
			if(hRet != DD_OK)
				break;
		}
		if(hRet != DDERR_WASSTILLDRAWING)
			break;
	}
}


void DisplayMessage(int x, int y, COLORREF color, char* msg,...)
{
	char szBuff[128];
	va_list va;
	va_start(va, msg);
	vsprintf(szBuff, msg, va);

	HDC hdc;
	lpBackSurface->GetDC(&hdc);
	   
	SetTextColor(hdc, color);
    SetBkMode(hdc, TRANSPARENT);
	
    TextOut(hdc, x, y, szBuff, strlen(szBuff));
	
	lpBackSurface->ReleaseDC(hdc);
}


void ImgLoad()
{
	// 
	lpLineImage = DDLoadBitmap(lpDirectOBJ, (LPCSTR)IDB_LINE, 0, 0);
	lpFoodImg = DDLoadBitmap(lpDirectOBJ, (LPCSTR)IDB_FOOD, 0, 0);
	lpTailImage = DDLoadBitmap(lpDirectOBJ, (LPCSTR)IDB_TAIL, 0, 0);
	lpMouthImage = DDLoadBitmap(lpDirectOBJ, (LPCSTR)IDB_MOUTH, 0, 0);
	lpMouthImageR = DDLoadBitmap(lpDirectOBJ, (LPCSTR)IDB_MOUTHR, 0, 0);
	lpMouthImageT = DDLoadBitmap(lpDirectOBJ, (LPCSTR)IDB_MOUTHT, 0, 0);
	lpMouthImageB = DDLoadBitmap(lpDirectOBJ, (LPCSTR)IDB_MOUTHB, 0, 0);
	//GameOvering -_-; 게임 오버링;;[?]
	GameOverImg = pngutLoadFilePng("GameOver.png", NULL);
}

void delay(DWORD ms)
{
   DWORD beginTime = timeGetTime();
   while ((timeGetTime() - beginTime) < ms);
}

void FileCheck()
{
	FILE* f;
	if( !(f=fopen("GameOver.png", "r")) )
	{
		ReleaseDC(GlobalWnd, GlobalDC);
		MessageBox(GlobalWnd, "GameOver.png 없'읍'니다. 그럼 -_-)/", "에로..;", MB_OK);
		DeleteAll();
		PostQuitMessage(WM_QUIT);
		return;
	}
	else
	{
		fclose(f);
	}
}

		
