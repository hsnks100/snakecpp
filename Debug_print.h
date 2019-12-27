#ifndef DE_PRINT_H_
#define DE_PRINT_H_
#include <stdlib.h>
#include <windows.h>
inline void forwardstr(char* str, const int* n) //n�� ndig�� ���ڴ�. -_-;
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
//���ڿ� ������...
inline void De_Print(const char* str)
{
	OutputDebugStringA(str);
	OutputDebugStringA("��\n");
}
//�̰� �ư�.


template <typename T>
inline void De_Print(const T& number, int antilogarithm)
{
	T dupn = number; //����.
	int length = 0; //���ڿ��� ����.
	//�ڸ��� ���ؼ� length �� �ֱ�.
	while(dupn)
	{
		++length;
		dupn /= 10;
	}


	//�Ҽ����
	if(number - (int)number > 0)
	{
		int ndig, sign;// ecvt �Լ��� ����.
		char* str; //��� �� ���ڿ�...
		//ecvt �Լ��� number �� ������ str�� ����.(��� ���°� ����� �غ��� ����)
		str = ecvt(number, 15, &ndig, &sign); 
		//"." ��Ʈ�� ��� ���� ... ��ĭ�� �ڷ� ����.
		forwardstr(str, &ndig); //������ ��ĭ -_-v
		str[ndig] = '.'; //������ ���� ���鿡 ����;
		OutputDebugString(str); //���
		OutputDebugString(" \n"); //�� �ٲ�.
	}
	else
	{
		//dupn �� �ڸ��� ���� �� ���� ��..;
		
		char *str = new char[length+2];
		itoa((int)number, str, antilogarithm);
		
		str[length] = '\n';
		str[length+1] = '\0';
		
		OutputDebugString(str);
		delete [] str;
	}
}


#endif