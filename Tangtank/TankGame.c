#include"stdio.h"
#include"stdlib.h"
#include"conio.h"
#include"Utils.h"
#include"windows.h"
#include"time.h"
#include"TankGame.h"
#include"Draw.h"
#include"Bullet.h"
#include"Tank.h"

int score;  //��Ϸ����
int enemyCount;//��������
int gameMap[40][40];//��Ϸ��ͼ
int existence[38][38];//��ͼ������
Object base;//����
Object ownTank;//�Լ���̹��
Object enemyTank[3];//���˵�̹��
Object ownBullet[50];//�Լ����ӵ�
Object enemyBullet[3];//����̹�˵��ӵ�

void initGame() {
	enemyCount = 10;
	score = 0;
	//�Լ�̹�˵ĳ�ʼ��
	ownTank.Camp = 1;
	ownTank.speed = 100;
	ownTank.CoordX = 6;
	ownTank.CoordY = 37;
	ownTank.Direction = 0;
	ownTank.HealthPoint = 10;

	//�з�̹�˵ĳ�ʼ��
	for (int i = 0; i < 3; i++) {
		enemyTank[i].CoordX = 2 + i * 15;
		enemyTank[i].CoordY = 2;
		enemyTank[i].Direction = 0;
		enemyTank[i].speed = 400;
		enemyTank[i].Camp = 2;
	}

	int _base[3][3] = { { 3,3,3 },{ 3,2,3 },{ 3,2,3 } };
	for (int i = 0; i < 3; i++)//���س�ʼ��
		for (int j = 0; j < 3; j++)
			base.Shape[i][j] = _base[i][j];

	//�Լ��ӵ���ʼ��
	for (int i = 0; i < 50; i++) {
		ownBullet[i].CoordX = 0;
		ownBullet[i].CoordY = 0;
		ownBullet[i].Direction = 0;
	}

	//�з�̹���ӵ��ĳ�ʼ��
	for (int i = 0; i < 3;i++) {
		enemyBullet[i].CoordX = 0;
		enemyBullet[i].CoordY = 0;
		enemyBullet[i].Direction = 0;
	}

	for (int i = 1; i < 39; i++)//��ͼ����
		for (int j = 1; j < 39; j++)
		{
			gotoXY(2 * i, j);
			printf("  ");
		}

	if (isNull()==1) {
		getExistMap();
	}

	renewMap();
	printBase();
	printExist();
	printScoreboard();

	turnUp(&ownTank);
	turnDown(&enemyTank[0]);
	turnDown(&enemyTank[1]);
	turnDown(&enemyTank[2]);
}


int isNull() {
	for (int i = 0; i < 38; i++) {
		for (int j = 0; j < 38; j++) {
			if (existence[i][j] != 0) {
				return 0;
				break;
			}
		}
	}

	return 1;
}

void stopGame() {
	int flag = 0;
	char key;
	while (1)
	{
		for (int i = 0; i < 50; i++)
		{
			Sleep(2000);
			if (_kbhit()) //���
			{
				key = _getch();//���񰴼�
				if (key == 32)
				{
					flag = 1;
					break;
				}
			}
			if (flag)
				break;
		}
		if (flag)
			break;
	}
}



//�жϸ÷����ܲ���ǰ��
int allowGo(Object* tank) {
	switch (tank->Direction)
	{
	case 1:
		if (gameMap[tank->CoordY - 2][tank->CoordX] == 0 &&
			gameMap[tank->CoordY - 2][tank->CoordX - 1] == 0 &&
			gameMap[tank->CoordY - 2][tank->CoordX + 1] == 0)
			return 1;
		else
			return 0;
	case 2:
		if (gameMap[tank->CoordY + 2][tank->CoordX] == 0 &&
			gameMap[tank->CoordY + 2][tank->CoordX - 1] == 0 &&
			gameMap[tank->CoordY + 2][tank->CoordX + 1] == 0)
			return 1;
		else
			return 0;
	case 3:
		if (gameMap[tank->CoordY][tank->CoordX - 2] == 0 &&
			gameMap[tank->CoordY - 1][tank->CoordX - 2] == 0 &&
			gameMap[tank->CoordY + 1][tank->CoordX - 2] == 0)
			return 1;
		else
			return 0;
	case 4:if (gameMap[tank->CoordY][tank->CoordX + 2] == 0 &&
		gameMap[tank->CoordY - 1][tank->CoordX + 2] == 0 &&
		gameMap[tank->CoordY + 1][tank->CoordX + 2] == 0)
		return 1;
		   else
			   return 0;
	}
	return 0;
}

