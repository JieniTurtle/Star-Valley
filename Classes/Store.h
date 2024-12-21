#ifndef __STORE_H__
#define __STORE_H__

#include "cocos2d.h"
#include "global.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2

#define MilkSellPrice 15
#define WoolSellPrice 12
#define EggSellPrice 12


#define FailSellDisplayTime 0.5

// ������
class Store : public cocos2d::Layer {
public:

    Vec2 mapPosition;//��ͼλ��
    int maplength;//��ͼ����
    int mapwidth;//��ͼ���
    Size visibleSize;//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    int mapWidth;  // �����ש����
    int mapHeight; // �����ש����
    int tileWidth; // ������ש�����ؿ��
    int tileHeight; // ������ש�����ظ߶�
    MenuItemImage* openItem;//�򿪰�ť
    MenuItemImage* closeItem;//�رհ�ť
    MenuItemImage* wheatsellItem;//С��������ť
    MenuItemImage* carrotsellItem;//carrot������ť
    MenuItemImage* milksellItem;//ţ��������ť
    MenuItemImage* woolsellItem;//��ë������ť
    MenuItemImage* eggsellItem;//����������ť
    MenuItemImage* seedsbuyItem;//seeds������ť
    MenuItemImage* seedstwobuyItem;//seedstwo������ť
    Label* woolsellLabel;//��ë�۸��ǩ
    Label* eggsellLabel;//�����۸��ǩ
    Label* wheatsellLabel;//С��۸��ǩ
    Label* carrotsellLabel;//carrot�۸��ǩ
    Label* milksellLabel;//ţ�̼۸��ǩ
    Label* seedsbuyLabel;//seeds�۸��ǩ
    Label* seedstwobuyLabel;//seedstwo�۸��ǩ
    Layer* StoreScene;//�̵����
    Menu* closemenu;//�رղ˵�
    Sprite* emptystoragesprite;//�ջ���
    //
    void setopenitem();//���ô򿪰�ť
    void setstorescene();//�����̵����
    void Store::setsell();
    void Store::setbuy();//����
    virtual bool init(TMXTiledMap* map);
    void menuOpenCallback();//���̵����
    static Store* create(TMXTiledMap* map);
    void CloseCallback();//�ر��̵����
    void sellfail();//��ʾ����ʧ��
    void buyfail();//��ʾ����ʧ��
    void pricechange();
};
#endif