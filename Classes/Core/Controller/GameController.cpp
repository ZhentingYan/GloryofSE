#include"Core/Controller/GameController.h"
#define hero_moonGoddess "hero/change/zhan/0649-3ea35add-00000.png"
#define hero_houyi "hero/houyi.jpg"
#define hero_yase "hero/yase.jpg"

#define hero_moonGoddess_pao " "
#define hero_moonGoddess_attack "hero\change\attck\0649-3ea35add-0%d00%d.png"
#define moonGoddess_big_skill "skills\role_skill\ziqidonglai%d.png"
#define moonGoddess_medium_skill "skills\role_skill\ziqidonglai%d.png"
#define moonGoddess_small_skill "skills\role_skill\ziqidonglai%d.png"

#define yase_big_skill "skills\role_skill\ziqidonglai%d.png"
#define yase_medium_skill "skills\role_skill\ziqidonglai%d.png"
#define yase_small_skill "skills\role_skill\ziqidonglai%d.png"


#define houyi_big_skill "skills\role_skill\ziqidonglai%d.png"
#define houyi_medium_skill "skills\role_skill\ziqidonglai%d.png"
#define houyi_small_skill "skills\role_skill\ziqidonglai%d.png"

#define moonGoddess_big_skill_num 13
#define moonGoddess_medium_skill_num 13
#define moonGoddess_small_skill_num 13


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
	//创建地图
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	createHero();

	_tileMap = TMXTiledMap::create("map/map.tmx");
	addChild(_tileMap, 0, 100);
	TMXObjectGroup* group = _tileMap->getObjectGroup("Objects");
	auto spawnPoint = group->getObject("Player1");
	_collidable = _tileMap->getLayer("Collidable");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	log("x is %f y is %f", x,y);
	hero1->initPos = Vec2(x, y);
	hero1->setPosition(Vec2(x, y));
	hero1->initBloodBar();
	spawnPoint = group->getObject("fieldMonster1");
	 x = spawnPoint["x"].asFloat();
	 y = spawnPoint["y"].asFloat();
	 log("x is %f y is %f", x,y);
	monster1 = (fieldMonster*)fieldMonster::create("monster/monsterofField_1.png");
	monster1->initPos = Vec2(x, y);
	monster1->setPosition(Vec2(x, y));
	spawnPoint = group->getObject("fieldMonster2");
	 x = spawnPoint["x"].asFloat();
	 y = spawnPoint["y"].asFloat();
	monster2 = (fieldMonster*)fieldMonster::create("monster/monsterofField_2.png");
	monster2->initPos = Vec2(x, y);
	monster2->setPosition(Vec2(x, y));
	monster1->initMonsterAttr(); //初始化属性，相当于构造函数 仍需更改其他！
	monster2->initMonsterAttr();
	addChild(monster1,100);
	addChild(monster2,200);
	addChild(hero1,300);
	this->setViewpointCenter(hero1->getPosition());
	//createBuff();  //创建Buff

				   //创建CannonFodder     简单起见  实现隔一段时间创建一队炮灰让他们沿着固定路径前进  
	//createCannonFodder();  //创建炮灰
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	//log("monster pos %f,%f", monster1->getPositionX(), monster1->getPositionY());
	this->schedule(schedule_selector(GameController::updateGame), 0.01f);
	return true;
	
}

