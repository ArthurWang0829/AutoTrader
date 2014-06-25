#pragma once
#include <tuple>
#include <vector>

using namespace std;

#define MainWinName _T("�����ڻ����Ͻ���ϵͳ(V3.0.12.5)--��7698037��")

// ���嵥�����ݵ�Ԫ ��������⣬��������
typedef tuple<HWND,CString,CString> WINTUPLE;
/*typedef vector<vector<tuple<HWND,CString,CString>>> WINVEC;*/
typedef vector<tuple<HWND,CString,CString>> TUPLEVEC;

// typedef vector<int> LayerIndex;
// typedef tuple<HWND,vector<int>> WinIndex;
// 
// typedef vector<WinIndex> MAININDEX;

class CTrader
{
public:
	CTrader(void);
	~CTrader(void);

public:
	//HWND Status_hwnd;
	WINTUPLE m_Status_Tuple;
	WINTUPLE m_Entrust_Tuple;
	TUPLEVEC m_TupleVec;
	TUPLEVEC m_Status_Tuple_Vec;
	TUPLEVEC m_Entrust_Tuple_Vec;
	TUPLEVEC m_Error_Tuple_Vec;
	TUPLEVEC m_ErrorIO_Tuple_Vec;

	WINTUPLE m_Code_Tuple;// Ʒ�ִ���
	WINTUPLE m_Query_Tuple;// ״̬����ѯ�ɹ�
	WINTUPLE m_OK_Tuple;// ȷ�ϰ�ť 14
	WINTUPLE m_Value_Tuple;// �۸�16
	WINTUPLE m_Volume_Tuple;// ���� 17
	WINTUPLE m_OpenClose_Tuple;//���� 18
	WINTUPLE m_BuySell_Tuple;// ��ƽ 19
	WINTUPLE m_Error_Tuple;// ���󴰿�
	WINTUPLE m_ErrorIO_Tuple;// ���󴰿�
	WINTUPLE m_OrderList_Tuple;// �б���

	CString m_bmp1;
	CString m_bmp2;

	void ListSnapshot(CString bmpPath);

	int FindWIN(TUPLEVEC tupleVec,CString Title,CString ClassName);
	//int FindWIN(TUPLEVEC tupleVec,CString Title,CString ClassName);
	
public:
	bool SetCode(CString Scode);
	bool SetValue(CString Svalue);
	bool SetVolume(CString Svolume);
	bool SetOpenClose(int Sbuy_sell);
	bool SetBuy_Sell(int Sbuild);
	bool SendOrder(void);
	CString GetStatusText();
	void CloseError();
	CString TestList();

private:
	char* CString2CharPt(CString InputString);

};

