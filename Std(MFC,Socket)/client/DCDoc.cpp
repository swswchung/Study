// DCDoc.cpp : CDCDoc Ŭ������ ����
//

#include "stdafx.h"
#include "DC.h"

#include "DCDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDCDoc

IMPLEMENT_DYNCREATE(CDCDoc, CDocument)

BEGIN_MESSAGE_MAP(CDCDoc, CDocument)
END_MESSAGE_MAP()


// CDCDoc ����/�Ҹ�

CDCDoc::CDCDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
}

CDCDoc::~CDCDoc()
{
}

BOOL CDCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CDCDoc serialization

void CDCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CDCDoc ����

#ifdef _DEBUG
void CDCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDCDoc ���
