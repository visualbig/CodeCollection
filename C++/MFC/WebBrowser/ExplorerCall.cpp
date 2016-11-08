// Type 


class CDlg::CDialogEx
{
	/*
	...
	*/
	protected:
	DECLARE_EVENTSINK_MAP()
	
	
	
	void DocumentCompleteExplorerMini(LPDISPATCH pDisp, VARIANT* URL);
	void NavigateErrorExplorerMini(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Frame, VARIANT* StatusCode, BOOL* Cancel);
	void StatusTextChangeExplorerMini(LPCTSTR Text);

	private:
	CExplorer m_pExplorerEx;

};

//Cpp

BEGIN_EVENTSINK_MAP(CDlg, CParentDlg)
	ON_EVENT(CDlg, IDC_EXPLORER_MAIN, 259, CDlg::DocumentCompleteExplorerMini, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CDlg, IDC_EXPLORER_MAIN, 271, CDlg::NavigateErrorExplorerMini, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	ON_EVENT(CDlg, IDC_EXPLORER_MAIN, 102, CDlg::StatusTextChangeExplorerMini, VTS_BSTR)
END_EVENTSINK_MAP()



void CDlg::DocumentCompleteExplorerMini(LPDISPATCH pDisp, VARIANT* URL)
{
	HRESULT   hr;
	LPUNKNOWN lpUnknown;
	LPUNKNOWN lpUnknownWB = NULL;
	LPUNKNOWN lpUnknownDC = NULL;

	if (m_ExplorerScreen.GetSafeHwnd() == NULL)	return;

	lpUnknown = m_ExplorerScreen.GetControlUnknown();

	ASSERT(lpUnknown);

	if (lpUnknown){
		hr = lpUnknown->QueryInterface(IID_IUnknown, (LPVOID*)&lpUnknownWB);
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr)){
			return;
		}

		hr = pDisp->QueryInterface(IID_IUnknown, (LPVOID*)&lpUnknownDC);
		ASSERT(SUCCEEDED(hr));
		if (SUCCEEDED(hr) && lpUnknownWB == lpUnknownDC){
			CComVariant	szURL;
			szURL = *URL;
			szURL.ChangeType(VT_BSTR);
			CString strURL = szURL;

		}

		if (lpUnknownWB){
			lpUnknownWB->Release();
		}

		if (lpUnknownDC){
			lpUnknownDC->Release();
		}
	}

}

void CDlg::NavigateErrorExplorerMini(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Frame, VARIANT* StatusCode, BOOL* Cancel)
{
	HRESULT   hr;
	LPUNKNOWN lpUnknown;
	LPUNKNOWN lpUnknownWB = NULL;
	LPUNKNOWN lpUnknownDC = NULL;

	if (m_ExplorerScreen.GetSafeHwnd() == NULL)	return;

	lpUnknown = m_ExplorerScreen.GetControlUnknown();

	ASSERT(lpUnknown);

	if (lpUnknown){
		hr = lpUnknown->QueryInterface(IID_IUnknown, (LPVOID*)&lpUnknownWB);
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr)){
			return;
		}

		hr = pDisp->QueryInterface(IID_IUnknown, (LPVOID*)&lpUnknownDC);
		ASSERT(SUCCEEDED(hr));
		if (SUCCEEDED(hr) && lpUnknownWB == lpUnknownDC){
			CComVariant	szURL;
			szURL = *URL;
			szURL.ChangeType(VT_BSTR);
			CString strURL = szURL;
			strURL.MakeUpper();
		
		}

		if (lpUnknownWB){
			lpUnknownWB->Release();
		}

		if (lpUnknownDC){
			lpUnknownDC->Release();
		}
	}
}

void CDlg::StatusTextChangeExplorerMini(LPCTSTR Text)
{
	//window.status 값을 전달받아 처리하는 함수
	
	m_bStatus = FALSE;
}