/**************************************************************
**			������װ�� v1.03								 **
** AutoCAD2010 x64											 **
** VS2008													 **
***************************************************************/
#pragma once
#include "StdAfx.h"
#include <vector>
#include <tuple>
#include <array>
#include<cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <math.h>

//#ifndef PI
//#define  PI 3.1415926535897932384626433832795;;
//#endif


using namespace std;
typedef vector<CString> LINEINFO;
//typedef tuple<CString, CString> ERRORUNIT;
//typedef vector<ERRORUNIT> ERRORLIST;
typedef AcDbEntity*  CADEnt;

#ifndef NREADMODE
#define  NREADMODE 1
#define  NWRITEMODE 0
#endif

class Additional_Class
{
public:
	Additional_Class(void);
	~Additional_Class(void);

private:
	//ERRORLIST m_ErrorList;
	//ERRORUNIT m_Error;

protected:
	//void SetError(CString ErrorState, CString FuncName);

public:
/****************************************************************************************************
��������
			|
			��ѡ��ʵ��
			|
			������ʵ��ID
			|
			���ж�ʵ�����ͣ�����߷���1����
			|
			������ͼ��
-----------------------------------------------------------------------
����ʵ��
			|
			�����ӱ����
			|
			������ֱ��(��ʼ�㣬��ֹ��)
			|
			���������֣����֣�����㣬�ָߣ��Ƕȣ�
			|
			������Բ������㣬�뾶��
			|
			�����Ʊ��
-----------------------------------------------------------------------
ʵ�����
			|
			����ȡ��չ����
			|
			���õ�����߶ε���Ŀ
*************************************************************************************************/

//******��������*****************************************************************

