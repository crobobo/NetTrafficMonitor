// NetTrafficMonitorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetTrafficMonitor.h"
#include "NetTrafficMonitorDlg.h"


// CNetTrafficMonitorDlg

IMPLEMENT_DYNAMIC(CNetTrafficMonitorDlg, CWnd)

CNetTrafficMonitorDlg::CNetTrafficMonitorDlg()
{

}

CNetTrafficMonitorDlg::~CNetTrafficMonitorDlg()
{
}


BEGIN_MESSAGE_MAP(CNetTrafficMonitorDlg, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
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
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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
	ShowWindow(SW_SHOW);

	return 0;
}


void CNetTrafficMonitorDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	CFont font;
	font.CreateFont(17, 0, 0, 0, 550,
		false, false, false,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_SCRIPT,
		_T("΢���ź�"));
	CFont* pOldFont = dc.SelectObject(&font);
	int nOldBkMode = dc.SetBkMode(TRANSPARENT);

	dc.DrawText(_T("��"), CRect(0, 0, 10, 20), DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
	dc.DrawText(_T("��"), CRect(80, 0, 90, 20), DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);

	dc.SetBkMode(nOldBkMode);
	dc.SelectObject(pOldFont);
}


void CNetTrafficMonitorDlg::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
}


void CNetTrafficMonitorDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize.x = lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x = 160;
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
	CMenu* pMenu = GetSystemMenu(FALSE);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN, lpPoint->x, lpPoint->y, this);
	pMenu->Detach();
	pMenu->DestroyMenu();
	delete lpPoint;

	CWnd::OnRButtonUp(nFlags, point);
}
