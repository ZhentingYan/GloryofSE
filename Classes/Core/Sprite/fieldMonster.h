#pragma once
#include"cocos2d.h"
#include"Core/Sprite/Hero.h"
USING_NS_CC;
class fieldMonster : public Sprite
{
public:
	ProgressTimer * blood;   //血量
	int bloodNum;  //血量
	//void attack();
	Vec2 initPos;
	int deadRewardmoney;	//打死奖励金币数量
	int deadRewardExp;		//打死奖励经验的数量
	int attackMinusNum;		//每次打人的
	virtual bool init();   //  野怪总的控制
	Rect* attack_rect;
	void setReward();
	void initBloodBar();
	void initMonsterAttr();
	bool checkHeroInRect(Hero* hero1,Hero* hero2);
	void attackHero(float dt);
	void minusBlood(int num);
	Hero* heroInRect;
	bool isAttacking;
	void scheduleAttack();
	void unscheduleAttack();
};