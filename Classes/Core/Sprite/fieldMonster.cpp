#include"Core/Sprite/fieldMonster.h"

bool fieldMonster::init()  //  Ӣ�۵��ܵĿ���
{
	return true;
}
void fieldMonster::initBloodBar() {	//��ʼ��Ѫ��
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
	blood->setPercentage(100);//��ֵ 100%
	addChild(blood, 0, 0);
}