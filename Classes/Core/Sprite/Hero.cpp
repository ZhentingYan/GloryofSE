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