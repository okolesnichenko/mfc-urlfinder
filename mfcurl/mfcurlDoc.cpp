/*Общие требования к реализации:
1. Ядро приложения работает с использованием контейнеров и алгоритмов STL
2. Отсутствие С-конструкций в коде (использование вместо них конструкций С++)
3. Удобный многодокументный интерфейс на базе MFC (QT, GDK…)
4. Система логирования, сохраняющая всю активность приложения и пользователя в файл формата (время, важность, текст сообщения)
5. Обработка исключений, защита от дурака

7. Дан список html-файлов, задаваемый в виде строки файлов, перечисляемых через запятую.
Найти в них все вхождения URL-адресов в формате протокол://www.tratata.ppp.ru, где протокол – http, ftp, gopher, news, telnet, file.
Выдать для каждого URL список вхождений (файл, строка, столбец).


https://www.youtube.com/playlist?list=PLnbQh4j9gZkK6BE59UVgwPQ6mTq_bTmv1
http://www.i2r.ru/static/374/out_18665.shtml

*/
// mfcurlDoc.cpp : implementation of the CmfcurlDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mfcurl.h"
#endif

#include "mfcurlDoc.h"
#include "mfcurlView.h"
#include "FileUrl.h"
#include <propkey.h>
#include <regex>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma warning(disable : 4996) 
// CmfcurlDoc

IMPLEMENT_DYNCREATE(CmfcurlDoc, CDocument)

BEGIN_MESSAGE_MAP(CmfcurlDoc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SOMEACTION, &CmfcurlDoc::OnUpdateActionSomeaction)
	ON_COMMAND(ID_ACTION_SOMEACTION, &CmfcurlDoc::OnActionSomeaction)
END_MESSAGE_MAP()


// CmfcurlDoc construction/destruction

CmfcurlDoc::CmfcurlDoc()
{
	// TODO: add one-time construction code here

}

CmfcurlDoc::~CmfcurlDoc()
{
	this->l_htmls.clear();
	this->l_urls.clear();
}

CString CmfcurlDoc::GetContent()
{
	return m_str;
}

list<CString> CmfcurlDoc::GetListHtml()
{
	return this->l_htmls;
}

list<FileUrl> CmfcurlDoc::GetListUrl()
{
	return this->l_urls;
}

void CmfcurlDoc::SetListUrl(list<FileUrl> urls)
{
	this->l_urls = urls;
}

void CmfcurlDoc::SetListHtml(list<CString> htmls)
{
	this->l_htmls = htmls;
}

void CmfcurlDoc::SetStr(CString str)
{
	this->m_str = str;
}

BOOL CmfcurlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CmfcurlDoc serialization

void CmfcurlDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
		char * m_buf;
		m_buf = new char[m_maxLength];
		try
		{
			strnset(m_buf, 0, m_maxLength);
			ar.Read(m_buf, m_maxLength);
			CFile * file = ar.GetFile();
			directory = file->GetFilePath();
			directory.Replace(file->GetFileName(), NULL);
			int len = strlen(m_buf);
			m_str.GetBufferSetLength(len);
			int n = m_str.GetAllocLength();
			mbstowcs(m_str.GetBuffer(), m_buf, len);
			delete[] m_buf;
		}
		catch (...)
		{
			delete[] m_buf;
		}

	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CmfcurlDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CmfcurlDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CmfcurlDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CmfcurlDoc diagnostics

#ifdef _DEBUG
void CmfcurlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CmfcurlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CmfcurlDoc commands

void CmfcurlDoc::OnActionSomeaction()
{
	//TODO: Add your command handler code here
	if (m_str.GetLength() != 0)
	{
		POSITION pos = theApp.GetFirstDocTemplatePosition();
		CDocTemplate * pTemplate = (CDocTemplate*)theApp.GetNextDocTemplate(pos);
		CString tmp;
		CFile file;
		CFileException fileException;
		// .html in list<CString> l_urls
		for (int i = 0; i <= m_str.GetLength(); i++)
		{
			if ((m_str[i] == ',') || (i == m_str.GetLength()))
			{
				l_htmls.push_back(tmp);
				tmp.Empty();
				i++;
			}
			else
			{
				tmp += m_str[i];
			}
		}
		// поиск в буффере и поиск url
		for (auto it = l_htmls.begin(); it != l_htmls.end(); it++)
		{
			char * buffer = new char[2000];
			memset(buffer, 0, sizeof(buffer));

			if (file.Open(directory += *it, CFile::modeReadWrite, &fileException))
			{
				file.Read(buffer, 2000);
			}

			string bufString(buffer);
			CT2CA pszConvertedAnsiString(*it);
			std::string strStd(pszConvertedAnsiString);
			FindUrls(bufString, strStd);

			directory.Replace(*it, NULL);
			delete[] buffer;
			file.Close();
		}
		CmfcurlDoc *d = (CmfcurlDoc*)(pTemplate->OpenDocumentFile(NULL));
		d->SetListUrl(l_urls);
		l_htmls.clear();
		l_urls.clear();
	}
}

void CmfcurlDoc::FindUrls(string buffer, string file)
{
	//http, ftp, gopher, news, telnet, file.
	vector<string> protocol = { "http://", "ftp://", "news://", "telnet://", "file://", "gopher://" };
	string tmp;
	int j = 0;
	int aFind = 0;
	int bFind = 1;
	int count = 1;
	int endline[20];
	while (buffer.find("\n") != -1)
	{
		endline[count++] = buffer.find("\n");
		buffer.erase(buffer.find("\n"), 1);
	}
	for (int i = 0; i < protocol.size(); i++)
	{
		aFind = buffer.find(protocol[i]);
		while (aFind != -1)
		{
			tmp = protocol[i];
			while ((buffer[aFind + protocol[i].size() + j] != '"') && (buffer[aFind + protocol[i].size() + j] != ' ') && (buffer[aFind + protocol[i].size() + j] != '<'))
			{
				tmp += buffer[aFind + protocol[i].size() + j];
				j++;
			}
			buffer.erase(aFind, protocol[i].size());

			while (aFind + protocol[i].size() > endline[bFind])
			{
				bFind++;
			}
			
			FileUrl url(tmp, file, bFind);
			l_urls.push_back(url);
			tmp.clear();
			j = 0;
			bFind = 1;
			aFind = buffer.find(protocol[i]);
		}
	}
	string res = tmp;
}


void CmfcurlDoc::OnUpdateActionSomeaction(class CCmdUI * pcMdui)
{

}
