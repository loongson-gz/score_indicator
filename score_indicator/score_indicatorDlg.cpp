fnfg
// score_indicatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "score_indicator.h"
#include "score_indicatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define UPDATE_SCORE  1001

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cscore_indicatorDlg 对话框



Cscore_indicatorDlg::Cscore_indicatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cscore_indicatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cscore_indicatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cscore_indicatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

// Cscore_indicatorDlg 消息处理程序

BOOL Cscore_indicatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	DoLoadConf();

	SetTimer(UPDATE_SCORE, 1000, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cscore_indicatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cscore_indicatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void Cscore_indicatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == UPDATE_SCORE)
	{
		DoLoadConf();
	}

	CDialogEx::OnTimer(nIDEvent);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cscore_indicatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cscore_indicatorDlg::DoLoadConf()
{
	CString config_path(_T("./config.ini"));
	CString section(_T("SCORE"));
	TCHAR lpTemp[MAX_PATH] = { 0 };
	GetPrivateProfileString(section, _T("CH1"), _T("80"), lpTemp, 10, config_path.GetBuffer(0));
	GetDlgItem(IDC_STATIC_1)->SetWindowText(lpTemp);
	GetPrivateProfileString(section, _T("CH2"), _T("80"), lpTemp, 10, config_path.GetBuffer(0));
	GetDlgItem(IDC_STATIC_2)->SetWindowText(lpTemp);
	GetPrivateProfileString(section, _T("CH3"), _T("80"), lpTemp, 10, config_path.GetBuffer(0));
	GetDlgItem(IDC_STATIC_3)->SetWindowText(lpTemp);
	GetPrivateProfileString(section, _T("CH4"), _T("80"), lpTemp, 10, config_path.GetBuffer(0));
	GetDlgItem(IDC_STATIC_4)->SetWindowText(lpTemp);
	GetPrivateProfileString(section, _T("CH5"), _T("80"), lpTemp, 10, config_path.GetBuffer(0));
	GetDlgItem(IDC_STATIC_5)->SetWindowText(lpTemp);
	UpdateData(FALSE);
}

