#pragma once
#include "afxwin.h"



// State �� ���Դϴ�.

class State : public CFormView
{
	DECLARE_DYNCREATE(State)

protected:
	State();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~State();

public:
	enum { IDD = IDD_STATE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


