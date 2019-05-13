#pragma once
#include"cocos2d.h"
#include"Core/Sprite/Hero.h"
#include"Core/Sprite/Tower.h"

#define enemy_pao "monster/kongjumo/pao/1004-6579bfb5-0%d00%d.png"
#define enemy_attck "monster/kongjumo/attck/1881-c1b24bac-0%d00%d.png"
USING_NS_CC;
//class Tower;
enum {
	up = 6,
	down = 4,
	lefts = 5,//
	rigth = 7,//
	rigth_up = 3,//
	rigth_down = 0,//
	left_down = 1,//
	left_up = 2//
};
class EnemySoldier : public Sprite
{
public:
	ProgressTimer * blood;   //Ѫ��
	int bloodNum;  //Ѫ��
	Vec2 initPos;
	Vec2 attackTowerPos;
	int deadRewardmoney;	//���������������
	int deadRewardExp;		//�����������������
	int attackMinusNum;		//ÿ�δ��˵ĵ�Ѫ��
	virtual bool init();   
	Rect* attack_rect;
	void initBloodBar();
	void initMonsterAttr(int attackAbility, int _bloodNum, int _rewardMoney, int _rewardExp,Vec2 towerPos);
	void setNewAttackRect();
	int getAttackDir(int tempDir);
	int getNowPointDir(Node * player, Vec2 newpoint);
	bool checkHeroInRect();
	void attackHero(float dt);
	void attackTower(float dt);
	void minusBlood(int num);
	void startWalkTowardsTower(int dir);
	//Hero* heroInRect;
	Hero* enemyHero;
	Tower* enemyTower;
	bool isAttacking;
	bool isWalking;
	void scheduleAttack(int way);
	void unscheduleAttack();
};