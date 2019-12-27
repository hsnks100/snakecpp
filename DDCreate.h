#ifndef DDC_H_
#define DDC_H_
#include <ddraw.h>


extern LPDIRECTDRAWCLIPPER pClipper;
extern LPDIRECTDRAW7 lpDirectOBJ;
extern LPDIRECTDRAWSURFACE7 lpPrimarySurface;
extern LPDIRECTDRAWSURFACE7 lpBackSurface;
extern LPDIRECTDRAW lpdd;

extern LPDIRECTDRAWSURFACE7 lpLineImage; //���� �̹���.
extern LPDIRECTDRAWSURFACE7 lpFoodImg; //���� �̹���.
extern LPDIRECTDRAWSURFACE7 lpMouthImage; //�� ���� �̹���.
extern LPDIRECTDRAWSURFACE7 lpMouthImageR; // �� ������ �̹���.
extern LPDIRECTDRAWSURFACE7 lpMouthImageT; //�� ���� �̹���.
extern LPDIRECTDRAWSURFACE7 lpMouthImageB; //�� �Ʒ� �̹���.
extern LPDIRECTDRAWSURFACE7 lpTailImage; //���� �̹���.
extern HBITMAP GameOverImg; //���� ���� �̹���.

extern RECT rcScreen;
extern RECT rcView;
void Flip(void); // �ʸ�! Blt �� ��ü.
//���� �޼���
BOOL ErrorMessage(HWND hWnd, char* str);
//DD ���� �Լ�.
HRESULT InitDirectDraw(int x, int y, int colordepth);
//Release �Լ�.
HRESULT DeleteAll();
//���� ���
void DisplayMessage(int x, int y, COLORREF color, char* msg,...);
//������ �ֱ�
void delay(DWORD ms);
//�̹��� �ε�.
void ImgLoad();
//���� üũ
void FileCheck();



#endif