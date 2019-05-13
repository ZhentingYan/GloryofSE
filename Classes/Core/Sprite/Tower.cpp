#include"Core/Sprite/Tower.h"

void Tower::initBloodBar() {	//��ʼ��Ѫ��
	auto bgSprite = Sprite::create("empty_bar.png");
	bgSprite->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 1.1));//����㣬����ڱ�����
	addChild(bgSprite);
	auto hpSprite = Sprite::create("full_bar.png");
	blood = ProgressTimer::create(hpSprite);
	blood->setType(ProgressTimer::Type::BAR);
	blood->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 1.1));//����㣬����ڱ�����
	blood->setMidpoint(cocos2d::ccp(1, 0.5));
	blood->setBarChangeRate(cocos2d::ccp(1, 0));
	blood->setMidpoint(Point(0, 0.5));
	blood->setBarChangeRate(Point(1, 0));
	blood->setPercentage(((float)bloodNum) / 10.0);//��ֵ 100%
							  //addChild(blood, 0, 0);
	addChild(blood);
}

void Tower::initTowerAttr(int attackAbility, int _bloodNum, int _rewardMoney, int _rewardExp,Hero* hero)
{
	attack_rect = new Rect(this->getPositionX() - 100, this->getPositionY() - 100, 200, 200);
	isAttacking = false;
	attackMinusNum = attackAbility;
	bloodNum = _bloodNum;
	deadRewardmoney = _rewardMoney;
	deadRewardExp = _rewardExp;
	enemyHero = hero;
	initBloodBar();
}

void Tower::minusBlood(int num, Node * attacker)
{
	if (bloodNum - num >= 0) {
		bloodNum -= num;
		blood->setPercentage(((float)bloodNum)/10.0);
	}
	else {//�����ж�
		blood->setPercentage(0);
		this->setVisible(false);	//�����ˣ����ɼ�
		bloodNum = 0;
		//this->setPosition(initPos);
		if (attacker == enemyHero)
			enemyHero->addReward(deadRewardmoney, deadRewardExp);
		this->unscheduleAllSelectors();
	}
}
