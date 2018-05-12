
// mfcurlView.cpp : implementation of the CmfcurlView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mfcurl.h"
#endif

#include "mfcurlDoc.h"
#include "mfcurlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfcurlView

IMPLEMENT_DYNCREATE(CmfcurlView, CView)

BEGIN_MESSAGE_MAP(CmfcurlView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CmfcurlView construction/destruction

CmfcurlView::CmfcurlView()
{
	// TODO: add construction code here

}

CmfcurlView::~CmfcurlView()
{
}

BOOL CmfcurlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CmfcurlView drawing

void CmfcurlView::OnDraw(CDC* /*pDC*/)
{
	CmfcurlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CmfcurlView printing

BOOL CmfcurlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CmfcurlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CmfcurlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CmfcurlView diagnostics

#ifdef _DEBUG
void CmfcurlView::AssertValid() const
{
	CView::AssertValid();
}

void CmfcurlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmfcurlDoc* CmfcurlView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmfcurlDoc)));
	return (CmfcurlDoc*)m_pDocument;
}
#endif //_DEBUG


// CmfcurlView message handlers
