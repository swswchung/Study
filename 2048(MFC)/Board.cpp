#include "stdafx.h"
#include "Board.h"
#include "Block.h"


Board::Board()
	: drawOption(true)//���ڸ� �������, ���� ���� �Ѵ� ������� ���Ѵ�.
	, moveLog(true)
	, turnLog(true)
	, logNum(1)
	, isGameOver(false)
{
	Block_Header = Block_Header->createLinkedList_h();
}

void Board::Paint(CDC* pDC)
{
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = RGB(255, 255, 255);

	CString msg;
	CBrush* pOldBrush = pDC->SelectObject(&newBrush);


	for (int y = 0 ; y < 4 ; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int num = Block_Header->createBoard(Block_Header, x, y);// �� ����� ���� �����´� ������ �������� ������ �ٲ�� ����.
			msg.Format("%d ", num);

			switch (num)
			{
			case 0:
				logBrush.lbColor = RGB(255, 255, 255);//0�Ͼ��
				break;
			case 2:
				logBrush.lbColor = RGB(255, 255, 0);//2 �����
				if(drawOption == true)pDC->SetBkColor(RGB(255, 255, 0));//���ڵ޹�濡�� ���������ش�. ���ڿͻ��� �޴��� üũ�Ǿ��־����.
				break;
			case 4:
				logBrush.lbColor = RGB(255, 127, 0);//4��������
				if (drawOption == true)pDC->SetBkColor(RGB(255, 127, 0));
				break;
			case 8:
				logBrush.lbColor = RGB(0, 255, 0);//8���
				if (drawOption == true)pDC->SetBkColor(RGB(0, 255, 0));
				break;
			case 16:
				logBrush.lbColor = RGB(0, 0, 255);//16�Ķ���
				if (drawOption == true)pDC->SetBkColor(RGB(0, 0, 255));
				break;
			case 32:
				logBrush.lbColor = RGB(166, 166, 166);//32ȸ��
				if (drawOption == true)pDC->SetBkColor(RGB(166, 166, 166));
				break;
			case 64:
				logBrush.lbColor = RGB(255, 0, 255);//64��ũ��
				if (drawOption == true)pDC->SetBkColor(RGB(255, 0, 255));
				break;
			case 128:
				logBrush.lbColor = RGB(0, 255, 255);//128�ϴû�
				if (drawOption == true)pDC->SetBkColor(RGB(0, 255, 255));
				break;
			case 256:
				logBrush.lbColor = RGB(128, 0, 128);//256��ȫ��
				if (drawOption == true)pDC->SetBkColor(RGB(128, 0, 128));
				break;
			case 512:
				logBrush.lbColor = RGB(112, 48, 160);//512���̿÷�
				if (drawOption == true)pDC->SetBkColor(RGB(112, 48, 160));
				break;
			case 1024:
				logBrush.lbColor = RGB(255, 255, 255);//1024�Ͼ��
				if (drawOption == true)pDC->SetBkColor(RGB(255, 255, 255));
				break;
			case 2048:
				logBrush.lbColor = RGB(255, 0, 0);//2048������
				if (drawOption == true)pDC->SetBkColor(RGB(255, 0, 0));
				break;
			default:
				logBrush.lbColor = RGB(255, 255, 255);//�׿� ������
				if (drawOption == true)pDC->SetBkColor(RGB(255, 255, 255));
				break;
			}

			if (drawOption == true)//���ڶ����� �޴��� üũ�Ǿ��������� �簢���� ���� �����ش�
			{
				newBrush.CreateBrushIndirect(&logBrush);	//�귯���� ������ ���� �־��ش�
				pOldBrush = pDC->SelectObject(&newBrush);	//pDC�� �־���
			}

			pDC->Rectangle(x * 64, y * 64, x * 64 + 64, y * 64 + 64);//64x64�ȼ��� �簢������
			
			if (num != 0)//0�� �ƴҰ�쿡��  ���ڸ� ���
			{
				pDC->TextOutA(x * 64 + 30, y * 64 + 30, msg);
			}
			
			pDC->SelectObject(pOldBrush);	// ��ĥ
			
			newBrush.DeleteObject();		//CBrush�� ���� �ٲٷ��� �ѹ� ���� �� �ٽ� ����������.
		}
	}
}
void Board::PushKey(int key)
{
	if (isGameOver == false)
	{
		Block_Header->moveNode(Block_Header, key, logNum, moveLog);
		if (moveLog == true)
		{
			logNum++;
		}
	}
	int gameOver = Block_Header->CheckGameOver(Block_Header);//���ӿ������� üũ�ϴ� ���� ���ӿ����� isGameOver�Һ����� true�ιٲ㼭 ���������� �ȵǰ� �Ѵ�.

	switch (gameOver)
	{
	case 1://1�̸� 2048�ϼ�
		AfxMessageBox("2048�ϼ�");
		isGameOver = true;
		break;
	case 2://2�̸� ���ӿ���
		AfxMessageBox("���ӿ���...");
		isGameOver = true;
		break;
	default://0�϶��� ����
		break;
	}
}
void Board::TurnBoard(int direction)//���带 ������ �Լ� 1�� ������ 2�� �������� ���带 ������.
{
	if (isGameOver == false)//���ӿ����� ���̻� ����Ұ�.
	{
		Block_Header->TurnNode(Block_Header, direction, logNum, turnLog);
		if (turnLog == true)
		{
			logNum++;
		}
	}
}

Board::~Board()
{
	//��� ����Ʈ�� ������
	delete Block_Header;
}
