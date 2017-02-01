#include "stdafx.h"
#include "Block.h"
#include "fstream"
using namespace std;

Block::Block()
{
	
}

Block* Block::createLinkedList_h() {	//16���� ���Ḯ��Ʈ�� ����� �Լ�, ������ ��� 2���� ���� 2�� �ִ´�.
	
	//��� = L ����� �������� ����,�˻���� ����.//
	Block* L;
	L = (Block*)malloc(sizeof(Block));
	L->m_number = 0;
	L->p_Up = NULL;
	L->p_Down = NULL;
	L->p_Left = NULL;
	L->p_Right = NULL;
	L->m_block = false;

	///////////////////////////////////////
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			addNode(L, x, y);	//4 X 4 ���� ���Ḯ��Ʈ ����
		}
	}
	//��� ��尡 ��������� ������ ��� 2���� ����2�� �ִ´�
	for (int i = 0 ; i < 2 ; i++)
	{
		addRandomNum(L);
	}
	return L;
}

// ����� �������� ��带 �߰�, switch�� Y�� �������� ���缭 ��带 �����Ŵ
void Block::addNode(Block* L, int x, int y)
{
	Block* newNode;
	newNode = (Block*)malloc(sizeof(Block));
	newNode->m_number = 0;
	newNode->m_block = false;
	newNode->p_Up = NULL;
	newNode->p_Down = NULL;
	newNode->p_Left = NULL;
	newNode->p_Right = NULL;

	switch (y){

	case 0:{	//ù��°��
		if (x == 0)return; //����ó��

		//ù��°���� ��� �׷��Ƿ� �ι�°������ ����

		if (x <= 2){
			while (L->p_Right != NULL) L = L->p_Right;
			//�¿�� �����Ŵ ���� ���Ʒ��� ��尡 �����Ƿ� ���߿��Ḯ��Ʈó�� ���������
			L->p_Right = newNode;
			newNode->p_Left = L;
		}
		
		else if (x == 3){
			//��ó�� while������ �ص� �ǰ� �̰�ó�� �밡���ڵ�� ���� ��
			L->p_Right->p_Right->p_Right = newNode;
			newNode->p_Left = L->p_Right->p_Right;
		}
		break;
	}

	case 1: {	//�ι�°���̹Ƿ� ������� �Ʒ��� �����;���

		if (x == 0){
			L->p_Down = newNode;   //��� �Ʒ��� ��带 ����
			newNode->p_Up = L;
		}
		else if (x <= 2){
			
			L = L->p_Down;	//���Ǹ� ���� ����� �Ʒ���
			//L�� �Ʒ��� �����Դٴ°͸� ���� ���� ����
			while (L->p_Right != NULL) L = L->p_Right;

			L->p_Right = newNode;
			newNode->p_Left = L;

			//���� ù��°�ٰ� ������������

			L->p_Up->p_Right->p_Down = newNode;
			newNode->p_Up = L->p_Up->p_Right;
		}

		else if (x == 3) {	//�ι�°���� ��������� ���������� ù��°�� ���������� ������������
			
			L = L->p_Down;	//���Ǹ� ���� ����� �Ʒ���
			while (L->p_Right != NULL) L = L->p_Right;

			L->p_Right = newNode; //3��°���� ����
			newNode->p_Left = L;

			L->p_Up->p_Right->p_Down = newNode; //ù��°�� ���������� ����
			newNode->p_Up = L->p_Up->p_Right;
		}
		break;
	}

	case 2: { //����°��
		if (x == 0){
			L->p_Down->p_Down = newNode;
			newNode->p_Up = L->p_Down;
		}
		
		else if (x <= 2){
			L = L->p_Down->p_Down;	//���Ǹ� ���� ����� ����°�ٷ�
			while (L->p_Right != NULL) L = L->p_Right;

			L->p_Right = newNode;
			newNode->p_Left = L;

			//�ι�°�ٰ� ����
			L->p_Up->p_Right->p_Down = newNode;
			newNode->p_Up = L->p_Up->p_Right;
		}
		
		else if (x == 3){
			L = L->p_Down->p_Down;	//���Ǹ� ���� ����� ����°�ٷ�
			while (L->p_Right != NULL) L = L->p_Right;

			L->p_Right = newNode;
			newNode->p_Left = L;

			L->p_Up->p_Right->p_Down = newNode; //�ι�°�� ���������� ����
			newNode->p_Up = L->p_Up->p_Right;
		}
		break;
	}
	case 3: {//��������
		if (x == 0) {
			L->p_Down->p_Down->p_Down = newNode;
			newNode->p_Up = L->p_Down->p_Down;
		}
		else if (x <= 2) {
			L = L->p_Down->p_Down->p_Down;	//���Ǹ� ���� ����� �׹�°�ٷ�
			while (L->p_Right != NULL) L = L->p_Right;

			L->p_Right = newNode;
			newNode->p_Left = L;

			L->p_Up->p_Right->p_Down = newNode;
			newNode->p_Up = L->p_Up->p_Right;
		}
		else if (x == 3) {
			L = L->p_Down->p_Down->p_Down;	//���Ǹ� ���� ����� �׹�°�ٷ�

			while (L->p_Right != NULL) L = L->p_Right;

			L->p_Right = newNode;
			newNode->p_Left = L;

			L->p_Up->p_Right->p_Down = newNode; //����°�� ���������� ����
			newNode->p_Up = L->p_Up->p_Right;
		}
		break;
	}
	default:
		break;
	}
	//case 1: case 2: case 3: ~~~ break;
	//�̷��� 3���� �Ѳ����� ���� �� x���� �������� L�� ��ġ�� �ٲ��൵ �ȴ�.
}

