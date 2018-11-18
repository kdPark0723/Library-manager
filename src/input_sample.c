#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "");
	
	/* 회원가입 */
	int i;
	for (i = 0; i < 100; ++i)
	{
		wprintf(
			L"1\n"
			L"2018%04d\n"
			L"1234\n"
			L"홍길동\n"
			L"서울시 동작구 상도동 숭실대학교\n"
			L"01012345678\n",
			i);
	}
	
	/* 도서 추가 */
	wprintf(
		L"2\n"
		L"admin\n"
		L"1234\n");
	for (i = 0; i < 100; ++i)
	{
		wprintf(
			L"1\n"
			L"Cygwin과 함께 배우는 C 프로그래밍%d\n"
			L"홍릉과학출판사\n"
			L"김명호\n"
			L"%013lu\n"
			L"중앙도서관 3층 자연과학실\n"
			L"Y\n",
			i, (unsigned long)i*i);
	}
	
	/* 프로그램 종료 */
	wprintf(L"8\n");
	
	return 0;
}