	// ��������������
	void Open_ORTHOMODE(void);
	// �ر�������������
	void Close_ORTHOMODE(void);
	// �û�ѡ��ʵ�庯��,�û���ʾ������ʵ�壬���ص�
	//void Select_Entity_Ent(CString ScreenPrint, ads_name &RtEntity, ads_point &RtPoint);
	bool Select_Entity_Ent(CString ScreenPrint, ads_name &RtEntity, ads_point &RtPoint);
	// ��ʵ�巵��ʵ��ID������ʵ����� ����ʵ��ID
	void Get_EntityID(ads_name RtEntity, AcDbObjectId &RtEntityID);
	// �ж϶������ͣ� �������ʵ��
	int Check_Entity(AcDbEntity* InputEntity);
	// ����ͼ��
	bool FindLayer(CString LaylerName);
	// �򿪹ر�ͼ��
	void SetLayerIsOff( CString strLayerName);
	// ���õ�ǰͼ��
	void SetCurLayler(CString LaylerName);
	void SetCurLayler(AcDbObjectId curlayerID);
	// ��õ�ǰͼ��ID
	AcDbObjectId GetCurLayler();
	// ȫģ�Ϳռ����
	AcDbObjectIdArray ObjectXdataFilter(CString XdataName, CString Xdata);
	// ����ͼ��, ͼ������ ���ط���������ʵ��ID���飬 ������������
	bool LaylerFilter(CString LaylerName, AcDbObjectIdArray &EntityID, bool(*Filter)(AcDbEntity*,	 AcDbObjectId&));
	// ȫ��ͼ�����
	bool LaylerFilter(AcDbObjectIdArray &EntityID, bool(*Filter)(AcDbEntity*,	 AcDbObjectId&));
	// �򿪿��
	void Open_BlockTable(AcDbBlockTable* &pBlockTable, int ReadMode);
	// ��ģ�Ϳռ�
	void Open_ModelTableRecord(AcDbBlockTableRecord* &pBlkTblRcd, AcDbBlockTable* &pBlkTbl, int ReadMode);
	// �û���ѡʵ��
	AcDbObjectIdArray Select_Entitys(CString ScreenPrint);
//*******����¼******************************************************************
	// ��������¼�Ƿ��п�
	bool BlkHasRef(CString RefName);
	// ������������
	void addXdata(AcDbObjectId entID, CString xdataStr);
	void addXdata(AcDbObjectId entID, CString xdataStr, CString xdataNameStr);
	// ��ȡ��������
	CString Get_Xdata(AcDbObjectId EntID, CString Xdata_Ref);

//*******����ʵ��******************************************************************
	// ����һ��ֱ��
	AcDbObjectId Draw_Line(AcGePoint3d stPoint, AcGePoint3d enPoint);
	AcDbObjectId Draw_Line(AcGePoint3d stPoint, AcGePoint3d enPoint, CString LineType, double TypeScale);
	// ��������
	AcDbObjectId Draw_Text(CString InputText, AcGePoint3d InsertPoint, double TextHeight, double TextAngle);
	AcDbObjectId Draw_MText(CString InputText, AcGePoint3d InsertPoint, double TextHeight, double TextAngle);
	// ����ԲȦ XYƽ��
	AcDbObjectId Draw_Circle(AcGePoint3d ptCircle, double Radius);
	// ���ƾ���
	AcDbObjectId Draw_Rectangle(AcGePoint2d stPt, double length, double height);
	// ������
	AcDbObjectId Creat_Table(AcGePoint3d TablePoint, vector<CString> Title, double ColWidth=100, double RowHeight = 20, double TextHeight =10);
	// ���ӱ����
	void Insert_TableRow(AcDbObjectId TableID, vector<CString> StrList);
	// ����Բ��
	AcDbObjectId Draw_Arc(AcGePoint3d CenterPt, double RadiusArc, double StartAngle, double EndAngle);
	// ����ģ����ɫ
	void Set_ObjectColor(AcDbObjectId ObID, int ColorIndex);
	void Set_ObjectColor(AcDbObjectIdArray obIDArray, int ColorIndex);
//********ʵ�����*****************************************************************
	// ׷������
	BOOL Add_LineType(CString linetype);
	// ��������
	BOOL Get_LineTypeID(CString linetype, AcDbObjectId &linetypeid);
	// ���ʵ���������
	AcGePoint3d Get_CenterPt(AcDbObjectId ObjID);
	// �ı�ֱ������յ㣬ֱ��ID
	void Change_Line(AcDbObjectId LineID, AcGePoint3d ptStart, AcGePoint3d ptEnd);
	void Change_Line(AcDbObjectId LineID, AcGeVector3d deltaVec);
	// �ı�����λ��
	void Change_TextPosition(AcDbObjectId TextID, AcGePoint3d ptText);
	// ɾ��ֱ��ʵ��ͨ��ID
	void Delete_AcDbObject(AcDbObjectId LineID);
	// �ж϶�����Ƿ�������
	bool PolyLineHasCruve(AcDbPolyline *PolyLineEntity);
	// �õ�����߼е�����
	AcGePoint3dArray Get_PolyLinePointArray(AcDbObjectId PolyLineId);
	// �õ�����߶ε���Ŀ
	int Get_NumPolyLine(AcDbPolyline *PolyLineEntity);
	// �ж϶�����Ƿ��Ǿ���
	bool PolyLineIfRectangle(AcDbPolyline *PolyLineEntity);
	// ���ؾ��εĳ��Ϳ�
	void Get_RectangleLW(AcDbPolyline *PolyLineEntity, double &Length, double &width);
	// �õ�����߶˵���������
	void Get_PolyLine_Point(AcDbObjectId PolyLineId,AcGePoint3dArray &PointArray);
	// �õ����߶�ÿ�γ�������
	void Get_PolyLine_Length(AcDbObjectId PolyLineId, AcGeDoubleArray &LengthArray);
	// �õ����߶������ַ�������
	void Get_PolyLineType(AcDbObjectId PolyLineId,LINEINFO &LineInfo_List);
	// �õ����߶�X��Y����ֵ
	void Get_PolyLineCoor(AcGePoint3dArray PointArray, LINEINFO &X_Coor_List,LINEINFO &Y_Coor_List);
	// �õ����߶εĵ�һ��
	void Get_PolyLineFirst(CString First_P, AcGeDoubleArray LineLengthList, LINEINFO &First_List);
	// �õ�ָ��ͼ��ģ��ĳ���
	bool Get_LayerLW(CString LayerName, double &Length, double &Width);
	// ��double�����Ϊcstring����
	void TransFrom(AcGeDoubleArray LineLength, LINEINFO &LengthStr);
	// �ı���λ��
	void Change_TablePoint(AcDbObjectId TableID,AcGePoint3d newPt);
	// �õ�Բ�����е�
	void Get_ArcMiddle(AcDbObjectId PolyLineId, AcGePoint3dArray &Middle_List, AcGePoint3dArray &CenterListInput, LINEINFO &ArcInfoRList, LINEINFO &ArcInfoAList);
	// ��ʵ����z����ת һ���Ƕ�
	void RotateEnt(AcDbObjectId EntID, double RotateAng, AcGePoint3d InpPt);
	// �ж�ʵ���ǲ���AcDBCurve��
	bool IsAcDbCurve(AcDbObjectId EntID);

//************************************************************************************************************
	// �������ͱ���
	double CalLineTypeScale(double Len);
	// ������ֵ�������
	int GetCountOrder(double Num);
	// �õ���������ĳ�������ֵ�ĵ�index
	int GetMAXPt(int pos, AcGePoint3dArray PtList);
	// �õ���������ĳ������Сֵ�ĵ�index
	int GetMINPt(int pos, AcGePoint3dArray PtList);
	// �ָ��ַ���
	CString SplitString(CString str, char split, CString& LastStr);
	// ���ж�ȡ�ļ�
	bool ReadFileL(CString Dir_ConfigFile, vector<CString> &FileData);
//************************************************************************************************************
	// ���󴰿�
	void ErrorBox(CString TextError, HWND MyHandle);
	// ��дע���
	void ReadReg(LPCTSTR data_Set, CString ValueName, CString & ReadStr);
	void WriteReg(LPCTSTR data_Set, CString ValueName, CString NewValue);
	bool CheckReg(LPCTSTR data_Set, CString ValueName);
	bool CheckReg(LPCTSTR data_Set, CString ValueName, CString &resStr);

