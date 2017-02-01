// State.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DC.h"
#include "State.h"


// State

IMPLEMENT_DYNCREATE(State, CFormView)

State::State()
	: CFormView(State::IDD)
{

}

State::~State()
{
}

void State::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(State, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// State �����Դϴ�.

#ifdef _DEBUG
void State::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void State::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// State �޽��� ó�����Դϴ�.

int State::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	
	CDCApp* pApp = (CDCApp*)AfxGetApp();
	pApp->m_pState = this;
	
	return 0;
}
