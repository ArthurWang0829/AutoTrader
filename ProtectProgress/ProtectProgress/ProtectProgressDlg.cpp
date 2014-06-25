
// ProtectProgressDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProtectProgress.h"
#include "ProtectProgressDlg.h"
#include "afxdialogex.h"
//#include "tinyxml.h"
//#include "tinystr.h"
#include "tinyxml.h"
#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProtectProgressDlg �Ի���
#define AbortWinName _T("Microsoft Visual C++ Debug Library")
#define AutoTraderWinName _T("AutoTrader")
#define AutoTrader _T("Auto Trader")


CProtectProgressDlg::CProtectProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProtectProgressDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProtectProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CProtectProgressDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CProtectProgressDlg::OnBnClickedOk)
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_BN_CLICKED(IDC_StartCap, &CProtectProgressDlg::OnBnClickedStartcap)
END_MESSAGE_MAP()


// CProtectProgressDlg ��Ϣ�������

BOOL CProtectProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	restartSwitch = false;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CProtectProgressDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CProtectProgressDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProtectProgressDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// start main progress while
	BeginProgress();
	//ReStartTradeMaster();
	//StartCaptureData();

	//CDialogEx::OnOK();
}

BOOL CALLBACK EnumChild_1L(HWND hwnd,LPARAM lParam)
{
	CProtectProgressDlg *this2 = (CProtectProgressDlg*)lParam;

	if (hwnd == NULL)
	{
		return FALSE;
	}
	TCHAR szTitle[MAX_PATH] = {0};
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	CHAR szClassName[MAX_PATH];
	GetClassNameA(hwnd, szClassName, MAX_PATH);
	WINTUPLE tempTuple;
	CString titleName(szTitle);
	CString className(szClassName);
	if (className == _T("Button") && titleName == _T("��ֹ(&A)") )
	{
		this2->m_Abort_hwnd = hwnd;
		SendMessage(hwnd,WM_LBUTTONDOWN,0,0);
		SendMessage(hwnd,WM_LBUTTONUP,0,0);
		this2->restartSwitch = true;
		Sleep(1000*5);
	}

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
	CProtectProgressDlg *this2 = (CProtectProgressDlg*)lParam;
	if (_tcsicmp(szTitle, AbortWinName) == 0)
	{
		// ö�������Ӵ���
		EnumChildWindows(hwnd, EnumChild_1L, (LPARAM)this2);
	}
	return TRUE;
}

void CProtectProgressDlg::GetTheAbortWin()
{
	m_TupleVec.clear();
	EnumWindows(EnumMainWinTrade, (LPARAM)this);

	//m_OK_Tuple = m_TupleVec.at(0);// ��ֹ��ť 14
}

UINT CProtectProgressDlg::RuntimeThread( LPVOID lpParameter )
{
	CProtectProgressDlg *this2;
	this2 = (CProtectProgressDlg *)lpParameter;

	while(1)
	{
		this2->GetAutoTraderWin();
		if (this2->m_TupleAutoTraderVec.size() == 0)
		{
			this2->restartSwitch = false;
			//this2->m_OK_Tuple = this2->m_TupleVec.at(0);// stop buttom
			this2->ReStartTradeMaster();
			this2->StartCaptureData();
		}

		this2->GetTheAbortWin();
		Sleep(1000*3);
		if (this2->restartSwitch == true )
		{
			this2->restartSwitch = false;
			//this2->m_OK_Tuple = this2->m_TupleVec.at(0);// stop buttom
			this2->ReStartTradeMaster();
			this2->StartCaptureData();
		}
		
	}
	return 0;
}


void CProtectProgressDlg::BeginProgress()
{
	hCapThread=AfxBeginThread(RuntimeThread,(LPVOID)this);
}

void CProtectProgressDlg::ReStartTradeMaster()
{
	CString TradeMasterPath = _T("C:\\Users\\Lio\\Documents\\Visual Studio 2012\\Projects\\AutoTrader\\test\\Win32\\AutoTrader.exe");
	char * Trademaster = CString2CharPt(TradeMasterPath);
	STARTUPINFO StartInfo;
	PROCESS_INFORMATION pinfo;
	//�Գ����������Ϣ�����κ��趨��ȫ����0
	memset(&StartInfo,0,sizeof(STARTUPINFO));
	StartInfo.cb = sizeof(STARTUPINFO);//�趨�ṹ�Ĵ�С

	//CreateProcess(TradeMasterPath,NULL,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&StartInfo,&pinfo);
	//ShellExecute(this->m_hWnd,"open","calc.exe","","",       SW_SHOW       );   
	//ShellExecute(NULL,"open","C:\\Test.txt",NULL,NULL,SW_SHOWNORMAL);
	int ss = WinExec(Trademaster,SW_SHOW);
}

char* CProtectProgressDlg::CString2CharPt( CString InputString )
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

