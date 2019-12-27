#include "GlobalHeader.h"
using namespace std;

std::vector<TailInfo> PassHead;


/* ������ ������ static ��... :)*/
INT CSnake::bPositionX = -1;
INT CSnake::bPositionY = -1;
INT CSnake::bFoodPositionX = -1;
INT CSnake::bFoodPositionY = -1;
int CSnake::iLength = 0; //ó���� �밡���� �����ϱ�.

CSnake::CSnake()
{
	// Construct
	result = 0;
	onerun = true;
}

//�⺻������ ������ �ִ� �׼��� ���Ѵ�. -_-;
void CSnake::DefaultPos(int x, int y)
{
	bPositionX = x;
	bPositionY = y;
	//��ǥ ���ٰ� �׸���.
	lpBackSurface->BltFast(21+(28*x), 21+(28*y), lpMouthImage, NULL, 
		DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
}

//�������� �̵�.
BOOL CSnake::LeftMove()
{
	TailInfo tempsave;
	result = timeGetTime()-before;
	if(result > 150) //�ð��� �̰� �ʰ����.
	{
		//�� �κ��� TRUE ��� -_-
		if(bPositionX == 0)
		{
			GAMEMODE = GAMEOVER;
			SnakeControl->Clear();
			PassHead.erase(PassHead.begin(), PassHead.end());
			return FALSE;
		}

		// ��� �ִ� �κ��� �� FALSE �� ����� ������ �������� ��ĭ ���� TRUE
		tempsave.TailX = bPositionX;
		tempsave.TailY = bPositionY;
		PassHead.push_back(tempsave);
		--bPositionX;

		//���� ���� ���� �ö������ �����߰�!
		if(bFoodPositionX == bPositionX && bFoodPositionY == bPositionY)
		{
			SnakeControl->TailAdd();
			delete SnakeControl;
			SnakeControl = new CPlusSnake;
			GAMEMODE = FOODEAT;
		}

		PassHead.erase(PassHead.begin(), PassHead.end()-1);
		before = timeGetTime();
	}
	//0.7�ʰ� �ȵǰ� �׸��� ������ų ��.
	else if(result < 150)
	{
		RECT rect;
		//21�� �����̰�, 28�� ĭ�� ũ��;
		//�� 28*���̸� top�� ����. ���� ����.
		rect.top = 21+(28*bPositionY);
		rect.left = 21+(28*bPositionX);
		lpBackSurface->BltFast(rect.left, rect.top, lpMouthImage, NULL,
			DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
	}
	return TRUE;
}


BOOL CSnake::RightMove()
{
	TailInfo tempsave;
	result = timeGetTime()-before;
	if(result > 150)
	{
		//�� �κ��� TRUE ���. 

		if(bPositionX == 14)
		{
			GAMEMODE = GAMEOVER;
			SnakeControl->Clear();
			PassHead.erase(PassHead.begin(), PassHead.end());
			return FALSE;
		}

		tempsave.TailX = bPositionX;
		tempsave.TailY = bPositionY;
		PassHead.push_back(tempsave);
		++bPositionX;

		//���� ���̸� �Ծ��ٸ� ���� �߰��ϰ� �Ļ�Ŭ������ �Ҵ�.
		if(bFoodPositionX == bPositionX && bFoodPositionY == bPositionY)
		{
			SnakeControl->TailAdd();
			delete SnakeControl;
			SnakeControl = new CPlusSnake;
			GAMEMODE = FOODEAT;
		}
				
		PassHead.erase(PassHead.begin(), PassHead.end()-1);
		before = timeGetTime();
	}
	//0.7�ʰ� �ȵǰ� �׸��� ������ų ��.
	else if(result < 150)
	{
		RECT rect;
		
		rect.top = 21+(28*bPositionY);
		rect.left = 21+(28*bPositionX);
		lpBackSurface->BltFast(rect.left, rect.top, lpMouthImageR, NULL,
			DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
	}
	return TRUE;
}


BOOL CSnake::TopMove()
{
	TailInfo tempsave;
	result = timeGetTime()-before;
	if(result > 150)
	{
		//�� �κ��� TRUE ���. 
		if(bPositionY == 0)
		{
			GAMEMODE = GAMEOVER;
			SnakeControl->Clear();
			PassHead.erase(PassHead.begin(), PassHead.end());
			return FALSE;
		}
		

		// ��� �ִ� �κ��� �� FALSE �� ����� ������ �������� ��ĭ ���� TRUE
		
		
		tempsave.TailX = bPositionX;
		tempsave.TailY = bPositionY;
		PassHead.push_back(tempsave);
		

		--bPositionY;
		//���� ���̸� �Ծ��ٸ� ���� �߰��ϰ� �Ļ�Ŭ������ �Ҵ�.
		if(bFoodPositionX == bPositionX && bFoodPositionY == bPositionY)
		{
			SnakeControl->TailAdd();
			delete SnakeControl;
			SnakeControl = new CPlusSnake;
			
			GAMEMODE = FOODEAT;
		}

		
		PassHead.erase(PassHead.begin(), PassHead.end()-1);
		before = timeGetTime();
	}		
	//0.7�ʰ� �ȵǰ� �׸��� ������ų ��.
	else if(result < 150)
	{
		RECT rect;
		
		rect.top = 21+(28*bPositionY);
		rect.left = 21+(28*bPositionX);
		lpBackSurface->BltFast(rect.left, rect.top, lpMouthImageT, NULL,
			DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
	}
	return TRUE;
}

BOOL CSnake::BottomMove()
{
	TailInfo tempsave;
	result = timeGetTime()-before;
	if(result > 150)
	{
		//�� �κ��� TRUE ���. 
		if(bPositionY == 14)
		{
			GAMEMODE = GAMEOVER;
			SnakeControl->Clear();
			PassHead.erase(PassHead.begin(), PassHead.end());
			return FALSE;
		}
		
		// ��� �ִ� �κ��� �� FALSE �� ����� ������ �������� ��ĭ ���� TRUE
		
		
		tempsave.TailX = bPositionX;
		tempsave.TailY = bPositionY;
		PassHead.push_back(tempsave);
		
		bPositionY++;
		//���� ���̸� �Ծ��ٸ� ���� �߰��ϰ� �Ļ�Ŭ������ �Ҵ�.
		if(bFoodPositionX == bPositionX && bFoodPositionY == bPositionY)
		{
			SnakeControl->TailAdd();
			delete SnakeControl;
			SnakeControl = new CPlusSnake;
			
			GAMEMODE = FOODEAT;
		}
		
		
		PassHead.erase(PassHead.begin(), PassHead.end()-1);
		before = timeGetTime();
	}
	//0.7�ʰ� �ȵǰ� �׸��� ������ų ��.
	else if(result < 150)
	{
		RECT rect;
		
		rect.top = 21+(28*bPositionY);
		rect.left = 21+(28*bPositionX);
		lpBackSurface->BltFast(rect.left, rect.top, lpMouthImageB, NULL,
			DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
	}
	return TRUE;
}
//�ð� �ٽ� ����.
void CSnake::ZeroTime()
{
	// 
	before = timeGetTime();
}

void CSnake::FoodDraw()
{
	//���̸�... ����.
	while(onerun)
	{
		SnakeControl->SetRandom(15);
		onerun = false;
	}
	RECT rect;


	//��� ��ƾ.
	rect.top = 21+(28*bFoodPositionY);
	rect.left = 21+(28*bFoodPositionX);
	lpBackSurface->BltFast(rect.left, rect.top, lpFoodImg, NULL,
		DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
}

//�������� ���̰� ��ǥ ����.
void CSnake::SetRandom(int mx)
{
	// 
	srand(time(NULL));
	bool loop = true;
	while(loop)
	{
		bFoodPositionX = rand() % mx;
		bFoodPositionY = rand() % mx;
		//��ǥ�� ���ٸ�
		if(bPositionX == bFoodPositionX && bFoodPositionY == bPositionY)
		{
			continue;
		}
		else
			loop = false;
	}
}

void CSnake::Clear()
{
	iLength=0;
	bPositionX = -1;
	bPositionY = -1;
}