
// MFC2048.h : MFC2048 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFC2048App:
// �� Ŭ������ ������ ���ؼ��� MFC2048.cpp�� �����Ͻʽÿ�.
//

class CMFC2048App : public CWinApp
{
public:
	CMFC2048App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC2048App theApp;
