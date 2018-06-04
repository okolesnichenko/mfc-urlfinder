
// mfcurlDoc.h : interface of the CmfcurlDoc class
//


#pragma once
#include <list>
#include "FileUrl.h"

using namespace std;

class CmfcurlDoc : public CDocument
{
private:
	static const int m_maxLength = 1000;
	CString m_str;
	CString directory;
	list <CString> l_htmls;
	list<FileUrl> l_urls;
	bool l_urlsIsEmpty{ true };
protected: // create from serialization only
	CmfcurlDoc();
	DECLARE_DYNCREATE(CmfcurlDoc)

// Attributes
public:

// Operations
public:
	CString GetContent();
	list<CString> GetListHtml();
	list<FileUrl> GetListUrl();
	
	void FindUrls(string, string);
	void SetListUrl(list<FileUrl>);
	void SetListHtml(list<CString>);
	void SetStr(CString);
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CmfcurlDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnUpdateActionSomeaction(CCmdUI *pCmdUI);
	afx_msg void OnActionSomeaction();
};
