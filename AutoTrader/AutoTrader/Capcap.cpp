#include "stdafx.h"
#include "Capcap.h"
#include "../inc.h"

CCapcap::CCapcap(void)
{
	_init_();
	AdapterName = m_AdapterNameList.at(2);
}


CCapcap::~CCapcap(void)
{
}

void CCapcap::_CreateCapFile()
{
	char FilePath[MAX_PATH];
	GetModuleFileNameA(0,FilePath,MAX_PATH-1);
	CapFilePath=FilePath;
	CapFilePath=CapFilePath.Left(CapFilePath.ReverseFind('\\'));
	CapFilePath+="\\CapTempData.CAP";
}

void CCapcap::_init_()
{
	InitializeCriticalSection(&csThreadStop);
	eThreadStart=CreateEventA(0,
		false,//�Զ�Reset
		false,//��ʼ����
		"StartCapTradeValue");

	_CreateCapFile();
	_GetAdapterList();
}

void CCapcap::_GetAdapterList()
{
	pcap_if_t *d;
	char errbuf[PCAP_ERRBUF_SIZE];
	// ��ȡ�豸�б�
	if (pcap_findalldevs(&AllDevs, errbuf) == -1)
	{
		//MessageBoxA("���ܵõ������������б�");
		printf("���ܵõ������������б�");
	}
	// �����б� 
	for(d=AllDevs; d; d=d->next)
	{
		CString tempStr(d->name);
		CString tempStr2(d->description);
		m_AdapterNameList.push_back(tempStr);
		//m_AdapterDescriptionList.push_back(tempStr2);
	}
}

bool CCapcap::StartCapture()
{
	// ��ʼץȡ����
	BOOL temp;
	// �����и����� ����Ҫת��Ϊ LPVOID ��������ָ��
	hCapThread=AfxBeginThread(CapThread,(LPVOID)this);
	// ��ֹ����Ӧ �����Զ��˳�
	WaitForSingleObject(eThreadStart, INFINITE);
	EnterCriticalSection(&csThreadStop);
	temp=bThreadStop;
	LeaveCriticalSection(&csThreadStop);
	if(temp)//�߳��Զ��˳�
	{
		return true;
	}
	else
	{
		printf("again and again");
// 		Status=1;
// 		GetDlgItem(IDC_EDIT1)->SetWindowText("");
// 		GetDlgItem(IDC_EDIT2)->SetWindowText("");
// 		this->SetMenuStatus();
	}
	return true;
}

bool CCapcap::StopCapture()
{
	DWORD result;

	EnterCriticalSection(&csThreadStop);
	bThreadStop=true;
	LeaveCriticalSection(&csThreadStop);
	result=WaitForSingleObject(hCapThread->m_hThread,3000);//����������ִ��ǰ�߳̾����˳�
	if(result==WAIT_TIMEOUT )
	{
		//MessageBox("�����̳߳�ʱ����Ӧ��ǿ�ƽ�����");
		TerminateThread(hCapThread->m_hThread,0);
	}
	//MessageBox("ֹͣץ��");
	return true;
}


