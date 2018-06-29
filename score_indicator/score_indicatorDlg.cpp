// score_indicatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "score_indicator.h"
#include "score_indicatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define UPDATE_SCORE  1001

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Cscore_indicatorDlg �Ի���



Cscore_indicatorDlg::Cscore_indicatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cscore_indicatorDlg::IDD, pParent)
	, m_ch1("")
	, m_ch2("")
	, m_ch3("")
	, m_ch4("")
	, m_ch5("")

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
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// Cscore_indicatorDlg ��Ϣ�������

BOOL Cscore_indicatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	DoLoadConf();
	GetClientRect(&m_rect);
	SetItemFont();
	SetTimer(UPDATE_SCORE, 1000, NULL);
	ShowWindow(SW_MAXIMIZE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cscore_indicatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	CString cs;
	cs.Format(_T("%s"), lpTemp);
	if (cs.Compare(m_ch1) != 0)
	{	
		m_ch1 = cs;
		GetDlgItem(IDC_STATIC_1)->SetWindowText(lpTemp);
		CRect rc;
		GetDlgItem(IDC_STATIC_1)->GetWindowRect(&rc);
		//ת��Ϊ�������
		ScreenToClient(&rc);
		//ˢ��ָ������,ע���2������Ϊ��,��ˢ�±���
		InvalidateRect(&rc, TRUE);
	}


	GetPrivateProfileString(section, _T("CH2"), _T("80"), lpTemp, 10, config_path.GetBuffer(0));
	cs.Format(_T("%s"), lpTemp);
	if (cs.Compare(m_ch2) != 0)
	{
		m_ch2 = cs;
		GetDlgItem(IDC_STATIC_2)->SetWindowText(lpTemp);
		CRect rc;
		GetDlgItem(IDC_STATIC_2)->GetWindowRect(&rc);
		//ת��Ϊ�������
		ScreenToClient(&rc);
		//ˢ��ָ������,ע���2������Ϊ��,��ˢ�±���
		InvalidateRect(&rc, TRUE);
	}
	GetPrivateProfileString(section, _T("CH3"), _T("80"), lpTemp, 10, config_path.GetBuffer(0));
	cs.Format(_T("%s"), lpTemp);
	if (cs.Compare(m_ch3) != 0)
	{
		m_ch3 = cs;
		GetDlgItem(IDC_STATIC_3)->SetWindowText(lpTemp);
		CRect rc;
		GetDlgItem(IDC_STATIC_3)->GetWindowRect(&rc);
		//ת��Ϊ�������
		ScreenToClient(&rc);
		//ˢ��ָ������,ע���2������Ϊ��,��ˢ�±���
		InvalidateRect(&rc, TRUE);
	}
	GetPrivateProfileString(section, _T("CH4"), _T("80"), lpTemp, 10, config_path.GetBuffer(0));
	cs.Format(_T("%s"), lpTemp);
	if (cs.Compare(m_ch4) != 0)
	{
		m_ch4 = cs;
		GetDlgItem(IDC_STATIC_4)->SetWindowText(lpTemp);
		CRect rc;
		GetDlgItem(IDC_STATIC_4)->GetWindowRect(&rc);
		//ת��Ϊ�������
		ScreenToClient(&rc);
		//ˢ��ָ������,ע���2������Ϊ��,��ˢ�±���
		InvalidateRect(&rc, TRUE);
	}
	GetPrivateProfileString(section, _T("CH5"), _T("80"), lpTemp, 10, config_path.GetBuffer(0));
	cs.Format(_T("%s"), lpTemp);
	if (cs.Compare(m_ch5) != 0)
	{
		m_ch5 = cs;
		GetDlgItem(IDC_STATIC_5)->SetWindowText(lpTemp);
		CRect rc;
		GetDlgItem(IDC_STATIC_5)->GetWindowRect(&rc);
		//ת��Ϊ�������
		ScreenToClient(&rc);
		//ˢ��ָ������,ע���2������Ϊ��,��ˢ�±���
		InvalidateRect(&rc, TRUE);
	}

	
	

	//GetDlgItem(IDC_STATIC_2)->GetWindowRect(&rc);
	////ת��Ϊ�������
	//ScreenToClient(&rc);
	////ˢ��ָ������,ע���2������Ϊ��,��ˢ�±���
	//InvalidateRect(&rc, TRUE);

	//GetDlgItem(IDC_STATIC_3)->GetWindowRect(&rc);
	////ת��Ϊ�������
	//ScreenToClient(&rc);
	////ˢ��ָ������,ע���2������Ϊ��,��ˢ�±���
	//InvalidateRect(&rc, TRUE);

	//GetDlgItem(IDC_STATIC_4)->GetWindowRect(&rc);
	////ת��Ϊ�������
	//ScreenToClient(&rc);
	////ˢ��ָ������,ע���2������Ϊ��,��ˢ�±���
	//InvalidateRect(&rc, TRUE);

	//GetDlgItem(IDC_STATIC_5)->GetWindowRect(&rc);
	////ת��Ϊ�������
	//ScreenToClient(&rc);
	////ˢ��ָ������,ע���2������Ϊ��,��ˢ�±���
	//InvalidateRect(&rc, TRUE);

	UpdateData(FALSE);
}

void Cscore_indicatorDlg::SetItemFont()
{
	m_font.CreatePointFont(500, _T("Arial"));

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

	// TODO:  �ڴ˸��� DC ���κ�����
	pDC->SetTextColor(RGB(109, 192, 173));

	static CBrush gBr;
	static bool isInited = false;
	if (!isInited)
	{
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP2);
		gBr.CreatePatternBrush(&bitmap);
		COLORREF clearColor = -1;
		bitmap.DeleteObject();
		isInited = true;
	}
	if (pWnd == this)
	{
		pDC->SetBkMode(TRANSPARENT);
		return gBr; //�����ڱ���ʹ���������ˢ
	}
	else
	{
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); //�����ؼ�ʹ��͸������
	}

	return hbr;
}


void Cscore_indicatorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType == 1) 
		return;//��С����ʲô������  
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
		if (pWnd[i])  //�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����
		{
			CRect rect;   //��ȡ�ؼ��仯ǰ�Ĵ�С 
			pWnd[i]->GetWindowRect(&rect);
			ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������

			//    cx/m_rect.Width()Ϊ�Ի����ں���ı仯����
			rect.left = rect.left*cx / m_rect.Width();//�����ؼ���С
			rect.right = rect.right*cx / m_rect.Width();
			rect.top = rect.top*cy / m_rect.Height();
			rect.bottom = rect.bottom*cy / m_rect.Height();
			pWnd[i]->MoveWindow(rect);//���ÿؼ���С
		}
	}

	GetClientRect(&m_rect);
}