void GameController::onEnter()  //  主要用来注册键盘和鼠标事件监听器
{

	Layer::onEnter();
	////注册事件监听器  监听键盘  hero可以释放技能
	auto releaseSkillListener = EventListenerKeyboard::create();
	/*
	releaseSkillListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_W)    //放大招 
		{
			hero1->attackTrick(bigSkillFormat, bigSkillNum);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)    //放中招 
		{
			hero1->attackTrick(mediumSkillFormat, mediumSkillNum);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)    //放小招 
		{
			hero1->attackTrick(smallSkillFormat,smallSkillNum);
		}

	};
	*/
	releaseSkillListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_W) {
			//换成clientPlayer
			clientPlayerAttack();
		}
		log("Key with keycode %d released", keyCode);
	};

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

	eventDispatcher->addEventListenerWithSceneGraphPriority(releaseSkillListener, this);

}
void GameController::clientPlayerAttack() {
	//换成clientPlayer,加死亡判断；
	hero1->attackEnemy(getAttackDir(hero1->currentPos));//播放攻击动画
	auto monster1Hit = checkHit(hero1->currentPos, getNowPointDir(monster1->getPosition()));
	auto monster2Hit = checkHit(hero1->currentPos, getNowPointDir(monster1->getPosition()));
	
	if (monster1Hit) 
		if(monster1->attack_rect->containsPoint(hero1->getPosition()))
			monster1->minusBlood(hero1->commonAttack);
	
	if (monster2Hit)
		if (monster2->attack_rect->containsPoint(hero1->getPosition()))
			monster2->minusBlood(hero1->commonAttack);
}
void GameController::collidableCheck()
{
	//日后改成clientPlayer
		auto pos = hero1->getPosition();
		Vec2 tileCoord = this->tileCoordFromPosition(pos);
		//获得瓦片的GID
		int tileGid = _collidable->getTileGIDAt(tileCoord);//只有碰撞层时
		if (tileGid > 0 && lastCollidablePos!=pos) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//提醒碰撞
			hero1->stopAllActions();
			//thisCollidableCheck = false;
			lastCollidablePos = pos;
		}
	}


/* WASD
Key with keycode 146 released
Key with keycode 124 released
Key with keycode 142 released
Key with keycode 127 released
*/
void GameController::createHero()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	switch (HeroRole)       //创建英雄
	{
	case moonGoddess:
	{
		hero1 = (Hero*)Hero::create(hero_moonGoddess);
		/*
		bigSkillFormat = moonGoddess_big_skill;
		mediumSkillFormat = moonGoddess_medium_skill;
		smallSkillFormat = moonGoddess_small_skill;
		bigSkillNum = moonGoddess_big_skill_num;
		mediumSkillNum= moonGoddess_medium_skill_num;   
		smallSkillNum= moonGoddess_small_skill_num;   
		*/
		hero1->isHeroWalking = false;
		hero1->initHeroAttr(100, 1.0,100,10);
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
	//this->addChild(hero1);
}

void GameController::createBuff()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < map1_buff_num; i++)
	{
		Buff *buff = new Buff();// ("npc/buff1.png");
		buff->initWithFile("npc/buff1.png");
		buff->setPosition(Vec2(origin.x + visibleSize.width * (0.1*i), origin.y + visibleSize.height * 0.2));// 设置野怪的位置  让它在初始位置生成
		this->addChild(buff);    //加到层中
		BuffVector.pushBack(buff);   //加到容器中
	}
}

void GameController::createCannonFodder() //创建炮灰
{

}

void GameController::createTower()    //创建塔
{

}