//���Ϻ�ˢ��
void turnUp(Object* tank1) {
	int tankUp[3][3] = { { 0,2,0 },{ 2,2,2 },{ 2,0,2 } };
	if (tank1->Direction == 1)
	{
		if (allowGo(tank1))
		{
			clearTank(tank1);
			tank1->CoordY--;
			printTank(tank1);
			renewMap();
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				tank1->Shape[i][j] = tankUp[i][j];
		clearTank(tank1);
		printTank(tank1);
		tank1->Direction = 1;
		renewMap();

	}
}


//���º�ˢ��
void turnDown(Object* tank2) {
	int tankDown[3][3] = { { 2,0,2 },{ 2,2,2 },{ 0,2,0 } };
	if (tank2->Direction == 2)
	{
		if (allowGo(tank2))
		{
			clearTank(tank2);
			tank2->CoordY++;
			printTank(tank2);
			renewMap();
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				tank2->Shape[i][j] = tankDown[i][j];
		clearTank(tank2);
		printTank(tank2);
		tank2->Direction = 2;
		renewMap();
	}
}

//�����ˢ��
void turnLeft(Object* tank3) {
	int tankLeft[3][3] = { { 0,2,2 },{ 2,2,0 },{ 0,2,2 } };
	if (tank3->Direction == 3)
	{
		if (allowGo(tank3))
		{
			clearTank(tank3);
			tank3->CoordX--;
			printTank(tank3);
			renewMap();
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				tank3->Shape[i][j] = tankLeft[i][j];
		clearTank(tank3);
		printTank(tank3);
		tank3->Direction = 3;
		renewMap();
	}
}

//���Һ�ˢ��
void turnRight(Object* tank4) {
	int tankRight[3][3] = { { 2,2,0 },{ 0,2,2 },{ 2,2,0 } };
	if (tank4->Direction == 4)
	{
		if (allowGo(tank4))
		{
			clearTank(tank4);
			tank4->CoordX++;
			printTank(tank4);
			renewMap();
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				tank4->Shape[i][j] = tankRight[i][j];
		clearTank(tank4);
		printTank(tank4);
		tank4->Direction = 4;
		renewMap();
	}
}


//����ӵ��Դ����ϰ���ĸı䣬������ײ��ĸı�
void existChange() {
	for (int i = 0; i < 50; i++) {
		int m = ownBullet[i].CoordX;
		int n = ownBullet[i].CoordY;
		if (m > 0 && m < 39 && n>0 && n < 39) {//����̹���ӵ�����
			if (existence[n - 1][m - 1] == 3)//����ǽ
			{
				existence[n - 1][m - 1] = 0;
				gotoXY(2 * m, n);
				printf("  ");
				ownBullet[i].CoordX = 0, ownBullet[i].CoordY = 0;//�ӵ���ʧ
				printExist();
				renewMap();
			}

			else if (existence[n - 1][m - 1] == 4)//�򵽸�ǽ
			{
				ownBullet[i].CoordX = 0, ownBullet[i].CoordY = 0;//�ӵ���ʧ
			}
		}
	}


	for (int i = 0; i < 3;i++) {
	int m1 = enemyBullet[i].CoordX;
	int n1 = enemyBullet[i].CoordY;

	if (m1 > 0 && m1 < 39 && n1>0 && n1 < 39) {//���з���̹�˵ĸ����ӵ�����
		if (existence[n1 - 1][m1 - 1] == 3)//����ǽ
		{
			existence[n1 - 1][m1 - 1] = 0;
			gotoXY(2 * m1, n1);
			printf("  ");
			enemyBullet[i].CoordX = 0, enemyBullet[i].CoordY = 0;
			printExist();
			renewMap();
		}
		else if (existence[n1 - 1][m1 - 1] == 4)//�򵽸�ǽ
		{
			enemyBullet[i].CoordX = 0, enemyBullet[i].CoordY = 0;//�ӵ���ʧ
		}
		else if (existence[n1 - 1][m1 - 1] == 2)//��̹��
		{
			enemyBullet[i].CoordX = 0, enemyBullet[i].CoordY = 0;//�ӵ���ʧ
		}
	}
	else {
		if (m1>40||m1<0||n1>40||n1<0) {
		gotoXY(2 * m1, n1);
		printf("  ");
		enemyBullet[i].CoordX = 0, enemyBullet[i].CoordY = 0;
		printExist();
		renewMap();
		}
	}
	}
}

//�����صı仯
void baseChange() {
	for (int i = 0; i < 50; i++) {
		int m = ownBullet[i].CoordX;
		int n = ownBullet[i].CoordY;
		if (m == 37 && n == 38 || m == 38 && n == 38) {
			gameOver();
			break;
		}

		for (int a = 0; a < 3; a++) {
			for (int b = 0; b < 3; b++) {//�Լ��ӵ��Ի��ص���ײ
				if (m == 36 + 2 * a  && n == 36 + b) {
					if (base.Shape[a][b] == 3) {
						base.Shape[a][b] = 0;
						gotoXY(2 * m, n);
						printf("  ");
						ownBullet[i].CoordX = 0;
						ownBullet[i].CoordY = 0;
						printBase();
						renewMap();
					}
				}
			}
		}
	}


	for (int i = 0; i < 3;i++) {

	int m1 = enemyBullet[i].CoordX;
	int n1 = enemyBullet[i].CoordY;//�����ӵ��Ի��ص���ײ
	if (m1 == 37 && n1 == 38 || m1 == 38 && n1 == 38) {
		gameOver();
		return;
	}

	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			if (m1 == 36 + 2 * a  && n1 == 36 + b) {
				if (base.Shape[a][b] == 3) {
					base.Shape[a][b] = 0;
					gotoXY(2 * m1, n1);
					printf("  ");
					enemyBullet[i].CoordX = 0;
					enemyBullet[i].CoordY = 0;
					printBase();
					renewMap();
				}
			}
		}
	}
	}
}


//��Ϸ��������ʾ
void gameOver() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoXY(30, 17);
	printf("          ��Ϸ����        ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoXY(32, 23);
	printf("    �� �ո�� ���¿�ʼ���߰� n �������˵�    ");

	while (1)
	{
		if (32 == _getch())
		{
			getExistMap();
			renewMap();
			startGame();
			break;
		}
		if('n'== _getch()){
			getExistMap();
			renewMap();
			WelcomeScreen();
			break;
		}
	}
}

//�����Ϸ�Ƿ����
void checkGame() {
	if (ownTank.HealthPoint == 0)
		gameOver();
	if (enemyCount == 0) {
		printf("�������Ϸ��ʤ����\n");
		system("pause");
		gameOver();
	}	
}


void getExistMap() {//�����ϰ���
	for (int j = 0; j < 38; j++) {
		existence[19][j] = 3;//��ǽ
		existence[20][j] = 3;
	}

	for (int i = 14; i < 28; i++) {
		existence[21][i] = 4;//��ǽ
	}
}


void renewMap() {
	for (int i = 0; i < 40; i++)          //��Ϸ��ͼ��ʼ��
		for (int j = 0; j < 40; j++)
			gameMap[i][j] = 0;

	for (int i = 0; i < 40; i++)    //Χǽ
	{
		gameMap[i][0] = 4;
		gameMap[i][39] = 4;
	}
	for (int j = 0; j < 40; j++)
	{
		gameMap[0][j] = 4;
		gameMap[39][j] = 4;
	}

	for (int i = 0; i < 38; i++)  //��ͼ������
		for (int j = 0; j < 38; j++)
			gameMap[i + 1][j + 1] = existence[i][j];

	for (int i = 0; i < 3; i++)   //����
		for (int j = 0; j < 3; j++)
			gameMap[i + 36][j + 18] = base.Shape[i][j];

	switch (ownTank.Direction)          //̹��
	{
	case 1:
	{
		gameMap[ownTank.CoordY - 1][ownTank.CoordX - 1] = 0;  gameMap[ownTank.CoordY - 1][ownTank.CoordX] = 2;      gameMap[ownTank.CoordY - 1][ownTank.CoordX + 1] = 0;
		gameMap[ownTank.CoordY][ownTank.CoordX - 1] = 2;    gameMap[ownTank.CoordY][ownTank.CoordX] = 2;        gameMap[ownTank.CoordY][ownTank.CoordX + 1] = 2;
		gameMap[ownTank.CoordY + 1][ownTank.CoordX - 1] = 2;  gameMap[ownTank.CoordY + 1][ownTank.CoordX] = 0;      gameMap[ownTank.CoordY + 1][ownTank.CoordX + 1] = 2;

	}break;
	case 2:
	{
		gameMap[ownTank.CoordY - 1][ownTank.CoordX - 1] = 2;  gameMap[ownTank.CoordY - 1][ownTank.CoordX] = 0;      gameMap[ownTank.CoordY - 1][ownTank.CoordX + 1] = 2;
		gameMap[ownTank.CoordY][ownTank.CoordX - 1] = 2;    gameMap[ownTank.CoordY][ownTank.CoordX] = 0;        gameMap[ownTank.CoordY][ownTank.CoordX + 1] = 2;
		gameMap[ownTank.CoordY + 1][ownTank.CoordX - 1] = 0;  gameMap[ownTank.CoordY + 1][ownTank.CoordX] = 2;      gameMap[ownTank.CoordY + 1][ownTank.CoordX + 1] = 0;

	}break;
	case 3:
	{
		gameMap[ownTank.CoordY - 1][ownTank.CoordX - 1] = 0;  gameMap[ownTank.CoordY - 1][ownTank.CoordX] = 2;      gameMap[ownTank.CoordY - 1][ownTank.CoordX + 1] = 2;
		gameMap[ownTank.CoordY][ownTank.CoordX - 1] = 2;    gameMap[ownTank.CoordY][ownTank.CoordX] = 2;        gameMap[ownTank.CoordY][ownTank.CoordX + 1] = 0;
		gameMap[ownTank.CoordY + 1][ownTank.CoordX - 1] = 0;  gameMap[ownTank.CoordY + 1][ownTank.CoordX] = 2;      gameMap[ownTank.CoordY + 1][ownTank.CoordX + 1] = 2;

	}break;
	case 4:
	{
		gameMap[ownTank.CoordY - 1][ownTank.CoordX - 1] = 2;  gameMap[ownTank.CoordY - 1][ownTank.CoordX] = 2;      gameMap[ownTank.CoordY - 1][ownTank.CoordX + 1] = 0;
		gameMap[ownTank.CoordY][ownTank.CoordX - 1] = 0;    gameMap[ownTank.CoordY][ownTank.CoordX] = 2;        gameMap[ownTank.CoordY][ownTank.CoordX + 1] = 2;
		gameMap[ownTank.CoordY + 1][ownTank.CoordX - 1] = 2;  gameMap[ownTank.CoordY + 1][ownTank.CoordX] = 2;      gameMap[ownTank.CoordY + 1][ownTank.CoordX + 1] = 0;
	}break;
	}

	for (int i = 0; i < 3; i++) {
		switch (enemyTank[i].Direction)  //�з�̹��
		{
		case 1://��
		{
			gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX - 1] = 0;  gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX] = 2;      gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX + 1] = 0;
			gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX - 1] = 2;    gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX] = 2;        gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX + 1] = 2;
			gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX - 1] = 2;  gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX] = 0;      gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX + 1] = 2;

		}break;
		case 2://��
		{
			gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX - 1] = 2;  gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX] = 0;      gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX + 1] = 2;
			gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX - 1] = 2;    gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX] = 0;        gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX + 1] = 2;
			gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX - 1] = 0;  gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX] = 2;      gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX + 1] = 0;

		}break;
		case 3://��
		{
			gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX - 1] = 0;  gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX] = 2;      gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX + 1] = 2;
			gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX - 1] = 2;    gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX] = 2;        gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX + 1] = 0;
			gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX - 1] = 0;  gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX] = 2;      gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX + 1] = 2;

		}break;
		case 4://��
		{
			gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX - 1] = 2;  gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX] = 2;      gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX + 1] = 0;
			gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX - 1] = 0;    gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX] = 2;        gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX + 1] = 2;
			gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX - 1] = 2;  gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX] = 2;      gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX + 1] = 0;
		}break;
		}
	}
}

