// Socket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DC.h"
#include "Socket.h"
#include "DCDoc.h"
#include "DCView.h"


// Socket

Socket::Socket()
{
}

Socket::~Socket()
{
}


// Socket ��� �Լ�

void Socket::OnConnect(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pView->RunConnect(nErrorCode);
	CAsyncSocket::OnConnect(nErrorCode);
}

void Socket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pView->RunReceive(nErrorCode);
	CAsyncSocket::OnReceive(nErrorCode);
}

void Socket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	AfxMessageBox("�����");
	CAsyncSocket::OnClose(nErrorCode);
}
