#pragma once
typedef struct _OBJECT {
	unsigned int CoordX : 6;  //物体中心点横坐标  //坦克取右下角为中心坐标
	unsigned int CoordY : 6;   //物体中心点纵坐标
	unsigned int HealthPoint : 6;  //生命值
	unsigned int Direction : 3;  //运动方向 1上2下3左4右
								 //unsigned int Collide:2; //碰撞体积
	unsigned int ID : 8;  //编号
	unsigned int Type : 4;  //对象类型 0空 1炮弹节点 2坦克节点 3土墙节点  4钢墙节点
	unsigned int Camp : 2;   //阵营  0中立   1友方    2敌方
	unsigned int Shape[3][3];   //显示形状
	int speed;//速度

}Object, *pObject;

extern int score;  //游戏分数
extern int enemyCount;//敌人数量
extern int gameMap[40][40];//游戏地图
extern int existence[38][38];//地图存在物
extern Object base;//基地
extern Object ownTank;//自己的坦克
extern Object enemyTank[3];//敌人的坦克
extern Object ownBullet[50];//自己的子弹
extern Object enemyBullet[3];//敌人坦克的子弹
void initGame();//初始化游戏

int allowGo(Object* tank);//监测某位置能不能走

void turnUp(Object* tank);//转上后刷新
void turnDown(Object* tank);//转下后刷新
void turnLeft(Object* tank);//转左后刷新
void turnRight(Object* tank);//转右后刷新

void existChange();//监测地图所有物的改变
void baseChange();//监测基地的改变

void gameOver();//游戏结束之后的操作
void checkGame();//监测游戏是否结束

void getExistMap();//获得初始化所有物地图
void renewMap();  //刷新地图
void startGame();  //开始游戏
void stopGame();  //停止游戏
int isNull();//判断地图障碍物数组是否为空