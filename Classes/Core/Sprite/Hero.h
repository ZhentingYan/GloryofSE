#pragma once
//http://www.87g.com/zixun/16123.html    һ������   ������ҫӢ��ͼ

//��SelectHero�����л���ѡ��Ӣ�۵Ľ��棬   �û����ĳ��Ӣ�ۣ�ͨ��һ���ص�����������һ��hero_role������
//Ȼ���������������ж�   ���ݲ�ͬ�������Ӣ��
#include"cocos2d.h"
#include<vector>
//#include"Scene/SelectHero.h"
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
//	daji = 0,    //槼�
//	houyi = 1,     //����
//	yase = 2,   //��ɪ
//
//}hero_role;
class Hero:public Sprite
{
private:
	Sprite * blood;   //Ѫ��
	//int blood;
	//vector<achievement_type> Achievement;  //����õĳɾ�
	hero_type type;                //Ӣ���������ֽ�ɫ  
	//hero_role role;
	int money;       //����
public:
    //static Hero * createSprite();
	//Hero(hero_role role);  //���ع��캯��
	
	virtual bool init();   //  Ӣ�۵��ܵĿ���
	virtual bool attack();   //����
	virtual bool checkIsAttack();  //����Ƿ��ܵ�����
	virtual void move();           //�ƶ�
	virtual void backHome();     //�س�
	
	//CREATE_FUNC(Hero);
};