int Block::createBoard(Block* L,int x,int y)//�������� �����. x,y�����̿��� ����� ���ڸ� ��ȯ��Ŵ
{
	int xnum = x, ynum = y; //x��,y�����޾� ��带 Ž���ϴ� �Լ�

	while (1 <= xnum) // x���� 1�̻��϶� �����ʳ��� �ű� 0�̸� �׳� ����
	{
		L = L->p_Right;
		xnum--;	//1�� ���ҽ��Ѽ� 0�̵ɶ�����
	}
	
	while (1 <= ynum) // y���� 1�̻��϶� �Ʒ��ʳ��� �ű� 0�̸� �׳� ����
	{
		L = L->p_Down;
		ynum--;	//���� ����
	}

	//���� ������� ���� ����� ���ڸ� ��ȯ

	return L->m_number;
}


void Block::moveNode(Block* L, int key, int logNum, bool log)
{

	CString msg;

	Block* tempNode[4];//�� ������ 4���� ��带 ������ �� ������ �������� m_number�� �����س�����.

	int movecount = 0;//������ Ƚ���� ������ Ű�� ���������� �ƹ��͵� ������ �ʾ���������(EX = ���ʺ��� ����4���� ������ ������ ���ڰ� �������) ���ڸ� �����������ϰ� �Ѵ�. �������� �ִ� ��� +�����ش�.

	int comparecount = 3; //��Ƚ�� = (ù��°,�ι�°)��� (1��)- > ((����°,�ι�°),ù��°) (2��) -> (((�׹�°,����°),�ι�°),ù��°) (3��)

	switch (key){
	case VK_DOWN://�Ʒ��� Ű�� �������� �Ʒ��ʺ� 4���� �������� �Ʒ��� ���, ���������� ����Ұ�� ������ ���ڰ� 2 2 2 4 �϶� 0 2 4 4 �̷��� ������ 0 4 2 4 �̷��� �ǹ���

		tempNode[0] = L->p_Down->p_Down->p_Down;
		tempNode[1] = L->p_Down->p_Down->p_Down->p_Right;
		tempNode[2] = L->p_Down->p_Down->p_Down->p_Right->p_Right;
		tempNode[3] = L->p_Down->p_Down->p_Down->p_Right->p_Right->p_Right;

		for (int i = 0; i < 4; i++)
		{
			while (comparecount != 0)
			{
				if (comparecount == 3) // ù��° ���� �ι�° ��� ��
				{
					if (tempNode[i]->p_Up->m_number != 0) //���ڰ� 0���� �˻�, 0�̸� ����� �ʿ䰡 ����.
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Up->m_number) //�Ȱ������ڸ� �ŵ�������Ű�� ���ڸ� �Ʒ��� ����
						{
							tempNode[i]->m_number *= 2;
							tempNode[i]->p_Up->m_number = 0;
							tempNode[i]->m_block = true;//���̻� ������ ���ϰ� ��忡 ������Ǵ�.
							movecount++;
						}
						else if(tempNode[i]->m_number == 0)
						{//���� 0�̾ƴ����� �Ʒ��� 0�ϰ�� �������ڸ� �Ʒ��� ������.
							tempNode[i]->m_number = tempNode[i]->p_Up->m_number;
							tempNode[i]->p_Up->m_number = 0;
							movecount++;
						}
						//�Ѵ� �ٸ���� (EX 2, 4) �ƹ��͵� �������� 
					}
				}

				//����°, �ι�°�� ���� �� �� ����� ù��°���� ��
				else if (comparecount == 2)
				{
					if (tempNode[i]->p_Up->p_Up->m_number != 0)//����°�� �ι�°�� ���Ѵ�.
					{
						if (tempNode[i]->p_Up->p_Up->m_number == tempNode[i]->p_Up->m_number)//���ڰ� ������ �ŵ�����
						{
							tempNode[i]->p_Up->m_number *= 2;
							tempNode[i]->p_Up->p_Up->m_number = 0;
							tempNode[i]->p_Up->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Up->m_number == 0)
						{
							tempNode[i]->p_Up->m_number = tempNode[i]->p_Up->p_Up->m_number;
							tempNode[i]->p_Up->p_Up->m_number = 0;
							movecount++;
						}
					}

					//�ι�°�� ù��°�� ���Ѵ�.
					if (tempNode[i]->p_Up->m_number != 0) //���ڰ� 0���� �˻�
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Up->m_number)
						{
							if (tempNode[i]->p_Up->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Up->m_number = 0;
								tempNode[i]->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//���� 0�̾ƴ����� �Ʒ��� 0�ϰ�� �������ڸ� �Ʒ��� ������.
							tempNode[i]->m_number = tempNode[i]->p_Up->m_number;
							tempNode[i]->p_Up->m_number = 0;
							movecount++;
						}
					}
				}

				//�׹�°,����°�� ��� �� �� ������� �ι�°��, �� �װ���� ù��°�� ���
				else if (comparecount == 1)
				{
					//�׹�°�� ����°�� ���
					if (tempNode[i]->p_Up->p_Up->p_Up->m_number != 0)
					{
						if (tempNode[i]->p_Up->p_Up->p_Up->m_number == tempNode[i]->p_Up->p_Up->m_number)
						{
							tempNode[i]->p_Up->p_Up->m_number *= 2;
							tempNode[i]->p_Up->p_Up->p_Up->m_number = 0;
							tempNode[i]->p_Up->p_Up->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Up->p_Up->m_number == 0)
						{
							tempNode[i]->p_Up->p_Up->m_number = tempNode[i]->p_Up->p_Up->p_Up->m_number;
							tempNode[i]->p_Up->p_Up->p_Up->m_number = 0;
							movecount++;
						}
					}
					//����°�� �ι�°�� ����Ѵ�.
					if (tempNode[i]->p_Up->p_Up->m_number != 0)
					{
						if (tempNode[i]->p_Up->p_Up->m_number == tempNode[i]->p_Up->m_number)
						{
							if (tempNode[i]->p_Up->p_Up->m_block == false && tempNode[i]->p_Up->m_block == false)
							{
								tempNode[i]->p_Up->m_number *= 2;
								tempNode[i]->p_Up->p_Up->m_number = 0;
								tempNode[i]->p_Up->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->p_Up->m_number == 0)
						{
							tempNode[i]->p_Up->m_number = tempNode[i]->p_Up->p_Up->m_number;
							tempNode[i]->p_Up->p_Up->m_number = 0;
							movecount++;
						}
					}

					//�ι�°�� ù��°�� ����Ѵ�.
					if (tempNode[i]->p_Up->m_number != 0) //���ڰ� 0���� �˻�
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Up->m_number)
						{
							if ((tempNode[i]->p_Up->m_block == false) && (tempNode[i]->m_block == false))
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Up->m_number = 0;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//���� 0�̾ƴ����� �Ʒ��� 0�ϰ�� �������ڸ� �Ʒ��� ������.
							tempNode[i]->m_number = tempNode[i]->p_Up->m_number;
							tempNode[i]->p_Up->m_number = 0;
							movecount++;
						}
					}
				}
				comparecount--;
			}
			comparecount = 3;//���� �����(�����ʳ��)����� ���� �ٽ� 3���� �ٲ��ش�.
		}

		//�ŵ������� ��ġ�� �Ʒ��� �������� ���� ������ ��忡 ���� 2�� ����ִ´�.
		if (movecount != 0)
		{
			addRandomNum(L);
		}
		break;

	case VK_LEFT://���� Ű�� �������� ���ʺ� 4���� �������� �������� ���
		tempNode[0] = L;
		tempNode[1] = L->p_Down;
		tempNode[2] = L->p_Down->p_Down;
		tempNode[3] = L->p_Down->p_Down->p_Down;

		
		for (int i = 0; i < 4; i++)
		{
			while (comparecount != 0)
			{
				if (comparecount == 3) // ù��° ���� �ι�° ��� ��
				{
					if (tempNode[i]->p_Right->m_number != 0) //���ڰ� 0���� �˻�, 0�̸� ����� �ʿ䰡 ����.
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Right->m_number) //�Ȱ������ڸ� �ŵ�������Ű�� ���ڸ� �Ʒ��� ����
						{
							tempNode[i]->m_number *= 2;
							tempNode[i]->p_Right->m_number = 0;
							tempNode[i]->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->m_number == 0)
						{//���� 0�̾ƴ����� �Ʒ��� 0�ϰ�� �������ڸ� �Ʒ��� ������.
							tempNode[i]->m_number = tempNode[i]->p_Right->m_number;
							tempNode[i]->p_Right->m_number = 0;
							movecount++;
						}
						//�Ѵ� �ٸ���� (EX 2, 4) �ƹ��͵� �������� 
					}
				}

				//����°, �ι�°�� ���� �� �� ����� ù��°���� ��
				else if (comparecount == 2)
				{
					if (tempNode[i]->p_Right->p_Right->m_number != 0)//����°�� �ι�°�� ���Ѵ�.
					{
						if (tempNode[i]->p_Right->p_Right->m_number == tempNode[i]->p_Right->m_number)//���ڰ� ������ �ŵ�����
						{
							tempNode[i]->p_Right->m_number *= 2;
							tempNode[i]->p_Right->p_Right->m_number = 0;
							tempNode[i]->p_Right->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Right->m_number == 0)
						{
							tempNode[i]->p_Right->m_number = tempNode[i]->p_Right->p_Right->m_number;
							tempNode[i]->p_Right->p_Right->m_number = 0;
							movecount++;
						}
					}

					//�ι�°�� ù��°�� ���Ѵ�.
					if (tempNode[i]->p_Right->m_number != 0) //���ڰ� 0���� �˻�
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Right->m_number)
						{
							if (tempNode[i]->p_Right->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Right->m_number = 0;
								tempNode[i]->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//���� 0�̾ƴ����� �Ʒ��� 0�ϰ�� �������ڸ� �Ʒ��� ������.
							tempNode[i]->m_number = tempNode[i]->p_Right->m_number;
							tempNode[i]->p_Right->m_number = 0;
							movecount++;
						}
					}
				}

				//�׹�°,����°�� ��� �� �� ������� �ι�°��, �� �װ���� ù��°�� ���
				else if (comparecount == 1)
				{
					//�׹�°�� ����°�� ���
					if (tempNode[i]->p_Right->p_Right->p_Right->m_number != 0)
					{
						if (tempNode[i]->p_Right->p_Right->p_Right->m_number == tempNode[i]->p_Right->p_Right->m_number)
						{
							tempNode[i]->p_Right->p_Right->m_number *= 2;
							tempNode[i]->p_Right->p_Right->p_Right->m_number = 0;
							tempNode[i]->p_Right->p_Right->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Right->p_Right->m_number == 0)
						{
							tempNode[i]->p_Right->p_Right->m_number = tempNode[i]->p_Right->p_Right->p_Right->m_number;
							tempNode[i]->p_Right->p_Right->p_Right->m_number = 0;
							movecount++;
						}
					}
					if (tempNode[i]->p_Right->p_Right->m_number != 0)//����°�� �ι�°�� ����Ѵ�.
					{
						if (tempNode[i]->p_Right->p_Right->m_number == tempNode[i]->p_Right->m_number)
						{
							if (tempNode[i]->p_Right->p_Right == false && tempNode[i]->p_Right->m_block == false)
							{
								tempNode[i]->p_Right->m_number *= 2;
								tempNode[i]->p_Right->p_Right->m_number = 0;
								tempNode[i]->p_Right->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->p_Right->m_number == 0)
						{
							tempNode[i]->p_Right->m_number = tempNode[i]->p_Right->p_Right->m_number;
							tempNode[i]->p_Right->p_Right->m_number = 0;
							movecount++;
						}
					}

					//�ι�°�� ù��°�� ����Ѵ�.
					if (tempNode[i]->p_Right->m_number != 0) //���ڰ� 0���� �˻�
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Right->m_number)
						{
							if (tempNode[i]->p_Right->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Right->m_number = 0;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//���� 0�̾ƴ����� �Ʒ��� 0�ϰ�� �������ڸ� �Ʒ��� ������.
							tempNode[i]->m_number = tempNode[i]->p_Right->m_number;
							tempNode[i]->p_Right->m_number = 0;
							movecount++;
						}
					}
				}
				comparecount--;
			}
			comparecount = 3;//���� �����(�����ʳ��)����� ���� �ٽ� 3���� �ٲ��ش�.
		}
		
		//�ŵ������� ��ġ�� �Ʒ��� �������� ���� ������ ��忡 ���� 2�� ����ִ´�.
		if (movecount != 0)
		{
			addRandomNum(L);
		}
		break;

	case VK_RIGHT:
		//�������� �������� ����Ѵ�.
		tempNode[0] = L->p_Right->p_Right->p_Right;
		tempNode[1] = L->p_Right->p_Right->p_Right->p_Down;
		tempNode[2] = L->p_Right->p_Right->p_Right->p_Down->p_Down;
		tempNode[3] = L->p_Right->p_Right->p_Right->p_Down->p_Down->p_Down;

		for (int i = 0; i < 4; i++)
		{
			while (comparecount != 0)
			{
				if (comparecount == 3) // ù��° ���� �ι�° ��� ��
				{
					if (tempNode[i]->p_Left->m_number != 0) //���ڰ� 0���� �˻�, 0�̸� ����� �ʿ䰡 ����.
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Left->m_number) //�Ȱ������ڸ� �ŵ�������Ű�� ���ڸ� �Ʒ��� ����
						{
							tempNode[i]->m_number *= 2;
							tempNode[i]->p_Left->m_number = 0;
							tempNode[i]->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->m_number == 0)
						{//���� 0�̾ƴ����� �Ʒ��� 0�ϰ�� �������ڸ� �Ʒ��� ������.
							tempNode[i]->m_number = tempNode[i]->p_Left->m_number;
							tempNode[i]->p_Left->m_number = 0;
							movecount++;
						}
						//�Ѵ� �ٸ���� (EX 2, 4) �ƹ��͵� �������� 
					}
				}

				//����°, �ι�°�� ���� �� �� ����� ù��°���� ��
				else if (comparecount == 2)
				{
					if (tempNode[i]->p_Left->p_Left->m_number != 0)//����°�� �ι�°�� ���Ѵ�.
					{
						if (tempNode[i]->p_Left->p_Left->m_number == tempNode[i]->p_Left->m_number)//���ڰ� ������ �ŵ�����
						{
							tempNode[i]->p_Left->m_number *= 2;
							tempNode[i]->p_Left->p_Left->m_number = 0;
							tempNode[i]->p_Left->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Left->m_number == 0)
						{
							tempNode[i]->p_Left->m_number = tempNode[i]->p_Left->p_Left->m_number;
							tempNode[i]->p_Left->p_Left->m_number = 0;
							movecount++;
						}
					}

					//�ι�°�� ù��°�� ���Ѵ�.
					if (tempNode[i]->p_Left->m_number != 0) //���ڰ� 0���� �˻�
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Left->m_number)
						{
							if (tempNode[i]->p_Left->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Left->m_number = 0;
								tempNode[i]->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//���� 0�̾ƴ����� �Ʒ��� 0�ϰ�� �������ڸ� �Ʒ��� ������.
							tempNode[i]->m_number = tempNode[i]->p_Left->m_number;
							tempNode[i]->p_Left->m_number = 0;
							movecount++;
						}
					}
				}

				//�׹�°,����°�� ��� �� �� ������� �ι�°��, �� �װ���� ù��°�� ���
				else if (comparecount == 1)
				{
					//�׹�°�� ����°�� ���
					if (tempNode[i]->p_Left->p_Left->p_Left->m_number != 0)
					{
						if (tempNode[i]->p_Left->p_Left->p_Left->m_number == tempNode[i]->p_Left->p_Left->m_number)
						{
							tempNode[i]->p_Left->p_Left->m_number *= 2;
							tempNode[i]->p_Left->p_Left->p_Left->m_number = 0;
							tempNode[i]->p_Left->p_Left->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Left->p_Left->m_number == 0)
						{
							tempNode[i]->p_Left->p_Left->m_number = tempNode[i]->p_Left->p_Left->p_Left->m_number;
							tempNode[i]->p_Left->p_Left->p_Left->m_number = 0;
							movecount++;
						}
					}
					if (tempNode[i]->p_Left->p_Left->m_number != 0)//����°�� �ι�°�� ����Ѵ�.
					{
						if (tempNode[i]->p_Left->p_Left->m_number == tempNode[i]->p_Left->m_number)
						{
							if (tempNode[i]->p_Left->p_Left->m_block == false && tempNode[i]->p_Left->m_block == false)
							{
								tempNode[i]->p_Left->m_number *= 2;
								tempNode[i]->p_Left->p_Left->m_number = 0;
								tempNode[i]->p_Left->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->p_Left->m_number == 0)
						{
							tempNode[i]->p_Left->m_number = tempNode[i]->p_Left->p_Left->m_number;
							tempNode[i]->p_Left->p_Left->m_number = 0;
							movecount++;
						}
					}

					//�ι�°�� ù��°�� ����Ѵ�.
					if (tempNode[i]->p_Left->m_number != 0) //���ڰ� 0���� �˻�
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Left->m_number)
						{
							if (tempNode[i]->p_Left->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Left->m_number = 0;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//���� 0�̾ƴ����� �Ʒ��� 0�ϰ�� �������ڸ� �Ʒ��� ������.
							tempNode[i]->m_number = tempNode[i]->p_Left->m_number;
							tempNode[i]->p_Left->m_number = 0;
							movecount++;
						}
					}
				}
				comparecount--;
			}
			comparecount = 3;//���� �����(�����ʳ��)����� ���� �ٽ� 3���� �ٲ��ش�.
		}

		//�ŵ������� ��ġ�� �Ʒ��� �������� ���� ������ ��忡 ���� 2�� ����ִ´�.
		if (movecount != 0)
		{
			addRandomNum(L);
		}
		break;
		
	case VK_UP://������ �������� ���
		tempNode[0] = L;
		tempNode[1] = L->p_Right;
		tempNode[2] = L->p_Right->p_Right;
		tempNode[3] = L->p_Right->p_Right->p_Right;

		for (int i = 0; i < 4; i++)
		{
			while (comparecount != 0)
			{
				if (comparecount == 3) // ù��° ���� �ι�° ��� ��
				{
					if (tempNode[i]->p_Down->m_number != 0) //���ڰ� 0���� �˻�, 0�̸� ����� �ʿ䰡 ����.
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Down->m_number) //�Ȱ������ڸ� �ŵ�������Ű�� ���ڸ� �Ʒ��� ����
						{
							tempNode[i]->m_number *= 2;
							tempNode[i]->p_Down->m_number = 0;
							tempNode[i]->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->m_number == 0)
						{//���� 0�̾ƴ����� �Ʒ��� 0�ϰ�� �������ڸ� �Ʒ��� ������.
							tempNode[i]->m_number = tempNode[i]->p_Down->m_number;
							tempNode[i]->p_Down->m_number = 0;
							movecount++;
						}
						//�Ѵ� �ٸ���� (EX 2, 4) �ƹ��͵� �������� 
					}
				}

				//����°, �ι�°�� ���� �� �� ����� ù��°���� ��
				else if (comparecount == 2)
				{
					if (tempNode[i]->p_Down->p_Down->m_number != 0)//����°�� �ι�°�� ���Ѵ�.
					{
						if (tempNode[i]->p_Down->p_Down->m_number == tempNode[i]->p_Down->m_number)//���ڰ� ������ �ŵ�����
						{
							tempNode[i]->p_Down->m_number *= 2;
							tempNode[i]->p_Down->p_Down->m_number = 0;
							tempNode[i]->p_Down->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Down->m_number == 0)
						{
							tempNode[i]->p_Down->m_number = tempNode[i]->p_Down->p_Down->m_number;
							tempNode[i]->p_Down->p_Down->m_number = 0;
							movecount++;
						}
					}

					//�ι�°�� ù��°�� ���Ѵ�.
					if (tempNode[i]->p_Down->m_number != 0) //���ڰ� 0���� �˻�
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Down->m_number)
						{
							if (tempNode[i]->p_Down->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Down->m_number = 0;
								tempNode[i]->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//���� 0�̾ƴ����� �Ʒ��� 0�ϰ�� �������ڸ� �Ʒ��� ������.
							tempNode[i]->m_number = tempNode[i]->p_Down->m_number;
							tempNode[i]->p_Down->m_number = 0;
							movecount++;
						}
					}
				}

				//�׹�°,����°�� ��� �� �� ������� �ι�°��, �� �װ���� ù��°�� ���
				else if (comparecount == 1)
				{
					//�׹�°�� ����°�� ���
					if (tempNode[i]->p_Down->p_Down->p_Down->m_number != 0)
					{
						if (tempNode[i]->p_Down->p_Down->p_Down->m_number == tempNode[i]->p_Down->p_Down->m_number)
						{
							tempNode[i]->p_Down->p_Down->m_number *= 2;
							tempNode[i]->p_Down->p_Down->p_Down->m_number = 0;
							tempNode[i]->p_Down->p_Down->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Down->p_Down->m_number == 0)
						{
							tempNode[i]->p_Down->p_Down->m_number = tempNode[i]->p_Down->p_Down->p_Down->m_number;
							tempNode[i]->p_Down->p_Down->p_Down->m_number = 0;
							movecount++;
						}
					}
					if (tempNode[i]->p_Down->p_Down->m_number != 0)//����°�� �ι�°�� ����Ѵ�.
					{
						if (tempNode[i]->p_Down->p_Down->m_number == tempNode[i]->p_Down->m_number)
						{
							if (tempNode[i]->p_Down->p_Down->m_block == false && tempNode[i]->p_Down->m_block == false)
							{
								tempNode[i]->p_Down->m_number *= 2;
								tempNode[i]->p_Down->p_Down->m_number = 0;
								tempNode[i]->p_Down->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->p_Down->m_number == 0)
						{
							tempNode[i]->p_Down->m_number = tempNode[i]->p_Down->p_Down->m_number;
							tempNode[i]->p_Down->p_Down->m_number = 0;
							movecount++;
						}
					}

					//�ι�°�� ù��°�� ����Ѵ�.
					if (tempNode[i]->p_Down->m_number != 0) //���ڰ� 0���� �˻�
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Down->m_number)
						{
							if (tempNode[i]->p_Down->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Down->m_number = 0;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//���� 0�̾ƴ����� �Ʒ��� 0�ϰ�� �������ڸ� �Ʒ��� ������.
							tempNode[i]->m_number = tempNode[i]->p_Down->m_number;
							tempNode[i]->p_Down->m_number = 0;
							movecount++;
						}
					}
				}
				comparecount--;
			}
			comparecount = 3;//���� �����(�����ʳ��)����� ���� �ٽ� 3���� �ٲ��ش�.
		}

		//�ŵ������� ��ġ�� �Ʒ��� �������� ���� ������ ��忡 ���� 2�� ����ִ´�.
		if (movecount != 0)
		{
			addRandomNum(L);
		}
		break;
	}

	if (log == true)//�α׸޴��� üũ�Ǿ������� �α������� ������ش�.
	{
		Block* storeNode = L;
		ofstream fcout;
		
		fcout.open("log.txt", ios::ate | ios::app);

		if (key == VK_LEFT)
		{
			fcout << logNum << ". KEY_LEFT\n[result]\n";
		}
		else if (key == VK_RIGHT)
		{
			fcout << logNum << ". KEY_RIFHT\n[result]\n";
		}
		else if (key == VK_DOWN)
		{
			fcout << logNum << ". KEY_DOWN\n[result]\n";
		}
		else if (key == VK_UP)
		{
			fcout << logNum << ". KEY_UP\n[result]\n";
		}

		for (int i = 0; i < 4; i++)
		{
			while (storeNode->p_Right != NULL)
			{
				if (storeNode->m_number == 0)	//���ڰ� 0�̸� ���鸸 �ִ´�.
				{
					fcout << "\t";
				}
				else
				{
					fcout << storeNode->m_number << "\t";
				}

				storeNode = storeNode->p_Right;	//�Է��� �Ϸ��ϸ� �������� ����.

				if (storeNode->p_Right == NULL)	//���� ������ ����� ���ڸ� �Է��ϰ� ��ĭ �Ʒ��� �����ش�
				{
					if (storeNode->m_number == 0)
					{
						fcout << "\t\n";
					}
					else
					{
						fcout << storeNode->m_number << "\t\n";
					}
				}
			}
			storeNode = storeNode->p_Left->p_Left->p_Left;
			storeNode = storeNode->p_Down;
		}
		fcout.close();
	}
}

