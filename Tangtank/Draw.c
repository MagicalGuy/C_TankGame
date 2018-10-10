#include"stdio.h"
#include"stdlib.h"
#include"windows.h"
#include"TankGame.h"
#include"Utils.h"
#include"editMap.h"
#include"Draw.h"

void WelcomeScreen() {
	setEnglish();
	system("cls");
	gotoXY(20,5);
	color(14);
	printf("        �������{�{�{�{�{�{\n");
	gotoXY(20, 6);
	printf("    �{�|�������������|�{�z�y\n");
	gotoXY(20, 7);
	printf("����������������������������\n");
	gotoXY(20, 8);
	printf("���ѡ��ѡ��ѡ��ѡ��ѡ��ѡ���\n");
	gotoXY(20, 10);
	printf("1����ʼ��Ϸ\n");
	gotoXY(20, 11);
	printf("2���༭��ͼ\n");
	gotoXY(20, 12);
	printf("3������˵��\n");
	gotoXY(20, 13);
	printf("4���˳���Ϸ\n");
	gotoXY(20, 14);
	printf("���������Ĳ���ѡ�");

	int flag = 1;
	char operate;
	while(flag) {
		operate = getchar();
		switch (operate) {
		case '1':startGame(); flag = 0; break;
		case '2':edit_map(); flag = 0; break;
		case '3':printInstru(); flag = 0; break;
		case '4':exit(0); flag = 0; break;
		default:printf("����������������룺");break;	
		}
	}
}

//��ӡ����˵��
void printInstru() {

	system("cls");
	gotoXY(20,10);
	printf("��Ϸ��wsad�����ֱ����̹�˵���������");
	gotoXY(20, 12);
	printf(" ��Ϸ��f��������p����ͣ���ո����ʼ ");
	gotoXY(1, 14);
	printf("�༭��ͼ�а��ĸ���ͷ�ƶ���꣬t��g��r���ֱ𴴽���ǽ����ǽ�Ͳ������ո��������༭��ʼ��Ϸ");
	gotoXY(20, 16);
	system("pause");
	getchar();
	WelcomeScreen();
}
//��ӡΧǽ
void printBorder() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);//��ɫ
	printf("��������������������������������������������������������������������������������\n");
	for (int i = 0; i<38; i++)
		printf("��                                                                            ��\n");
	printf("��������������������������������������������������������������������������������\n");
}


void printBase() {

	for (int i = 0; i < 3; i++)          //��ӡ����
		for (int j = 0; j < 3; j++)
		{
			if (base.Shape[i][j] == 2) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				gotoXY(36 + 2 * j, 36 + i);
				printf("��");
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				gotoXY(36 + 2 * j, 36 + i);
				printf("��");
			}
		}
}


void printExist() {
	for (int j = 0; j < 38; j++)
		for (int i = 0; i < 38; i++)
			if (existence[i][j] == 3)//��ǽ
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				gotoXY(2 + 2 * j, 1 + i);
				printf("��");
			}
			else if (existence[i][j] == 4)////��ǽ
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoXY(2 + 2 * j, 1 + i);
				printf("��");
			}
}

//��ӡ̹��
void printTank(Object* tank) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			if (tank->Shape[i][j] == 2 && tank->Camp == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);// ��ɫ
				gotoXY(2 * tank->CoordX + 2 * j - 2, tank->CoordY + i - 1);
				printf("��");
			}
			if (tank->Shape[i][j] == 2 && tank->Camp == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);//����ɫ
				gotoXY(2 * tank->CoordX + 2 * j - 2, tank->CoordY + i - 1);
				printf("��");
			}
		}
}


void clearTank(Object* tank) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			gotoXY(2 * tank->CoordX + 2 * j - 2, tank->CoordY + i - 1);
			printf("  ");
		}
}

//��ӡ�Լ����ӵ�
void printBullet() {
	for (int i = 0; i < 50; i++) {
		if (ownBullet[i].CoordX != 0 && ownBullet[i].CoordY != 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			gotoXY(ownBullet[i].CoordX * 2, ownBullet[i].CoordY);
			ownBullet[i].ID = i;
			printf("��");
		}
	}
}

//��ӡ�����ӵ�
void printBadBullet(Object* badBullet) {

	if (badBullet->CoordX != 0 && badBullet->CoordY != 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		if (badBullet->CoordX * 2 < 80) {
			gotoXY(badBullet->CoordX * 2, badBullet->CoordY);
			printf("  ");
		}
		gotoXY(badBullet->CoordX * 2, badBullet->CoordY);
		printf("��");
	}
}


//��ӡ�Ʒ�
void printScoreboard() {
	gotoXY(5 * 2, 41);
	printf("                               ");
	gotoXY(10 * 2, 41);
	printf("                               ");
	gotoXY(5 * 2, 41);
	printf("score: %d", score);
	gotoXY(12 * 2, 41);
	printf("HP: %d", ownTank.HealthPoint);
}


//����Լ����ӵ�
void clearBullet(Object* object) {
	for (int i = 0; i < 50; i++) {
		if (object[i].CoordX != 0 && object[i].CoordY != 0) {
			gotoXY(object[i].CoordX * 2, object[i].CoordY);
			printf("  ");
		}
	}
}

//����з�̹���ӵ�
void clearBadBullet(int x, int y) {
	if (x != 0 && y != 0)
	{
		gotoXY(2 * x, y);
		printf("  ");
	}
}

