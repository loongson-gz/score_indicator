
// score_indicatorDlg.h : ͷ�ļ�
//

#pragma once


// Cscore_indicatorDlg �Ի���
class Cscore_indicatorDlg : public CDialogEx
{
// ����
public:
	Cscore_indicatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SCORE_INDICATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void DoLoadConf();
	void SetItemFont();
	CFont m_font;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CRect m_rect;
	CString m_ch1;
	CString m_ch2;
	CString m_ch3;
	CString m_ch4;
	CString m_ch5;

};
