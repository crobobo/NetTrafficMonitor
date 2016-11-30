
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

	HWND hShellTrayWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	HWND hTrayNotifyWnd = ::FindWindowEx(hShellTrayWnd, NULL, _T("TrayNotifyWnd"), NULL);

	RECT rcTrayNotify;
	::GetWindowRect(hTrayNotifyWnd, &rcTrayNotify);

	int nWidth = 80;
	m_pMainWnd = new CNetTrafficMonitorDlg();
	m_pMainWnd->CreateEx(0, AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS),
		_T("NetTrafficMonitor"), WS_CHILDWINDOW | WS_VISIBLE,
		rcTrayNotify.right, 0, nWidth, rcTrayNotify.bottom - rcTrayNotify.top, hTrayNotifyWnd, NULL);

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	//return FALSE;
	return TRUE;
}

