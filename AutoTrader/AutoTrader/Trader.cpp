#include "StdAfx.h"
#include "Trader.h"
#include "AutoTrader.h"

// #define MainWinName _T("�����ڻ����Ͻ���ϵͳ(V3.0.12.5)--��7698037��")
// 
// // ���嵥�����ݵ�Ԫ ��������⣬��������
// typedef tuple<HWND,CString,CString> WINTUPLE;
// typedef vector<WINTUPLE> WINVEC;
// typedef vector<int> LayerIndex;
// typedef tuple<HWND,LayerIndex> WinIndex;
// typedef vector<WinIndex> MAININDEX;
// 
// static MAININDEX m_MainIndex;
// vector<WINVEC> m_MainVec;

//using namespace std;

BOOL CALLBACK EnumChild_Entrust(HWND hwnd,LPARAM lParam)
{
	CTrader *this2 = (CTrader*)lParam;

	if (hwnd == NULL)
	{
		return FALSE;
	}
	TCHAR szTitle[MAX_PATH] = {0};
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	CHAR szClassName[MAX_PATH];
	GetClassNameA(hwnd, szClassName, MAX_PATH);
	WINTUPLE tempTuple;
	get<0>(tempTuple) =hwnd;get<1>(tempTuple)=szTitle;get<2>(tempTuple)=szClassName;
	this2->m_Entrust_Tuple_Vec.push_back(tempTuple);
	return TRUE;
}


BOOL CALLBACK EnumChild_Status(HWND hwnd,LPARAM lParam)
{
	CTrader *this2 = (CTrader*)lParam;

	if (hwnd == NULL)
	{
		return FALSE;
	}
	TCHAR szTitle[MAX_PATH] = {0};
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	CHAR szClassName[MAX_PATH];
	GetClassNameA(hwnd, szClassName, MAX_PATH);
	WINTUPLE tempTuple;
	get<0>(tempTuple) =hwnd;get<1>(tempTuple)=szTitle;get<2>(tempTuple)=szClassName;
	this2->m_Status_Tuple_Vec.push_back(tempTuple);
	return TRUE;
}


BOOL CALLBACK EnumChild_1L(HWND hwnd,LPARAM lParam)
{
	CTrader *this2 = (CTrader*)lParam;

	if (hwnd == NULL)
	{
		return FALSE;
	}
	TCHAR szTitle[MAX_PATH] = {0};
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	CHAR szClassName[MAX_PATH];
	GetClassNameA(hwnd, szClassName, MAX_PATH);
	WINTUPLE tempTuple;
	get<0>(tempTuple) =hwnd;get<1>(tempTuple)=szTitle;get<2>(tempTuple)=szClassName;
	this2->m_TupleVec.push_back(tempTuple);

	return TRUE;
}


//*************************************
// ������:  	
// Ŀ��:	���ҳ��������̾��
// ʱ�䣺   2014/03/25
//*************************************
BOOL CALLBACK EnumMainWinTrade(HWND hwnd,LPARAM lParam)
{
	if (hwnd == NULL)
	{
		return FALSE;
	}

	TCHAR szTitle[MAX_PATH] = {0};
	LPWSTR* ss = new LPWSTR();
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	GetClassName(hwnd,*ss,10);
	//
	CTrader *this2 = (CTrader*)lParam;
	if (_tcsicmp(szTitle, MainWinName) == 0)
	{
		//::ShowWindow(hwnd,SW_SHOW);
		//LPRECT rect;
		//GetWindowRect(hwnd,rect);
		//::SetWindowPos(hwnd,HWND_BOTTOM,0,0,rect->left-rect->right, rect->top-rect->bottom,SWP_SHOWWINDOW);
		// ö�������Ӵ���
		EnumChildWindows(hwnd, EnumChild_1L, (LPARAM)this2);
	}
	return TRUE;
}




