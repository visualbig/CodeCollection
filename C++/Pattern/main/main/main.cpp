// main.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


#include "abstractfactory.h"


int AbstractFactory()
{
	CompilerFactory* pFactory;

	if (1)
		pFactory = new HPCompilerFactory;
	else
		pFactory = new SunCompilerFactory;

	Scanner* pScanner = pFactory->CreateScanner();
	Parser* pParser = pFactory->CreateParser();
	CodeGenerator* pCodeGenerator = pFactory->CreateCodeGenerator();
	Optimizer* pOptimizer = pFactory->CreateOptimizer();


	return 0;

}

//extern int AbstractFactory();

int _tmain(int argc, _TCHAR* argv[])
{
	int choice = 0;
	bool quit = false;


	while (1)
	{
		cout << "디자인 패턴 선택"			<< endl;
		cout << "1. Abstrace Factory"		<< endl;
		cout << "Q. 종료"					<< endl;
		choice = getchar();

		switch (choice)
		{
		case '1':
			AbstractFactory();
			break;
		case 'q':
		case 'Q':
		{
			quit = true;
		}
		break;

		}
		if (quit)
			break;
	}

	return 0;
}

