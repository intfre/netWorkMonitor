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
	m_nWidth = 0;
	m_bSelfStarting = FALSE;
}

CNetTrafficMonitorDlg::CNetTrafficMonitorDlg(int nWidth)
{
	m_nWidth = nWidth;
	m_bSelfStarting = FALSE;
}

CNetTrafficMonitorDlg::~CNetTrafficMonitorDlg()
{
}


BEGIN_MESSAGE_MAP(CNetTrafficMonitorDlg, CWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
//	ON_WM_MOVE()
//	ON_WM_GETMINMAXINFO()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
//	ON_WM_HSCROLL()
//	ON_WM_KILLFOCUS()
	ON_BN_CLICKED(IDC_SELFSTARTING, OnSelfStarting)
	//ON_BN_CLICKED(IDC_TOPMOST, OnTopMost)
	//ON_BN_CLICKED(IDC_TRANSPARENCY, OnTransparency)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
END_MESSAGE_MAP()



// CNetTrafficMonitorDlg ��Ϣ�������




//BOOL CNetTrafficMonitorDlg::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO:  �ڴ����ר�ô����/����û���
//	WNDCLASSEX wcex;
//	wcex.cbSize = sizeof(WNDCLASSEX);
//	if (GetClassInfoEx(cs.hInstance, cs.lpszClass, &wcex))
//	{
//		return TRUE;
//	}
//	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
//	wcex.lpfnWndProc = AfxWndProc;
//	wcex.cbClsExtra = 0;
//	wcex.cbWndExtra = 0;
//	wcex.hInstance = cs.hInstance;
//	wcex.hIcon = wcex.hIconSm = LoadIcon(cs.hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
//	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
//	wcex.lpszMenuName = NULL;
//	wcex.lpszClassName = cs.lpszClass;
//	return RegisterClassEx(&wcex);
//
//	//return CWnd::PreCreateWindow(cs);
//}


int CNetTrafficMonitorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CString strText;
	GetWindowText(strText);
	HANDLE hMutex = CreateMutex(NULL, FALSE, strText);
	if (ERROR_ALREADY_EXISTS == GetLastError())									// ��ֹ����࿪
	{
		AfxMessageBox(_T("�����Ѿ�����"));
		return -1;
	}

	//CRect rcWorkArea;
	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);					// ��ȡϵͳ��������(��ȥ�·�������)
	//MoveWindow(rcWorkArea.right - m_iWidth - 80, 60, m_iWidth, m_iHeight);

	//ModifyStyle(WS_THICKFRAME, 0);												// ���ɵ���С
	//ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);							// ����������ͼ��
	//SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);				// �ö�
	//SetWindowLong(m_hWnd,
	//	GWL_EXSTYLE,
	//	GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);					// Ϊ���ڼ���WS_EX_LAYERED��չ����
	//SetLayeredWindowAttributes(0, (255 * m_iTransparency) / 100, LWA_ALPHA);	// m_iTransparency%͸����
	SetTimer(TIMER_TRAFFIC, 1000, NULL);										// ���1000msˢ��
	SetTimer(1, 10, NULL);
	//ShowWindow(SW_SHOW);

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
	RegCloseKey(hKey);															// �ر�ע���

	//m_pSlider = new CSliderCtrl();
	//m_pSlider->Create(WS_VISIBLE | TBS_HORZ | TBS_AUTOTICKS, CRect(0, 0, m_iWidth, m_iHeight / 2), this, 1001);
	//m_pSlider->SetRange(30, 100);
	//m_pSlider->SetTicFreq(10);
	//m_pSlider->SetPos(m_iTransparency);
	//m_pSlider->ShowWindow(SW_HIDE);
	//m_cToolTip.Create(m_pSlider);
	//m_cToolTip.AddTool(m_pSlider);
	RECT rc;
	GetClientRect(&rc);
	m_pFont = new CFont();
	m_pFont->CreateFont(15, 0, 0, 0, 800,
		false, false, false,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_SCRIPT,
		_T("΢���ź�"));
	m_pStatic1 = new CStatic();
	m_pStatic1->Create(_T("��"), WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, CRect(0, 0, 10, rc.bottom / 2), this);
	m_pStatic1->SetFont(m_pFont);
	m_pStatic2 = new CStatic();
	m_pStatic2->Create(_T("��"), WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, CRect(0, rc.bottom / 2, 10, rc.bottom), this);
	m_pStatic2->SetFont(m_pFont);
	m_pUploadStatic = new CStatic();
	m_pUploadStatic->Create(_T(""), WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE, CRect(10, 0, rc.right, rc.bottom / 2), this);
	m_pUploadStatic->SetFont(m_pFont);
	m_pDownloadStatic = new CStatic();
	m_pDownloadStatic->Create(_T(""), WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE, CRect(10, rc.bottom / 2, rc.right, rc.bottom), this);
	m_pDownloadStatic->SetFont(m_pFont);

	m_cCheckNo.LoadBitmap(IDB_CHECKNO);
	m_cCheckYes.LoadBitmap(IDB_CHECKYES);
	m_cExit.LoadBitmap(IDB_EXIT);

	return 0;
}


void CNetTrafficMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (TIMER_TRAFFIC == nIDEvent)
	{
		CNetTraffic* pNetTraffic = CNetTraffic::create_instance();
		pNetTraffic->RefreshInterfacesTraffic();

		DWORD dwUploadTraffic = 0;
		DWORD dwDownloadTraffic = 0;
		int iNetworkInterfacesCount = pNetTraffic->GetNetworkInterfacesCount();
		for (int i = 0; i < iNetworkInterfacesCount; ++i)
		{
			dwUploadTraffic += pNetTraffic->GetIncrementalOutgoingTraffic(i);
		}
		for (int i = 0; i < iNetworkInterfacesCount; ++i)
		{
			dwDownloadTraffic += pNetTraffic->GetIncrementalIncomingTraffic(i);
		}

		CString strUploadText;
		if (dwUploadTraffic / (1024 * 1024) >= 1)
		{
			strUploadText.Format(_T("%.2f MB/s "), dwUploadTraffic / (1024 * 1024.00));
		}
		else
		{
			strUploadText.Format(_T("%.2f KB/s "), dwUploadTraffic / 1024.00);
		}
		CString strDownloadText;
		if (dwDownloadTraffic / (1024 * 1024) >= 1)
		{
			strDownloadText.Format(_T("%.2f MB/s "), dwDownloadTraffic / (1024 * 1024.00));
		}
		else
		{
			strDownloadText.Format(_T("%.2f KB/s "), dwDownloadTraffic / 1024.00);
		}

		m_pUploadStatic->SetWindowText(strUploadText);
		m_pDownloadStatic->SetWindowText(strDownloadText);
	}
	if (nIDEvent == 1)
	{
		HWND hShellTrayWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
		HWND hReBarWnd = ::FindWindowEx(hShellTrayWnd, NULL, _T("ReBarWindow32"), NULL);
		HWND hTaskWnd = ::FindWindowEx(hReBarWnd, NULL, _T("MSTaskSwWClass"), NULL);
		HWND hCiceroUIWnd = ::FindWindowEx(hReBarWnd, NULL, _T("CiceroUIWndFrame"), NULL);

		RECT rcReBar;
		::GetClientRect(hReBarWnd, &rcReBar);
		RECT rcTask;
		::GetClientRect(hTaskWnd, &rcTask);
		RECT rcCiceroUI;
		::GetClientRect(hCiceroUIWnd, &rcCiceroUI);
		if (rcTask.right + rcCiceroUI.right >= rcReBar.right - 8 &&
			rcTask.right + rcCiceroUI.right <= rcReBar.right + 8)
		{
			::MoveWindow(hTaskWnd, 0, 0, rcTask.right - m_nWidth, rcTask.bottom, TRUE);
			MoveWindow(rcTask.right - m_nWidth, 0, m_nWidth, rcReBar.bottom, TRUE);
		}

		RECT rc;
		GetClientRect(&rc);
		m_pStatic1->MoveWindow(CRect(0, 0, 10, rc.bottom / 2), TRUE);
		m_pStatic2->MoveWindow(CRect(0, rc.bottom / 2, 10, rc.bottom), TRUE);
		m_pUploadStatic->MoveWindow(CRect(10, 0, rc.right, rc.bottom / 2), TRUE);
		m_pDownloadStatic->MoveWindow(CRect(10, rc.bottom / 2, rc.right, rc.bottom), TRUE);
	}

	CWnd::OnTimer(nIDEvent);
}


