// DCDoc.h : CDCDoc Ŭ������ �������̽�
//


#pragma once

class CDCDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CDCDoc();
	DECLARE_DYNCREATE(CDCDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CDCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
public:

protected:
	DECLARE_MESSAGE_MAP()
};


