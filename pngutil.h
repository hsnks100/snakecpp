/*

*/

#ifndef	HDR_PNGSIMPLEDRAWUTIL
#define HDR_PNGSIMPLEDRAWUTIL

#include <windows.h>
#include <windowsx.h>

/*
 note!!!: �� �ҽ����� ����ϴ� RECT����ü ����� �ǹ̴� �׻� ������ ����.
          ����� �̸���� ������� �ʴ´�.
          left  : ���� ��������� x��ǥ
          top   : ���� ��������� y��ǥ
          right : ������ ������. ������� ��ǥ�� ���� �ƴ�!
          bottom: ������ ���γ���. ������� ��ǥ�� ���� �ƴ�!
*/

/*------------------------------------------------------------
 �׸��� ���� ��ƿ �Լ�
 RECT *�� �μ��� �־�� �� ũ�⳪ ������ �𸦶� �׳� NULL�� �־ �ȴ�.
---------------------------------------*/

int pngutDrawBmp2DC(
  HDC hdc,         // ��Ʈ���� �׸� �������� dc
  RECT *prcDest,   // ��µ� dc���� ����. NULL�� ��� 0,0���� ��Ʈ�� ũ�⸸ŭ �׸���.
  HBITMAP hbmp,    // �׸��� �ϴ� ��Ʈ��
  RECT *prcSrc     // ��Ʈ�ʿ��� �׸� �κ�. NULL�� ��� ���κ��� �׸���.
  );


/*------------------------------------------------------------
 PNG �ε� �Լ�.
 �� �Լ� ��� HBITMAP�� ��ȯ�ϸ�, ���� �ִ� �Լ��� ���ϴ�DC�� �׸� ��
 �ִ�. ��ȯ���� HBITMAP�� ����� ������ ��� �ݵ�� DeleteObject()��
 �����ؾ߸� �Ѵ�.

 ��) POINT   pngsiz;
     RECT    rcPng;
     HBITMAP hbm = NULL;

       // png������ �а� ũ�⸦ ��´�.
       hbm = LoadFilePng( "test.png", &pngsiz );
       if( hbm != NULL ) {
          // ũ�⸦ �����Ѵ�.
          rcPng.left = rcPng.top = 0;
          rcPng.right = pngsiz.x;
          rcPng.bottom = pngsiz.y;
          // dc�� ����Ѵ�.
          DrawBmp2DC( pDC->m_hDC, NULL, hbm, &rcPng );
          // ����� �������Ƿ� �����.
          DeleteObject( (HGDIOBJ)hbm );
       }

 # ���� ������ �������� �����ϻ��̴�. ������ ������ �ڵ��� ��� png�� �׷���
   �����찡 wm_paint�޽����� ���������� �ε��� �ؾ� �ϹǷ� �� ���� ����� �ƴϴ�.
   ������ �ε��� HBITMAP�� ���� �����ϰ� �ִٰ� �׷����� �Ҷ� �ε����� �׸��� ��
   �̻� �ʿ䰡 �������� DeleteObject()�� ����°� ����.

-----------------------------------------*/

// ���ҽ����� png�� �ε��Ѵ�.
// �����ϸ� ��Ʈ�� �ڵ��� ��ȯ, �����ϸ� NULL�� ��ȯ
HBITMAP pngutLoadResPng(
  char *szResName,  // ���ҽ� �̸�
  char *szResType,  // ���ҽ� Ÿ��
  POINT *pSize      // NULL�� �ƴ� ���� �Ѱ��ָ� png������ ����, ���� ũ�⸦ x, y����� �־��ش�.
  );

// ���Ͽ��� png�� �ε��Ѵ�.
HBITMAP pngutLoadFilePng(
  char *szPngFileName, // ���ϸ�
  POINT *pSize         // NULL�� �ƴ� ���� �Ѱ��ָ� png������ ����, ���� ũ�⸦ x, y����� �־��ش�.
  );


/*------------------------------------------------------------
 PNG �ε� & �׸��� �Լ�.
-----------------------------------------*/
int pngutDrawResPng( char *szResName, char *szResType, HDC hDCDest, RECT *pRc );
int pngutDrawFilePng( char *szPngFileName, HDC hDCDest, RECT *pRc );


/*------------------------------------------------------------
 PNG ���� �Լ�.
-----------------------------------------*/
int pngutSaveFilePng( char *szPngFileName, HDC hDCSrc, RECT *pRc, 
					  char *szTitle, char*szAuthor, char *szDesc );


#endif
