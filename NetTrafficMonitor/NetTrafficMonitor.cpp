
// NetTrafficMonitor.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "NetTrafficMonitor.h"
#include "NetTrafficMonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetTrafficMonitorApp

BEGIN_MESSAGE_MAP(CNetTrafficMonitorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CNetTrafficMonitorApp ����

CNetTrafficMonitorApp::CNetTrafficMonitorApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CNetTrafficMonitorApp ����

CNetTrafficMonitorApp theApp;


// CNetTrafficMonitorApp ��ʼ��

BOOL CNetTrafficMonitorApp::InitInstance()
{
	CWinApp::InitInstance();

	m_pMainWnd = new CNetTrafficMonitorDlg();
	m_pMainWnd->CreateEx(0, _T("CNetTrafficMonitorDlg"), _T(""), WS_POPUPWINDOW | WS_THICKFRAME,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	//return FALSE;
	return TRUE;
}

