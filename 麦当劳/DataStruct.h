#pragma once
typedef struct {
	char name[60]; //ʳ������
	int time; //����ʱ��
	int capacity; //���洢��
}Food; //����ʳ����
typedef struct {
	char name[60]; //�ײ�����
	int sum; //�ײ���ʳ�����Ŀ
	Food food[10]; //�ײͰ�����ʳ������
}Combo;
typedef struct {
	Food food[110]; //�˵��еĵ�Ʒ
	Combo combo[110];  //�˵��е��ײ�
	int N, M, W1, W2;
}Menu;
void PrintMenu();