BOOL CALLBACK EnumCapButtom(HWND hwnd,LPARAM lParam)
{
	CProtectProgressDlg *this2 = (CProtectProgressDlg*)lParam;

	if (hwnd == NULL)
	{
		return FALSE;
	}
	TCHAR szTitle[MAX_PATH] = {0};
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	CHAR szClassName[MAX_PATH];
	GetClassNameA(hwnd, szClassName, MAX_PATH);
	WINTUPLE tempTuple;
	CString titleName(szTitle);
	CString className(szClassName);
	if (className == _T("Button") && titleName == _T("��ʼץ��") )
	{
		this2->m_Abort_hwnd = hwnd;
		SendMessage(hwnd,WM_LBUTTONDOWN,0,0);
		SendMessage(hwnd,WM_LBUTTONUP,0,0);
	}

	return TRUE;
}

//*************************************
// ������:  	
// Ŀ��:	���ҳ��������̾��
// ʱ�䣺   2014/03/25
//*************************************
BOOL CALLBACK EnumAutoTraderWinTrade(HWND hwnd,LPARAM lParam)
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
	CProtectProgressDlg *this2 = (CProtectProgressDlg*)lParam;
	if (_tcsicmp(szTitle, AutoTraderWinName) == 0)
	{
		// ö�������Ӵ���
		EnumChildWindows(hwnd, EnumCapButtom, (LPARAM)this2);
	}
	return TRUE;
}

void CProtectProgressDlg::StartCaptureData()
{
	m_AutoTrader_Vec.clear();
	EnumWindows(EnumAutoTraderWinTrade, (LPARAM)this);
}


void CProtectProgressDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//////////////////////////////////////////////////////////////////////////
// 	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
// 	{
// 		CAboutDlg dlgAbout;
// 		dlgAbout.DoModal();
// 	}
	if(nID == SC_MAXIMIZE) //���
	{
		this->ShowWindow(SW_SHOW);
	}
	else if(nID == SC_MINIMIZE) //��С����������������
	{
		LetItSmall();
		//this->ShowWindow(SW_HIDE);
		
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
	//CDialogEx::OnSysCommand(nID, lParam);
}

void CProtectProgressDlg::LetItSmall()
{
	m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd    = this->m_hWnd;
	m_nid.uID     = IDR_MAINFRAME;
	m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // �Զ������Ϣ����
	m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	char * ch=new char[50];
	WCHAR *p=new WCHAR[25];
	p=_T("made by crazy!");
	//strcpy(m_nid.szTip, p);                // ��Ϣ��ʾ��Ϊ"����������"��VS2008 UNICODE������wcscpy_s()����
	lstrcpyW(m_nid.szTip, L"ProtectPrgess");
	::Shell_NotifyIcon(NIM_ADD,&m_nid );
	this->ShowWindow(SW_HIDE);
}

LRESULT CProtectProgressDlg::OnShowTask( WPARAM wParam, LPARAM lParam )
{
	if(wParam != IDR_MAINFRAME)
		return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP:                                        // �Ҽ�����ʱ�����˵�
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);                    // �õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();                    // ����һ������ʽ�˵�
			//menu.AppendMenu(MF_STRING, WM_DESTROY, "�ر�");
			//menu.AppendMenuW(MF_STRING,WM_DESTROY,"�˳�");
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK:                                 // ˫������Ĵ���
		{
			if (this->IsWindowVisible() == FALSE)
			{
				this->ShowWindow(SW_SHOWNORMAL);
			}
			else
			{
				LetItSmall();
			}
		}
		break;
	}
	return 0;
}


void CProtectProgressDlg::OnBnClickedStartcap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ReStartTradeMaster();
	StartCaptureData();
}



BOOL CALLBACK EnumAutoTrade(HWND hwnd,LPARAM lParam)
{
	if (hwnd == NULL)
	{
		return FALSE;
	}

	TCHAR szTitle[MAX_PATH] = {0};
	LPWSTR* ss = new LPWSTR();

	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	CHAR szClassName[MAX_PATH];
	GetClassNameA(hwnd, szClassName, MAX_PATH);
	CString comm(szTitle);
	CString className(szClassName);
	//
	CProtectProgressDlg *this2 = (CProtectProgressDlg*)lParam;
	if (comm == _T("AutoTrader") || comm == _T("Auto Trader"))
	{
		// ö�������Ӵ���
		tuple<HWND, CString, CString> tempTup;
		get<0>(tempTup) = hwnd;get<1>(tempTup) = comm;
		get<2>(tempTup) = className;
		this2->m_TupleAutoTraderVec.push_back(tempTup);
		//EnumChildWindows(hwnd, EnumChild_1L, (LPARAM)this2);
	}
	return TRUE;
}

void CProtectProgressDlg::GetAutoTraderWin()
{
	m_TupleAutoTraderVec.clear();
	EnumWindows(EnumAutoTrade, (LPARAM)this);
}
