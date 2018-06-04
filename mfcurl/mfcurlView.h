
// mfcurlView.h : interface of the CmfcurlView class
//

#pragma once


class CmfcurlView : public CView
{
protected: // create from serialization only
	CmfcurlView();
	DECLARE_DYNCREATE(CmfcurlView)

// Attributes
public:
	CmfcurlDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CmfcurlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnActionSomeaction();
private:
	bool listUrlFull{ false };
public:
	afx_msg void OnUpdateActionSomeaction(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in mfcurlView.cpp
inline CmfcurlDoc* CmfcurlView::GetDocument() const
   { return reinterpret_cast<CmfcurlDoc*>(m_pDocument); }
#endif

