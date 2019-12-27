#include "GlobalHeader.h"
CPlusSnake::CPlusSnake()
{
	// Construct
	result = 0;
	onerun = true;
	clearscore = 0;
}

/*virtual*/ BOOL CPlusSnake::LeftMove()
{
	result = timeGetTime()-before;
	if(result > 150) //시간이 이것 초과라면.
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "현재 점수 : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "클리어 점수 : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "만든놈 = 한경수");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		//끝 부분이 TRUE 라면 -_-
		if(bPositionX == 0)
		{
			GAMEMODE = GAMEOVER;
			SnakeControl->Clear();
			PassHead.erase(PassHead.begin(), PassHead.end());
			delete SnakeControl;
			SnakeControl = new CSnake;
			return FALSE;
		}

		TailInfo tempsave;
		tempsave.TailX = bPositionX;
		tempsave.TailY = bPositionY;
		PassHead.push_back(tempsave);
		--bPositionX;

		for(int TailClash=PassHead.size(); TailClash>=0; --TailClash)
		{
			if(PassHead[TailClash].TailX == bPositionX &&
				PassHead[TailClash].TailY == bPositionY)
			{
				GAMEMODE = GAMEOVER;
				SnakeControl->Clear();
				PassHead.erase(PassHead.begin(), PassHead.end());
				delete SnakeControl;
				SnakeControl = new CSnake;
				return FALSE;
			}
		}
		//만약 먹이 위에 올라왔으면 꼬리추가!
		if(bFoodPositionX == bPositionX && bFoodPositionY == bPositionY)
		{
			SnakeControl->TailAdd();
			clearscore++;
			if(clearscore==10-1)
			{
				MessageBox(GlobalWnd, "클리어 성공 -_-/", "축하..;;", MB_OK);
				GAMEMODE = GAMEOVER;
			}
			SnakeControl->SetRandom(15);
		}
		
		PassHead.erase(PassHead.begin(), PassHead.end()-SnakeControl->GetLength());
		before = timeGetTime();
	}
	//0.7초가 안되고 그림을 유지시킬 때.
	else if(result < 150)
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "현재 점수 : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "클리어 점수 : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "만든놈 = 한경수");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		RECT rect;

		//21는 여백이고, 28은 칸의 크기;
		//즉 28*높이를 top에 대입. 이하 동문.
		
		rect.top = 21+(28*bPositionY);
		rect.left = 21+(28*bPositionX);
		lpBackSurface->BltFast(rect.left, rect.top, lpMouthImage, NULL,
			DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		for(int Tailsize = PassHead.size(); Tailsize > 0; --Tailsize)
		{
			rect.top = 21+(28* PassHead[Tailsize-1].TailY);
			rect.left = 21+(28* PassHead[Tailsize-1].TailX);
			lpBackSurface->BltFast(rect.left, rect.top, lpTailImage, NULL,
				DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		}
	}
	return TRUE;
}

