#ifndef BGDRAW_H_
#define BGDRAW_H_
#include <ddraw.h>
#include <windows.h>
class CBgdraw
{
private:
	RECT PlayScreen;//플레이 하는 영역
public:
	CBgdraw(); //생성자.
	void Fill(); //배경을 회색으로.
	void draw(); //그리는 놈.
	void linedraw();
	void GameOverFill();
};
#endif