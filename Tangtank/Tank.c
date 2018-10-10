#include"Tank.h"
#include"Draw.h"
#include"windows.h"
#include"conio.h"
#include"Utils.h"

#define KEYDOWN(vk_code)((GetAsyncKeyState(vk_code)&0x8000)?1:0)
#define KEYUP(vk_code)((GetAsyncKeyState(vk_code)&0x8000)?0:1)

//����Լ�̹��״̬�ĸı�
void ownTankChange() {

	int x = ownTank.CoordX;
	int y = ownTank.CoordY;

	switch (ownTank.Direction)
	{
	case 1:    //���ҵ�̹�˷�������ʱ
	{
		for (int i = 0; i < 3; i++) {
			int m1 = enemyBullet[i].CoordX;
			int n1 = enemyBullet[i].CoordY;

			if (x == m1 && (y - 1) == n1 || (x - 1) == m1&&y == n1 || x == m1&&y == n1 ||
				(x + 1) == m1&&y == n1 || (x - 1) == m1 && (y + 1) == n1 || (x + 1) == m1 && (y + 1) == n1)
				enemyBullet[i].CoordX = 0,
				enemyBullet[i].CoordY = 0,
				ownTank.HealthPoint--,
				printScoreboard(),
				checkGame(),
				turnUp(&ownTank);
			//̹���ӵ���ʧ������ֵ��1�������Ϸ�Ƿ��������û������ʼ������
		}

	}break;
	case 2:
	{
		for (int i = 0; i < 3; i++) {
			int m1 = enemyBullet[i].CoordX;
			int n1 = enemyBullet[i].CoordY;
			if (x == m1 && (y + 1) == n1 || (x - 1) == m1&&y == n1 || x == m1&&y == n1 || (x + 1) == m1&&y == n1 ||
				(x - 1) == m1 && (y - 1) == n1 || (x + 1) == m1 && (y - 1) == n1)
				enemyBullet[i].CoordX = 0,
				enemyBullet[i].CoordY = 0,
				ownTank.HealthPoint--,
				printScoreboard(),
				checkGame(),
				turnUp(&ownTank);
		}

	}break;
	case 3:
	{
		for (int i = 0; i < 3; i++) {
			int m1 = enemyBullet[i].CoordX;
			int n1 = enemyBullet[i].CoordY;
			if (x == m1 && (y - 1) == n1 || (x - 1) == m1&&y == n1 || x == m1&&y == n1 ||
				(x + 1) == m1 && (y - 1) == n1 || x == m1 && (y + 1) == n1 || (x + 1) == m1 && (y + 1) == n1)
				enemyBullet[i].CoordX = 0, enemyBullet[i].CoordY = 0, ownTank.HealthPoint--, printScoreboard(), checkGame(), turnUp(&ownTank);
		}
	}break;
	case 4:
	{
		for (int i = 0; i < 3; i++) {
			int m1 = enemyBullet[i].CoordX;
			int n1 = enemyBullet[i].CoordY;
			if (x == m1 && (y - 1) == n1 || (x - 1) == m1 && (y - 1) == n1 || x == m1&&y == n1 ||
				(x - 1) == m1 && (y + 1) == n1 || x == m1 && (y + 1) == n1 || (x + 1) == m1&&y == n1)
				enemyBullet[i].CoordX = 0,
				enemyBullet[i].CoordY = 0,
				ownTank.HealthPoint--,
				printScoreboard(),
				checkGame(),
				turnUp(&ownTank);
		}
	}break;

	}
}