void Block::addRandomNum(Block* L)//�����Ѱ��� 2�� �Է��Ѵ�.
{
	//x,y�� �̿��� ������ ��带 �����Ѵ�.
	int ranx = 1;
	int rany = 1;
	srand((unsigned int)time(NULL));

	/////////////////////////////////////////////////
	Block* tempNode = L;
	//x��ŭ �����ʳ���,y��ŭ �Ʒ��ʳ��� �̵��Ѵ�.
	
	while (ranx != 0 || rany != 0) //   (ex) x == 0 y == 1�̸� x�� ����, L->p_Down�� �����Ѵ�.
	{
		ranx = rand() % 4;
		rany = rand() % 4;

		while (ranx != 0) {
			tempNode = tempNode->p_Right;
			ranx--;
		}
		while (rany != 0) {
			tempNode = tempNode->p_Down;
			rany--;
		}

		if (tempNode->m_number != 0)//���� ������ ��忡 ���ڰ� ��������� �ٽ� �����Ѱ����־� ���ڰ����� ��尡 ���ö����� ����Ѵ�.
		{
			ranx = 1;
			tempNode = L;	//���� �ٽ� ��������� �������´�.
		}
	}
	tempNode->m_number = 2;	//����� �Ϸ�Ǹ� ������ ���m_number�� 2�� �ִ´�
}

