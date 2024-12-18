#ifndef __STORE_H__
#define __STORE_H__

#include "cocos2d.h"

#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
#define WheatSellPrice 10
#define MilkSellPrice 15
#define WoolSellPrice 12
#define EggSellPrice 12
#define CarrotSellPrice 10
#define SeedsBuyPrice 2
#define SeedsTwoBuyPrice 3
#define FailSellDisplayTime 0.5
extern int money;
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
    void setstorescene(int& wheatnum, int& milknum, int& woolnum, int& eggnum, int& seedsnum, int& fertilzernum, int&seedstwonum, int&carrotnum);//�����̵����
    void Store::setsell(int& wheatnum,  int& milknum, int& woolnum, int& eggnum, int& seedsnum, int& fertilzernum, int& seedstwonum, int& carrotnum);
    void Store::setbuy(int& wheatnum, int& milknum, int& woolnum, int& eggnum, int& seedsnum, int& fertilzernum, int& seedstwonum, int& carrotnum);//����
    virtual bool init(TMXTiledMap* map,int &wheatnum, int& milknum, int& woolnum, int& eggnum, int& seedsnum, int& fertilzernum, int& seedstwonum, int& carrotnum);
    void menuOpenCallback();//���̵����
    static Store* create(TMXTiledMap* map, int& wheatnum, int& milknum, int& woolnum, int& eggnum, int& seedsnum, int& fertilzernum, int& seedstwonum, int& carrotnum);
    void CloseCallback();//�ر��̵����
    void sellfail();//��ʾ����ʧ��
    void buyfail();//��ʾ����ʧ��
};
#endif