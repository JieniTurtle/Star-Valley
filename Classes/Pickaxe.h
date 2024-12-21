#ifndef __PICKAXE_H__
#define __PICKAXE_H__

#include "cocos2d.h"
#include "global.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
#define StoneID 5564  //��ͨʯ��
#define GemID 5530  //��ʯ��
#define GemExp 20
// ������
class Pickaxe : public cocos2d::Layer {
public:
    bool ispickaxe;//�Ƿ���
    ui::CheckBox* pickaxecheckbox;//��ѡ��
    Vec2 mapPosition;//��ͼλ��
    int maplength;//��ͼ����
    int mapwidth;//��ͼ���
    Size visibleSize;//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    int mapWidth;  // �����ש����
    int mapHeight; // �����ש����
    int tileWidth; // ������ש�����ؿ��
    int tileHeight; // ������ש�����ظ߶�
    virtual bool init(TMXTiledMap* map);
    void setpickaxecheckbox();//���ó�ͷ��ѡ��

    static Pickaxe* create(TMXTiledMap* map);
    void pickaxeListenerMouse(TMXTiledMap* map);//���ؼ�������

};


#endif