int Block::CheckGameOver(Block* L)//2048�� �ϼ��ϰų� ����忡 ���ڰ� ������ 2048�� ������� ���ӿ��� �޼����� ��� �� ���α׷��� �����Ų��.
{
	int numcount = 0; //�� ����� m_number�� ���ڰ� �ִ��� �˻��ϴ� ����, 16�̵Ǹ� ��������, ������ �����ϼ� �ִ� ����� ���� �������� ��� ����
	int gameover = 0; //0�̸� ��� ����, 1�̸� 2048�ϼ�, 2����ڰ� ������ ���ӿ���
	Block* tempNode = L;

	//�˻��ϴ±迡 ��忡m_block�� ���� false�� �ʱ�ȭ��Ų��.

	for (int y = 0 ; y < 4 ; y++)
	{
		if (y == 0)//ù��° ��
		{
			while (tempNode!=NULL)
			{
				tempNode->m_block = false;
				if (tempNode->m_number == 2048)//m_number�� 2048���� �˻�
				{
					gameover = 1;
					return gameover;	//2048�̸� �ٷ� ���ӿ�����ȣ�� ����
				}
				if (tempNode->m_number != 0)//���� 16���� ��á���� numcount�� Ȯ���Ѵ�.
				{
					numcount += 1;
				}
				tempNode = tempNode->p_Right;
			}
			tempNode = L; //Ȯ�������� �ٽ� ����� ���ư���.
		}
		else if (y == 1)
		{
			tempNode = tempNode->p_Down;
			while (tempNode != NULL)
			{
				tempNode->m_block = false;
				if (tempNode->m_number == 2048)
				{
					gameover = 1;
					return gameover;
				}
				if (tempNode->m_number != 0)
				{
					numcount += 1;
				}
				tempNode = tempNode->p_Right;
			}
			tempNode = L;
		}
		else if (y == 2)
		{
			tempNode = tempNode->p_Down->p_Down;
			while (tempNode != NULL)
			{
				tempNode->m_block = false;
				if (tempNode->m_number == 2048)
				{
					gameover = 1;
					return gameover;
				}
				if (tempNode->m_number != 0)
				{
					numcount += 1;
				}
				tempNode = tempNode->p_Right;
			}
			tempNode = L;
		}
		else if (y == 3)
		{
			tempNode = tempNode->p_Down->p_Down->p_Down;
			while (tempNode != NULL)
			{
				tempNode->m_block = false;
				if (tempNode->m_number == 2048)
				{
					gameover = 1;
					return gameover;
				}
				if (tempNode->m_number != 0)
				{
					numcount += 1;
				}
				tempNode = tempNode->p_Right;
			}
			tempNode = L;
		}
	}

	Block* lastCheck = L;
	int checknum = 0;

	if (numcount == 16)//��� ��忡 ���ڰ� ��������� ���� �̵������� ��尡 �������(EX-2,2�� �پ��������)���ӿ����� �����ʴ´�.
	{
		for (int y = 0 ; y < 4 ; y++)//����,�������� ������ ������ �ִ��� �˻�
		{
			while (lastCheck != NULL)
			{
				if (lastCheck->m_number == lastCheck->p_Right->m_number)
				{
					checknum++;
				}
				if (lastCheck->p_Right->p_Right != NULL)//3���� �˻��Ѵ�. 12 , 23,  34 ���� 4��°������ �� �ʿ䰡 ����.
				{
					lastCheck = lastCheck->p_Right;
				}
				else
				{
					break;
				}
			}
			lastCheck = lastCheck->p_Left->p_Left->p_Down;//�ٽ� ���󺹱��ϰ� ��ĭ �Ʒ��� ������
		}
		
		lastCheck = L;

		for (int x = 0 ; x < 4 ; x++)//���� ����,�Ʒ��� ���ڸ� �˻��Ѵ�.
		{
			while (lastCheck != NULL)
			{
				if (lastCheck->m_number == lastCheck->p_Down->m_number)
				{
					checknum++;
				}
				if (lastCheck->p_Down->p_Down != NULL)
				{
					lastCheck = lastCheck->p_Down;
				}
				else
				{
					break;
				}
			}
			lastCheck = lastCheck->p_Up->p_Up->p_Right;
		}

		if (checknum == 0)//checknum�� �ƹ��͵� ������ �ʾ������(��� �̿��� ����� ���ڰ� �ٸ����)���ӿ������ȴ�.
		{
			gameover = 2;
		}
	}
	return gameover;
}