clock_t time1_start;
clock_t time1_end;
clock_t time2_start;
clock_t time2_end;

void startGame() {
	system("mode con cols=90 lines=45");
	system("title ̹�˴�ս");
	hideCursor();
	printBorder();//��ӡΧǽ
	initGame();//��ʼ������
	srand((unsigned int)time(NULL));
	while (1) {

		time1_end = clock();
		if (time1_end - time1_start > ownTank.speed)
		{
			time1_start = time1_end;
			tankMove();//�Լ�̹���ƶ�
			ownBulletMove();//�Լ��ӵ��ƶ�
		}

		time2_end = clock();
		if (time2_end - time2_start > enemyTank[0].speed)
		{
			time2_start = time2_end;

			badTankMove(&enemyTank[0]);//�о��ƶ�
			badTankMove(&enemyTank[1]);
			badTankMove(&enemyTank[2]);

			badTankfire(&enemyTank[0], &enemyBullet[0]);//�о�����
			enemyBulletMove(&enemyBullet[0]);//�о��ӵ��ƶ�

			badTankfire(&enemyTank[1], &enemyBullet[1]);
			enemyBulletMove(&enemyBullet[1]);

			badTankfire(&enemyTank[2], &enemyBullet[2]);
			enemyBulletMove(&enemyBullet[2]);

		}
	}
}

int main() {
	WelcomeScreen();//��Ϸѡ����˵�
	system("pause");
	return 0;
}