CTrader::CTrader(void)
{
	
	//(strrchr(szAppPath, '\\'))[0] = 0; 
	//////////////////////////////////////////////////////////////////////////
	EnumWindows(EnumMainWinTrade, (LPARAM)this);
	if (m_TupleVec.size() == 0)
	{
		theApp.MessageShow(_T("HS isn't run!"));
		return;
	}
	//
	int tempPos = FindWIN(m_TupleVec,_T("ί��[1]"),_T("TTabSheet"));
	if (tempPos != -1)
	{
		m_OrderList_Tuple = m_TupleVec.at(tempPos+1);
	}
	//
	//::ShowWindow(get<0>(m_OrderList_Tuple));
	m_bmp1 = theApp.m_AppPath + _T("bmp1.bmp");
	m_bmp2 = theApp.m_AppPath + _T("bmp2.bmp");
	//////////////////////////////////////////////////////////////////////////
	//	 ��ͼ����
	CDC dc;  
	CDC *pDC = &dc;//��ĻDC 
	HDC activeDC = ::GetWindowDC(get<0>(m_OrderList_Tuple));   //���Ҫ�����Ĵ��ڵ�hDC  
	pDC->Attach(activeDC);//��ȡ��ǰ����ڵ�DC  
	RECT rect;  
	::GetWindowRect(get<0>(m_OrderList_Tuple),&rect);//�õ����ڵĴ�С
	int Width = rect.right - rect.left;  
	int Height = rect.bottom - rect.top; 
	CDC memDC;//�ڴ�DC  
	memDC.CreateCompatibleDC(pDC);
	CBitmap memBitmap, *oldmemBitmap;//��������Ļ���ݵ�bitmap
	memBitmap.CreateCompatibleBitmap(pDC, Width, Height);
	oldmemBitmap = memDC.SelectObject(&memBitmap);//��memBitmapѡ���ڴ�DC 
	memDC.BitBlt(0, 0, Width, Height, pDC, 0, 0, SRCCOPY);//������Ļͼ���ڴ�DC
	BITMAP bmp;
	memBitmap.GetBitmap(&bmp);//���λͼ��Ϣ 
	
	FILE *fp = fopen(CString2CharPt(m_bmp1), "w+b"); 
	BITMAPINFOHEADER bih = {0};//λͼ��Ϣͷ  
	bih.biBitCount = bmp.bmBitsPixel;//ÿ�������ֽڴ�С  
	bih.biCompression = BI_RGB;  
	bih.biHeight = bmp.bmHeight;//�߶� 
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER); 
	bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//ͼ�����ݴ�С 
	bih.biWidth = bmp.bmWidth;//���
	BITMAPFILEHEADER bfh = {0};//λͼ�ļ�ͷ 
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//��λͼ���ݵ�ƫ����
	bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;//�ļ��ܵĴ�С
	bfh.bfType = (WORD)0x4d42;  
	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//д��λͼ�ļ�ͷ  
	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//д��λͼ��Ϣͷ  
	byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];//�����ڴ汣��λͼ����  
	GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, Height, p, 
		(LPBITMAPINFO) &bih, DIB_RGB_COLORS);//��ȡλͼ����  
	fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);//д��λͼ����  
	delete [] p;  
	fclose(fp);


	//////////////////////////////////////////////////////////////////////////
	int StatusPos = FindWIN(m_TupleVec,_T("PnlStatus"),_T("TPanel"));
	if (StatusPos != -1)
	{
		m_Status_Tuple = m_TupleVec.at(StatusPos);
		EnumChildWindows(get<0>(m_Status_Tuple),EnumChild_Status,(LPARAM)this);

		m_Query_Tuple = m_Status_Tuple_Vec.at(1);
	}
	int EntrustPos = FindWIN(m_TupleVec,_T("��ͨί��"),_T("TTabSheet"));
	{
		m_Entrust_Tuple = m_TupleVec.at(EntrustPos);
		EnumChildWindows(get<0>(m_Entrust_Tuple),EnumChild_Entrust,(LPARAM)this);

		m_Code_Tuple = m_Entrust_Tuple_Vec.at(7);
		m_OK_Tuple = m_Entrust_Tuple_Vec.at(14);// ȷ�ϰ�ť 14
		m_Value_Tuple = m_Entrust_Tuple_Vec.at(16);// �۸�16
		m_Volume_Tuple = m_Entrust_Tuple_Vec.at(17);// ���� 17
		m_OpenClose_Tuple = m_Entrust_Tuple_Vec.at(18);//���� 18
		m_BuySell_Tuple = m_Entrust_Tuple_Vec.at(19);// ��ƽ 19
	}
}


CTrader::~CTrader(void)
{

}

