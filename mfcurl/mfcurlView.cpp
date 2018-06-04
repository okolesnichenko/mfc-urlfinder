
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
	ON_COMMAND(ID_ACTION_SOMEACTION, &CmfcurlView::OnActionSomeaction)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SOMEACTION, &CmfcurlView::OnUpdateActionSomeaction)
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

void CmfcurlView::OnDraw(CDC* pDC)
{
	CmfcurlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	RECT rect;
	int nY = 0;
	// размеры нашего окна
	GetClientRect(&rect);
	//pDC->Ellipse(&rect);
	pDC->DrawText(pDoc->GetContent(), &rect, DT_LEFT);
	nY = 20;
	if (!listUrlFull)
	{
		list <FileUrl> buf = pDoc->GetListUrl();
		for (auto it = buf.begin(); it != buf.end(); it++)
		{
			FileUrl d(*it);
			CString cfile(d.GetFile().c_str());
			CString cstr(d.GetName().c_str());
			CString cline;
			cline.Format(_T("%d"), d.GetLine());
			// перерсовывается для каждого URL
			CString f("File"), s("URL"), l("Line");
			pDC->TextOutW(0, 0, f);
			pDC->TextOutW(300, 0, s);
			pDC->TextOutW(600, 0, l);

			pDC->TextOutW(0, nY, cfile);
			pDC->TextOutW(300, nY, cstr);
			pDC->TextOutW(600, nY, cline);
			nY += 20;
		}
	}

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


void CmfcurlView::OnActionSomeaction()
{
	CmfcurlDoc * doc = GetDocument();
	listUrlFull = !listUrlFull;
	doc->OnActionSomeaction();
	Invalidate();
	UpdateWindow();
	// TODO: Add your command handler code here
}


void CmfcurlView::OnUpdateActionSomeaction(CCmdUI *pCmdUI)
{
	POSITION pos = theApp.GetFirstDocTemplatePosition();
	CDocTemplate * pTemplate = (CDocTemplate*)theApp.GetNextDocTemplate(pos);
	POSITION posDoc = pTemplate->GetFirstDocPosition();
	if (!posDoc)
	{
		pCmdUI->Enable(FALSE);
	}

	CDocument *pDoc = pTemplate->GetNextDoc(posDoc);
	CmfcurlDoc *doC = GetDocument();
	if (doC->GetContent().GetLength() == 0)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(pDoc != NULL);
	}
	

	
	// TODO: Add your command update UI handler code here
}
