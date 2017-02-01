
// MFC2048View.cpp : CMFC2048View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFC2048.h"
#endif

#include "MFC2048Doc.h"
#include "MFC2048View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC2048View

IMPLEMENT_DYNCREATE(CMFC2048View, CView)

BEGIN_MESSAGE_MAP(CMFC2048View, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_MOVE_LOG, &CMFC2048View::OnMoveLog)
	ON_COMMAND(ID_ONLY_NUM, &CMFC2048View::OnOnlyNum)
	ON_COMMAND(ID_NUM_COL, &CMFC2048View::OnNumCol)
	ON_COMMAND(ID_TURN_LOG, &CMFC2048View::OnTurnLog)
	ON_UPDATE_COMMAND_UI(ID_MOVE_LOG, &CMFC2048View::OnUpdateMoveLog)
	ON_UPDATE_COMMAND_UI(ID_NUM_COL, &CMFC2048View::OnUpdateNumCol)
	ON_UPDATE_COMMAND_UI(ID_ONLY_NUM, &CMFC2048View::OnUpdateOnlyNum)
	ON_UPDATE_COMMAND_UI(ID_TURN_LOG, &CMFC2048View::OnUpdateTurnLog)
END_MESSAGE_MAP()

// CMFC2048View ����/�Ҹ�

CMFC2048View::CMFC2048View()
	: m_bOnlyChecked(false)
	, m_bNCChecked(true)
	, m_bMLogChecked(true)
	, m_bTLogChecked(true)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMFC2048View::~CMFC2048View()
{
}

BOOL CMFC2048View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMFC2048View �׸���

void CMFC2048View::OnDraw(CDC* pDC)
{
	CMFC2048Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	m_Board.Paint(pDC);	

	ReleaseDC(pDC);
}


// CMFC2048View ����

#ifdef _DEBUG
void CMFC2048View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC2048View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC2048Doc* CMFC2048View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC2048Doc)));
	return (CMFC2048Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC2048View �޽��� ó����


BOOL CMFC2048View::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN)		//Ű�����Է��� �޾� �� ����� ���ڸ� �����δ�.
	{
		m_Board.PushKey(pMsg->wParam);
		Invalidate();
	}


	
	
	return CView::PreTranslateMessage(pMsg);
}


void CMFC2048View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//���콺 Ŭ�� �ÿ� �� ���� x��ǥ�� ���� ���带 ������.
	pt.x = point.x;
	pt.y = point.y;
	m_drag = true;	//�巡�׻������� Ȯ���ϴ� ����

	CView::OnLButtonDown(nFlags, point);
}


void CMFC2048View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_drag == true)
	{
		m_drag = false;

		if (pt.y <= 256 && point.y <= 256)//����ۿ����� �巡�״� �����϶� �ϼ����� ��� �ȿ��� �巡���Ѱ͸� üũ�Ѵ�.
		{
			if (pt.x < point.x) //������ �巡�� �� ���带 ���������� ����.
			{
				m_Board.TurnBoard(1);
				Invalidate();
			}
			else if (point.x < pt.x)//�������� �巡�� �� ���带 �������� ����.
			{
				m_Board.TurnBoard(2);
				Invalidate();
			}
		}
	}
	CView::OnLButtonUp(nFlags, point);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//���ڸ� ���ϰ��� ����,���� �Ѵ� ���ϰ��� ����. �Ѱ��� üũ���°��Ǹ� �ٸ��ϳ��� ��üũ�ȴ�.
void CMFC2048View::OnNumCol()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	//�⺻������ true�����̴�. ��üũ�� �����϶� ������ üũ���°���.
	m_bNCChecked = true;
	m_bOnlyChecked = false;//���ڸ� ���̰��ϴ� �޴��� ��üũ�Ѵ�.
	m_Board.drawOption = true;
	Invalidate();
}

void CMFC2048View::OnUpdateNumCol(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (m_bNCChecked == true)
	{
		pCmdUI->SetCheck(TRUE);//üũ���´� TRUE�� ����� ���ڿ� ������ ���ÿ� ����ϰ� ��.

	}
	else
	{
		pCmdUI->SetCheck(FALSE);//üũ���°� false�� ��üũ��.
	}
}

void CMFC2048View::OnOnlyNum()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Board.drawOption = false;
	m_bOnlyChecked = true;
	m_bNCChecked = false;
	Invalidate();
}


void CMFC2048View::OnUpdateOnlyNum(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (m_bOnlyChecked == true)
	{
		pCmdUI->SetCheck(TRUE);

	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//�α����ϻ����� �ϳ��� üũ���°��ɼ����ְ� �ΰ��� üũ���°� �ɼ����ִ�.


void CMFC2048View::OnMoveLog()	//Ű���� �̵� ����� �����. �⺻������ üũ�Ǿ�����.
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (m_bMLogChecked == false)
	{
		m_bMLogChecked = true;
		m_Board.moveLog = true;	//üũ�Ǿ������� �̵��Ҷ����� �α������� ���ŵȴ�.
	}
	else
	{
		m_bMLogChecked = false;
		m_Board.moveLog = false;
	}
}

void CMFC2048View::OnUpdateMoveLog(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (m_bMLogChecked == true)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMFC2048View::OnTurnLog()	//���콺 �巡�� �̵� ����� �����, üũ�Ǿ������� ��ϵ�, Ű����,���콺 �ΰ��� ����Ҽ����ְ� �ϳ��� �Ҽ��� ����.
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (m_bTLogChecked == false)
	{
		m_bTLogChecked = true;
		m_Board.turnLog = true;//üũ�Ǿ������� ���带 ���������� �α������� ���ŵȴ�.
	}
	else
	{
		m_bTLogChecked = false;
		m_Board.turnLog = false;
	}
	
}

void CMFC2048View::OnUpdateTurnLog(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (m_bTLogChecked == true)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}