//*************************************
// ������:  	
// Ŀ��:	
// ʱ�䣺   2014/03/20
//*************************************
UINT CCapcap::CapThread( LPVOID lpParameter )
{

	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_dumper_t *dumpfile;
	struct pcap_pkthdr *header;
	const u_char *data;
	DWORD res;
	bool bExit;
	static long i=0,j=0;

	ListData List;

	struct ether_header *eth;
	u_char* mac_string;
	struct iphead *IPHead;
	struct arphead *ARPHead;
	in_addr ipaddr;

	bool bThreadStop;

	// ǿת����������
	const char* adpName = (char*)AdapterName.GetBuffer();
	if((adhandle= pcap_open_live(adpName,65536,1 ,10,errbuf)) == NULL)
	{
		//::MessageBox(0,"���ܴ�����������,�������������о�������","����",0);
		//EnterCriticalSection(&(this2->csThreadStop));
		bThreadStop=true;
		//LeaveCriticalSection(&(this2->csThreadStop));
		//SetEvent(this2->eThreadStart);
		return 0;  
	}

	const char* capFile = (char*)CapFilePath.GetBuffer();
	dumpfile=pcap_dump_open(adhandle,capFile);
	if(dumpfile==NULL)
	{
		::MessageBox(0,_T("���ܴ򿪼�¼�ļ�"),_T("����"),0);

		//EnterCriticalSection(&(this2->csThreadStop));
		bThreadStop=true;
		//LeaveCriticalSection(&(this2->csThreadStop));
		//SetEvent(this2->eThreadStart);
		return 0;
	}

	//EnterCriticalSection(csThreadStop));
	//bThreadStop=false;
	bThreadStop = false;;
	//LeaveCriticalSection(&(this2->csThreadStop));
	//SetEvent(this2->eThreadStart);

	//::MessageBox(0,"��ʼץ��","ok",0);
	while(1)
	{
		if (bThreadStop == true)
		{
			return 0;
		}

		res = pcap_next_ex(adhandle,&header,&data);
		if(res==0)
		{
			Sleep(100);
			continue;
		}
		else if(res<0)
		{
			break;
		}

		pcap_dump((u_char *)dumpfile, header, data);

		eth=(ether_header *)data;
		mac_string=eth->ether_shost;
		sprintf_s(List.sMac,"%02X:%02X:%02X:%02X:%02X:%02X",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
		mac_string=eth->ether_dhost;
		sprintf_s(List.dMac,"%02X:%02X:%02X:%02X:%02X:%02X",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
		//ltoa����������ת���������ѳ�������ת��Ϊ������Ƶ��ַ����ĺ���
		//ltoa(header->caplen,List.Len,10);

		memcpy(List.Text,data,45);//���ݲ�����̫��ͷ
		List.Text[45]='\0';
		DecodeChar(List.Text,45);

		switch(ntohs(eth->ether_type))
		{
		case ETHERTYPE_ARP:
			//if(!this2->FilterSet.bAllProtocol && !this2->FilterSet.bArp)
			//{bFilter=true;break;}
			strcpy_s(List.Protocol,"ARP");
			ARPHead=(arphead *)(data+14);

			sprintf_s(List.sIP,"%d.%d.%d.%d",ARPHead->arp_source_ip_address[0],ARPHead->arp_source_ip_address[1],ARPHead->arp_source_ip_address[2],ARPHead->arp_source_ip_address[3]);
			sprintf_s(List.dIP,"%d.%d.%d.%d",ARPHead->arp_destination_ip_address[0],ARPHead->arp_destination_ip_address[1],ARPHead->arp_destination_ip_address[2],ARPHead->arp_destination_ip_address[3]);
			strcpy_s(List.sPort,"--");
			strcpy_s(List.dPort,"--");
			break;
		case ETHERTYPE_REVARP: 
			strcpy_s(List.Protocol,"RARP");
			break;
		case ETHERTYPE_IP:
			IPHead=(iphead *)(data+14);
			ipaddr=IPHead->ip_souce_address;
			//IPHead->ip_souce_address;
			sprintf_s(List.sIP,"%d.%d.%d.%d",ipaddr.S_un.S_un_b.s_b1,ipaddr.S_un.S_un_b.s_b2,ipaddr.S_un.S_un_b.s_b3,ipaddr.S_un.S_un_b.s_b4);
			ipaddr=IPHead->ip_destination_address;
			sprintf_s(List.dIP,"%d.%d.%d.%d",ipaddr.S_un.S_un_b.s_b1,ipaddr.S_un.S_un_b.s_b2,ipaddr.S_un.S_un_b.s_b3,ipaddr.S_un.S_un_b.s_b4);
			switch(IPHead->ip_protocol)
			{
			case 1:
				//if(!this2->FilterSet.bAllProtocol && !this2->FilterSet.bIcmp){bFilter=true;break;}
				strcpy_s(List.Protocol,"ICMP");
				strcpy_s(List.sPort,"--");
				strcpy_s(List.dPort,"--");
				break;
			case 6:
				//if(!this2->FilterSet.bAllProtocol && !this2->FilterSet.bTcp){bFilter=true;break;}
				strcpy_s(List.Protocol,"TCP");
				sprintf_s(List.sPort,"%d",ntohs( ((tcphead *)(data+16+20))->th_sport ));
				sprintf_s(List.dPort,"%d",ntohs( ((tcphead *)(data+16+20))->th_dport ));
				break;
			case 17:
				//if(!this2->FilterSet.bAllProtocol && !this2->FilterSet.bUdp){bFilter=true;break;}
				strcpy_s(List.Protocol,"UDP");
				sprintf_s(List.sPort,"%d",ntohs( ((udphead *)(data+16+20))->udp_source_port ));
				sprintf_s(List.dPort,"%d",ntohs( ((udphead *)(data+16+20))->udp_destinanion_port ));
				break;
			default:
				strcpy_s(List.Protocol,"δ֪IP��");
				strcpy_s(List.sIP,"----------");
				strcpy_s(List.dIP,"----------");
				strcpy_s(List.sPort,"--");
				strcpy_s(List.dPort,"--");
				break;
			}

			break;
		case ETHERTYPE_PUP:
			strcpy_s(List.Protocol,"PUP");
			strcpy_s(List.sIP,"----------");
			strcpy_s(List.dIP,"----------");
			strcpy_s(List.sPort,"--");
			strcpy_s(List.dPort,"--");
			break;
		default:
			strcpy_s(List.Protocol,"δ֪��̫��");
			strcpy_s(List.sIP,"----------");
			strcpy_s(List.dIP,"----------");
			strcpy_s(List.sPort,"--");
			strcpy_s(List.dPort,"--");
			break;
		}
// 		if(bFilter)
// 		{
// 			j++;
// 			List.Falg=true;
// 		}
// 		else
// 		{
// 			i++;j++;
// 			List.Falg=false;
// 		}
		//ltoa(i,List.ID,10);
		//ltoa(j,List.TotalPacket,10);
		//SendMessageTimeout(this2->m_hWnd,WM_UPDATE_LIST,(WPARAM)&List,0,SMTO_BLOCK,1000,&res);
		//bFilter=false;
	}

	return 0;
}

void CCapcap::DecodeChar( char *data,DWORD len )
{

}
