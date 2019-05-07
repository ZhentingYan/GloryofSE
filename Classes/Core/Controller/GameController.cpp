#include"Core/Controller/GameController.h"
#define hero_daji "hero/daji.png"
#define hero_houyi "hero/houyi.jpg"
#define hero_yase "hero/yase.jpg"

#define daji_big_skill "skills\role_skill\ziqidonglai%d.png"
#define daji_medium_skill "skills\role_skill\ziqidonglai%d.png"
#define daji_small_skill "skills\role_skill\ziqidonglai%d.png"

#define yase_big_skill "skills\role_skill\ziqidonglai%d.png"
#define yase_medium_skill "skills\role_skill\ziqidonglai%d.png"
#define yase_small_skill "skills\role_skill\ziqidonglai%d.png"


#define houyi_big_skill "skills\role_skill\ziqidonglai%d.png"
#define houyi_medium_skill "skills\role_skill\ziqidonglai%d.png"
#define houyi_small_skill "skills\role_skill\ziqidonglai%d.png"

#define daji_big_skill_num 13
#define daji_medium_skill_num 13
#define daji_small_skill_num 13


#define houyi_big_skill_num 13
#define houyi_medium_skill_num 13
#define houyi_small_skill_num 13


#define yase_big_skill_num 13
#define yase_medium_skill_num 13
#define yase_small_skill_num 13


#define map1_buff_num 8
USING_NS_CC;
extern hero_role HeroRole;
GameController* GameController::createScene()
{
	return (GameController*)GameController::create();
}
void GameController::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

bool GameController::init()
{
	//������ͼ
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_tileMap = TMXTiledMap::create("map/map.tmx");
	addChild(_tileMap, 0, 100);

	//����Ӣ�۵�λ��
	createHero();


	createBuff();  //����Buff

				   //����CannonFodder     �����  ʵ�ָ�һ��ʱ�䴴��һ���ڻ����������Ź̶�·��ǰ��  

	createCannonFodder();  //�����ڻ�


	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->schedule(schedule_selector(GameController::updateGame), 0.2f);
	return true;
	
}

void GameController::onEnter()  //  ��Ҫ����ע����̺�����¼�������
{

	Layer::onEnter();

	//ע���¼�������  ��������ߵ�λ���ƶ�Ӣ��
	auto moveHeroListener = EventListenerMouse::create();
	moveHeroListener->onMouseDown = [this](Event *e)
	{
		EventMouse* em = (EventMouse*)e;
		mouse_down = em->getLocation();
		mouse_down = Director::getInstance()->convertToGL(mouse_down);
		ismousedown = true;
		//mouse_down = location+repair;
	};
	moveHeroListener->onMouseUp = [this](Event *e)
	{
		EventMouse* em = (EventMouse*)e;

		if (ismousedown)
		{
			auto heroPostion = hero1->getPosition();
			heroPostion = Director::getInstance()->convertToGL(heroPostion);
			auto move = mouse_down - heroPostion;
			//��Ҫ��һ��˲ʱ�����þ��鳯���˶�����
			Action*moveaction = hero1->runAction(MoveBy::create(10,move));
			moveaction->setTag(1);
		}
		ismousedown = false;

	};

	////ע���¼�������  ��������  hero�����ͷż���
	auto releaseSkillListener = EventListenerKeyboard::create();
	releaseSkillListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_W)    //�Ŵ��� 
		{
			hero1->attackTrick(bigSkillFormat, bigSkillNum);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)    //������ 
		{
			hero1->attackTrick(mediumSkillFormat, mediumSkillNum);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)    //��С�� 
		{
			hero1->attackTrick(smallSkillFormat,smallSkillNum);
		}

	};
	releaseSkillListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event)
	{
		log("Key with keycode %d released", keyCode);
	};

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(moveHeroListener, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(releaseSkillListener, this);

}

void GameController::createHero()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	switch (HeroRole)       //����Ӣ��
	{
	case daji:
	{
		hero1 = (Hero*)Hero::create(hero_daji);
		bigSkillFormat = daji_big_skill;
		mediumSkillFormat = daji_medium_skill;
		smallSkillFormat = daji_small_skill;

		bigSkillNum = daji_big_skill_num;
		mediumSkillNum= daji_medium_skill_num;   
		smallSkillNum= daji_small_skill_num;   
		break;
	}
	case yase:
	{
		hero1 = (Hero*)Hero::create(hero_yase);
		bigSkillFormat = yase_big_skill;
		mediumSkillFormat = yase_medium_skill;
		smallSkillFormat = yase_small_skill;

		bigSkillNum = yase_big_skill_num;
		mediumSkillNum = yase_medium_skill_num;
		smallSkillNum = yase_small_skill_num;
		break;
	}
	case houyi:
	{
		hero1 = (Hero*)Hero::create(hero_houyi);
		bigSkillFormat = houyi_big_skill;
		mediumSkillFormat = houyi_medium_skill;
		smallSkillFormat = houyi_small_skill;

		bigSkillNum = houyi_big_skill_num;
		mediumSkillNum = houyi_medium_skill_num;
		smallSkillNum = houyi_small_skill_num;
		break;
	}
	default:break;
	}
	hero1->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.5));
	this->addChild(hero1);
}

void GameController::createBuff()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < map1_buff_num; i++)
	{
		Buff *buff = new Buff();// ("npc/buff1.png");
		buff->initWithFile("npc/buff1.png");
		buff->setPosition(Vec2(origin.x + visibleSize.width * (0.1*i), origin.y + visibleSize.height * 0.2));// ����Ұ�ֵ�λ��  �����ڳ�ʼλ������
		this->addChild(buff);    //�ӵ�����
		BuffVector.pushBack(buff);   //�ӵ�������
	}
}

void GameController::createCannonFodder() //�����ڻ�
{




}

void GameController::createTower()    //������
{

}


void  GameController::updateGame(float dt)  //ˢ�º���
{
	CannonFodderMoving();  //���ڻ��߼���   
	if (isHeroDeath())
	{
		//������������
	}
	if (isGameOver())
	{
		//����ս������
	}
	if (isCannonFodderDeath())
	{
		//���ڻҴ��������Ƴ�
	}


}

void GameController::onExit()
{
	Layer::onExit();
	log("HelloWorld onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}





void GameController::CannonFodderMoving()
{

}
void GameController::backHome()  //�س�
{




}

bool GameController::isHeroDeath()          //�ж�Ӣ���Ƿ�����
{
	if (hero1->bloodnum < 0)
		return true;
	else
		return false;
}
bool GameController::isGameOver()       //�ж���Ϸ�Ƿ����
{
	//�жϴ�Ӫ�����Ƿ���
	//��������˵
	return true;
}
bool GameController::isCannonFodderDeath()//�ж��ڻ��Ƿ�����
{
	return true;
}
bool GameController::isBuffDeath()//�ж�Buff�Ƿ�����
{
	return true;
}
bool GameController::isHeroResurrection()//Ӣ�۸����
{
	return true;
}
bool GameController::isTowerPushed()   //�ж����Ƿ���
{
	return true;
}



