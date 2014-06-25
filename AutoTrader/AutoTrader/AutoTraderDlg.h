
// AutoTraderDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>
#include "ShowInfo.h"
#include "VspdcToMySQL.h"
#include "Trader.h"
#include "Strategy.h"
#include "AutoInfo.h"

 #include "pcap.h"
// #include <pcap\usb.h>
 //#include <inc.h>

using namespace std;


#define WM_SHOWTASK WM_USER+8
// #ifndef ListData
// 
// struct ListData
// {
// 	char ID[10];
// 	char TotalPacket[10];
// 	bool Falg;
// 	char Protocol[20];
// 	char sIP[16],sMac[19],sPort[10];
// 	char dIP[16],dMac[19],dPort[10];
// 	char Len[10];
// 	char Text[50];
// };
// 
// #endif




// CAutoTraderDlg �Ի���
class CAutoTraderDlg : public CDialogEx
{
// ����
public:
	//CAutoTraderDlg();
	CAutoTraderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AUTOTRADER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	//CVspdCToMySQL * vspdctomysql = new CVspdCToMySQL;
	VspdcToMySQL * vspdctomysql_AutoTrader;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	// �����¼�
	afx_msg void OnBnClickedStartCapture();
	afx_msg void OnBnClickedStopCapture();
	afx_msg void OnClose();
	afx_msg void OnBnClickedShowdlgSwitch();
	afx_msg void OnBnClickedConnSql();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSmall();
	afx_msg void OnDestroy();
	//afx_msg LRESULT OnSystemTray(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNotifyIcon(WPARAM wParam, LPARAM lParam);

	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
//////////////////////////////////////////////////////////////////////////
public:
	NOTIFYICONDATA m_nid;
	CStrategy m_Strategy;
	// ���list
	vector<CString> AutoList;
	// ��ش����б���֤ÿ����Լֻ����һ��
	vector<CString> AutoListTime;
	// ��С��ͼ��
	NOTIFYICONDATA NotifyIcon;
	// ���ƽ��� ��ֹ�쳣�˳�
	CWinThread *hCapThread;// ץȡ������
	CWinThread *hCapErrorThread;// ������
	CRITICAL_SECTION  csThreadStop;
	HANDLE eThreadStart;
	bool bThreadStop; // �쳣��������
	CString CapFilePath;
	CString OldTimer; // �ɵ�ʱ��ֵ
	// ��ʾ��ȡ�ַ���	
	CStatic m_res_char;
	// ץȡ����б�
	vector<CString> m_resList;
	// ��ʾ�Ի���
	CShowInfo* m_ShowDlg;
	// trader
	CTrader* m_trader;
	// �ļ�
	FILE* fp;
	// �Ƿ��һ�����п���
	vector<bool> FirstRun;


//////////////////////////////////////////////////////////////////////////
// ������
	static UINT CapThread(LPVOID lpParameter);// ץȡ����
	static UINT CapErrorThread(LPVOID lpParameter);//  ������Ի���
	// ����ץȡ�����ַ���
	vector<CString> SplitString(CString input);
	// ���ݿ��������
	void InsertSQL(vector<CString> input);
	void InsertSQL(vector<CString> input, CString TableName);
	// ������ʾ�Ի���
	void updataShowDlg(vector<CString> input);
	// ��С������
	void LetItSmall();
	// Ԥ������

private:
	char* Wstr2Astr(WCHAR *wstr);
	char* CString2CharPt(CString InputString);
	// ����β��ת������
	void DecodeChar(char *data,DWORD len);
	// �и����
	CString GetTradeCode(CString data);
	// �ж��Ƿ�������
	bool IsNum(CString str);
	// vector���Ƿ���cstring
	bool VectorIsHas(vector<CString> vec, CString str);
	int VectorPos(vector<CString> vec, CString str);
	void WriteError(CString errorStr);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CComboBox m_Net_ComboBox;
	pcap_if_t m_AllDevs;
	vector<pcap_if_t> m_AllDevs_Vec;
	const char * m_adpter_char;
	afx_msg void OnCbnSelchangeComboNet();
	afx_msg void OnBnClickedStopStrategy();
	afx_msg void OnBnClickedSimButtom();
	CStatic m_ID_Test;
	void SetTestText(CStatic ss);
};

//extern CAutoTraderDlg theAppDlg;
