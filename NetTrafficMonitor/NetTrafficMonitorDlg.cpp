// NetTrafficMonitorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetTrafficMonitor.h"
#include "NetTrafficMonitorDlg.h"
#include "NetTraffic.h"


// CNetTrafficMonitorDlg

IMPLEMENT_DYNAMIC(CNetTrafficMonitorDlg, CWnd)

CNetTrafficMonitorDlg::CNetTrafficMonitorDlg()
{
	m_cTextUpload.m_hWnd = NULL;
	m_cTextDownload.m_hWnd = NULL;
}

CNetTrafficMonitorDlg::~CNetTrafficMonitorDlg()
{
}


BEGIN_MESSAGE_MAP(CNetTrafficMonitorDlg, CWnd)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_EXIT, OnExit)
END_MESSAGE_MAP()



// CNetTrafficMonitorDlg ��Ϣ�������




BOOL CNetTrafficMonitorDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ����ר�ô����/����û���
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	if (GetClassInfoEx(cs.hInstance, cs.lpszClass, &wcex))
	{
		return TRUE;
	}
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = AfxWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = cs.hInstance;
	wcex.hIcon = wcex.hIconSm = LoadIcon(cs.hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = cs.lpszClass;
	return RegisterClassEx(&wcex);

	//return CWnd::PreCreateWindow(cs);
}


int CNetTrafficMonitorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ModifyStyle(WS_THICKFRAME, 0);
	SetTimer(1, 1000, NULL);
	ShowWindow(SW_SHOW);

	if (NULL == m_cTextUpload.m_hWnd)
	{
		m_cTextUpload.Create(_T(" �� 0.00 KB/s"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 10001);
	}
	if (NULL == m_cTextDownload.m_hWnd)
	{
		m_cTextDownload.Create(_T(" �� 0.00 KB/s"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 10001);
	}

	return 0;
}


HBRUSH CNetTrafficMonitorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	CFont font;
	font.CreateFont(17, 0, 0, 0, 550,
		false, false, false,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_SCRIPT,
		_T("΢���ź�"));
	pDC->SelectObject(&font);

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CNetTrafficMonitorDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
}


void CNetTrafficMonitorDlg::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (m_cTextUpload.m_hWnd)
	{
		m_cTextUpload.MoveWindow(0, 0, cx / 2, cy);
	}
	if (m_cTextDownload.m_hWnd)
	{
		m_cTextDownload.MoveWindow(cx / 2, 0, cx - cx / 2, cy);
	}
}


void CNetTrafficMonitorDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize.x = lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x = 150;
	lpMMI->ptMinTrackSize.y = lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y = 20;

	CWnd::OnGetMinMaxInfo(lpMMI);
}


void CNetTrafficMonitorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);

	CWnd::OnLButtonDown(nFlags, point);
}


void CNetTrafficMonitorDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_NCLBUTTONDBLCLK, HTCAPTION, 0);

	CWnd::OnLButtonDblClk(nFlags, point);
}


void CNetTrafficMonitorDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	LPPOINT lpPoint = new tagPOINT();
	GetCursorPos(lpPoint);
	CMenu menu;
	menu.CreatePopupMenu();	// ����һ������ʽ�˵�
	menu.AppendMenu(MF_STRING, IDC_EXIT, _T("�˳�"));	// ���Ӳ˵���˳��������������Ϣ�������ڽ��������
	SetForegroundWindow();
	menu.TrackPopupMenu(TPM_LEFTALIGN, lpPoint->x, lpPoint->y, this);	// ȷ������ʽ�˵���λ��
	menu.Detach();	// ��Դ����
	menu.DestroyMenu();
	delete lpPoint;

	CWnd::OnRButtonUp(nFlags, point);
}


void CNetTrafficMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	double dUploadTraffic = 0.0;
	double dDownloadTraffic = 0.0;
	CNetTraffic* pNetTraffic = CNetTraffic::create_instance();
	pNetTraffic->RefreshInterfacesTraffic();
	int iNetworkInterfacesCount = pNetTraffic->GetNetworkInterfacesCount();
	for (int i = 0; i < iNetworkInterfacesCount; ++i)
	{
		dUploadTraffic += pNetTraffic->GetIncrementalOutgoingTraffic(i);
	}
	for (int i = 0; i < iNetworkInterfacesCount; ++i)
	{
		dDownloadTraffic += pNetTraffic->GetIncrementalIncomingTraffic(i);
	}

	char szText[128];
	sprintf_s(szText, sizeof(szText), " �� %.2f KB/s", dUploadTraffic/1024);
	m_cTextUpload.SetWindowText(szText);
	sprintf_s(szText, sizeof(szText), " �� %.2f KB/s", dDownloadTraffic/1024);
	m_cTextDownload.SetWindowText(szText);

	CWnd::OnTimer(nIDEvent);
}


void CNetTrafficMonitorDlg::OnExit()
{
	DestroyWindow();
}
