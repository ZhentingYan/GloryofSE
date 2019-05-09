#include"Core/Controller/GameController.h"
#define hero_daji "hero/change/zhan/0649-3ea35add-00000.png"
#define hero_houyi "hero/houyi.jpg"
#define hero_yase "hero/yase.jpg"

#define hero_daji_pao ""
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
	createHero();

	_tileMap = TMXTiledMap::create("map/map.tmx");
	addChild(_tileMap, 0, 100);
	TMXObjectGroup* group = _tileMap->getObjectGroup("Objects");
	spawnPoint = group->getObject("Player1");
	////����Ӣ��
	//createHero();    //����Ӣ��
	//hero1->setPosition(Vec2(origin.x + visibleSize.width * 0.2, origin.y + visibleSize.height * 0.2));
	//addChild(hero1, 1)
	_collidable = _tileMap->getLayer("Collidable");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	hero1->setPosition(Vec2(x, y));
	addChild(hero1);
	this->setViewpointCenter(hero1->getPosition());

	//����Ӣ�۵�λ��


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
	/*
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
	*/
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
	//eventDispatcher->addEventListenerWithSceneGraphPriority(moveHeroListener, this);
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
		/*
		bigSkillFormat = daji_big_skill;
		mediumSkillFormat = daji_medium_skill;
		smallSkillFormat = daji_small_skill;
		bigSkillNum = daji_big_skill_num;
		mediumSkillNum= daji_medium_skill_num;   
		smallSkillNum= daji_small_skill_num;   
		*/
		hero1->isHeroWalking = false;
		hero1->initHeroAttr(100, 2.0);
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
void GameController::setViewpointCenter(Vec2 position)
{
	log("setViewpointCenter");

	log("position (%f ,%f) ", position.x, position.y);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//���Է�ֹ����ͼ��߳�����Ļ֮�⡣
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	//���Է�ֹ����ͼ�ұ߳�����Ļ֮�⡣
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//��Ļ���ĵ�
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//ʹ���鴦����Ļ���ģ��ƶ���ͼĿ��λ��
	Vec2 pointB = Vec2(x, y);
	log("Ŀ��λ�� (%f ,%f) ", pointB.x, pointB.y);

	//��ͼ�ƶ�ƫ����
	Vec2 offset = pointA - pointB;
	log("offset (%f ,%f) ", offset.x, offset.y);
	this->setPosition(offset);

}

Vec2 GameController::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}
int GameController::getNowPointDir(Vec2 newpoint)
{
	int thisdir = rigth_down; //Ĭ��Ϊ����
							  //�����ƶ�����
	float center_x, center_y, player_x, player_y;
	int move_x, move_y;
	//����NPC����״̬
	Size origin = Director::getInstance()->getVisibleSize();
	Size size = Director::getInstance()->getWinSize();

	center_x = size.width / 2;
	center_y = size.height / 2;
	player_x = hero1->getPositionX();
	player_y = hero1->getPositionY();

	move_x = (int)(player_x - newpoint.x);
	move_y = (int)(player_y - newpoint.y - 20);

	if (move_x >= 10 && move_y <= -10)
	{
		//����
		thisdir = left_up;
	}
	else if (move_x >= 10 && move_y >= 10)
	{
		//����
		thisdir = left_down;
	}
	else if (move_x <= -10 && move_y <= -10)
	{
		//����
		thisdir = rigth_up;
	}
	else if (move_x <= -10 && move_y >= 10)
	{
		//����
		thisdir = rigth_down;
	}
	else if (move_x>-10 && move_x<10 && move_y>0)
	{
		//��
		thisdir = down;
	}
	else if (move_x>-10 && move_x<10 && move_y<0)
	{
		//��
		thisdir = up;
	}
	else if (move_x>0 && move_y>-10 && move_y<10)
	{
		//��
		thisdir = lefts;
	}
	else if (move_x<0 && move_y>-10 && move_y<10)
	{
		//��
		thisdir = rigth;
	}
	return thisdir;
}
void GameController::setPlayerPosition(Vec2 position) {
	//hero1->stopAllActions();


	//�����ص�����ת��Ϊ��Ƭ����
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	//�����Ƭ��GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);//ֻ����ײ��ʱ
	log("new Gid %d", tileGid);
	if (tileGid > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//������ײ
		hero1->stopAllActions();
		return;
	}
	//�ƶ�����
	hero1->setPosition(position);
	//������ͼ
	this->setViewpointCenter(hero1->getPosition());
	//hero1->stopAllActions();

}

