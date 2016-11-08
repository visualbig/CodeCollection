// FolderRelated.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <string>
#include <Windows.h>
#include <tchar.h>

#ifndef _UNICODE
	#define CtrString std::string
#else
	#define CtrString std::wstring
#endif


//���� ���� 
CtrString GetExeDirectory()
{
	TCHAR sPath[255];
	CtrString strDummyPath;
	CtrString strPath;
	DWORD dwLength = GetModuleFileName(::GetModuleHandle(NULL), sPath, MAX_PATH);
	strDummyPath = sPath;
	int szIndex;
	if (strDummyPath.size())
	{
		szIndex = strDummyPath.find_last_of('\\');
		strPath = strDummyPath.substr(0, szIndex);
		strPath += '\\';
	}
	return strPath;
}

//���� ����
BOOL CreateSetDirectory(CtrString strPath, int Index)
{
	Index = strPath.find('\\', Index + 1);
	
	CtrString DummyPath = strPath.substr(0, Index);
	CtrString CurrentPath = GetExeDirectory() + DummyPath;
	if (GetFileAttributes(CurrentPath.c_str()) == -1)		// ���� ���� ���� Ȯ��
	{ 
		CreateDirectory(CurrentPath.c_str(), NULL);
	}
	if (Index != -1)
	{
		CreateSetDirectory(strPath, Index);
	}


	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	CtrString Path = _T("Test\\WOW32\\CC");
	CreateSetDirectory(Path, 0);

	return 0;
}

