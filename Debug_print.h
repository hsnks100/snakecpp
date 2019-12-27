#ifndef DE_PRINT_H_
#define DE_PRINT_H_
#include <stdlib.h>
#include <windows.h>
inline void forwardstr(char* str, const int* n) //n엔 ndig가 들어가겠다. -_-;
{
	int i;
	int strleng = strlen(str);
	char* dupstr = new char[strleng+1];
	int count = 0;
	for(i=*n; i!=strleng+1; i++)
	{
		dupstr[count] = str[i];
		++count;
	}
	count = 0;
	for(i=*n; i!=strleng; i++)
	{
		str[i+1] = dupstr[count];
		++count;
	}
	delete [] dupstr;
}
//문자열 넣으면...
inline void De_Print(const char* str)
{
	OutputDebugStringA(str);
	OutputDebugStringA("　\n");
}
//이건 됐고.


template <typename T>
inline void De_Print(const T& number, int antilogarithm)
{
	T dupn = number; //복제.
	int length = 0; //문자열의 길이.
	//자릿수 구해서 length 에 넣기.
	while(dupn)
	{
		++length;
		dupn /= 10;
	}


	//소수라면
	if(number - (int)number > 0)
	{
		int ndig, sign;// ecvt 함수에 쓰임.
		char* str; //출력 될 문자열...
		//ecvt 함수로 number 의 정보를 str에 넣음.(어떻게 들어가는가 디버깅 해보면 알음)
		str = ecvt(number, 15, &ndig, &sign); 
		//"." 도트를 찍기 위한 ... 한칸씩 뒤로 땡김.
		forwardstr(str, &ndig); //앞으로 한칸 -_-v
		str[ndig] = '.'; //위에서 구한 공백에 넣음;
		OutputDebugString(str); //출력
		OutputDebugString(" \n"); //줄 바꿈.
	}
	else
	{
		//dupn 은 자릿수 구할 때 쓰는 놈..;
		
		char *str = new char[length+2];
		itoa((int)number, str, antilogarithm);
		
		str[length] = '\n';
		str[length+1] = '\0';
		
		OutputDebugString(str);
		delete [] str;
	}
}


#endif