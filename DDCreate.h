#ifndef DDC_H_
#define DDC_H_
#include <ddraw.h>


extern LPDIRECTDRAWCLIPPER pClipper;
extern LPDIRECTDRAW7 lpDirectOBJ;
extern LPDIRECTDRAWSURFACE7 lpPrimarySurface;
extern LPDIRECTDRAWSURFACE7 lpBackSurface;
extern LPDIRECTDRAW lpdd;

extern LPDIRECTDRAWSURFACE7 lpLineImage; //선의 이미지.
extern LPDIRECTDRAWSURFACE7 lpFoodImg; //먹이 이미지.
extern LPDIRECTDRAWSURFACE7 lpMouthImage; //입 왼쪽 이미지.
extern LPDIRECTDRAWSURFACE7 lpMouthImageR; // 입 오른쪽 이미지.
extern LPDIRECTDRAWSURFACE7 lpMouthImageT; //입 위쪽 이미지.
extern LPDIRECTDRAWSURFACE7 lpMouthImageB; //입 아래 이미지.
extern LPDIRECTDRAWSURFACE7 lpTailImage; //꼬리 이미지.
extern HBITMAP GameOverImg; //게임 오버 이미지.

extern RECT rcScreen;
extern RECT rcView;
void Flip(void); // 필립! Blt 로 대체.
//에러 메세지
BOOL ErrorMessage(HWND hWnd, char* str);
//DD 생성 함수.
HRESULT InitDirectDraw(int x, int y, int colordepth);
//Release 함수.
HRESULT DeleteAll();
//글자 출력
void DisplayMessage(int x, int y, COLORREF color, char* msg,...);
//딜레이 주기
void delay(DWORD ms);
//이미지 로드.
void ImgLoad();
//파일 체크
void FileCheck();



#endif