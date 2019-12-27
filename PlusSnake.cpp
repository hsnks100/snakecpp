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
	if(result > 150) //�ð��� �̰� �ʰ����.
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "���� ���� : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "Ŭ���� ���� : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "����� = �Ѱ��");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		//�� �κ��� TRUE ��� -_-
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
		//���� ���� ���� �ö������ �����߰�!
		if(bFoodPositionX == bPositionX && bFoodPositionY == bPositionY)
		{
			SnakeControl->TailAdd();
			clearscore++;
			if(clearscore==10-1)
			{
				MessageBox(GlobalWnd, "Ŭ���� ���� -_-/", "����..;;", MB_OK);
				GAMEMODE = GAMEOVER;
			}
			SnakeControl->SetRandom(15);
		}
		
		PassHead.erase(PassHead.begin(), PassHead.end()-SnakeControl->GetLength());
		before = timeGetTime();
	}
	//0.7�ʰ� �ȵǰ� �׸��� ������ų ��.
	else if(result < 150)
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "���� ���� : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "Ŭ���� ���� : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "����� = �Ѱ��");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		RECT rect;

		//21�� �����̰�, 28�� ĭ�� ũ��;
		//�� 28*���̸� top�� ����. ���� ����.
		
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
	if(result > 150) //�ð��� �̰� �ʰ����.
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "���� ���� : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "Ŭ���� ���� : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "����� = �Ѱ��");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		//�� �κ��� TRUE ��� -_-
		if(bPositionX == 14)
		{
			GAMEMODE = GAMEOVER;
			SnakeControl->Clear();
			PassHead.erase(PassHead.begin(), PassHead.end());
			delete SnakeControl;
			SnakeControl = new CSnake;
			return FALSE;
		}
		
		
		// ��� �ִ� �κ��� �� FALSE �� ����� ������ �������� ��ĭ ���� TRUE

		
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

		//���� ���� ���� �ö������ �����߰�!
		if(bFoodPositionX == bPositionX && bFoodPositionY == bPositionY)
		{
			SnakeControl->TailAdd();
			clearscore++;
			if(clearscore==60-1)
			{
				MessageBox(GlobalWnd, "Ŭ���� ���� -_-/", "����..;;", MB_OK);
				GAMEMODE = GAMEOVER;	
			}
			SnakeControl->SetRandom(15);
		}

		PassHead.erase(PassHead.begin(), PassHead.end()-SnakeControl->GetLength());
		before = timeGetTime();
	}
	//0.7�ʰ� �ȵǰ� �׸��� ������ų ��.
	else if(result < 150)
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "���� ���� : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "Ŭ���� ���� : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "����� = �Ѱ��");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		RECT rect;
		//21�� �����̰�, 28�� ĭ�� ũ��;
		//�� 28*���̸� top�� ����. ���� ����.
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
	if(result > 150) //�ð��� �̰� �ʰ����.
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "���� ���� : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "Ŭ���� ���� : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "����� = �Ѱ��");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		//�� �κ��� TRUE ��� -_-
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
		//���� ���� ���� �ö������ �����߰�!
		if(bFoodPositionX == bPositionX && bFoodPositionY == bPositionY)
		{
			SnakeControl->TailAdd();
			clearscore++;
			if(clearscore==60-1)
			{
				MessageBox(GlobalWnd, "Ŭ���� ���� -_-/", "����..;;", MB_OK);
				GAMEMODE = GAMEOVER;
			}
			SnakeControl->SetRandom(15);
		}
		
		
		PassHead.erase(PassHead.begin(), PassHead.end()-SnakeControl->GetLength());
		before = timeGetTime();
	}
	//0.7�ʰ� �ȵǰ� �׸��� ������ų ��.
	else if(result < 150)
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "���� ���� : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "Ŭ���� ���� : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "����� = �Ѱ��");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		RECT rect;

		//21�� �����̰�, 28�� ĭ�� ũ��;
		//�� 28*���̸� top�� ����. ���� ����.
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
	if(result > 150) //�ð��� �̰� �ʰ����.
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "���� ���� : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "Ŭ���� ���� : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "����� = �Ѱ��");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		//�� �κ��� TRUE ��� -_-

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
		//���� ���� ���� �ö������ �����߰�!
		if(bFoodPositionX == bPositionX && bFoodPositionY == bPositionY)
		{
			SnakeControl->TailAdd();
			clearscore++;
			if(clearscore==60-1)
			{
				MessageBox(GlobalWnd, "Ŭ���� ���� -_-/", "����..;;", MB_OK);
				GAMEMODE = GAMEOVER;
			}
			SnakeControl->SetRandom(15);
		}

		PassHead.erase(PassHead.begin(), PassHead.end()-SnakeControl->GetLength());
		before = timeGetTime();
	}
	//0.7�ʰ� �ȵǰ� �׸��� ������ų ��.
	else if(result < 150)
	{
		DisplayMessage(500, 15, RGB(255, 255, 255), "���� ���� : %d", SnakeControl->GetLength());
		DisplayMessage(500, 250, RGB(255, 255, 255), "Ŭ���� ���� : 60");
		DisplayMessage(480, 330, RGB(255, 255, 255), "����� = �Ѱ��");
		DisplayMessage(480, 350, RGB(255, 255, 255), "hsnks100@hotmail.com");
		RECT rect;
		//21�� �����̰�, 28�� ĭ�� ũ��;
		//�� 28*���̸� top�� ����. ���� ����.
		rect.top = 21+(28*bPositionY);
		rect.left = 21+(28*bPositionX);
		lpBackSurface->BltFast(rect.left, rect.top, lpMouthImageB, NULL,
			DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		for(int Tailsize = PassHead.size(); Tailsize > 0; --Tailsize)
		{			
			rect.top = 21+(28* PassHead[Tailsize-1].TailY);
			rect.left = 21+(28* PassHead[Tailsize-1].TailX);
			//å ����. �ѹ��� �����ϰ� �������. �̻��ϰ� �ڲ� ��ǥ�� �̻��ؼ� ...[?]
			lpBackSurface->BltFast(rect.left, rect.top, lpTailImage, NULL,
				DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		}
	}
	return TRUE;
}


/*virtual*/ void CPlusSnake::SetRandom(int mx)
{
	
	srand(time(NULL));
	int tempwidth=0;     //����������(��������) ���� �� ����.
	int tempheight=0;	 //����������(��������) ���� �� ����.
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
