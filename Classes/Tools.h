#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "cocos2d.h"
#include "Seeds.h"
#include "Gloves.h"
#include "Wheat.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
#define HoeOverID 1753  //�������ͼ��id
#define AbleHoeID 809  //�ɸ�����ͼ��id
// ������
class Tools: public cocos2d::Layer{
public:
    bool ishoe;//�Ƿ��ó�ͷ
    ui::CheckBox* hoecheckbox;//��ͷ��ѡ��
    Vec2 mapPosition;//��ͼλ��
    int maplength;//��ͼ����
    int mapwidth;//��ͼ���
    Size visibleSize;//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    int mapWidth ;  // �����ש����
    int mapHeight ; // �����ש����
    int tileWidth ; // ������ש�����ؿ��
    int tileHeight ; // ������ש�����ظ߶�
    virtual bool init(TMXTiledMap* map);
    void sethoecheckbox();//���ó�ͷ��ѡ��
 
    static Tools* create(TMXTiledMap* map);
    void hoeListenerMouse(TMXTiledMap* map);//���ؼ�������
   
};


#endif
