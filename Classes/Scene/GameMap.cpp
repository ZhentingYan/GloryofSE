#include"Scene/GameMap.h"

#define map1_buff_num 8
//extern hero_role HeroRole;
GameMap* GameMap::createScene()
{
	return (GameMap*)GameMap::create();
}

//���򽻻�
bool GameMap::init()
{
	//������ͼ
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_tileMap = TMXTiledMap::create("map/map.tmx");
	addChild(_tileMap, 0, 100);

	//����Ӣ�۵�λ��
	//setHero();
	

	createBuff();  //����Buff

				   //����CannonFodder     �����  ʵ�ָ�һ��ʱ�䴴��һ���ڻ����������Ź̶�·��ǰ��  

	createCannonFodder();  //�����ڻ�


	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->schedule(schedule_selector(GameMap::updateGame), 0.2f);
	return true;

}
void GameMap::setHero()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	hero1->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.5));
	this->addChild(hero1);
}

void GameMap::createBuff()
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

void GameMap::createCannonFodder() //�����ڻ�
{




}

void GameMap::onEnter()  //  ��Ҫ����ע����̺�����¼�������
{

	Layer::onEnter();
	setHero();
	
	//ע���¼�������  ��������ߵ�λ���ƶ�Ӣ��
	auto moveHeroListener= EventListenerMouse::create();
	moveHeroListener->onMouseDown = [this](Event *e)
	{
		EventMouse* em = (EventMouse*)e;
		mouse_down = em->getLocation();
		mouse_down = Director::getInstance()->convertToGL(mouse_down);
		ismousedown =true;
		//mouse_down = location+repair;
	};
	moveHeroListener->onMouseUp= [this](Event *e)
	{
		EventMouse* em = (EventMouse*)e;

		if (ismousedown) 
		{
			//��Ҫ��һ��˲ʱ�����þ��鳯���˶�����
			Action*moveaction =hero1->runAction(MoveTo::create(10, Vec2(mouse_down.x, mouse_down.y)));
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
			//hero1->attackBigTrick();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)    //������ 
		{
			//hero1->attackMediumTrick();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)    //��С�� 
		{
			//hero1->attackSmallTrick();
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

void GameMap::updateGame(float dt)  //ˢ�º���
{
	
	

}

void GameMap::onExit()
{
	Layer::onExit();
	log("HelloWorld onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

bool GameMap::onTouchBegan(Touch *touch, Event*unused_event)
{
	log("OnTouchBegan");
	return true;

}
void GameMap::onTouchEnded(Touch *touch, Event*unused_event)
{
	log("OnTouchMoved");

}
void GameMap::onTouchMoved(Touch *touch, Event*unused_event)
{
	log("onTouchEnded");
	//���OpenGL����
	Vec2 touchLocation = touch->getLocation();
	//log("touchLocation (%f ,%f) ", touchLocation.x, touchLocation.y);

	Vec2 HeroPos = hero1->getPosition();
	Vec2 diff = touchLocation - HeroPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			HeroPos.x += _tileMap->getTileSize().width;
			hero1->runAction(FlipX::create(false));
		}
		else {
			HeroPos.x -= _tileMap->getTileSize().width;
			hero1->runAction(FlipX::create(true));
		}
	}
	else {
		if (diff.y > 0) {
			HeroPos.y += _tileMap->getTileSize().height;
		}
		else {
			HeroPos.y -= _tileMap->getTileSize().height;
		}
	}
	//log("HeroPos (%f ,%f) ", HeroPos.x, HeroPos.y);
	hero1->setPosition(HeroPos);



}