void Block::TurnNode(Block* L, int direction, int logNum, bool log)
{
	//���������� ���� �� case 1:
	/*1 2 3 4				13 9 5 1
	5 6 7 8		->			14 10 6 2
	9 10 11 12				15 11 7 3
	13 14 15 16				16 12 8 4
	*///������ �ݴ�� case2:
	Block* tempNode[4];

	int tempcount = 0;	//tempnum�� �������ϸ� +1������ ��� ���ڸ� �����Ű���Ѵ�.
	int tempnum[16];	//���ڸ� ��� ������ ���ġ�Ѵ�.

	//��带 �����ֱ����� �ӽ������带 �����. 
	tempNode[0] = L;
	tempNode[1] = L->p_Down;
	tempNode[2] = L->p_Down->p_Down;
	tempNode[3] = L->p_Down->p_Down->p_Down;

	switch (direction)
	{
	case 1://���������� ������.

		for (int i = 0 ;i < 4 ;i++)
		{
			while (tempNode[i]->p_Right != NULL)//���ʿ��� ���������� ���鼭 ���ڸ� tempnum�������Ѵ�
			{
				tempnum[tempcount] = tempNode[i]->m_number;
				tempcount++;
				tempNode[i] = tempNode[i]->p_Right;
				if (tempNode[i]->p_Right == NULL)//������ ���� while�� ���ǿ� ���� ������ �ȵǹǷ� ���� ������ ����� �ش�.
				{
					tempnum[tempcount] = tempNode[i]->m_number;
					tempcount++;
				}
			}
		}

		//��� ��带 �����ʺ��� ���ʷ� �ٽ� �������Ѵ�.
		tempNode[0] = L->p_Right->p_Right->p_Right;
		tempNode[1] = L->p_Right->p_Right;
		tempNode[2] = L->p_Right;
		tempNode[3] = L;
		//tempnum �迭�� �����ϱ����� tempcount�� �ٽ� 0���� �ٲ۴�.
		tempcount = 0;
		//���� tempnum�� ����� ���ڸ� �ٽ� ���ġ�Ѵ�.
		for (int i = 0 ; i < 4 ; i++)
		{
			while (tempNode[i]->p_Down != NULL)
			{
				tempNode[i]->m_number = tempnum[tempcount];
				tempcount++;
				tempNode[i] = tempNode[i]->p_Down;
				if (tempNode[i]->p_Down == NULL)//���� ���������� ���� ������ ������ش�.
				{
					tempNode[i]->m_number = tempnum[tempcount];
					tempcount++;
				}
			}
		}
		break;

	case 2://�������� ������.
		/*		1 2 3 4		->		4 8 12 16
				5 6 7 8				3 7 11 15
				9 10 11 12			2 6 10 14
		*///	13 14 15 16			1 5 9 13

		//���ڸ� �̴°��� ����.
		for (int i = 0; i < 4; i++)
		{
			while (tempNode[i]->p_Right != NULL)//���ʿ��� ���������� ���鼭 ���ڸ� tempnum�������Ѵ�
			{
				tempnum[tempcount] = tempNode[i]->m_number;
				tempcount++;
				tempNode[i] = tempNode[i]->p_Right;
				if (tempNode[i]->p_Right == NULL)//������ ���� while�� ���ǿ� ���� ������ �ȵǹǷ� ���� ������ ����� �ش�.
				{
					tempnum[tempcount] = tempNode[i]->m_number;
					tempcount++;
				}
			}
		}

		//��� ��带 �Ʒ��ʺ��� ���ʷ� �ٽ� �������Ѵ�.
		tempNode[0] = L->p_Down->p_Down->p_Down;
		tempNode[1] = L->p_Down->p_Down->p_Down->p_Right;
		tempNode[2] = L->p_Down->p_Down->p_Down->p_Right->p_Right;
		tempNode[3] = L->p_Down->p_Down->p_Down->p_Right->p_Right->p_Right;

		//tempnum �迭�� �����ϱ����� tempcount�� �ٽ� 0���� �ٲ۴�.
		tempcount = 0;

		//���� tempnum�� ����� ���ڸ� �ٽ� ���ġ�Ѵ�.
		for (int i = 0; i < 4; i++)
		{
			while (tempNode[i]->p_Up != NULL)
			{
				tempNode[i]->m_number = tempnum[tempcount];
				tempcount++;
				tempNode[i] = tempNode[i]->p_Up;
				if (tempNode[i]->p_Up == NULL)//���� ���������� ���� ������ ������ش�.
				{
					tempNode[i]->m_number = tempnum[tempcount];
					tempcount++;
				}
			}
		}
		break;

	default:

		break;
	}

	if (log == true)//ȸ���α׸޴��� üũ�Ǿ������� log���Ͽ� ��������ش�
	{
		Block* storeNode = L;
		ofstream f;
		
		f.open("log.txt",ios::ate | ios::app);

		if (direction == 1) //������
		{
			f << logNum << ". Mouse_Left_to_Right\n[result]\n";
		}
		else if (direction == 2)//����
		{
			f << logNum << ". Mouse_Right_to_Left\n[result]\n";
		}

		for (int i = 0; i < 4; i++)//�����Է��� Ű�����Է¶��� ����.
		{
			while (storeNode->p_Right != NULL)
			{
				if (storeNode->m_number == 0)	//���ڰ� 0�̸� ���鸸 �ִ´�.
				{
					f << "\t";
				}
				else
				{
					f << storeNode->m_number << "\t";
				}

				storeNode = storeNode->p_Right;	//�Է��� �Ϸ��ϸ� �������� ����.

				if (storeNode->p_Right == NULL)	//���� ������ ����� ���ڸ� �Է��ϰ� ��ĭ �Ʒ��� �����ش�
				{
					if (storeNode->m_number == 0)
					{
						f << "\t\n";
					}
					else
					{
						f << storeNode->m_number << "\t\n";
					}
				}
			}
			storeNode = storeNode->p_Left->p_Left->p_Left;
			storeNode = storeNode->p_Down;
		}

		f.close();
	}
}

Block::~Block()
{

}