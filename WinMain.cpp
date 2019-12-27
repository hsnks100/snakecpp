#include "GlobalHeader.h"
#pragma warning(disable:4100)
#pragma warning(disable:4098)
HDC GlobalDC; //DC... GetDC(hWnd)���� ���� ����.

LPDIRECTDRAWSURFACE7 lpLineImage; //���� �̹���.
LPDIRECTDRAWSURFACE7 lpFoodImg; //���� �̹���.
LPDIRECTDRAWSURFACE7 lpMouthImage; //�� ���� �̹���.
LPDIRECTDRAWSURFACE7 lpMouthImageR; // �� ������ �̹���.
LPDIRECTDRAWSURFACE7 lpMouthImageT; //�� ���� �̹���.
LPDIRECTDRAWSURFACE7 lpMouthImageB; //�� �Ʒ� �̹���.
LPDIRECTDRAWSURFACE7 lpTailImage; //���� �̹���.
HBITMAP GameOverImg; //���ӿ��� �̹���.


CBgdraw Background;
CSnake* SnakeControl = new CSnake;
HWND GlobalWnd;
//���� ���.
int GAMEMODE = NOSTART; //���� �� ��ŸƮ
BOOL KeyState[41] = {FALSE}; //Ű ����;

void Render(); //���.
//���� ���� WinMain.
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
	//DD �����Լ� ȣ��.
	InitDirectDraw(640, 480, 16);
	
	ImgLoad(); //�̹��� �ε�. -_-;

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
			FileCheck(); //������ ���ٰ� �˷���.
		}
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int KeyLoop; //Ű ���� �ؼ� �˻�.
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
		//�����߰ų� ���� ���߰ų� ���̸� �Ծ�����.
		if(GAMEMODE == NOSTART || GAMEMODE == START || GAMEMODE == FOODEAT)
		{
			//���� Ű ��������
			if(wParam == VK_LEFT)
			{
				for(KeyLoop=0; KeyLoop<41; KeyLoop++)
				{
					KeyState[KeyLoop] = FALSE;
				}
				KeyState[VK_LEFT] = TRUE;

				//���� �������� ��ŸƮ�� ����...
				if(GAMEMODE == NOSTART)
					GAMEMODE = START;
				else if(SnakeControl->GetLength() > 0)//������ �޷�����.
					GAMEMODE = FOODEAT;
			}
			//������ Ű �������� ���� FALSE ��Ű�� VK_RIGHT �� TRUEȭ
			else if(wParam == VK_RIGHT)
			{
				for(KeyLoop=0; KeyLoop<41; KeyLoop++)
				{
					KeyState[KeyLoop] = FALSE;
				}
				KeyState[VK_RIGHT] = TRUE;
				
				//���� �������� ��ŸƮ�� ����...
				if(GAMEMODE==NOSTART)
					GAMEMODE = START;
				else if(SnakeControl->GetLength() > 0)//������ �޷�����.
					GAMEMODE = FOODEAT;
			}
			//��Ű �������� ���� FALSE ��Ű�� VK_UP�� TRUEȭ.
			else if(wParam == VK_UP)
			{	
				for(KeyLoop=0; KeyLoop<41; KeyLoop++)
				{
					KeyState[KeyLoop] = FALSE;
				}
				KeyState[VK_UP] = TRUE;

				//���� �������� ��ŸƮ�� ����...
				if(GAMEMODE==NOSTART)
					GAMEMODE = START;
				else if(SnakeControl->GetLength() > 0)//������ �޷�����.
					GAMEMODE = FOODEAT;
			}
			//�ٿ�Ű �������� ���� FALSE ��Ű�� VK_DOWN �� TRUEȭ
			else if(wParam == VK_DOWN)
			{
				for(KeyLoop=0; KeyLoop<41; KeyLoop++)
				{
					KeyState[KeyLoop] = FALSE;
				}
				KeyState[VK_DOWN] = TRUE;

				//���� �������� ��ŸƮ�� ����...
				if(GAMEMODE==NOSTART)
					GAMEMODE = START;
				else if(SnakeControl->GetLength() > 0)//������ �޷�����.
					GAMEMODE = FOODEAT;
			}
		}
		//���� ������ ���¿��� ���� ������. �� ��ŸƮ�� �ٲ�.
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
/* �̱��� �� �� ����													*/
/************************************************************************/

//������
void Render()
{
	static bool onerun = true;
	switch(GAMEMODE)
	{
	case NOSTART: //���� ���ϸ� �⺻���� �͵��� �׷��ش�. -_-/
		Background.Fill(); //���� ä���
		Background.draw(); //���� �׸���
		Background.linedraw(); //�� �߱�.
		SnakeControl->SetRandom(15);
		SnakeControl->DefaultPos(7,7); //�⺻������ ���.
		DisplayMessage(500, 15, RGB(255, 255, 255), "���� ���� : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "Ŭ���� ���� : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "����� = �Ѱ��");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		Flip(); //_-_ �ø���.
		break;
	case START: //���� �ϸ� ���� ����ϰ� Ű�� ���� ������ ���δ�.
		Background.Fill();
		Background.draw();
		Background.linedraw();
		SnakeControl->FoodDraw(); //���� �׷���.
		DisplayMessage(500, 15, RGB(255, 255, 255), "���� ���� : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "Ŭ���� ���� : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "����� = �Ѱ��");
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
			if(KeyState[VK_LEFT] == 1)//KEYDOWN ���� Ʈ�� ó�� ���ش�. -_-;
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
		if(KeyState[VK_LEFT] == 1)//KEYDOWN ���� Ʈ�� ó�� ���ش�. -_-;
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

//�۾�1

//w�۾�2