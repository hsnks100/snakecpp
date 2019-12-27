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
	bool onerun; //���̰� ó���� �ѹ��� ���� ó��.
	//��ġ. ���� 15, 15 ������ ������ �ϳ��� ���鿡 �浹... üũ
public:
	CSnake(); // onerun = true �� ����.
	virtual ~CSnake(){}//���� �ı� -_-;
	void DefaultPos(int x, int y); //�⺻ ���. 
	virtual BOOL LeftMove();  //�������� �̵�
	virtual BOOL RightMove(); // ���������� �̵�
	virtual BOOL TopMove(); //���� �̵�
 	virtual BOOL BottomMove();//�Ʒ��� �̵�
	void TailAdd(){++iLength;} //���� �߰� +_+;
	void ZeroTime();// �ð� ���Ҵ�
	void FoodDraw();//���� ���.
	virtual void Clear();
	virtual void SetRandom(int mx); //�������� ����.
	int GetLength(){return iLength;}
protected:
	static INT bPositionX, bPositionY;
	static INT bFoodPositionX, bFoodPositionY;
	static int iLength; // ������ ����. �밡���� ���� �� 0;
	DWORD before; //.5�� ����.-_-
	DWORD result; //.5�� ����...
};


class CPlusSnake : public CSnake
{
private:
	bool onerun; //���̰� ó���� �ѹ��� ���� ó��.
	int clearscore;
public:
	CPlusSnake();
	virtual BOOL LeftMove();  //�������� �̵�
	virtual BOOL RightMove(); // ���������� �̵�
	virtual BOOL TopMove(); //���� �̵�
	virtual BOOL BottomMove();//�Ʒ��� �̵�
	virtual void SetRandom(int mx); //�������� ����.
	virtual void Clear();
};

#endif