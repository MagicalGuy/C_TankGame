#include"stdio.h"
#include"stdlib.h"
#include"Utils.h"
#include"windows.h"
#include"conio.h"
#include"TankGame.h"
#include"Draw.h"
#include"editMap.h"

void edit_map() {
	system("cls");

	int x = 1, y = 4;//�༭��ͼ��������
	int map[38][38] = { 0 };//�Զ���ĵ�ͼ

	char key;

	for (int i = 0; i < 38; i++)      //��ʼ��
		for (int j = 0; j < 38; j++)
			existence[i][j] = 0;   //�ÿ�

	ownTank.CoordX = 6;//��ʼ��̹��
	ownTank.CoordY = 37;
	ownTank.Camp = 1;
	ownTank.Direction = 0;

	//�з�̹��λ�õĳ�ʼ��
	for (int i = 0; i < 3; i++) {
		enemyTank[i].CoordX = 2 + i * 15;
		enemyTank[i].CoordY = 2;
		enemyTank[i].Camp = 2;
		enemyTank[i].Direction = 0;
	}

	printBorder();

	int _base[3][3] = { { 3,3,3 },{ 3,2,3 },{ 3,2,3 } };
	for (int i = 0; i < 3; i++)//����λ�ó�ʼ��
		for (int j = 0; j < 3; j++)
			base.Shape[i][j] = _base[i][j];

	printBase();//��ӡ����

	int tankUp[3][3] = { { 0,2,0 },{ 2,2,2 },{ 2,0,2 } };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			ownTank.Shape[i][j] = tankUp[i][j];
	printTank(&ownTank);//�༭��ͼ�ϴ�ӡһ���ҵ�̹��

	int tankDown[3][3] = { { 2,0,2 },{ 2,2,2 },{ 0,2,0 } };

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			enemyTank[0].Shape[i][j] = tankDown[i][j];
			enemyTank[1].Shape[i][j] = tankDown[i][j];
			enemyTank[2].Shape[i][j] = tankDown[i][j];
		}
	printTank(&enemyTank[0]);//�༭��ͼ�ϴ�ӡ��������̹��
	printTank(&enemyTank[1]);
	printTank(&enemyTank[2]);

//	setEnglish();

	int flag = 1;

	while (flag)
	{
		gotoXY(2 * x, y);
		switch (map[y - 1][x - 1])
		{
		case 0:
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
			printf("��");
		}break;
		case 3://��ǽ
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			printf("��");
		}break;
		case 4://��ǽ
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("��");
		}break;

		}

		if (_kbhit()) //��⣬����а�����ִ��if�����
		{
			key = _getch();//���񰴼�
			switch (key)
			{
			case 72: //�ϼ�ͷ
			{
				if (map[y - 1][x - 1] == 0) {
					gotoXY(2 * x, y);
					printf("  ");
				}
				if (y > 4)    y--;//�༭�����Χ
			}break;
			case 75: //���ͷ
			{
				if (map[y - 1][x - 1] == 0) {
					gotoXY(2 * x, y);
					printf("  ");
				}
				if (x > 1)    x--;//�༭�����Χ
			}break;
			case 77: //�Ҽ�ͷ
			{
				if (map[y - 1][x - 1] == 0) {
					gotoXY(2 * x, y);
					printf("  ");
				}
				if (x < 38)   x++;//�༭�����Χ
			}break;
			case 80: //�¼�ͷ
			{
				if (map[y - 1][x - 1] == 0) {
					gotoXY(2 * x, y);
					printf("  ");
				}
				if (y < 38)   y++;//�༭�����Χ
			}break;
			case 32: //���ո�ʼ��Ϸ
			{
				if (map[y - 1][x - 1] == 0) {
					gotoXY(2 * x, y);
					printf("  ");
				}
				flag = 0;
			}break;
			case 116:  //t��������ǽ
			{
				map[y - 1][x - 1] = 3;
			}break;
			case 103:  //g �����ø�ǽ
			{
				map[y - 1][x - 1] = 4;
			}break;
			case 114:  //r �����λ��
			{
				map[y - 1][x - 1] = 0;
			}break;
			default:;
			}
		}
	}

	for (int i = 0; i < 38; i++)
		for (int j = 0; j < 38; j++)
			existence[i][j] = map[i][j];//���Զ����ͼ���ݱ�������ͼ����������

	renewMap();//ˢ�µ�ͼ

	startGame();//��ʼ��Ϸ

	system("cls");

}