#include"Core/Sprite/Hero.h"




bool Hero::init()  //  Ӣ�۵��ܵĿ���
{
	return true;
}


bool Hero::checkIsAttack()  //����Ƿ��ܵ�����
{

	return true;
}

bool Hero::attackTrick(const char *format,int num)   //��������  �Ŵ���
{
	Animation *animation = Animation::create();

	for (int i = 0; i < num; i++)
	{
		__String *frameName = __String::createWithFormat(format, i);
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName
			->getCString());
		animation->addSpriteFrame(spriteFrame);

	}
	animation->setDelayPerUnit(0.15f);     //��������֡�����¼�
	animation->setRestoreOriginalFrame(true);
	Animate *action = Animate::create(animation);
	this->runAction(RepeatForever::create(action));
	return true;
}
void Hero::updateHeroSpeed(float newspeed)
{
	speed = newspeed;
}
float Hero::getHeroSpeed()
{
	return speed;
}
void Hero::initBloodBar() {	//��ʼ��Ѫ��
	auto bgSprite = Sprite::create("empty_bar.png");
	bgSprite->setPosition(Vec2(getContentSize().width/2, getContentSize().height / 1.1));//����㣬����ڱ�����

	addChild(bgSprite);
	auto hpSprite = Sprite::create("full_bar.png");
	blood = ProgressTimer::create(hpSprite);
	blood->setType(ProgressTimer::Type::BAR);
	blood->setPosition(Vec2(getContentSize().width/2, getContentSize().height / 1.1));//����㣬����ڱ�����
	blood->setMidpoint(cocos2d::ccp(1, 0.5));
	blood->setBarChangeRate(cocos2d::ccp(1, 0));
	blood->setMidpoint(Point(0, 0.5));
	blood->setBarChangeRate(Point(1, 0));
	blood->setPercentage(100);//��ֵ 100%
	addChild(blood, 0, 0);
}