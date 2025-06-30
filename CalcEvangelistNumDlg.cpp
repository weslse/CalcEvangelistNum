// CalcEvangelistNumDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CalcEvangelistNum.h"
#include "CalcEvangelistNumDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <vector>
#include <algorithm>
#include <string>

// CCalcEvangelistNumDlg 대화 상자



CCalcEvangelistNumDlg::CCalcEvangelistNumDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCEVANGELISTNUM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalcEvangelistNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVANGELIST_LIST, m_evangelist_list);
	DDX_Control(pDX, IDC_NUM, m_num);
}

BEGIN_MESSAGE_MAP(CCalcEvangelistNumDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_CALC, &CCalcEvangelistNumDlg::OnBnClickedCalc)
	ON_BN_CLICKED(IDC_RESET, &CCalcEvangelistNumDlg::OnBnClickedReset)
END_MESSAGE_MAP()


// CCalcEvangelistNumDlg 메시지 처리기

BOOL CCalcEvangelistNumDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ModifyStyle(0, WS_SYSMENU, 0);
	SetIcon(m_hIcon, FALSE);

	SetWindowTextW(_T("Evangelist Number Calculator"));

	// 멀티라인 + 세로 스크롤만 추가
	m_evangelist_list.ModifyStyle(WS_HSCROLL, ES_MULTILINE | WS_VSCROLL);

	return TRUE;
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCalcEvangelistNumDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCalcEvangelistNumDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalcEvangelistNumDlg::OnBnClickedCalc()
{
	CString srcStr;
	m_evangelist_list.GetWindowTextW(srcStr);
	if (srcStr.IsEmpty()) {
		m_num.SetWindowTextW(_T("0(0)"));
		return;
	}

	std::vector<CString> evangelists;
	LPCTSTR delimiters = _T(" .,;\n");
	int curPos = 0;
	CString token;
	while (!(token = srcStr.Tokenize(delimiters, curPos)).IsEmpty()) {
		token.Trim();
		token.TrimRight(_T(".,;\n")); // . , ; \n 이 포함되어 있으면 제거	
		if (!token.IsEmpty())
			evangelists.push_back(token);
	}

	CString total_num = CString(std::to_string(evangelists.size()).c_str());
	std::sort(evangelists.begin(), evangelists.end());
	evangelists.erase(std::unique(evangelists.begin(), evangelists.end()), evangelists.end());
	CString sieve_num = CString(std::to_string(evangelists.size()).c_str());

	CString result_string = sieve_num + '(' + total_num + ')';
	m_num.SetWindowTextW(result_string);
}

void CCalcEvangelistNumDlg::OnBnClickedReset()
{
	m_evangelist_list.SetWindowTextW(_T(""));
	m_num.SetWindowTextW(_T(""));
}