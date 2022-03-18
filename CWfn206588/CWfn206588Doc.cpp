
// CWfn206588Doc.cpp : implementation of the CCWfn206588Doc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CWfn206588.h"
#endif
#include "CMyLine.h"
#include "CMyRectangle.h"
#include "CWfn206588Doc.h"
#include <string>
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCWfn206588Doc

IMPLEMENT_DYNCREATE(CCWfn206588Doc, CDocument)

BEGIN_MESSAGE_MAP(CCWfn206588Doc, CDocument)
END_MESSAGE_MAP()


// CCWfn206588Doc construction/destruction

CCWfn206588Doc::CCWfn206588Doc() noexcept
{
	// TODO: add one-time construction code here

}

CCWfn206588Doc::~CCWfn206588Doc()
{
}

BOOL CCWfn206588Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CCWfn206588Doc serialization

void CCWfn206588Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		string file = "";

		for (int i = 0; i < this->objects.size(); i++) {
			if (this->objects[i]->type.compare("CMyRectangle")) {
				file = file + "1";
			}
			else if (this->objects[i]->type.compare("CMyLine")) {
				file = file + "0";
			}
			file = file + "\n";
			file = file
				+ std::to_string(this->objects[i]->startX)
				+ std::to_string(this->objects[i]->startY)
				+ std::to_string(this->objects[i]->endX)
				+ std::to_string(this->objects[i]->endY)
				+ "\n";
		}
		ar.Write(&file, file.size());
	}
	else
	{
		// TODO: add loading code here
		char ss[80];
		bool isRectangle = false;
		int isRect = 0,
			startX = 0,
			startY = 0,
			endX = 0,
			endY = 0;
		ar.Read(ss, 79);
		sscanf_s(ss, "%d", &isRect);
		isRectangle = isRect;
		ar.Read(ss, 79);
		sscanf_s(ss, "%d %d %d %d", &startX, &startY, &endX, &endY);
		CFigure* figure;
		if (isRectangle) {
			figure = new CMyRectangle(startX, startY, endX, endY);
		}
		else {
			figure = new CMyLine(startX, startY, endX, endY);
		}
		this->objects.push_back(figure);
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CCWfn206588Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CCWfn206588Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCWfn206588Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCWfn206588Doc diagnostics

#ifdef _DEBUG
void CCWfn206588Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCWfn206588Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCWfn206588Doc commands
