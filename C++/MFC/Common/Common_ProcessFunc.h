#pragma once

#include <time.h>
#include <atltime.h>
#include <Mshtml.h>



class CCommon_ProcessFunc
{
public:
	CCommon_ProcessFunc()	{}
	~CCommon_ProcessFunc()	{}

public:
	static CString	GetMainExePath();				///< ���� ������ ��θ� ������
	static BOOL		ShellExecute(const CString& sFileName, const CString& sParameter = _T(""));		///< �ش� ������ ������
	static BOOL		ProcessMessage(UINT nMsg, LPCTSTR sCaptionName, LPCTSTR sTransMessage = _T(""), CWnd* chWnd = NULL);	///< �ٸ� ���μ����� �޽��� ������
	static HWND		FindWindow(LPCTSTR sCaptionName);	///< �ٸ� ���μ��� ã��
	static void		TopWindow(HWND hWnd);				///< �׻� �ش� �����찡 �ֻ�ܿ� �ߵ���
	static BOOL		Redundancycheck(LPCTSTR sCaptionName); ///< �ٸ� ���μ��� ���� ���� Check
	static void		Wait(DWORD dwMillisecond);				///< Sleep ��ü�Լ�
	static void		Wait(DWORD dwMillisecond, HWND hWnd);	///< �����Ѱ� ���� �Լ����� ���ѷ����߻��ɼ�����
};



inline
CString CCommon_ProcessFunc::GetMainExePath()
{
	CString szPathName(_T(""));
	if (::GetModuleFileName(::GetModuleHandle(NULL)
		, szPathName.GetBuffer(_MAX_PATH)
		, _MAX_PATH) == 0){
		szPathName = _T("");
		return szPathName;
	}
	szPathName.ReleaseBuffer();
	int	nIndex = szPathName.ReverseFind('\\');
	szPathName = szPathName.Left(nIndex);

	return szPathName;
}

inline
BOOL CCommon_ProcessFunc::ShellExecute(const CString& sFileName, const CString& sParameter)
{
	SHELLEXECUTEINFO cs;
	CString sPath;
	sPath = GetMainExePath() + '\\' + sFileName;
	ZeroMemory(&cs, sizeof(cs));
	cs.cbSize = sizeof(cs);
	cs.lpVerb = _T("open");
	cs.lpFile = sPath;
	cs.lpParameters = sParameter;

	cs.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOCLOSEPROCESS;
	cs.nShow = SW_SHOWDEFAULT;

	if (ShellExecuteEx(&cs) == FALSE)
		return FALSE;

	return TRUE;
}

inline
BOOL CCommon_ProcessFunc::ProcessMessage(UINT nMsg, LPCTSTR sCaptionName, LPCTSTR sTransMessage, CWnd* chWnd)
{
	COPYDATASTRUCT cds;

	TCHAR buf[1024];

	_stprintf_s(buf, _T("%s"), sTransMessage);


	cds.cbData = sizeof(TCHAR) * 1024;
	//cds.dwData = TEL_INFO;
	cds.lpData = buf;

	HWND hWnd = FindWindow(sCaptionName);


	::SendMessage(hWnd, nMsg, (WPARAM)&chWnd, (LPARAM)&cds);
	return 0;

}

inline
HWND CCommon_ProcessFunc::FindWindow(LPCTSTR sCaptionName)
{
	TCHAR caption[1024];
	_stprintf_s(caption, _T("%s"), sCaptionName);

	HWND hWnd = ::FindWindow(NULL, caption);


	return hWnd;

}

inline
void CCommon_ProcessFunc::TopWindow(HWND hWnd)
{
	if (::GetForegroundWindow() != hWnd){
		HWND h_active_wnd = ::GetForegroundWindow();
		if (h_active_wnd != NULL){
			DWORD thread_id = GetWindowThreadProcessId(h_active_wnd, NULL);
			DWORD current_thread_id = GetCurrentThreadId();
			if (current_thread_id != thread_id){
				if (AttachThreadInput(current_thread_id, thread_id, TRUE)){
					BringWindowToTop(hWnd);
					AttachThreadInput(current_thread_id, thread_id, FALSE);
				}
			}
		}
	}
}


inline
BOOL CCommon_ProcessFunc::Redundancycheck(LPCTSTR sCaptionName)
{
	HWND hWnd = FindWindow(sCaptionName);

	if (hWnd)
		return TRUE;

	return FALSE;
}


inline
void CCommon_ProcessFunc::Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart, dwTest, dwThreadID;
	BOOL bSleepChk = FALSE;
	HANDLE hThread = NULL;
	DWORD pID;

	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

}


inline
void CCommon_ProcessFunc::Wait(DWORD dwMillisecond, HWND hWnd)
{
	MSG msg;
	DWORD dwStart, dwTest, dwThreadID;
	BOOL bSleepChk = FALSE;
	HANDLE hThread = NULL;
	DWORD pID;

	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

}