#pragma once
void WelcomeScreen();
void printBorder();
void printInstru();

void printBase();//��ӡ����
void printExist();//��ӡ��ͼ������
void printTank(Object* tank);//��ӡ̹��
void clearTank(Object* tank);//���̹��
void printBullet();//��ӡ�Լ����ӵ�
void printBadBullet(Object* badBullet);//��ӡ�����ӵ�
void clearBullet(Object* object);//����Լ��ӵ�
void clearBadBullet(int x, int y);//�������̹�˵��ӵ�
void printScoreboard();