#pragma once
//http://www.87g.com/zixun/16123.html    һ������   ������ҫӢ��ͼ

//��SelectHero�����л���ѡ��Ӣ�۵Ľ��棬   �û����ĳ��Ӣ�ۣ�ͨ��һ���ص�����������һ��hero_role������
//Ȼ���������������ж�   ���ݲ�ͬ�������Ӣ��
#include"cocos2d.h"
#include<vector>
#define hero_moonGoddess_attack "hero/change/attck/1047-6a75dcb1-0%d00%d.png"

using namespace std;
USING_NS_CC;
typedef enum {
	shooter = 0,    //����
	Master = 1,     //��ʦ
	auxiliary = 2,   //����
	Assassin=3,       //�̿�
	tank=4			 //̹��
}hero_type;
//typedef enum {
//	bestteammate = 0,    //  ��Ѷ���
//	slaughter = 1,     //   Ѫ���ȷ�
//	lifewinner = 2,   //    ����Ӯ��
//       //��������������
//}achievement_type;
//typedef enum {
//	moonGoddess = 0,    //槼�
//	houyi = 1,     //����
//	yase = 2,   //��ɪ
//
//}hero_role;
class Hero:public Sprite
{
	
public:
	ProgressTimer* blood;   //Ѫ��
	int bloodNum;
	//vector<achievement_type> Achievement;  //����õĳɾ�
	hero_type type;                //Ӣ���������ֽ�ɫ  
	//hero_role role;
	int money;       //����
	float speed;		//�����ƶ��ٶ�
	Vec2 initPos;
	int commonAttack; //��ͨ����ֵ
	virtual bool init();   //  Ӣ�۵��ܵĿ���
	bool attackTrick(const char *format,int num);   //  ����
	virtual bool checkIsAttack();  //����Ƿ��ܵ�����   
	bool isHeroWalking;
	int currentPos;
	float getHeroSpeed();	     //�����ٶ�
	void initBloodBar();
	void minusBlood(int num);
	void attackEnemy(int dir);
	void updateHeroSpeed(float newspeed);
	void initHeroAttr(int _money, float _speed,int _blood,int _commonAttack) {
		money = _money;
		speed = _speed;
		bloodNum = _blood;
		commonAttack = _commonAttack;
	}
	//CREATE_FUNC(Hero);   �����벻��д������Ȼ�޷�createӢ��
};

