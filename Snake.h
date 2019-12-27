#ifndef SNAKE_H_
#define SNAKE_H_
#include "GlobalHeader.h"

struct TailInfo
{
	int TailX;
	int TailY;
};
extern std::vector<TailInfo> PassHead;
class CSnake
{
private:
	bool onerun; //먹이감 처음에 한번만 랜덤 처리.
	//위치. 원래 15, 15 이지만 나머지 하나는 벽면에 충돌... 체크
public:
	CSnake(); // onerun = true 로 잡음.
	virtual ~CSnake(){}//가상 파괴 -_-;
	void DefaultPos(int x, int y); //기본 출력. 
	virtual BOOL LeftMove();  //왼쪽으로 이동
	virtual BOOL RightMove(); // 오른쪽으로 이동
	virtual BOOL TopMove(); //위로 이동
 	virtual BOOL BottomMove();//아래로 이동
	void TailAdd(){++iLength;} //꼬리 추가 +_+;
	void ZeroTime();// 시간 재할당
	void FoodDraw();//먹이 출력.
	virtual void Clear();
	virtual void SetRandom(int mx); //랜덤으로 정의.
	int GetLength(){return iLength;}
protected:
	static INT bPositionX, bPositionY;
	static INT bFoodPositionX, bFoodPositionY;
	static int iLength; // 꼬리의 길이. 대가리만 있을 땐 0;
	DWORD before; //.5초 관련.-_-
	DWORD result; //.5초 관련...
};


class CPlusSnake : public CSnake
{
private:
	bool onerun; //먹이감 처음에 한번만 랜덤 처리.
	int clearscore;
public:
	CPlusSnake();
	virtual BOOL LeftMove();  //왼쪽으로 이동
	virtual BOOL RightMove(); // 오른쪽으로 이동
	virtual BOOL TopMove(); //위로 이동
	virtual BOOL BottomMove();//아래로 이동
	virtual void SetRandom(int mx); //랜덤으로 정의.
	virtual void Clear();
};

#endif