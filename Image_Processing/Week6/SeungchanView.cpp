
// SeungchanView.cpp: CSeungchanView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Seungchan.h"
#endif

#include "SeungchanDoc.h"
#include "SeungchanView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSeungchanView

IMPLEMENT_DYNCREATE(CSeungchanView, CView)

BEGIN_MESSAGE_MAP(CSeungchanView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSeungchanView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DOWN_SAMPLING, &CSeungchanView::OnDownSampling)
	ON_COMMAND(ID_UP_SAMPLING, &CSeungchanView::OnUpSampling)
	ON_COMMAND(ID_QUANTIZATION, &CSeungchanView::OnQuantization)
	ON_COMMAND(ID_SUM_CONSTANT, &CSeungchanView::OnSumConstant)
	ON_COMMAND(ID_SUB_CONSTANT, &CSeungchanView::OnSubConstant)
	ON_COMMAND(ID_MUL_CONSTANT, &CSeungchanView::OnMulConstant)
	ON_COMMAND(ID_DIV_CONSTANT, &CSeungchanView::OnDivConstant)
	ON_COMMAND(ID_AND_OPERATE, &CSeungchanView::OnAndOperate)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CSeungchanView::OnNegaTransform)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CSeungchanView::OnGammaCorrection)
	ON_COMMAND(ID_BINARIZATION, &CSeungchanView::OnBinarization)
	ON_COMMAND(32785, &CSeungchanView::On32785)
	ON_COMMAND(ID_HISTO_STRETCH, &CSeungchanView::OnHistoStretch)
	ON_COMMAND(ID_END_IN_SEARCH, &CSeungchanView::OnEndInSearch)
	ON_COMMAND(ID_HISTOGRAM, &CSeungchanView::OnHistogram)
	ON_COMMAND(ID_HISTO_EQUAL, &CSeungchanView::OnHistoEqual)
END_MESSAGE_MAP()

// CSeungchanView 생성/소멸

CSeungchanView::CSeungchanView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSeungchanView::~CSeungchanView()
{
}

BOOL CSeungchanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSeungchanView 그리기

void CSeungchanView::OnDraw(CDC* pDC)
{
	CSeungchanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int i, j;
	unsigned char R, G, B;

	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = G = B = pDoc->m_InputImage[i * pDoc->m_width + j];
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}
	// 축소된 영상 출력
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}
}


// CSeungchanView 인쇄


void CSeungchanView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSeungchanView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSeungchanView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSeungchanView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSeungchanView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSeungchanView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSeungchanView 진단

#ifdef _DEBUG
void CSeungchanView::AssertValid() const
{
	CView::AssertValid();
}

void CSeungchanView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSeungchanDoc* CSeungchanView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSeungchanDoc)));
	return (CSeungchanDoc*)m_pDocument;
}
#endif //_DEBUG


// CSeungchanView 메시지 처리기

void CSeungchanView::OnDownSampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnDownSampling(); // Doc 클래스에 OnDownSampling 함수 호출

	Invalidate(TRUE); // 화면 갱신

}

void CSeungchanView::OnUpSampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnUpSampling(); // Doc 클래스에 OnUpSampling 함수 호출

	Invalidate(TRUE); // 화면 갱신

}

void CSeungchanView::OnQuantization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnQuantization(); // Doc 클래스에 OnQuantization 함수 호출

	Invalidate(TRUE); // 화면 갱신

}

void CSeungchanView::OnSumConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument();
	// 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnSumConstant();

	Invalidate(TRUE);

}

void CSeungchanView::OnSubConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument();// 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnSubConstant();

	Invalidate(TRUE);

}

void CSeungchanView::OnMulConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument(); // 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnMulConstant();

	Invalidate(TRUE);

}

void CSeungchanView::OnDivConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument(); // 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnDivConstant();

	Invalidate(TRUE);

}

void CSeungchanView::OnAndOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndOperate();

	Invalidate(TRUE);

}

void CSeungchanView::OnNegaTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNegaTransform();

	Invalidate(TRUE);

}

void CSeungchanView::OnGammaCorrection()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGammaCorrection();

	Invalidate(TRUE);

}

void CSeungchanView::OnBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinarization();

	Invalidate(TRUE);

}

void CSeungchanView::On32785()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnStressTransform();

	Invalidate(TRUE);

}

void CSeungchanView::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretch();

	Invalidate(TRUE);

}

void CSeungchanView::OnEndInSearch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEndInSearch();

	Invalidate(TRUE);

}

void CSeungchanView::OnHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistogram();
	Invalidate(TRUE);

}

void CSeungchanView::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeungchanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();

	Invalidate(TRUE);
}
