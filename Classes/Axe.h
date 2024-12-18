#ifndef __AXE_H__
#define __AXE_H__

#include "cocos2d.h"
#include "Seeds.h"
#include "Gloves.h"
#include "Wheat.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
#define HoeOverID 1753  //�������ͼ��id
#define AbleHoeID 809  //�ɸ�����ͼ��id
#define numberOfTree 3  //��ͼ�������
#define OneTreeForWood 5  //һ�������ڼ���ľͷ
// ������
class Axe : public cocos2d::Layer {
public:
    bool isaxe;//�Ƿ��ø�ͷ
    ui::CheckBox* axecheckbox;//��ͷ��ѡ��
    Vec2 mapPosition;//��ͼλ��
    int maplength;//��ͼ����
    int mapwidth;//��ͼ���
    Size visibleSize;//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    int mapWidth;  // �����ש����
    int mapHeight; // �����ש����
    int tileWidth; // ������ש�����ؿ��
    int tileHeight; // ������ש�����ظ߶�
    virtual bool init(TMXTiledMap* map, int& woodnum);
    void setaxecheckbox();//���ó�ͷ��ѡ��

    static Axe* create(TMXTiledMap* map, int& woodnum);
    void axeListenerMouse(TMXTiledMap* map, int& woodnum);//���ؼ�������

};


#endif
