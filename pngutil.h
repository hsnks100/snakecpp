/*

*/

#ifndef	HDR_PNGSIMPLEDRAWUTIL
#define HDR_PNGSIMPLEDRAWUTIL

#include <windows.h>
#include <windowsx.h>

/*
 note!!!: 이 소스에서 사용하는 RECT구조체 멤버의 의미는 항상 다음과 같다.
          멤버의 이름대로 사용하지 않는다.
          left  : 영역 좌측상단의 x좌표
          top   : 영역 좌측상단의 y좌표
          right : 영역의 가로폭. 우측상단 좌표가 절대 아님!
          bottom: 영역의 세로높이. 우측상단 좌표가 절대 아님!
*/

/*------------------------------------------------------------
 그리기 관련 유틸 함수
 RECT *형 인수에 넣어야 할 크기나 영역을 모를땐 그냥 NULL을 넣어도 된다.
---------------------------------------*/

int pngutDrawBmp2DC(
  HDC hdc,         // 비트맵을 그릴 윈도우의 dc
  RECT *prcDest,   // 출력될 dc내의 영역. NULL일 경우 0,0부터 비트맵 크기만큼 그린다.
  HBITMAP hbmp,    // 그리려 하는 비트맵
  RECT *prcSrc     // 비트맵에서 그릴 부분. NULL일 경우 모든부분을 그린다.
  );


/*------------------------------------------------------------
 PNG 로딩 함수.
 두 함수 모두 HBITMAP를 반환하며, 위에 있는 함수로 원하는DC에 그릴 수
 있다. 반환받은 HBITMAP은 사용이 끝났을 경우 반드시 DeleteObject()로
 제거해야만 한다.

 예) POINT   pngsiz;
     RECT    rcPng;
     HBITMAP hbm = NULL;

       // png파일을 읽고 크기를 얻는다.
       hbm = LoadFilePng( "test.png", &pngsiz );
       if( hbm != NULL ) {
          // 크기를 셋팅한다.
          rcPng.left = rcPng.top = 0;
          rcPng.right = pngsiz.x;
          rcPng.bottom = pngsiz.y;
          // dc로 출력한다.
          DrawBmp2DC( pDC->m_hDC, NULL, hbm, &rcPng );
          // 사용이 끝났으므로 지운다.
          DeleteObject( (HGDIOBJ)hbm );
       }

 # 위의 예제는 어디까지나 예제일뿐이다. 실제로 저렇게 코딩할 경우 png가 그려진
   윈도우가 wm_paint메시지를 받을때마다 로딩을 해야 하므로 썩 좋은 방법은 아니다.
   가급적 로딩된 HBITMAP을 따로 보관하고 있다가 그려져야 할때 로딩없이 그리고 더
   이상 필요가 없어질때 DeleteObject()로 지우는게 좋다.

-----------------------------------------*/

// 리소스에서 png를 로딩한다.
// 성공하면 비트맵 핸들을 반환, 실패하면 NULL을 반환
HBITMAP pngutLoadResPng(
  char *szResName,  // 리소스 이름
  char *szResType,  // 리소스 타입
  POINT *pSize      // NULL이 아닌 값을 넘겨주면 png파일의 가로, 세로 크기를 x, y멤버에 넣어준다.
  );

// 파일에서 png를 로딩한다.
HBITMAP pngutLoadFilePng(
  char *szPngFileName, // 파일명
  POINT *pSize         // NULL이 아닌 값을 넘겨주면 png파일의 가로, 세로 크기를 x, y멤버에 넣어준다.
  );


/*------------------------------------------------------------
 PNG 로딩 & 그리기 함수.
-----------------------------------------*/
int pngutDrawResPng( char *szResName, char *szResType, HDC hDCDest, RECT *pRc );
int pngutDrawFilePng( char *szPngFileName, HDC hDCDest, RECT *pRc );


/*------------------------------------------------------------
 PNG 저장 함수.
-----------------------------------------*/
int pngutSaveFilePng( char *szPngFileName, HDC hDCSrc, RECT *pRc, 
					  char *szTitle, char*szAuthor, char *szDesc );


#endif
