
// CWfn206588View.cpp : implementation of the CCWfn206588View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CWfn206588.h"
#endif

#include "CWfn206588Doc.h"
#include "CWfn206588View.h"

#include "CMyLine.h"
#include "CMyRectangle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCWfn206588View

bool isDrawingRectangle = false;

IMPLEMENT_DYNCREATE(CCWfn206588View, CView)

BEGIN_MESSAGE_MAP(CCWfn206588View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCWfn206588View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCWfn206588View construction/destruction

CCWfn206588View::CCWfn206588View() noexcept
{
	// TODO: add construction code here

}

CCWfn206588View::~CCWfn206588View()
{
}

BOOL CCWfn206588View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCWfn206588View drawing

void CCWfn206588View::OnDraw(CDC* pDC)
{
	CCWfn206588Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); 
	if (!pDoc)
		return;
	
	// TODO: add draw code for native data here
	for (int i = 0; i < pDoc->objects.size(); i++) {
		pDoc->objects[i]->draw(pDC);
	}
}


// CCWfn206588View printing


void CCWfn206588View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCWfn206588View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCWfn206588View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCWfn206588View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCWfn206588View diagnostics

#ifdef _DEBUG
void CCWfn206588View::AssertValid() const
{
	CView::AssertValid();
}

void CCWfn206588View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCWfn206588Doc* CCWfn206588View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCWfn206588Doc)));
	return (CCWfn206588Doc*)m_pDocument;
}
#endif //_DEBUG


// CCWfn206588View message handlers


int startPosX = 0, startPosY = 0;

void CCWfn206588View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	startPosX = point.x;
	startPosY = point.y;

	CView::OnLButtonDown(nFlags, point);
}


void CCWfn206588View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CCWfn206588Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	if (isDrawingRectangle) {
		CFigure* rect = new CMyRectangle(startPosX, startPosY, point.x, point.y);
		pDoc->objects.push_back(rect);
	}
	else {
		CFigure* line = new CMyLine(startPosX, startPosY, point.x, point.y);
		pDoc->objects.push_back(line);
	}
	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}

void CCWfn206588View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	// Change draweing modes by pressing R for Rectangle and L for Line
	if (nChar == 'R') {
		AfxMessageBox(_T("Drawing rectangles"));
		isDrawingRectangle = true;
	}
	else if (nChar == 'L') {
		AfxMessageBox(_T("Drawing Lines"));
		isDrawingRectangle = false;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCWfn206588View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CCWfn206588Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	for (int i = 0; i < pDoc->objects.size(); i++) {	
		if (pDoc->objects[i]->pointIsWithin3px(point)) {
			pDoc->objects.erase(pDoc->objects.begin() + i);
		}
	}
	Invalidate();

	CView::OnRButtonUp(nFlags, point);
}