int CTrader::FindWIN( TUPLEVEC tupleVec,CString Title,CString ClassName )
{
	WINTUPLE temp;CString tempTitle;CString tempClassName;
	for (int i = 0; i < tupleVec.size(); i++)
	{
		temp = tupleVec.at(i);
		tempTitle = get<1>(temp);
		tempClassName = get<2>(temp);
		if (tempTitle == Title && tempClassName == ClassName)
		{
			return i;
		}
	}
	return -1;
}

bool CTrader::SetCode( CString Scode )
{
	//m_Code_Tuple
	char * clearStr = "";
	char tempChar;
	CString tempCStr;
	SendMessage(get<0>(m_Code_Tuple),WM_SETTEXT,2,LPARAM(clearStr));//���������
	for(int i=0; i<Scode.GetLength();i++)
	{
		tempCStr = Scode.GetAt(i);
		tempChar = *CString2CharPt(tempCStr);
		//char tempTest = 'a';
		SendMessage(get<0>(m_Code_Tuple), WM_CHAR, (WPARAM)tempChar, 0);//��д�ı���
	}

	return true;
}

char* CTrader::CString2CharPt( CString InputString )
{
	CString str = InputString;
	//ע�⣺����n��len��ֵ��С��ͬ,n�ǰ��ַ�����ģ�len�ǰ��ֽڼ����
	int n = str.GetLength();     // n = 14, len = 18
	//��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����
	int len = WideCharToMultiByte(CP_ACP,0,str,str.GetLength(),NULL,0,NULL,NULL);
	char * pFileName = new char[len+1];   //���ֽ�Ϊ��λ
	//���ֽڱ���ת���ɶ��ֽڱ���
	WideCharToMultiByte(CP_ACP,0,str,str.GetLength() + 1 ,pFileName,len + 1 ,NULL,NULL);
	return pFileName;
}

bool CTrader::SetValue( CString Svalue )
{
	char * clearStr = "";
	char tempChar;
	CString tempCStr;
	SendMessage(get<0>(m_Value_Tuple),WM_SETTEXT,2,LPARAM(clearStr));//���������
	for(int i=0; i<Svalue.GetLength();i++)
	{
		tempCStr = Svalue.GetAt(i);
		tempChar = *CString2CharPt(tempCStr);
		SendMessage(get<0>(m_Value_Tuple), WM_CHAR, (WPARAM)tempChar, 0);//��д�ı���
	}
	return true;
}

bool CTrader::SetVolume( CString Svolume )
{
	char * clearStr = "";
	char tempChar;
	CString tempCStr;
	SendMessage(get<0>(m_Volume_Tuple),WM_SETTEXT,2,LPARAM(clearStr));//���������
	for(int i=0; i<Svolume.GetLength();i++)
	{
		tempCStr = Svolume.GetAt(i);
		tempChar = *CString2CharPt(tempCStr);
		SendMessage(get<0>(m_Volume_Tuple), WM_CHAR, (WPARAM)tempChar, 0);//��д�ı���
	}
	return true;
}


//*************************************
// ������:  	SetOpenClose
// Ŀ��:	���ÿ�ƽ��  0������  1��ƽ�� 2��ƽ���
// ʱ�䣺   2014/03/25
//*************************************
bool CTrader::SetOpenClose( int Sbuy_sell )
{

	SendMessage(get<0>(m_OpenClose_Tuple),CB_SETCURSEL,Sbuy_sell,0);// Hwd, CB_SETCURSEL,  Index, 0

	return true;
}


//*************************************
// ������:  	SetBuy_Sell
// Ŀ��:	���ÿ�ƽ��  0������  1������
// ʱ�䣺   2014/03/25
//*************************************
bool CTrader::SetBuy_Sell( int Sbuild )
{
	SendMessage(get<0>(m_BuySell_Tuple),CB_SETCURSEL,Sbuild,0);// Hwd, CB_SETCURSEL,  Index, 0
	return true;
}


BOOL CALLBACK EnumChild_Error(HWND hwnd,LPARAM lParam)
{
	CTrader *this2 = (CTrader*)lParam;

	if (hwnd == NULL)
	{
		return FALSE;
	}
	TCHAR szTitle[MAX_PATH] = {0};
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	CHAR szClassName[MAX_PATH];
	GetClassNameA(hwnd, szClassName, MAX_PATH);
// 
// 	if (szClassName == "TMessageForm")
// 	{
	WINTUPLE tempTuple;
	get<0>(tempTuple) =hwnd;get<1>(tempTuple)=szTitle;get<2>(tempTuple)=szClassName;
	this2->m_Error_Tuple_Vec.push_back(tempTuple);
/*	}*/
	
}


