//맥주소 가지고 옴

unsigned long GetMacAddr(char* pMacAddr)
{
	if (pMacAddr == NULL){
		return -1;
	}

	PIP_ADAPTER_INFO pinfo = NULL;

	unsigned  long nError = 0;
	unsigned  long len = 0;
	nError = GetAdaptersInfo(pinfo, &len);
	if (nError == 0){
		if (pinfo){
			sprintf(pMacAddr, "%02X%02X%02X%02X%02X%02X", pinfo->Address[0]
				, pinfo->Address[1]
				, pinfo->Address[2]
				, pinfo->Address[3]
				, pinfo->Address[4]
				, pinfo->Address[5]);
			delete pinfo;
			pinfo = NULL;
		}
	}
	else if (nError == ERROR_NO_DATA){
		::OutputDebugString(_T("No adapter information exists for the local computer"));
	}
	else if (nError == ERROR_NOT_SUPPORTED){
		::OutputDebugString(_T("GetAdaptersInfo is not supported by the operating system running on the local computer"));
	}
	else if (nError == ERROR_BUFFER_OVERFLOW){
		pinfo = (PIP_ADAPTER_INFO)malloc(len);
		memset(pinfo, 0x00, len);
		nError = GetAdaptersInfo(pinfo, &len);
		if (nError == 0){
			if (pinfo){
				sprintf(pMacAddr, "%02X%02X%02X%02X%02X%02X", pinfo->Address[0]
					, pinfo->Address[1]
					, pinfo->Address[2]
					, pinfo->Address[3]
					, pinfo->Address[4]
					, pinfo->Address[5]);
				delete pinfo;
				pinfo = NULL;
			}
		}
	}

	return nError;
}


//Gateway Mac과 연결된 모든 Mac주소 Search


int RecvARP(char* pMacAddr, char* sGateAddr) const
{
	int nErrorCode = 0;
	
	ULONG ulMACAddr[2], nSize = 6;
	LPBYTE pBuffer;
	
	nErrorCode = SendARP(inet_addr(sGateAddr), 0, ulMACAddr, &nSize);

	if (nErrorCode == NO_ERROR)
	{
		pBuffer = (LPBYTE)ulMACAddr;

		sprintf(pMacAddr, "%02X%02X%02X%02X%02X%02X", pBuffer[0],
			pBuffer[1],
			pBuffer[2],
			pBuffer[3],
			pBuffer[4],
			pBuffer[5]);

	}

	return nErrorCode;

}


// 순서가 뒤죽박죽일수 있고 메인 맥으로 안잡힐수 있음(블루투스등...)
void IP_ADAPTER_INIT()
{
	unsigned  long len = sizeof(PIP_ADAPTER_INFO);
	PIP_ADAPTER_INFO pInfo = NULL;

	pInfo = (PIP_ADAPTER_INFO)malloc(len);
	m_nErrorCode = GetAdaptersInfo(pInfo, &len);

	if (m_nErrorCode == ERROR_NO_DATA){
		::OutputDebugString(_T("No adapter information exists for the local computer"));
	}
	else if (m_nErrorCode == ERROR_NOT_SUPPORTED){
		::OutputDebugString(_T("GetAdaptersInfo is not supported by the operating system running on the local computer"));
	}
	else if (m_nErrorCode == ERROR_BUFFER_OVERFLOW){
		pInfo = (PIP_ADAPTER_INFO)malloc(len);
		memset(pInfo, 0x00, len);
		m_nErrorCode = GetAdaptersInfo(pInfo, &len);
	}

	char* pGateChar = new char[128];
	char* pLocalChar = new char[128];
	char *sMacAddr = new char[128];
	char *sGateAddr = new char[128];

	PIP_ADDR_STRING pGateAddr = NULL;
	PIP_ADDR_STRING pLocalAddr = NULL;

	::ZeroMemory(pLocalChar, sizeof(pLocalChar));
	::ZeroMemory(pGateChar, sizeof(pGateChar));
	::ZeroMemory(sMacAddr, sizeof(sMacAddr));
	::ZeroMemory(sGateAddr, sizeof(sGateAddr));

	while (1)
	{
		if (pInfo)
		{
			pGateAddr = &pInfo->GatewayList;
			pLocalAddr = &pInfo->IpAddressList;
			pInfo = pInfo->Next;

			if (strlen(sGateAddr) == 0 && pGateAddr)
			{
				strcpy_s(sGateAddr, sizeof(pGateAddr->IpAddress.String) + 1, pGateAddr->IpAddress.String);

				RecvARP(pGateChar, sGateAddr);

				strcpy_s(sGateAddr, strlen(pGateChar) + 1, pGateChar);

				if (strlen(sGateAddr) == 0)
					continue;
			}


			if (strlen(sMacAddr) == 0 && pLocalAddr)
			{
				strcpy_s(sMacAddr, sizeof(pGateAddr->IpAddress.String) + 1, pGateAddr->IpAddress.String);

				RecvARP(pLocalChar, sMacAddr);

				strcpy_s(sMacAddr, strlen(pLocalChar) + 1, pLocalChar);

				if (strlen(sMacAddr) == 0)
					continue;
			}
			pInfo = NULL;
		}
		else
		{
			if (pLocalAddr)
			{
				m_pIPAddr = (char*)malloc(sizeof(pLocalAddr->IpAddress.String) + 1);
				strcpy(m_pIPAddr, pLocalAddr->IpAddress.String);
			}

	//		m_pLocaInfo = pLocalChar;	맥 주소
	//		m_pGateWayInfo = pGateChar; 게이트웨이 주소
			break;
		}

	}
}

unsigned long CSearchMacAddrEx::GetEquipList(char* pEquipList)	// 차선책 장비 이름에 의한 맥주소 추출
{
	unsigned  long len = sizeof(PIP_ADAPTER_INFO);
	PIP_ADAPTER_INFO pInfo = NULL;


	pInfo = (PIP_ADAPTER_INFO)malloc(len);
	m_nErrorCode = GetAdaptersInfo(pInfo, &len);

	if (m_nErrorCode == ERROR_NO_DATA){
		::OutputDebugString(_T("No adapter information exists for the local computer"));
	}
	else if (m_nErrorCode == ERROR_NOT_SUPPORTED){
		::OutputDebugString(_T("GetAdaptersInfo is not supported by the operating system running on the local computer"));
	}
	else if (m_nErrorCode == ERROR_BUFFER_OVERFLOW){
		pInfo = (PIP_ADAPTER_INFO)malloc(len);
		memset(pInfo, 0x00, len);
		m_nErrorCode = GetAdaptersInfo(pInfo, &len);
	}

	CString sMacAddr(_T(""));


	while (1)
	{
		if (pInfo)
		{
			sMacAddr += pInfo->Description;
			sMacAddr += "@";

			pInfo = pInfo->Next;
		}
		else
		{
			break;
		}

	}
	strcpy(pEquipList, sMacAddr.GetBuffer(0));

	return 0L;
}
