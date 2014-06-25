#pragma once
#include <stdio.h>
#include <string>
#include <afxsock.h>
#include "mysql.h"
#include <vector>

using   namespace   std;

// class Field
// {
// public:
// 	Field();
// 	~Field();
// 
// 	vector<string> m_name;
// 	vector<enum_field_types> m_type;
// 
// private:
// 
// };
// 
// 
// 
// class Record
// {
// public:
// 	Record();
// 	~Record();
// 	Record(Field *m_f);
// 
// 	vector<string> m_rs;
// 	Field *m_field;
// 
// 	void SetData(string value);
// 
// 
// };




class VspdcToMySQL
{
public:
	MYSQL mysql;
	VspdcToMySQL(void);
	~VspdcToMySQL(void);

	// 	��Ҫ�Ĺ��ܣ�
	// 		��ʼ�����ݿ�
	// 		�������ݿ�
	// 		�����ַ���
	// 		��ڲ�����
	// 		host ��MYSQL������IP
	// port:���ݿ�˿�
	// 	 Db�����ݿ�����
	// 	 user�����ݿ��û�
	// 	 passwd�����ݿ��û�������
	// 	 charset��ϣ��ʹ�õ��ַ���
	// Msg:���ص���Ϣ������������Ϣ
	// 	���ڲ�����
	// 	int ��0��ʾ�ɹ���1��ʾʧ��
	int ConnMySQL(char *host,char * port,char * Db,char * user,char* passwd,char * charset,char * Msg);
	// 	��Ҫ�Ĺ��ܣ�
	// 		��ڲ�����
	// 		SQL����ѯ��SQL���
	// Cnum:��ѯ������
	// Msg:���ص���Ϣ������������Ϣ
	// 	���ڲ�����
	// 	string ׼�����÷��ص����ݣ�������¼����0x06����,�����λ��0x05����
	// 	��� ���صĳ��ȣ� 0�����ʾ����
	string SelectData(char * SQL,int Cnum ,int Row,char * Msg);
	// 	��Ҫ���ܣ�
	// 		SQL����ѯ��SQL���
	/*Msg:���ص���Ϣ������������Ϣ*/
	/*	���ڲ�����*/
	/*	int ��0��ʾ�ɹ���1��ʾʧ��*/
	int InsertData(char * SQL,char * Msg);
	// 	��Ҫ���ܣ�
	// 		SQL����ѯ��SQL���
	// Msg:���ص���Ϣ������������Ϣ
	// 	���ڲ�����
	// 	int ��0��ʾ�ɹ���1��ʾʧ��
	int UpdateData(char * SQL,char * Msg);
	// 	��Ҫ���ܣ�
	// 		SQL����ѯ��SQL���
	// Msg:���ص���Ϣ������������Ϣ
	// 	���ڲ�����
	// 	int ��0��ʾ�ɹ���1��ʾʧ��
	int DeleteData(char * SQL,char * Msg);

	void CleanTable(CString tableName);
	// 	��Ҫ���ܣ�
	// 		�ر����ݿ�����
	void CloseMySQLConn();
	//*************************************
	// ������:  	SelectData
	// Ŀ��:	��ȡ����������
	// ʱ�䣺   2014/03/27
	//*************************************
	vector<CString> GetDataVec(char * SQL,int Cnum ,int Row,char * Msg);
	//*************************************
	// ������:  	GetTableNum
	// Ŀ��:	��ȡ�������
	// ʱ�䣺   2014/03/27
	//*************************************
	int GetTableNum(CString tableName);

	char* CString2CharPt(CString inputData);

};