//������̹��״̬�ĸı�
void badTankChange()
{

	for (int i = 0; i < 50; i++) {
		int m = ownBullet[i].CoordX;
		int n = ownBullet[i].CoordY;

		for (int j = 0; j < 3; j++) {

			int x1 = enemyTank[j].CoordX;
			int y1 = enemyTank[j].CoordY;

			switch (enemyTank[j].Direction)
			{
			case 1:
			{//��̹�����ĵ㿪ʼ�ж��������Ƿ����ӵ������غ�
				if (x1 == m && (y1 - 1) == n || (x1 - 1) == m && y1 == n || x1 == m&&y1 == n ||
					(x1 + 1) == m && y1 == n || (x1 - 1) == m && (y1 + 1) == n || (x1 + 1) == m && (y1 + 1) == n) {
					//����ҵ�̹���ӵ��򵽵���
					clearTank(&enemyTank[j]); //����о�̹��
					enemyTank[j].CoordX = 2 + j * 10;//�о�̹�˻ص���ʼλ��
					enemyTank[j].CoordY = 2;
					ownBullet[i].CoordX = 0;//�ҵ�̹���ӵ���ʧ
					ownBullet[i].CoordY = 0;
					enemyCount--; //����̹��������1
					score = score + 100;//������100
					printScoreboard();
					checkGame();//�����Ϸ�Ƿ�ʤ��
				}

			}break;
			case 2:
			{
				if (x1 == m && (y1 + 1) == n || (x1 - 1) == m&&y1 == n || x1 == m&&y1 == n ||
					(x1 + 1) == m&&y1 == n || (x1 - 1) == m && (y1 - 1) == n || (x1 + 1) == m && (y1 - 1) == n) {
					clearTank(&enemyTank[j]);
					enemyTank[j].CoordX = 2 + j * 10;
					enemyTank[j].CoordY = 2;
					ownBullet[i].CoordX = 0;
					ownBullet[i].CoordY = 0;
					enemyCount--;
					score = score + 100;
					printScoreboard();
					checkGame();
				}

			}break;
			case 3:
			{
				if (x1 == m && (y1 - 1) == n || (x1 - 1) == m&&y1 == n || x1 == m&&y1 == n ||
					(x1 + 1) == m && (y1 - 1) == n || x1 == m && (y1 + 1) == n || (x1 + 1) == m && (y1 + 1) == n) {
					clearTank(&enemyTank[j]);
					enemyTank[j].CoordX = 2 + j * 10;
					enemyTank[j].CoordY = 2;
					ownBullet[i].CoordX = 0;
					ownBullet[i].CoordY = 0;
					enemyCount--;
					score = score + 100;
					printScoreboard();
					checkGame();
				}

			}break;
			case 4:
			{
				if (x1 == m && (y1 - 1) == n || (x1 - 1) == m && (y1 - 1) == n || x1 == m&&y1 == n ||
					(x1 - 1) == m && (y1 + 1) == n || x1 == m && (y1 + 1) == n || (x1 + 1) == m&&y1 == n) {
					clearTank(&enemyTank[j]);
					enemyTank[j].CoordX = 2 + j * 10;
					enemyTank[j].CoordY = 2;
					ownBullet[i].CoordX = 0;
					ownBullet[i].CoordY = 0;
					enemyCount--;
					score = score + 100;
					printScoreboard();
					checkGame();
				}
			}break;
			}
		}
	}
}


void ownTankfire() {
	for (int i = 0; i < 50; i++) {
		int m = ownBullet[i].CoordX;
		int n = ownBullet[i].CoordY;

		if (m == 0 && n == 0)//�ڼ����ӵ�û��,�����������ӵ�
		{
			switch (ownTank.Direction)
			{
			case 1:
			{
				ownBullet[i].CoordX = ownTank.CoordX;
				ownBullet[i].CoordY = ownTank.CoordY - 2;
				ownBullet[i].Direction = 1;
			}break;
			case 2:
			{
				ownBullet[i].CoordX = ownTank.CoordX;;
				ownBullet[i].CoordY = ownTank.CoordY + 2;
				ownBullet[i].Direction = 2;
			}break;
			case 3:
			{
				ownBullet[i].CoordX = ownTank.CoordX - 2;
				ownBullet[i].CoordY = ownTank.CoordY;
				ownBullet[i].Direction = 3;
			}break;
			case 4:
			{
				ownBullet[i].CoordX = ownTank.CoordX + 2;
				ownBullet[i].CoordY = ownTank.CoordY;
				ownBullet[i].Direction = 4;
			}break;
			}

			break;
		}

	}
}


void badTankfire(Object* badTank, Object* badTankBullet) {

	int m = badTankBullet->CoordX;
	int n = badTankBullet->CoordY;

	if (m == 0 && n == 0)//û��̹�˵��ӵ�,�����·����ӵ�
	{
		switch (badTank->Direction)
		{
		case 1:
		{
			badTankBullet->CoordX = badTank->CoordX;
			badTankBullet->CoordY = badTank->CoordY - 2;
			badTankBullet->Direction = 1;
		}break;
		case 2:
		{
			badTankBullet->CoordX = badTank->CoordX;;
			badTankBullet->CoordY = badTank->CoordY + 2;
			badTankBullet->Direction = 2;
		}break;
		case 3:
		{
			badTankBullet->CoordX = badTank->CoordX - 2;
			badTankBullet->CoordY = badTank->CoordY;
			badTankBullet->Direction = 3;
		}break;
		case 4:
		{
			badTankBullet->CoordX = badTank->CoordX + 2;
			badTankBullet->CoordY = badTank->CoordY;
			badTankBullet->Direction = 4;
		}break;
		}
	}
}


void tankMove() {

	if (KEYDOWN('f') || KEYDOWN('F'))
	{
		ownTankfire();
		return;
	}
	if (KEYDOWN('W') || KEYDOWN('w'))
	{
		turnUp(&ownTank);
		return;
	}
	if (KEYDOWN('s') || KEYDOWN('S'))
	{
		turnDown(&ownTank);
		return;
	}
	if (KEYDOWN('a') || KEYDOWN('A'))
	{
		turnLeft(&ownTank);
		return;
	}
	if (KEYDOWN('d') || KEYDOWN('D'))
	{
		turnRight(&ownTank);
		return;
	}
	if (KEYDOWN('p') || KEYDOWN('P'))
	{
		stopGame();
		return;
	}
	if (KEYDOWN('o') || KEYDOWN('O'))
	{
		exit(0);
		return;
	}
}


void badTankMove(Object* badTank) {

	int direction = (rand() % 4 + 1);
	switch (direction)
	{
	case 1:turnUp(badTank); break;
	case 2:turnDown(badTank); break;
	case 3:turnLeft(badTank); break;
	case 4:turnRight(badTank); break;
	}
}