/*virtual*/ BOOL CPlusSnake::RightMove()
{
	// 
	result = timeGetTime()-before;
	if(result > 150) //시간이 이것 초과라면.
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "현재 점수 : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "클리어 점수 : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "만든놈 = 한경수");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		//끝 부분이 TRUE 라면 -_-
		if(bPositionX == 14)
		{
			GAMEMODE = GAMEOVER;
			SnakeControl->Clear();
			PassHead.erase(PassHead.begin(), PassHead.end());
			delete SnakeControl;
			SnakeControl = new CSnake;
			return FALSE;
		}
		
		
		// 밟고 있던 부분은 다 FALSE 로 만들어 버리고 왼쪽으로 한칸 가서 TRUE

		
		TailInfo tempsave;
		tempsave.TailX = bPositionX;
		tempsave.TailY = bPositionY;
		PassHead.push_back(tempsave);
		++bPositionX;
		
		for(int TailClash=PassHead.size(); TailClash>=0; --TailClash)
		{
			if(PassHead[TailClash].TailX == bPositionX &&
				PassHead[TailClash].TailY == bPositionY)
			{
				GAMEMODE = GAMEOVER;
				SnakeControl->Clear();
				PassHead.erase(PassHead.begin(), PassHead.end());
				delete SnakeControl;
				SnakeControl = new CSnake;
				return FALSE;
			}
		}

		//만약 먹이 위에 올라왔으면 꼬리추가!
		if(bFoodPositionX == bPositionX && bFoodPositionY == bPositionY)
		{
			SnakeControl->TailAdd();
			clearscore++;
			if(clearscore==60-1)
			{
				MessageBox(GlobalWnd, "클리어 성공 -_-/", "축하..;;", MB_OK);
				GAMEMODE = GAMEOVER;	
			}
			SnakeControl->SetRandom(15);
		}

		PassHead.erase(PassHead.begin(), PassHead.end()-SnakeControl->GetLength());
		before = timeGetTime();
	}
	//0.7초가 안되고 그림을 유지시킬 때.
	else if(result < 150)
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "현재 점수 : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "클리어 점수 : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "만든놈 = 한경수");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		RECT rect;
		//21는 여백이고, 28은 칸의 크기;
		//즉 28*높이를 top에 대입. 이하 동문.
		rect.top = 21+(28*bPositionY);
		rect.left = 21+(28*bPositionX);
		lpBackSurface->BltFast(rect.left, rect.top, lpMouthImageR, NULL,
			DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		for(int Tailsize = PassHead.size(); Tailsize > 0; --Tailsize)
		{
			rect.top = 21+(28* PassHead[Tailsize-1].TailY);
			rect.left = 21+(28* PassHead[Tailsize-1].TailX);
			lpBackSurface->BltFast(rect.left, rect.top, lpTailImage, NULL,
				DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		}
	}
	return TRUE;
}

/*virtual*/ BOOL CPlusSnake::TopMove()
{
	// 
	result = timeGetTime()-before;
	if(result > 150) //시간이 이것 초과라면.
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "현재 점수 : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "클리어 점수 : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "만든놈 = 한경수");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		//끝 부분이 TRUE 라면 -_-
		if(bPositionY == 0)
		{
			GAMEMODE = GAMEOVER;
			SnakeControl->Clear();
			PassHead.erase(PassHead.begin(), PassHead.end());
			delete SnakeControl;
			SnakeControl = new CSnake;
			return FALSE;
		}

		TailInfo tempsave;
		tempsave.TailX = bPositionX;
		tempsave.TailY = bPositionY;
		PassHead.push_back(tempsave);
		--bPositionY;
		for(int TailClash=PassHead.size(); TailClash>0; --TailClash)
		{
			if(PassHead[TailClash].TailX == bPositionX &&
				PassHead[TailClash].TailY == bPositionY)
			{
				GAMEMODE = GAMEOVER;
				SnakeControl->Clear();
				PassHead.erase(PassHead.begin(), PassHead.end());
				delete SnakeControl;
				SnakeControl = new CSnake;
				return FALSE;
			}
		}
		//만약 먹이 위에 올라왔으면 꼬리추가!
		if(bFoodPositionX == bPositionX && bFoodPositionY == bPositionY)
		{
			SnakeControl->TailAdd();
			clearscore++;
			if(clearscore==60-1)
			{
				MessageBox(GlobalWnd, "클리어 성공 -_-/", "축하..;;", MB_OK);
				GAMEMODE = GAMEOVER;
			}
			SnakeControl->SetRandom(15);
		}
		
		
		PassHead.erase(PassHead.begin(), PassHead.end()-SnakeControl->GetLength());
		before = timeGetTime();
	}
	//0.7초가 안되고 그림을 유지시킬 때.
	else if(result < 150)
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "현재 점수 : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "클리어 점수 : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "만든놈 = 한경수");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		RECT rect;

		//21는 여백이고, 28은 칸의 크기;
		//즉 28*높이를 top에 대입. 이하 동문.
		rect.top = 21+(28*bPositionY);
		rect.left = 21+(28*bPositionX);
		lpBackSurface->BltFast(rect.left, rect.top, lpMouthImageT, NULL,
			DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		for(int Tailsize = PassHead.size(); Tailsize > 0; --Tailsize)
		{			
			rect.top = 21+(28* PassHead[Tailsize-1].TailY);
			rect.left = 21+(28* PassHead[Tailsize-1].TailX);
			lpBackSurface->BltFast(rect.left, rect.top, lpTailImage, NULL,
				DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		}
	}
	return TRUE;
}

