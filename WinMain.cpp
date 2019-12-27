#include "GlobalHeader.h"
#pragma warning(disable:4100)
#pragma warning(disable:4098)
HDC GlobalDC; //DC... GetDC(hWnd)으로 구할 것임.

LPDIRECTDRAWSURFACE7 lpLineImage; //선의 이미지.
LPDIRECTDRAWSURFACE7 lpFoodImg; //먹이 이미지.
LPDIRECTDRAWSURFACE7 lpMouthImage; //입 왼쪽 이미지.
LPDIRECTDRAWSURFACE7 lpMouthImageR; // 입 오른쪽 이미지.
LPDIRECTDRAWSURFACE7 lpMouthImageT; //입 위쪽 이미지.
LPDIRECTDRAWSURFACE7 lpMouthImageB; //입 아래 이미지.
LPDIRECTDRAWSURFACE7 lpTailImage; //꼬리 이미지.
HBITMAP GameOverImg; //게임오버 이미지.


CBgdraw Background;
CSnake* SnakeControl = new CSnake;
HWND GlobalWnd;
//게임 모드.
int GAMEMODE = NOSTART; //게임 노 스타트
BOOL KeyState[41] = {FALSE}; //키 버퍼;

void Render(); //출력.
//전형 적인 WinMain.
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	WNDCLASS wc;
	HWND hWnd;
	MSG Message = {0};

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON));
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszClassName = "Snake";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&wc);
	hWnd = CreateWindow(wc.lpszClassName, "Snake 0.12", WS_CAPTION | WS_SYSMENU, 0,0, 640, 480, NULL,
		(HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nShowCmd);

	GlobalWnd = hWnd;
	//DD 생성함수 호출.
	InitDirectDraw(640, 480, 16);
	
	ImgLoad(); //이미지 로드. -_-;

	while( Message.message != WM_QUIT )
	{
		if(PeekMessage( &Message, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &Message );
			DispatchMessage( &Message );
		}
		else
		{
			Render();
			FileCheck(); //파일이 없다고 알려줌.
		}
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int KeyLoop; //키 루프 해서 검사.
	switch(iMessage)
	{
	case WM_CREATE:
		GlobalDC = GetDC(hWnd);
		break;
	case WM_MOVE:
		GetClientRect(GlobalWnd, &rcView);
		GetClientRect(GlobalWnd, &rcScreen);
		ClientToScreen(GlobalWnd, (POINT*)&rcScreen.left);
		ClientToScreen(GlobalWnd, (POINT*)&rcScreen.right);
		break;
	case WM_KEYDOWN:
		//시작했거나 시작 안했거나 먹이를 먹었으면.
		if(GAMEMODE == NOSTART || GAMEMODE == START || GAMEMODE == FOODEAT)
		{
			//왼쪽 키 눌렀으면
			if(wParam == VK_LEFT)
			{
				for(KeyLoop=0; KeyLoop<41; KeyLoop++)
				{
					KeyState[KeyLoop] = FALSE;
				}
				KeyState[VK_LEFT] = TRUE;

				//시작 안했으면 스타트로 만듬...
				if(GAMEMODE == NOSTART)
					GAMEMODE = START;
				else if(SnakeControl->GetLength() > 0)//꼬리가 달렸으면.
					GAMEMODE = FOODEAT;
			}
			//오른쪽 키 눌렀으면 전부 FALSE 시키고 VK_RIGHT 만 TRUE화
			else if(wParam == VK_RIGHT)
			{
				for(KeyLoop=0; KeyLoop<41; KeyLoop++)
				{
					KeyState[KeyLoop] = FALSE;
				}
				KeyState[VK_RIGHT] = TRUE;
				
				//시작 안했으면 스타트로 만듬...
				if(GAMEMODE==NOSTART)
					GAMEMODE = START;
				else if(SnakeControl->GetLength() > 0)//꼬리가 달렸으면.
					GAMEMODE = FOODEAT;
			}
			//업키 눌렀으면 전부 FALSE 시키고 VK_UP만 TRUE화.
			else if(wParam == VK_UP)
			{	
				for(KeyLoop=0; KeyLoop<41; KeyLoop++)
				{
					KeyState[KeyLoop] = FALSE;
				}
				KeyState[VK_UP] = TRUE;

				//시작 안했으면 스타트로 만듬...
				if(GAMEMODE==NOSTART)
					GAMEMODE = START;
				else if(SnakeControl->GetLength() > 0)//꼬리가 달렸으면.
					GAMEMODE = FOODEAT;
			}
			//다운키 눌렀으면 전부 FALSE 시키고 VK_DOWN 만 TRUE화
			else if(wParam == VK_DOWN)
			{
				for(KeyLoop=0; KeyLoop<41; KeyLoop++)
				{
					KeyState[KeyLoop] = FALSE;
				}
				KeyState[VK_DOWN] = TRUE;

				//시작 안했으면 스타트로 만듬...
				if(GAMEMODE==NOSTART)
					GAMEMODE = START;
				else if(SnakeControl->GetLength() > 0)//꼬리가 달렸으면.
					GAMEMODE = FOODEAT;
			}
		}
		//게임 오버인 상태에서 엔터 누르면. 노 스타트로 바꿈.
		else if(GAMEMODE == GAMEOVER)
		{
			if(wParam == VK_RETURN)
			{
				for(KeyLoop=0; KeyLoop<41; KeyLoop++)
				{
					KeyState[KeyLoop] = FALSE;
				}
				KeyState[VK_RETURN] = TRUE;
				GAMEMODE = NOSTART;
			}
		}
		break;
	case WM_DESTROY:
		//Release ~
		ReleaseDC(hWnd, GlobalDC);
		DeleteAll();
		PostQuitMessage(WM_QUIT);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);

}
/************************************************************************/
/* 이까지 볼 거 없음													*/
/************************************************************************/

//랜더링
void Render()
{
	static bool onerun = true;
	switch(GAMEMODE)
	{
	case NOSTART: //시작 안하면 기본적인 것들은 그려준다. -_-/
		Background.Fill(); //바탕 채우기
		Background.draw(); //영역 그리기
		Background.linedraw(); //선 긋기.
		SnakeControl->SetRandom(15);
		SnakeControl->DefaultPos(7,7); //기본적으로 출력.
		DisplayMessage(500, 15, RGB(255, 255, 255), "현재 점수 : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "클리어 점수 : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "만든놈 = 한경수");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		Flip(); //_-_ 플리핑.
		break;
	case START: //시작 하면 먹이 출력하고 키에 따른 반응을 보인다.
		Background.Fill();
		Background.draw();
		Background.linedraw();
		SnakeControl->FoodDraw(); //먹이 그려서.
		DisplayMessage(500, 15, RGB(255, 255, 255), "현재 점수 : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "클리어 점수 : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "만든놈 = 한경수");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		if(KeyState[VK_LEFT] == 1)
		{
			SnakeControl->LeftMove();
		}
		else if(KeyState[VK_RIGHT] == 1)
		{
			SnakeControl->RightMove();
		}
		else if(KeyState[VK_UP] == 1)
		{
			SnakeControl->TopMove();
		}
		else if(KeyState[VK_DOWN] == 1)
		{
			SnakeControl->BottomMove();
		}
		Flip();
		break;
	case FOODEAT:
		if(onerun)
		{
			if(KeyState[VK_LEFT] == 1)//KEYDOWN 에서 트루 처리 해준다. -_-;
			{
				SnakeControl->LeftMove();
			}
			else if(KeyState[VK_RIGHT] == 1)
			{
				SnakeControl->RightMove();
			}
			else if(KeyState[VK_UP] == 1)
			{
				SnakeControl->TopMove();
			}
			else if(KeyState[VK_DOWN] == 1)
			{
				SnakeControl->BottomMove();
			}
			Flip();
			onerun = false;
			delay(150);			
			break;
		}
		Background.Fill();
		Background.draw();
		Background.linedraw();
		SnakeControl->FoodDraw();
		if(KeyState[VK_LEFT] == 1)//KEYDOWN 에서 트루 처리 해준다. -_-;
		{
			SnakeControl->LeftMove();
		}
		else if(KeyState[VK_RIGHT] == 1)
		{
			SnakeControl->RightMove();
		}
		else if(KeyState[VK_UP] == 1)
		{
			SnakeControl->TopMove();
		}
		else if(KeyState[VK_DOWN] == 1)
		{
			SnakeControl->BottomMove();
 		}
		Flip();
		break;
	case GAMEOVER:
		Background.GameOverFill();
		break;
	}
}

//작업1

//w작업2