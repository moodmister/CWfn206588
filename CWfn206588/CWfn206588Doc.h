
// CWfn206588Doc.h : interface of the CCWfn206588Doc class
//


#pragma once
#include "CFigure.h"
#include<vector>
using namespace std;

class CCWfn206588Doc : public CDocument
{
protected: // create from serialization only
	CCWfn206588Doc() noexcept;
	DECLARE_DYNCREATE(CCWfn206588Doc)

// Attributes
public:
	vector <CFigure*> objects;

// Operations
public:

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
	virtual ~CCWfn206588Doc();
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
};