	//////////////////////////////////////////////////////////////////////////
	
	inline CString Int2CString(int NeedInt)
	{
		char a[200];
		itoa(NeedInt, a, 10);
		CString ss = a;
		return ss;
	}

	inline char* CString2CharPt( CString InputString )
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

	inline CString Double2CString(double NeedInt)
	{
		char a[200];
		itoa(NeedInt, a, 10);
		CString ss = a;
		return ss;
	}
	inline double CString2Double(CString str)
	{
		double res;
		//char c[1024];
		char *c;
		c = CString2CharPt(str);
		//lstrcpyn(c, str , _countof(c));
		res = atof(c);
		//res = _ttof(str);
		return res;
	}
	inline LPBYTE CString2LPBYTE(CString str)
	{
		LPBYTE lpb = (LPBYTE)(LPCTSTR)str;
		return lpb;
	}
	inline TCHAR* CString2TCHAR(CString str)
	{
		int iLen = str.GetLength(); 
		TCHAR* szRs = new TCHAR[iLen]; 
		lstrcpy(szRs, str.GetBuffer(iLen)); 
		str.ReleaseBuffer(); 
		return szRs;
	}
	// ���ڲ���
	inline void PrintTest(int T_T)
	{
		CString StrName = Int2CString(T_T);
		acutPrintf(_T("���Խ��: %s\n"), StrName);
	}
	inline void PrintTest(CString T_T)
	{
		acutPrintf(_T("���Խ��: %s\n"), T_T);
	}
	inline void PrintTest(bool T_T)
	{
		if (T_T == true)
		{
			acutPrintf(_T("���Խ��: True"));
		}
		acutPrintf(_T("���Խ��: False"));
	}
	inline void PrintTest(char *T_T)
	{
		acutPrintf(_T("���Խ��:"));
		//acutPrintf(T_T);
	}
	inline void PrintTest(AcGePoint3d T_T)
	{
		acutPrintf(_T("���Խ��:"));
		CString temp;
		temp = Double2CString(T_T[0]);
		acutPrintf(_T("X:")+temp);
		temp = Double2CString(T_T[1]);
		acutPrintf(_T("Y") + temp);
		temp = Double2CString(T_T[2]);
		acutPrintf(_T("Z")+temp);
	}
};