
// score_indicatorDlg.h : 头文件
//

#pragma once

#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")

// Cscore_indicatorDlg 对话框
class Cscore_indicatorDlg : public CDialogEx
{
// 构造
public:
	Cscore_indicatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SCORE_INDICATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	void OnOK();
	// 生成的消息映射函数
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
	CString m_ch[5];

	Gdiplus::GdiplusStartupInput m_GdiplusStarupInput;
	ULONG_PTR m_uGdiplusToken;

	Gdiplus::Image* m_img;
	int m_iFontSize;
};