//*************************************
// ������:  	
// Ŀ��:	���ҳ��������
// ʱ�䣺   2014/03/25
//*************************************
BOOL CALLBACK EnumMainWinError(HWND hwnd,LPARAM lParam)
{
	if (hwnd == NULL)
	{
		return FALSE;
	}

	TCHAR szTitle[MAX_PATH] = {0};
	//LPWSTR* ss = new LPWSTR();
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	//CHAR szClassName[MAX_PATH];
	TCHAR szClassName[MAX_PATH];
	GetClassName(hwnd, szClassName, MAX_PATH);
	//0x003de1d4 "TMessageForm"
	CTrader *this2 = (CTrader*)lParam;
	//if (_tcsicmp(szTitle, _T("����")) == 0 && ClassName == _T("TMessageForm"))
	if (_tcsicmp(szTitle,  _T("����")) == 0)
	{
		//WINTUPLE tempTuple;
		//if (szClassName ==  _T("TMessageForm") )
		if( _tcsicmp(szClassName, _T("TMessageForm")) == 0 )
		{
			// ö�������Ӵ���
			EnumChildWindows(hwnd, EnumChild_Error, (LPARAM)this2);
			//get<0>(tempTuple) =hwnd;get<1>(tempTuple)=szTitle;get<2>(tempTuple)=ClassName;
			//this2->m_Error_Tuple = tempTuple;
		}
		
	}
	return TRUE;
}


bool CTrader::SendOrder( void )
{
	CString OriStr = GetStatusText();
	//SendMessage(get<0>(m_OK_Tuple),CB_SETCURSEL,Sbuild,0);// Hwd, CB_SETCURSEL,  Index, 0
	SendMessage(get<0>(m_OK_Tuple),WM_LBUTTONDOWN,0,0);
	SendMessage(get<0>(m_OK_Tuple),WM_LBUTTONUP,0,0);
	//
	
	//
	
	//EnumChildWindows(get<0>(m_Error_Tuple),EnumChild_Error,(LPARAM)this);
	//
	return true;
}

CString CTrader::GetStatusText()
{
	//m_Status_Tuple
	TCHAR szTitle[MAX_PATH] = {0};
	GetWindowText(get<0>(m_Query_Tuple), szTitle, ARRAYSIZE(szTitle));
	CString res;
	res = szTitle;
	return res;
}



BOOL CALLBACK EnumChild_ErrorIO(HWND hwnd,LPARAM lParam)
{
	CTrader *this2 = (CTrader*)lParam;

	if (hwnd == NULL)
	{
		return FALSE;
	}
	TCHAR szTitle[MAX_PATH] = {0};
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	CHAR szClassName[MAX_PATH];
	GetClassNameA(hwnd, szClassName, MAX_PATH);

	// 	if (szClassName == "TMessageForm")
	// 	{
	WINTUPLE tempTuple;
	get<0>(tempTuple) =hwnd;get<1>(tempTuple)=szTitle;get<2>(tempTuple)=szClassName;
	//}


	this2->m_ErrorIO_Tuple_Vec.push_back(tempTuple);
}


BOOL CALLBACK EnumMainWinErrorIO(HWND hwnd,LPARAM lParam)
{
	if (hwnd == NULL)
	{
		return FALSE;
	}

	TCHAR szTitle[MAX_PATH] = {0};
	//LPWSTR* ss = new LPWSTR();
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	//CHAR szClassName[MAX_PATH];
	TCHAR szClassName[MAX_PATH];
	GetClassName(hwnd, szClassName, MAX_PATH);
	//0x003de1d4 "TMessageForm"
	CTrader *this2 = (CTrader*)lParam;
	//if (_tcsicmp(szTitle, _T("����")) == 0 && ClassName == _T("TMessageForm"))
	if (_tcsicmp(szTitle,  _T("��7698037��--ţ����")) == 0)
	{
		//WINTUPLE tempTuple;
		//if (szClassName ==  _T("TMessageForm") )
		if( _tcsicmp(szClassName, _T("#32770")) == 0 )
		{
			// ö�������Ӵ���
			EnumChildWindows(hwnd, EnumChild_ErrorIO, (LPARAM)this2);
			//get<0>(tempTuple) =hwnd;get<1>(tempTuple)=szTitle;get<2>(tempTuple)=ClassName;
			//this2->m_Error_Tuple = tempTuple;
		}
		
	}
	return TRUE;
}


