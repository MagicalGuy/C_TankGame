#pragma once
typedef struct _OBJECT {
	unsigned int CoordX : 6;  //�������ĵ������  //̹��ȡ���½�Ϊ��������
	unsigned int CoordY : 6;   //�������ĵ�������
	unsigned int HealthPoint : 6;  //����ֵ
	unsigned int Direction : 3;  //�˶����� 1��2��3��4��
								 //unsigned int Collide:2; //��ײ���
	unsigned int ID : 8;  //���
	unsigned int Type : 4;  //�������� 0�� 1�ڵ��ڵ� 2̹�˽ڵ� 3��ǽ�ڵ�  4��ǽ�ڵ�
	unsigned int Camp : 2;   //��Ӫ  0����   1�ѷ�    2�з�
	unsigned int Shape[3][3];   //��ʾ��״
	int speed;//�ٶ�

}Object, *pObject;

extern int score;  //��Ϸ����
extern int enemyCount;//��������
extern int gameMap[40][40];//��Ϸ��ͼ
extern int existence[38][38];//��ͼ������
extern Object base;//����
extern Object ownTank;//�Լ���̹��
extern Object enemyTank[3];//���˵�̹��
extern Object ownBullet[50];//�Լ����ӵ�
extern Object enemyBullet[3];//����̹�˵��ӵ�
void initGame();//��ʼ����Ϸ

int allowGo(Object* tank);//���ĳλ���ܲ�����

void turnUp(Object* tank);//ת�Ϻ�ˢ��
void turnDown(Object* tank);//ת�º�ˢ��
void turnLeft(Object* tank);//ת���ˢ��
void turnRight(Object* tank);//ת�Һ�ˢ��

void existChange();//����ͼ������ĸı�
void baseChange();//�����صĸı�

void gameOver();//��Ϸ����֮��Ĳ���
void checkGame();//�����Ϸ�Ƿ����

void getExistMap();//��ó�ʼ���������ͼ
void renewMap();  //ˢ�µ�ͼ
void startGame();  //��ʼ��Ϸ
void stopGame();  //ֹͣ��Ϸ
int isNull();//�жϵ�ͼ�ϰ��������Ƿ�Ϊ��