/*virtual*/ BOOL CPlusSnake::BottomMove()
{
	//
	result = timeGetTime()-before;
	if(result > 150) //시간이 이것 초과라면.
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "현재 점수 : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "클리어 점수 : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "만든놈 = 한경수");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		//끝 부분이 TRUE 라면 -_-

		if(bPositionY == 14)
		{
			GAMEMODE = GAMEOVER;
			SnakeControl->Clear();
			PassHead.erase(PassHead.begin(), PassHead.end());
			delete SnakeControl;
			SnakeControl = new CSnake;
			return FALSE;
		}
		

		
		TailInfo tempsave;
		tempsave.TailX = bPositionX;
		tempsave.TailY = bPositionY;
		PassHead.push_back(tempsave);
		++bPositionY;
		for(int TailClash=PassHead.size(); TailClash>0; --TailClash)
		{
			if(PassHead[TailClash].TailX == bPositionX &&
				PassHead[TailClash].TailY == bPositionY)
			{
				GAMEMODE = GAMEOVER;
				SnakeControl->Clear();
				PassHead.erase(PassHead.begin(), PassHead.end());
				delete SnakeControl;
				SnakeControl = new CSnake;
				return FALSE;
			}
		}
		//만약 먹이 위에 올라왔으면 꼬리추가!
		if(bFoodPositionX == bPositionX && bFoodPositionY == bPositionY)
		{
			SnakeControl->TailAdd();
			clearscore++;
			if(clearscore==60-1)
			{
				MessageBox(GlobalWnd, "클리어 성공 -_-/", "축하..;;", MB_OK);
				GAMEMODE = GAMEOVER;
			}
			SnakeControl->SetRandom(15);
		}

		PassHead.erase(PassHead.begin(), PassHead.end()-SnakeControl->GetLength());
		before = timeGetTime();
	}
	//0.7초가 안되고 그림을 유지시킬 때.
	else if(result < 150)
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "현재 점수 : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "클리어 점수 : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "만든놈 = 한경수");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		RECT rect;
		//21는 여백이고, 28은 칸의 크기;
		//즉 28*높이를 top에 대입. 이하 동문.
		rect.top = 21+(28*bPositionY);
		rect.left = 21+(28*bPositionX);
		lpBackSurface->BltFast(rect.left, rect.top, lpMouthImageB, NULL,
			DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		for(int Tailsize = PassHead.size(); Tailsize > 0; --Tailsize)
		{			
			rect.top = 21+(28* PassHead[Tailsize-1].TailY);
			rect.left = 21+(28* PassHead[Tailsize-1].TailX);
			//책 갈피. 한번만 실행하게 만들겠음. 이상하게 자꾸 좌표가 이상해서 ...[?]
			lpBackSurface->BltFast(rect.left, rect.top, lpTailImage, NULL,
				DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		}
	}
	return TRUE;
}


/*virtual*/ void CPlusSnake::SetRandom(int mx)
{
	
	srand(time(NULL));
	int tempwidth=0;     //실질적으로(랜덤으로) 설정 할 가로.
	int tempheight=0;	 //실질적으로(랜덤으로) 설정 할 세로.
	int count=0;
	bool loopcontinue = true;
	while(PassHead.size() != (unsigned)count || loopcontinue==true)
	{
		count = 0;
		tempwidth = rand() % mx;
		tempheight = rand() % mx;
		for(int wh=PassHead.size(); wh>0; --wh)
		{
			if( (PassHead[wh].TailX==tempwidth && PassHead[wh].TailY==tempheight) ||
				(bPositionX == tempwidth && tempheight == bPositionY) )
			{
				loopcontinue = true;
				break;
			}
			else
			{
				count++;
				loopcontinue = false;
			}
		}
	}
	bFoodPositionX = tempwidth;
	bFoodPositionY = tempheight;
}


/*virtual*/ void CPlusSnake::Clear()
{
	// 
	CSnake::Clear();
	clearscore = 0;
}
