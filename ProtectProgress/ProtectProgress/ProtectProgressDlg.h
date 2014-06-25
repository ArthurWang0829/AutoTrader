
// ProtectProgressDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>
#include <tuple>

#define WM_SHOWTASK WM_USER+8

using namespace std;
// ���嵥�����ݵ�Ԫ ��������⣬��������
typedef tuple<HWND,CString,CString> WINTUPLE;
typedef vector<tuple<HWND,CString,CString>> TUPLEVEC;

// CProtectProgressDlg �Ի���
class CProtectProgressDlg : public CDialogEx
{
// ����
public:
	CProtectProgressDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PROTECTPROGRESS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	TUPLEVEC m_TupleVec;
	TUPLEVEC m_TupleAutoTraderVec;
	TUPLEVEC m_AutoTrader_Vec;
	WINTUPLE m_OK_Tuple;
	CWinThread *hCapThread;// ץȡ������ ʵʱ���½���
	// find the abort window
	bool restartSwitch;
	void GetTheAbortWin();
	void GetAutoTraderWin();

	void BeginProgress();
	static UINT RuntimeThread(LPVOID lpParameter);// ץȡ����
	void ReStartTradeMaster();
	void StartCaptureData();
	char* CString2CharPt( CString InputString );
	//
	HWND m_Abort_hwnd;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	NOTIFYICONDATA m_nid;
	// ��С������
	void LetItSmall();
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedStartcap();
};
