#pragma once
#include "VspdcToMySQL.h"
#include "AutoInfo.h"
#include "Trader.h"
//#include "SplitedData.h"
#include "MinuteData.h"
#include "RunningData.h"
#include "RunningData5.h"
#include "RunningData15.h"


#ifndef  BUYORDER
#define  BUYORDER 0
#endif

#ifndef SELLORDER
#define SELLORDER 1
#endif

#ifndef NONEORDER
#define  NONEORDER -1
#endif

#ifndef FASTDEAL
#define  FASTDEAL 2;
#endif // !FASTDEAL


/*enum ORDER*/
// {
// 
// };

class CStrategy
{
public:
	CStrategy(void);
	CStrategy(CTrader *trader, CString code);
	CStrategy(CString code);
	~CStrategy(void);

	CString m_Code;
	//VspdcToMySQL * m_vspdctomysql;
	VspdcToMySQL * m_vspdctomysql_Strategy;
	bool m_TradeSwitch;
	void SetTradeCode(CString code);
	void SetTrader(CTrader *trader);
	void Start();
	void Sim();
	void SimProgress();
	void Stop();
	CString m_Date;
	// �и����
	CString GetTradeCode(CString data);

	void SetMySQLpt(VspdcToMySQL * sqlPt);

public:
	//
	int m_Sim_ID;
	CTrader *m_Trader;
	int m_Average;// ƽ���߼������� Ĭ��Ϊ20��
	CWinThread *hCapThread;// ץȡ������ ʵʱ���½���
	// 1��������
	vector<CMinuteData> m_Data;
	// ģ������
	// ʣ�µ�����
	CRunningData5 m_SimData5Min;
	CRunningData15 m_SimData15Min;
	vector<CMinuteData> m_Sim_Data;
	vector<vector<CString>> TestDatalist;
	vector<vector<CString>> SimDataList;
	// ����ʱ����
	CRunningData5 m_runData5Min;
	CRunningData15 m_runData15Min;
	// ׷��
	bool m_FastDeal;
	//
	bool IsIn5Min(CMinuteData dataStd, HSTimer inputTime);
	bool IsIn15Min(CMinuteData dataStd, HSTimer inputTime);
	// Open one buy tick
	bool OpenBuyTickStrategy(void);
	bool OpenBuyTickStrategy_Sim(void);
	// Open one sell tick
	bool OpenSellTickStrategy(void);
	bool OpenSellTickStrategy_Sim(void);
	// Close one buy tick
	bool CloseBuyTickStrategy(void);
	bool CloseBuyTickStrategy_Sim(void);

	bool CloseSellTickStrategy(void);
	bool CloseSellTickStrategy_Sim(void);
	// Sent Ord
	void SentOpenBuyOrd(CString inputValue);
	void SentOpenBuyOrd_Sim(CString inputValue);
	void SentOpenBuyOrd_Sim(vector<CString> inputData);
	void SentCloseBuyOrd(CString inputValue);
	void SentCloseBuyOrd_Sim(CString inputValue);
	void SentCloseBuyOrd_Sim(vector<CString> inputData);

	void SentOpenSellOrd(CString inputValue);
	void SentOpenSellOrd_Sim(CString inputValue);
	void SentOpenSellOrd_Sim(vector<CString> inputData);
	void SentCloseSellOrd(CString inputValue);
	void SentCloseSellOrd_Sim(CString inputValue);
	void SentCloseSellOrd_Sim(vector<CString> inputData);

	void SetSentOrderStauts(CString price,CString openclose, CString buysell, CString volume);
	void SetSentOrderStauts_Sim(CString price,CString openclose, CString buysell, CString volume);
	void SetSentOrderStauts_Sim(CString price,CString openclose, CString buysell, CString volume,CString time);
	void SetSentOrderStauts_Sim(CString price,CString openclose, CString buysell, CString volume,CString time,CString mark);
	// check is an order is senting now
	//bool IsOrdSentNow;
	bool IsOrdSentNow(void);
	bool IsOrdSentNow_Sim(void);
	bool hasHoldedNow(void);
	bool hasHoldedNow_Sim(void);

	int HolderType(void);
	int HolderType_Sim(void);
	// get current ord open or close
	OPENCLOSE GetCurrentOrderType_Sim();
	BUYSELL GetCurrentOrder_Sim();

	// check order wether successfull
	bool CheckOrderSuccessfull(CString nowValue);
	bool CheckOrderSuccessfullbySnap(CString nowValue);
	bool CheckOrderSuccessfull_Sim(CString nowValue);
	// change the order now to hold database
	void Transform_Delete_Order();
	void Transform_Delete_Order_Sim();
	void Transform_Delete_Order(CString nowValue);
	void Transform_Delete_Order_Sim(CString nowValue);
	// delete OrderNow
	void CleanOrderNowTable();
	void CleanOrderNowTable_Sim();
	void CleanOrderHold_Sim();
	// write log
	void WriteLogDatabase(CString price,CString openclose, CString buysell, CString volume);
	void WriteLogDatabase_Sim(CString price,CString openclose, CString buysell, CString volume, CString mark);
	void WriteLogDatabase_Sim(vector<CString> inputData,CString openclose, CString buysell, CString volume, CString mark);
	void WriteLogDatabase_Sim(CString price,CString openclose, CString buysell, CString volume, CString mark, CString timer);

	bool CompareBmp(CString bmp1, CString bmp2);

public:
	vector<CMinuteData> DataFactoryOneMinute(vector<vector<CString>> inputData);
	vector<CMinuteData> DataFactoryFiveMinute(vector<vector<CString>> inputData);
	vector<CMinuteData> DataFactoryFifteenMinute(vector<vector<CString>> inputData);
	static UINT RuntimeThread(LPVOID lpParameter);// ץȡ����
	char* CString2CharPt(CString InputString);
	CString Int2CString(int InputData);
	//CString CString2Int(CString InputData);
	void DecodeChar(char *data,DWORD len);



//	SELECT
//	/*`ag1412`.`ID` AS `ID`,
//	`ag1412`.`MySqlTimeStamp` AS `MySqlTimeStamp`,
//	`ag1412`.`CODE` AS `CODE`,
//FROM
//	`ag1412`
//WHERE
//	(
//		(
//			`ag1412`.`MySqlTimeStamp` > '2014-3-27 10:55:00'
//		)
//		AND (
//			`ag1412`.`MySqlTimeStamp` < '2014-3-27 11:00:00'
//		)
//	)

	// ��ѯ��������� x ������
	// avg('NewPrice') AS `AVG` // ��ƽ��
	// select * from ag1412  order by  MySqlTimeStamp desc limit 0,10; // ���10����¼
	vector<vector<CString>> GetDataFromSQL(int Num);
	vector<CString> GetDataByID(int ID);
	vector<vector<CString>> GetDataFromSQL(int StartID, int EndID);
	int GetTableNum(CString tableNam);
	// ����ȡ�����ݽ�һ���ָ�
	vector<CString> SplitString(CString DataStr);
};