void  GameController::updateGame(float dt)  //刷新函数
{
	this->setViewpointCenter(hero1->getPosition());
	//CannonFodderMoving();  //让炮灰走几步   
	collidableCheck();
	if (monster1->checkHeroInRect(hero1, hero2) == true) {
		if (monster1->isAttacking == false) {
			monster1->isAttacking = true;
			monster1->scheduleAttack();
		}
	}
	if (monster2->checkHeroInRect(hero1, hero2) == true) {
		if (monster2->isAttacking == false) {
			monster2->isAttacking = true;
			monster2->scheduleAttack();
		}
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
void GameController::backHome()  //回城
{




}

bool GameController::isHeroDeath()          //判断英雄是否死亡
{
	if (hero1->bloodNum < 0)
		return true;
	else
		return false;
}
bool GameController::isGameOver()       //判断游戏是否结束
{
	//判断大本营的塔是否被推
	//建出来再说
	return true;
}
bool GameController::isCannonFodderDeath()//判断炮灰是否死亡
{
	return true;
}
bool GameController::isBuffDeath()//判断Buff是否死亡
{
	return true;
}
bool GameController::isHeroResurrection()//英雄复活函数
{
	return true;
}
bool GameController::isTowerPushed()   //判断塔是否被推
{
	return true;
}
void GameController::setViewpointCenter(Vec2 position)
{
	log("setViewpointCenter");

	log("position (%f ,%f) ", position.x, position.y);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//可以防止，视图左边超出屏幕之外。
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	//可以防止，视图右边超出屏幕之外。
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//屏幕中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//使精灵处于屏幕中心，移动地图目标位置
	Vec2 pointB = Vec2(x, y);
	log("目标位置 (%f ,%f) ", pointB.x, pointB.y);

	//地图移动偏移量
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
	int thisdir = rigth_down; //默认为右下
							  //计算移动数据
	float center_x, center_y, player_x, player_y;
	int move_x, move_y;
	//更新NPC方向，状态
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
		//左上
		thisdir = left_up;
	}
	else if (move_x >= 10 && move_y >= 10)
	{
		//左下
		thisdir = left_down;
	}
	else if (move_x <= -10 && move_y <= -10)
	{
		//右上
		thisdir = rigth_up;
	}
	else if (move_x <= -10 && move_y >= 10)
	{
		//右下
		thisdir = rigth_down;
	}
	else if (move_x>-10 && move_x<10 && move_y>0)
	{
		//下
		thisdir = down;
	}
	else if (move_x>-10 && move_x<10 && move_y<0)
	{
		//上
		thisdir = up;
	}
	else if (move_x>0 && move_y>-10 && move_y<10)
	{
		//左
		thisdir = lefts;
	}
	else if (move_x<0 && move_y>-10 && move_y<10)
	{
		//右
		thisdir = rigth;
	}
	return thisdir;
}
int GameController::getAttackDir(int tempDir) { //转换8个方向
	//int tempDir = getNowPointDir(newPoint);
	if (tempDir == rigth_down || tempDir == down)
		return 0;
	if (tempDir == left_down || tempDir == lefts)
		return 1;
	if (tempDir == left_up || tempDir == up)
		return 2;
	if (tempDir == rigth_up || tempDir == rigth)
		return 3;
}
void GameController::setPlayerPosition(Vec2 position) {
	//hero1->stopAllActions();


	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	//获得瓦片的GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);//只有碰撞层时
	log("new Gid %d", tileGid);
	if (tileGid > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//提醒碰撞
		hero1->stopAllActions();
		return;
	}
	//移动精灵
	hero1->setPosition(position);
	//滚动地图
	this->setViewpointCenter(hero1->getPosition());
	//hero1->stopAllActions();

}


bool GameController::onTouchBegan(Touch* touch, Event* event)
{

	log("onTouchBegan");
	return true;
}

void GameController::onTouchMoved(Touch *touch, Event *event)
{

	log("onTouchMoved");
}
bool GameController::checkHit(int standDir, int monsterDir) {
	if (monsterDir == rigth_down) {
		if (standDir == down || standDir == rigth || standDir == rigth_down)
			return true;
	}
	if (monsterDir == rigth_up) {
		if (standDir == up || standDir == rigth || standDir == rigth_up)
			return true;
	}
	if (monsterDir == rigth) {
		if (standDir == rigth_up || standDir == rigth || standDir == rigth_down)
			return true;
	}
	if (monsterDir == down) {
		if (standDir == left_down || standDir == down || standDir == rigth_down)
			return true;
	}
	if (monsterDir == lefts) {
		if (standDir == left_up || standDir == lefts || standDir == left_down)
			return true;
	}
	if (monsterDir == left_up) {
		if (standDir == left_up || standDir == lefts || standDir == up)
			return true;
	}
	if (monsterDir == left_down) {
		if (standDir == left_down || standDir == lefts || standDir == down)
			return true;
	}
	if (monsterDir == up) {
		if (standDir == up || standDir == left_up || standDir == rigth_up)
			return true;
	}
	return false;
}
void GameController::onTouchEnded(Touch *touch, Event *event)
{
	if (hero1->isHeroWalking == true)
		return;
	hero1->isHeroWalking = true;
	hero1->stopAllActions();
	log("onTouchEnded");
	//获得在OpenGL坐标
	Vec2 touchLocation = touch->getLocation();
	//转换为当前层的模型坐标系
	touchLocation = this->convertToNodeSpace(touchLocation);

	Vec2 playerPos = hero1->getPosition();
	Vec2 diff = touchLocation - playerPos;
	int newDir = getNowPointDir(touchLocation);
	hero1->currentPos = newDir;
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
	//获得瓦片的GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);//只有碰撞层时
	log("new Gid %d", tileGid);
	if (tileGid > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//提醒碰撞
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
	//log("dis is %f", dis);
	hero1->runAction(MoveTo::create(dis*speed / 100, touchLocation));
	hero1->isHeroWalking = false;
	//hero1->stopAllActions();
	//this->setViewpointCenter(hero1->getPosition()); //放到updateGame里实现顺滑滚动
}



