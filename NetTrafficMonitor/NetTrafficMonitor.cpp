
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
	HWND hReBarWnd = ::FindWindowEx(hShellTrayWnd, NULL, _T("ReBarWindow32"), NULL);
	HWND hTaskWnd = ::FindWindowEx(hReBarWnd, NULL, _T("MSTaskSwWClass"), NULL);
	HWND hCiceroUIWnd = ::FindWindowEx(hReBarWnd, NULL, _T("CiceroUIWndFrame"), NULL);

	int nWidth = 80;
	RECT rcReBar;
	::GetClientRect(hReBarWnd, &rcReBar);
	RECT rcTask;
	::GetClientRect(hTaskWnd, &rcTask);
	RECT rcCiceroUI;
	::GetClientRect(hCiceroUIWnd, &rcCiceroUI);
	if (rcTask.right + rcCiceroUI.right >= rcReBar.right - 8 &&
		rcTask.right + rcCiceroUI.right <= rcReBar.right + 8)
	{
		::MoveWindow(hTaskWnd, 0, 0, rcTask.right - nWidth, rcTask.bottom, TRUE);
	}

	m_pMainWnd = new CNetTrafficMonitorDlg(nWidth);
	m_pMainWnd->CreateEx(0, AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS),
		_T("NetTrafficMonitor"), WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		rcTask.right - nWidth, 0, nWidth, rcReBar.bottom, hReBarWnd, NULL);

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	//return FALSE;
	return TRUE;
}

