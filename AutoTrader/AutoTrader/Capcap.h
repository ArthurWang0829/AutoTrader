#pragma once
#include <vector>
#include <pcap.h>
#include <atlstr.h>
#include <afx.h>
using namespace std;
//using namespace ATL;

struct ListData
{
	char ID[10];
	char TotalPacket[10];
	bool Falg;
	char Protocol[20];
	char sIP[16],sMac[19],sPort[10];
	char dIP[16],dMac[19],dPort[10];
	char Len[10];
	char Text[50];
};


class CCapcap
{
public:
	CCapcap(void);
	~CCapcap(void);

	// ��Ҫץȡ������
	vector<CString> m_Get_Config;
	// �߳̿���
	bool StartCapture();
	bool StopCapture();
	// ���ó�����
	bool SetConfig();
	vector<CString> GetConfig();
	bool AddConfig();

	static void DecodeChar(char *data,DWORD len);
	// ��ȡ��ʱ��¼�ļ�

public:
	// ��ֹ�����ж�
	bool bThreadStop;

private:
	
	// �������б�
	vector<CString> m_AdapterNameList;
	vector<CString> m_AdapterDescriptionList;
	pcap_if_t *AllDevs;
	// ��ѡ������������
	static CString AdapterName;
	// ��ʱ�ļ�·��
	static CString CapFilePath;
	// ����
	CWinThread *hCapThread;//ץȡ����
	CRITICAL_SECTION  csThreadStop;
	HANDLE eThreadStart;

private:
	// ץȡѭ������ ������
	static UINT CapThread(LPVOID lpParameter);
	// ��ʱ��¼�ļ� ����
	void _CreateCapFile();
	// �������ݰ�
	void AnalsePacket(const pcap_pkthdr *header,const u_char *data);
	// ��ʼ��
	void _init_();
	// ��ȡ�������б�
	void _GetAdapterList();
};

