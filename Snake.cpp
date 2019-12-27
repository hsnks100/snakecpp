#include "GlobalHeader.h"
using namespace std;

std::vector<TailInfo> PassHead;


/* 믿음직 스러운 static 들... :)*/
INT CSnake::bPositionX = -1;
INT CSnake::bPositionY = -1;
INT CSnake::bFoodPositionX = -1;
INT CSnake::bFoodPositionY = -1;
int CSnake::iLength = 0; //처음에 대가리만 있으니까.

CSnake::CSnake()
{
	// Construct
	result = 0;
	onerun = true;
}

//기본적으로 가만히 있는 액션을 취한다. -_-;
void CSnake::DefaultPos(int x, int y)
{
	bPositionX = x;
	bPositionY = y;
	//좌표 에다가 그린다.
	lpBackSurface->BltFast(21+(28*x), 21+(28*y), lpMouthImage, NULL, 
		DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
}

//왼쪽으로 이동.
BOOL CSnake::LeftMove()
{
	TailInfo tempsave;
	result = timeGetTime()-before;
	if(result > 150) //시간이 이것 초과라면.
	{
		//끝 부분이 TRUE 라면 -_-
		if(bPositionX == 0)
		{
			GAMEMODE = GAMEOVER;
			SnakeControl->Clear();
			PassHead.erase(PassHead.begin(), PassHead.end());
			return FALSE;
		}

		// 밟고 있던 부분은 다 FALSE 로 만들어 버리고 왼쪽으로 한칸 가서 TRUE
		tempsave.TailX = bPositionX;
		tempsave.TailY = bPositionY;
		PassHead.push_back(tempsave);
		--bPositionX;

		//만약 먹이 위에 올라왔으면 꼬리추가!
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
	//0.7초가 안되고 그림을 유지시킬 때.
	else if(result < 150)
	{
		RECT rect;
		//21는 여백이고, 28은 칸의 크기;
		//즉 28*높이를 top에 대입. 이하 동문.
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
		//끝 부분이 TRUE 라면. 

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

		//만약 먹이를 먹었다면 꼬리 추가하고 파생클래스로 할당.
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
	//0.7초가 안되고 그림을 유지시킬 때.
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
		//끝 부분이 TRUE 라면. 
		if(bPositionY == 0)
		{
			GAMEMODE = GAMEOVER;
			SnakeControl->Clear();
			PassHead.erase(PassHead.begin(), PassHead.end());
			return FALSE;
		}
		

		// 밟고 있던 부분은 다 FALSE 로 만들어 버리고 위로으로 한칸 가서 TRUE
		
		
		tempsave.TailX = bPositionX;
		tempsave.TailY = bPositionY;
		PassHead.push_back(tempsave);
		

		--bPositionY;
		//만약 먹이를 먹었다면 꼬리 추가하고 파생클래스로 할당.
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
	//0.7초가 안되고 그림을 유지시킬 때.
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
		//끝 부분이 TRUE 라면. 
		if(bPositionY == 14)
		{
			GAMEMODE = GAMEOVER;
			SnakeControl->Clear();
			PassHead.erase(PassHead.begin(), PassHead.end());
			return FALSE;
		}
		
		// 밟고 있던 부분은 다 FALSE 로 만들어 버리고 위로으로 한칸 가서 TRUE
		
		
		tempsave.TailX = bPositionX;
		tempsave.TailY = bPositionY;
		PassHead.push_back(tempsave);
		
		bPositionY++;
		//만약 먹이를 먹었다면 꼬리 추가하고 파생클래스로 할당.
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
	//0.7초가 안되고 그림을 유지시킬 때.
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
//시간 다시 저장.
void CSnake::ZeroTime()
{
	// 
	before = timeGetTime();
}

void CSnake::FoodDraw()
{
	//참이면... 섞음.
	while(onerun)
	{
		SnakeControl->SetRandom(15);
		onerun = false;
	}
	RECT rect;


	//출력 루틴.
	rect.top = 21+(28*bFoodPositionY);
	rect.left = 21+(28*bFoodPositionX);
	lpBackSurface->BltFast(rect.left, rect.top, lpFoodImg, NULL,
		DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
}

//랜덤으로 먹이감 좌표 저장.
void CSnake::SetRandom(int mx)
{
	// 
	srand(time(NULL));
	bool loop = true;
	while(loop)
	{
		bFoodPositionX = rand() % mx;
		bFoodPositionY = rand() % mx;
		//좌표가 같다면
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