#include <stdio.h>

int main(void)
{
	//문자, character
	// 1byte
	char c;
	//정수형 
	// 2 byte
	short s;
	// 4 byte
	int i;
	//실수형
	// 8 byte
	float f;
	// 8 byte
	double d = 10;
	//array 
	char cs[10];
	//array = 그냥 같은 데이터 타입을 조금 더 편하게 선언하고 싶다. 라는 욕구에서 기원
	//연속하면 조금더 처리하기 좋지 않을까?
	char lf[26];
	//%d = 정수형 format, %c = char, %s = string,
	printf("%lf\n", d);
	return 0;
}
