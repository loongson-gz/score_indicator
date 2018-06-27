fnfg
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

	SetTimer(UPDATE_SCORE, 1000, NULL);

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

