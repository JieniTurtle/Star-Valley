#ifndef __MINERAL_H__
#define __MINERAL_H__

#include "cocos2d.h"
#include "global.h"

#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2

// ������
class Mineral : public cocos2d::Layer {
public:

    ui::CheckBox* stonecheckbox;//stone��ѡ��
    ui::CheckBox* gemcheckbox;//gem��ѡ��

    int stonenum= stone_number;//stone����
    int gemnum = mineral_number;//gem����

    Vec2 mapPosition;//��ͼλ��
    int maplength;//��ͼ����
    int mapwidth;//��ͼ���
    Size visibleSize;//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    int mapWidth;  // �����ש����
    int mapHeight; // �����ש����
    int tileWidth; // ������ש�����ؿ��
    int tileHeight; // ������ש�����ظ߶�
    virtual bool init(TMXTiledMap* map);
    void setcheckbox();//���ø�ѡ��

    void showstonenum();//��ʾ����
    void showgemnum();
 
    static Mineral* create(TMXTiledMap* map);

};


#endif