/*
void GameScene::menuCloseCallback(Ref* pSender)
{
//Close the cocos2d-x game scene and quit the application
Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif

}
*/

bool GameController::onTouchBegan(Touch* touch, Event* event)
{

	log("onTouchBegan");
	return true;
}

void GameController::onTouchMoved(Touch *touch, Event *event)
{

	log("onTouchMoved");
}

void GameController::onTouchEnded(Touch *touch, Event *event)
{
	if (hero1->isHeroWalking == true)
		return;
	hero1->isHeroWalking = true;
	hero1->stopAllActions();
	log("onTouchEnded");
	//�����OpenGL����
	Vec2 touchLocation = touch->getLocation();
	//ת��Ϊ��ǰ���ģ������ϵ
	touchLocation = this->convertToNodeSpace(touchLocation);

	Vec2 playerPos = hero1->getPosition();
	Vec2 diff = touchLocation - playerPos;
	int newDir = getNowPointDir(touchLocation);
	Animation* animation = Animation::create();
	for (int i = 0; i <= 7; i++)
	{
		__String *frameName = __String::createWithFormat("hero/change/pao/2154-e1380841-0%d00%d.png", newDir, i);
		log("frameName = %s", frameName->getCString());
		//SpriteFrame *spriteFrame = SpriteFrame::
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setDelayPerUnit(0.15f);
	animation->setRestoreOriginalFrame(false);
	Animate* action = Animate::create(animation);
	hero1->runAction(RepeatForever::create(action));
	//log(_tileMap->getTileSize().height);
	Vec2 tileCoord = this->tileCoordFromPosition(touchLocation);
	//�����Ƭ��GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);//ֻ����ײ��ʱ
	log("new Gid %d", tileGid);
	if (tileGid > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//������ײ
		hero1->isHeroWalking = false;
		hero1->stopAllActions();
		return;
	}
	float speed = hero1->getHeroSpeed();
	float x1 = playerPos.x;
	float y1 = playerPos.y;
	float x2 = touchLocation.x;
	float y2 = touchLocation.y;
	float dif_x = x1 - x2;
	float dif_y = y1 - y2;
	float dis = sqrt(dif_x*dif_x + dif_y * dif_y);
	log("dis is %f", dis);
	hero1->runAction(MoveTo::create(dis*speed / 100, touchLocation));
	/*
	while (abs(diff.x) > 0 || abs(diff.x) > 0) {
	if (abs(diff.x) > abs(diff.y)) {
	if (diff.x > 0) {
	playerPos.x += 1.0;
	diff.x -= 1.0;
	if (diff.x < 0)
	diff.x = 0;
	//hero1->runAction(FlipX::create(false));
	}
	else {
	playerPos.x -= 1.0;
	diff.x += 1.0;
	if (diff.x > 0)
	diff.x = 0;
	//hero1->runAction(FlipX::create(true));
	}
	}
	else {
	if (diff.y > 0) {
	playerPos.y += 1.0;
	diff.y -= 1.0;
	if (diff.y < 0)
	diff.y = 0;
	}
	else {
	playerPos.y -= 1.0;
	diff.y += 1.0;
	if (diff.y > 0)
	diff.y = 0;
	}
	}

	hero1->setPosition(playerPos);
	//������ͼ
	this->setViewpointCenter(hero1->getPosition());
	//this->setPlayerPosition(playerPos);
	}
	*/
	//hero1->stopAllActions();
	//hero1->setPosition(playerPos);
	//������ͼ
	hero1->isHeroWalking = false;
	//hero1->stopAllActions();
	this->setViewpointCenter(hero1->getPosition());


}



