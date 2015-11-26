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
	m_llWidth = 70;
	m_llHeight = 30;
	m_dwUploadTraffic = 0;
	m_dwDownloadTraffic = 0;
	m_bSelfStarting = FALSE;
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
	ON_BN_CLICKED(IDC_SELFSTARTING, OnSelfStarting)
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
	wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
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
	ModifyStyle(WS_THICKFRAME, 0);									// ���ɵ���С
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);				// ����������ͼ��
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);	// �ö�
	SetTimer(1, 1000, NULL);										// ���1��ˢ��
	ShowWindow(SW_SHOW);

	TCHAR szFileFullPath[MAX_PATH] = { 0 };
	TCHAR szFileName[_MAX_FNAME] = { 0 };
	GetModuleFileName(NULL, szFileFullPath, MAX_PATH);							// �õ����������ȫ·��
	_wsplitpath(szFileFullPath, NULL, NULL, szFileName, NULL);					// ��ó�����
	HKEY hKey;
	LPCTSTR lpRun = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");	// �ҵ�ϵͳ��������
	if (ERROR_SUCCESS == RegOpenKey(HKEY_CURRENT_USER, lpRun, &hKey))			// ��������Key
	{
		DWORD dwType = REG_SZ, dwSize = MAX_PATH;
		TCHAR szValue[MAX_PATH] = { 0 };
		if (ERROR_SUCCESS == RegQueryValueEx(hKey, szFileName, NULL, &dwType, (LPBYTE)szValue, &dwSize))
		{
			m_bSelfStarting = TRUE;
		}
		else
		{
			m_bSelfStarting = FALSE;
		}
	}
	RegCloseKey(hKey);											// �ر�ע���

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
	CFont font;
	font.CreateFont(15, 0, 0, 0, 550,
		false, false, false,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_SCRIPT,
		_T("΢���ź�"));
	dc.SelectObject(&font);
	dc.SetBkMode(TRANSPARENT);

	CString strText;
	strText.Format(_T(" �� %.2f KB/s"), m_dwUploadTraffic / 1024.00);
	dc.DrawText(strText, CRect(0, 0, m_llWidth, m_llHeight / 2), DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
	strText.Format(_T(" �� %.2f KB/s"), m_dwDownloadTraffic / 1024.00);
	dc.DrawText(strText, CRect(0, m_llHeight / 2, m_llWidth, m_llHeight), DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);

	m_cCheckNo.LoadBitmap(IDB_CHECKNO);
	m_cCheckYes.LoadBitmap(IDB_CHECKYES);
	m_cExit.LoadBitmap(IDB_EXIT);
}


void CNetTrafficMonitorDlg::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
}


void CNetTrafficMonitorDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize.x = lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x = m_llWidth;
	lpMMI->ptMinTrackSize.y = lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y = m_llHeight;

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
	menu.AppendMenu(MF_STRING, IDC_SELFSTARTING, _T("��������"));
	menu.AppendMenu(MF_STRING, IDC_EXIT, _T("�˳�"));	// ���Ӳ˵���˳��������������Ϣ�������ڽ��������
	if (m_bSelfStarting)
	{
		menu.SetMenuItemBitmaps(0, MF_BYPOSITION | MF_STRING | MF_ENABLED, &m_cCheckYes, &m_cCheckYes);
	}
	else
	{
		menu.SetMenuItemBitmaps(0, MF_BYPOSITION | MF_STRING | MF_ENABLED, &m_cCheckNo, &m_cCheckNo);
	}
	menu.SetMenuItemBitmaps(1, MF_BYPOSITION | MF_STRING | MF_ENABLED, &m_cExit, &m_cExit);
	//SetForegroundWindow();
	menu.TrackPopupMenu(TPM_LEFTALIGN, lpPoint->x, lpPoint->y, this);	// ȷ������ʽ�˵���λ��
	menu.Detach();	// ��Դ����
	menu.DestroyMenu();
	delete lpPoint;

	CWnd::OnRButtonUp(nFlags, point);
}


void CNetTrafficMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CNetTraffic* pNetTraffic = CNetTraffic::create_instance();
	pNetTraffic->RefreshInterfacesTraffic();
	
	m_dwUploadTraffic = 0;
	m_dwDownloadTraffic = 0;
	int iNetworkInterfacesCount = pNetTraffic->GetNetworkInterfacesCount();
	for (int i = 0; i < iNetworkInterfacesCount; ++i)
	{
		m_dwUploadTraffic += pNetTraffic->GetIncrementalOutgoingTraffic(i);
	}
	for (int i = 0; i < iNetworkInterfacesCount; ++i)
	{
		m_dwDownloadTraffic += pNetTraffic->GetIncrementalIncomingTraffic(i);
	}

	Invalidate();

	CWnd::OnTimer(nIDEvent);
}


void CNetTrafficMonitorDlg::OnSelfStarting()
{
	TCHAR szFileFullPath[MAX_PATH] = { 0 };
	TCHAR szFileName[_MAX_FNAME] = { 0 };
	GetModuleFileName(NULL, szFileFullPath, MAX_PATH);							// �õ����������ȫ·��
	_wsplitpath(szFileFullPath, NULL, NULL, szFileName, NULL);					// ��ó�����
	HKEY hKey;
	LPCTSTR lpRun = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");	// �ҵ�ϵͳ��������
	if (ERROR_SUCCESS == RegOpenKey(HKEY_CURRENT_USER, lpRun, &hKey))			// ��������Key
	{
		if (m_bSelfStarting)
		{
			if (ERROR_SUCCESS == RegDeleteValue(hKey, szFileName))				// ɾ��һ����Key
			{
				m_bSelfStarting = FALSE;
			}
		}
		else
		{
			if (ERROR_SUCCESS == RegSetValueEx(hKey,
				szFileName,
				0,
				REG_SZ,
				(LPBYTE)szFileFullPath,
				(lstrlen(szFileFullPath) + 1) * sizeof(TCHAR)))					// ���һ����Key,������ֵ
			{
				m_bSelfStarting = TRUE;
			}
		}
	}
	RegCloseKey(hKey);															// �ر�ע���
}


void CNetTrafficMonitorDlg::OnExit()
{
	DestroyWindow();
}
