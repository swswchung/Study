#pragma once

#include "DCDoc.h"
#include "DCView.h"

// Login ��ȭ �����Դϴ�.

class Login : public CDialog
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Login();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_id;
	CFrameWnd* m_pWnd;
	CDCView* m_pView;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
