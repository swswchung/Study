// Interface.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DC.h"
#include "Interface.h"


// Interface

IMPLEMENT_DYNCREATE(Interface, CFormView)

Interface::Interface()
	: CFormView(Interface::IDD)
{

}

Interface::~Interface()
{
}

void Interface::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Interface, CFormView)
END_MESSAGE_MAP()


// Interface �����Դϴ�.

#ifdef _DEBUG
void Interface::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Interface::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Interface �޽��� ó�����Դϴ�.
