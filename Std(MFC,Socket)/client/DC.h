// DC.h : DC ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "chat.h"
#include "state.h"

#include "DCDoc.h"
#include "DCView.h"
// CDCApp:
// �� Ŭ������ ������ ���ؼ��� DC.cpp�� �����Ͻʽÿ�.
//

class CDCApp : public CWinApp
{
public:
	CDCApp();
	Chat* m_pChat;
	CDCView* m_pView;
	State* m_pState;

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

};

extern CDCApp theApp;