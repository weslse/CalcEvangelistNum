
// CalcEvangelistNumDlg.h: 헤더 파일
//

#pragma once


// CCalcEvangelistNumDlg 대화 상자
class CCalcEvangelistNumDlg : public CDialogEx
{
// 생성입니다.
public:
	CCalcEvangelistNumDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCEVANGELISTNUM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_evangelist_list;
	CEdit m_num;

	afx_msg void OnBnClickedCalc();
	afx_msg void OnBnClickedReset();
};
