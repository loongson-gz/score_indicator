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
	, m_ch()
	, m_iFontSize(50)

{
	Gdiplus::GdiplusStartup(&m_uGdiplusToken, &m_GdiplusStarupInput, nullptr);

	//在不需要GDI + 的时候卸载它
	//Gdiplus::GdiplusShutdown(m_uGdiplusToken);
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
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// Cscore_indicatorDlg 消息处理程序

void Cscore_indicatorDlg::OnOK()
{
	return;
}

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
	char buf[256] = "";
	GetCurrentDirectoryA(256, buf);
	sprintf_s(buf, "%s\\res\\55.bmp", buf);
	CStringW s;   //转为宽字符
	s = buf;
	m_img = Gdiplus::Image::FromFile(s);  //加载图片

	DoLoadConf();
	GetClientRect(&m_rect);
	SetItemFont();
	SetTimer(UPDATE_SCORE, 1000, NULL);
	ShowWindow(SW_MAXIMIZE);

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
	CPaintDC dc(this);
	CRect rect = { 0 };
	GetClientRect(&rect);   //获取客户区大小
	Gdiplus::Graphics g(dc);
	g.DrawImage(m_img, 0, 0, rect.Width(), rect.Height());

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
		//SetItemFont();
		//UpdateWindow();
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

	m_iFontSize = GetPrivateProfileInt(_T("FONT"), _T("size"), 50, config_path.GetBuffer(0));

	CString section(_T("SCORE"));
	CWnd *pWnd[5] = {0};
	pWnd[0] = GetDlgItem(IDC_STATIC_1);
	pWnd[1] = GetDlgItem(IDC_STATIC_2);
	pWnd[2] = GetDlgItem(IDC_STATIC_3);
	pWnd[3] = GetDlgItem(IDC_STATIC_4);
	pWnd[4] = GetDlgItem(IDC_STATIC_5);

	for (size_t i = 0; i < 5; i++)
	{
		TCHAR lpTemp[MAX_PATH] = { 0 };
		CString ch;
		ch.Format(_T("CH%d"),(i+1));
		GetPrivateProfileString(section, ch, _T("80"), lpTemp, 10, config_path.GetBuffer(0));
		CString cs;
		cs.Format(_T("%s"), lpTemp);
		if (cs.Compare(m_ch[i]) != 0 && pWnd[i])
		{	
			m_ch[i] = cs;
			pWnd[i]->SetWindowText(lpTemp);
			//以下操作用以解决设置为透明背景时文字有重叠的BUG
			CRect rc;
			pWnd[i]->GetWindowRect(&rc);
			//转换为相对坐标
			ScreenToClient(&rc);
			//刷新指定区域,注意第2个参数为真,即刷新背景
			InvalidateRect(&rc, TRUE);
		}
	}

	UpdateData(FALSE);
}

void Cscore_indicatorDlg::SetItemFont()
{
	//m_font.CreatePointFont(500, _T("Arial"));
	m_font.CreateFont(
		m_iFontSize,               // nHeight
		m_iFontSize,               // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,                   // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		SHIFTJIS_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily 
		_T("Arial"));
	///_T("MS UI Gothic"));

	GetDlgItem(IDC_STATIC_1)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_2)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_3)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_4)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_5)->SetFont(&m_font);

	GetDlgItem(IDC_STATIC_11)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_12)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_13)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_14)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_15)->SetFont(&m_font);
}



HBRUSH Cscore_indicatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	pDC->SetTextColor(RGB(255, 0, 0));

	static CBrush gBr;
	//static bool isInited = false;
	//if (!isInited)
	//{
	//	CBitmap bitmap;
	//	bitmap.LoadBitmap(IDB_BITMAP2);
	//	gBr.CreatePatternBrush(&bitmap);
	//	COLORREF clearColor = -1;
	//	bitmap.DeleteObject();
	//	isInited = true;
	//}
	if (pWnd == this)
	{
		pDC->SetBkMode(TRANSPARENT);
		return gBr; //主窗口背景使用这个背景刷
	}
	else
	{
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); //其他控件使用透明背景
	}

	return hbr;
}


void Cscore_indicatorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (nType == 1) 
		return;//最小化则什么都不做  
	CWnd *pWnd[10] = {0};
	pWnd[0] = GetDlgItem(IDC_STATIC_1);
	pWnd[1] = GetDlgItem(IDC_STATIC_2);
	pWnd[2] = GetDlgItem(IDC_STATIC_3);
	pWnd[3] = GetDlgItem(IDC_STATIC_4);
	pWnd[4] = GetDlgItem(IDC_STATIC_5);
	pWnd[5] = GetDlgItem(IDC_STATIC_11);
	pWnd[6] = GetDlgItem(IDC_STATIC_12);
	pWnd[7] = GetDlgItem(IDC_STATIC_13);
	pWnd[8] = GetDlgItem(IDC_STATIC_14);
	pWnd[9] = GetDlgItem(IDC_STATIC_15);

	for (size_t i = 0; i < 10; i++)
	{
		if (pWnd[i])  //判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
		{
			CRect rect;   //获取控件变化前的大小 
			pWnd[i]->GetWindowRect(&rect);
			ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标

			//    cx/m_rect.Width()为对话框在横向的变化比例
			rect.left = rect.left*cx / m_rect.Width();//调整控件大小
			rect.right = rect.right*cx / m_rect.Width();
			rect.top = rect.top*cy / m_rect.Height();
			rect.bottom = rect.bottom*cy / m_rect.Height();
			pWnd[i]->MoveWindow(rect);//设置控件大小
		}
	}

	GetClientRect(&m_rect);
	Invalidate(FALSE);
}
