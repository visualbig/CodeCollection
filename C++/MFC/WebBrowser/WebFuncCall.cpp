// Type 
CExplorer m_pExplorerEx;

//CPP

BOOL ExecuteJScript(const CString &strFunction)	 ///<< 웹 Func 호출
{
	BOOL bRet	= FALSE;
	if(strFunction.GetLength() == 0)	return bRet; 
	if(m_pExplorerEx == NULL)			return bRet;

	HRESULT     hr	= E_FAIL;
	CComVariant vtResult(0);
	CComPtr<IDispatch>      spDisp		= NULL;
	CComPtr<IHTMLDocument2> spDocument	= NULL;
	CComPtr<IHTMLWindow2>   spWindow	= NULL;

	spDisp = m_pExplorerEx->get_Document();    // 도큐먼트 인터페이스 구하기
	if(spDisp == NULL){
		return bRet;
	}

	hr = spDisp->QueryInterface(IID_IHTMLDocument2, (void **)&spDocument);
	spDisp = NULL;
	if(FAILED(hr) || spDocument == NULL){
		return bRet;
	}


	hr = spDocument->get_parentWindow(&spWindow);
	spDocument = NULL;
	if(SUCCEEDED(hr) && spWindow != NULL){
		hr = spWindow->execScript	(CComBSTR((LPCTSTR)strFunction)
									, CComBSTR(_T("JScript"))
									, &vtResult);
		if(SUCCEEDED(hr)){
			bRet	= TRUE;
		}
		spWindow = NULL;
	}

	return	bRet;
}