HBRUSH CNetTrafficMonitorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return  HBRUSH(GetStockObject(BLACK_BRUSH));
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


//void CNetTrafficMonitorDlg::OnMove(int x, int y)
//{
//	CWnd::OnMove(x, y);
//
//	// TODO:  �ڴ˴������Ϣ����������
//	CRect rcWorkArea;
//	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);		// ��ȡϵͳ��������(��ȥ�·�������)
//	CRect rc;
//	GetWindowRect(&rc);
//	if (rc.left < 20)
//	{
//		rc.left = 0;
//		rc.right = m_iWidth;
//	}
//	if (rcWorkArea.right - rc.right < 20)
//	{
//		rc.left = rcWorkArea.right - m_iWidth;
//		rc.right = rcWorkArea.right;
//	}
//	if (rc.top < 20)
//	{
//		rc.top = 0;
//		rc.bottom = m_iHeight;
//	}
//	if (rcWorkArea.bottom - rc.bottom < 20)
//	{
//		rc.top = rcWorkArea.bottom - m_iHeight;
//		rc.bottom = rcWorkArea.bottom;
//	}
//	MoveWindow(&rc);
//}


//void CNetTrafficMonitorDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	lpMMI->ptMinTrackSize.x = lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x = m_iWidth;
//	lpMMI->ptMinTrackSize.y = lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y = m_iHeight;
//
//	CWnd::OnGetMinMaxInfo(lpMMI);
//}


//void CNetTrafficMonitorDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	if (m_pSlider->IsWindowVisible())
//	{
//		m_pSlider->ShowWindow(SW_HIDE);
//	}
//
//	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
//
//	CWnd::OnLButtonDown(nFlags, point);
//}


//void CNetTrafficMonitorDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	SendMessage(WM_NCLBUTTONDBLCLK, HTCAPTION, 0);
//
//	CWnd::OnLButtonDblClk(nFlags, point);
//}


void CNetTrafficMonitorDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//if (m_pSlider->IsWindowVisible())
	//{
	//	m_pSlider->ShowWindow(SW_HIDE);
	//}

	CMenu menu;
	menu.CreatePopupMenu();	// ����һ������ʽ�˵�
	menu.AppendMenu(MF_STRING, IDC_SELFSTARTING, _T("��������"));
	//menu.AppendMenu(MF_STRING, IDC_TOPMOST, _T("�ö�"));
	//CString strText;
	//strText.Format(_T("͸����: %d%%"), m_iTransparency);
	//menu.AppendMenu(MF_STRING, IDC_TRANSPARENCY, strText);
	menu.AppendMenu(MF_STRING, IDC_EXIT, _T("�˳�"));	// ���Ӳ˵���˳��������������Ϣ�������ڽ��������
	if (m_bSelfStarting)
	{
		menu.SetMenuItemBitmaps(IDC_SELFSTARTING, MF_BYCOMMAND | MF_STRING | MF_ENABLED, &m_cCheckYes, &m_cCheckYes);
	}
	else
	{
		menu.SetMenuItemBitmaps(IDC_SELFSTARTING, MF_BYCOMMAND | MF_STRING | MF_ENABLED, &m_cCheckNo, &m_cCheckNo);
	}
	//if (m_bTopMost)
	//{
	//	menu.SetMenuItemBitmaps(IDC_TOPMOST, MF_BYCOMMAND | MF_STRING | MF_ENABLED, &m_cCheckYes, &m_cCheckYes);
	//}
	//else
	//{
	//	menu.SetMenuItemBitmaps(IDC_TOPMOST, MF_BYCOMMAND | MF_STRING | MF_ENABLED, &m_cCheckNo, &m_cCheckNo);
	//}
	menu.SetMenuItemBitmaps(IDC_EXIT, MF_BYCOMMAND | MF_STRING | MF_ENABLED, &m_cExit, &m_cExit);
	//SetForegroundWindow();

	LPPOINT lpPoint = new tagPOINT();
	GetCursorPos(lpPoint);
	menu.TrackPopupMenu(TPM_LEFTALIGN, lpPoint->x, lpPoint->y, this);	// ȷ������ʽ�˵���λ��

	menu.Detach();	// ��Դ����
	menu.DestroyMenu();
	delete lpPoint;

	//CWnd::OnRButtonUp(nFlags, point);	// �����������Լ����Ҽ��˵�
}


//void CNetTrafficMonitorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	CString strText;
//	strText.Format(_T("%d%%"), m_pSlider->GetPos());
//	m_cToolTip.UpdateTipText(strText, m_pSlider);
//
//	m_iTransparency = m_pSlider->GetPos();
//	SetLayeredWindowAttributes(0, (255 * m_iTransparency) / 100, LWA_ALPHA);	// m_iTransparency%͸����
//
//	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
//}


//void CNetTrafficMonitorDlg::OnKillFocus(CWnd* pNewWnd)
//{
//	CWnd::OnKillFocus(pNewWnd);
//
//	// TODO:  �ڴ˴������Ϣ����������
//	if (m_pSlider->IsWindowVisible() && GetFocus() != m_pSlider)
//	{
//		m_pSlider->ShowWindow(SW_HIDE);
//	}
//}


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


//void CNetTrafficMonitorDlg::OnTopMost()
//{
//	if (m_bTopMost)
//	{
//		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);			// ȡ���ö�
//		m_bTopMost = FALSE;
//	}
//	else
//	{
//		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);				// �ö�
//		m_bTopMost = TRUE;
//	}
//}


//void CNetTrafficMonitorDlg::OnTransparency()
//{
//	if (!m_pSlider->IsWindowVisible())
//	{
//		m_pSlider->ShowWindow(SW_SHOW);
//	}
//}


void CNetTrafficMonitorDlg::OnExit()
{
	//m_pSlider->DestroyWindow();
	//m_cToolTip.DestroyWindow();
	HWND hShellTrayWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	HWND hReBarWnd = ::FindWindowEx(hShellTrayWnd, NULL, _T("ReBarWindow32"), NULL);
	HWND hTaskWnd = ::FindWindowEx(hReBarWnd, NULL, _T("MSTaskSwWClass"), NULL);
	HWND hCiceroUIWnd = ::FindWindowEx(hReBarWnd, NULL, _T("CiceroUIWndFrame"), NULL);

	RECT rcReBar;
	::GetClientRect(hReBarWnd, &rcReBar);
	RECT rcTask;
	::GetClientRect(hTaskWnd, &rcTask);
	RECT rcCiceroUI;
	::GetClientRect(hCiceroUIWnd, &rcCiceroUI);
	if (rcTask.right + rcCiceroUI.right < rcReBar.right - 8 ||
		rcTask.right + rcCiceroUI.right > rcReBar.right + 8)
	{
		::MoveWindow(hTaskWnd, 0, 0, rcTask.right + m_nWidth, rcTask.bottom, TRUE);
	}

	DestroyWindow();
}
