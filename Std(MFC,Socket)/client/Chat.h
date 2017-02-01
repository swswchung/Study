#pragma once
#include "afxwin.h"



// Chat �� ���Դϴ�.

class Chat : public CFormView
{
	DECLARE_DYNCREATE(Chat)

public:
	Chat();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~Chat();

public:
	enum { IDD = IDD_CHAT };
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
	CString m_msg;
	afx_msg void OnBnClickedButton1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


