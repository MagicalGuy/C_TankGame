#include"TankGame.h"
#include"Tank.h"
#include"Bullet.h"
#include"Draw.h"

int checkBullet(int x, int y)//����ܲ����ڴ˴�ӡ�ӵ�
{
	if (gameMap[y][x])
		return 0;
	return 1;
}


void ownBulletMove() {
	for (int i = 0; i < 50; i++) {
		int m = ownBullet[i].CoordX;
		int n = ownBullet[i].CoordY;

		if (m != 0 || n != 0)
			if (gameMap[n][m] == 0)//�Ȳ���		
				clearBullet(ownBullet);

		switch (ownBullet[i].Direction)
		{
		case 1:ownBullet[i].CoordY--; break;
		case 2:ownBullet[i].CoordY++; break;
		case 3:ownBullet[i].CoordX--; break;
		case 4:ownBullet[i].CoordX++; break;
		}

		//����Ƿ�����ϰ���
		existChange();
		//����Ƿ���л���
		baseChange();
		//����Ƿ�����ӵ�
		bulletChange();
		//����Ƿ���ез�̹��
		badTankChange();

		if (checkBullet(ownBullet[i].CoordX, ownBullet[i].CoordY))
			printBullet();
		else
			ownBullet[i].CoordX = 0, ownBullet[i].CoordY = 0;
	}
}



void enemyBulletMove(Object* badTankBullet) {
	int m = badTankBullet->CoordX;
	int n = badTankBullet->CoordY;

	if (m != 0 || n != 0)
		if (gameMap[n][m] == 0) {//�������	
			clearBadBullet(m, n);
		}

	switch (badTankBullet->Direction)
	{
	case 1:badTankBullet->CoordY--; break;
	case 2:badTankBullet->CoordY++; break;
	case 3:badTankBullet->CoordX--; break;
	case 4:badTankBullet->CoordX++; break;
	}

	//����Ƿ�����ϰ���
	existChange();

	//����Ƿ���л���
	baseChange();

	//����Ƿ�����ӵ�
	bulletChange();

	//����Ƿ�����ҵ�̹��
	ownTankChange();

	if (badTankBullet->CoordX != 0 && badTankBullet->CoordY != 0) {
		if (checkBullet(badTankBullet->CoordX, badTankBullet->CoordY))
			printBadBullet(badTankBullet);
		else
			badTankBullet->CoordX = 0, badTankBullet->CoordY = 0;
	}
}


//����ӵ���ײ�ĸı�
void bulletChange() {
	for (int i = 0; i < 50; i++) {
		int m = ownBullet[i].CoordX;
		int n = ownBullet[i].CoordY;

		for (int i = 0; i < 3; i++) {//�ҵ�̹���ӵ��͵���̹���ӵ�����ײ

			if (enemyBullet[i].CoordX == m && m != 0 && enemyBullet[i].CoordY == n && n != 0) {
				clearBullet(&ownBullet[i]);//ɾ����̹�˵��ӵ�
				ownBullet[i].CoordX = 0;
				ownBullet[i].CoordY = 0;

				clearBadBullet(enemyBullet[i].CoordX, enemyBullet[i].CoordY);//ɾ���з�̹�˵��ӵ�
				enemyBullet[i].CoordX = 0;
				enemyBullet[i].CoordY = 0;
			}
		}
	}
}