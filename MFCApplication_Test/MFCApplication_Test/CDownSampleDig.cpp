// CDownSampleDig.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication_Test.h"
#include "afxdialogex.h"
#include "CDownSampleDig.h"


// CDownSampleDig 대화 상자

IMPLEMENT_DYNAMIC(CDownSampleDig, CDialog)

CDownSampleDig::CDownSampleDig(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_DownSampleRate(0)
{

}

CDownSampleDig::~CDownSampleDig()
{
}

void CDownSampleDig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_DownSampleRate);
	DDV_MinMaxInt(pDX, m_DownSampleRate, 1, 32);
}


BEGIN_MESSAGE_MAP(CDownSampleDig, CDialog)
END_MESSAGE_MAP()


// CDownSampleDig 메시지 처리기