void CTrader::CloseError()
{
	EnumWindows(EnumMainWinError, (LPARAM)this);
	EnumWindows(EnumMainWinErrorIO, (LPARAM)this);
	if (m_Error_Tuple_Vec.size() != 0)
	{
		m_Error_Tuple = m_Entrust_Tuple_Vec.at(0);
		SendMessage(get<0>(m_Error_Tuple),WM_LBUTTONDOWN,0,0);
		SendMessage(get<0>(m_Error_Tuple),WM_LBUTTONUP,0,0);
		m_Error_Tuple_Vec.pop_back();
	}
	if (m_ErrorIO_Tuple_Vec.size() != 0)
	{

		m_ErrorIO_Tuple = m_ErrorIO_Tuple_Vec.at(0);
		SendMessage(get<0>(m_ErrorIO_Tuple),WM_LBUTTONDOWN,0,0);
		SendMessage(get<0>(m_ErrorIO_Tuple),WM_LBUTTONUP,0,0);
		//Sleep(2000);
		m_ErrorIO_Tuple_Vec.clear();
	}
}



CString CTrader::TestList()
{
	LPLVCOLUMN listCol;
	char str_buff[255];
	int count = SendMessage(get<0>(m_OrderList_Tuple),WM_GETTEXT, 255,(LPARAM)str_buff);
	//SendMessage()
	//ReadProcessMemory()
	//LVM_INSERTCOLUMN,1,(LPARAM)&listCol
	//SendMessage(get<0>(m_OrderList_Tuple),LVM_INSERTCOLUMN,1,(LPARAM)&listCol);
	return _T("");
}

void CTrader::ListSnapshot(CString bmpPath)
{
	//////////////////////////////////////////////////////////////////////////
	//	 ��ͼ����
	CDC dc;  
	CDC *pDC = &dc;//��ĻDC 
	HDC activeDC = ::GetWindowDC(get<0>(m_OrderList_Tuple));   //���Ҫ�����Ĵ��ڵ�hDC  
	pDC->Attach(activeDC);//��ȡ��ǰ����ڵ�DC  
	RECT rect;  
	::GetWindowRect(get<0>(m_OrderList_Tuple),&rect);//�õ����ڵĴ�С
	int Width = rect.right - rect.left;  
	int Height = rect.bottom - rect.top; 
	CDC memDC;//�ڴ�DC  
	memDC.CreateCompatibleDC(pDC);
	CBitmap memBitmap, *oldmemBitmap;//��������Ļ���ݵ�bitmap
	memBitmap.CreateCompatibleBitmap(pDC, Width, Height);
	oldmemBitmap = memDC.SelectObject(&memBitmap);//��memBitmapѡ���ڴ�DC 
	memDC.BitBlt(0, 0, Width, Height, pDC, 0, 0, SRCCOPY);//������Ļͼ���ڴ�DC
	BITMAP bmp;
	memBitmap.GetBitmap(&bmp);//���λͼ��Ϣ 
	FILE *fp = fopen(CString2CharPt(bmpPath), "w+b"); 
	BITMAPINFOHEADER bih = {0};//λͼ��Ϣͷ  
	bih.biBitCount = bmp.bmBitsPixel;//ÿ�������ֽڴ�С  
	bih.biCompression = BI_RGB;  
	bih.biHeight = bmp.bmHeight;//�߶� 
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER); 
	bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//ͼ�����ݴ�С 
	bih.biWidth = bmp.bmWidth;//���
	BITMAPFILEHEADER bfh = {0};//λͼ�ļ�ͷ 
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//��λͼ���ݵ�ƫ����
	bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;//�ļ��ܵĴ�С
	bfh.bfType = (WORD)0x4d42;  
	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//д��λͼ�ļ�ͷ  
	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//д��λͼ��Ϣͷ  
	byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];//�����ڴ汣��λͼ����  
	GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, Height, p, 
		(LPBITMAPINFO) &bih, DIB_RGB_COLORS);//��ȡλͼ����  
	fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);//д��λͼ����  
	delete [] p;  
	fclose(fp);
}
