#ifndef BGDRAW_H_
#define BGDRAW_H_
#include <ddraw.h>
#include <windows.h>
class CBgdraw
{
private:
	RECT PlayScreen;//�÷��� �ϴ� ����
public:
	CBgdraw(); //������.
	void Fill(); //����� ȸ������.
	void draw(); //�׸��� ��.
	void linedraw();
	void GameOverFill();
};
#endif