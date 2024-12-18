#ifndef __PICKAXE_H__
#define __PICKAXE_H__

#include "cocos2d.h"

#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
#define StoneID 5564  //��ͨʯ��
#define GemID 5530  //��ʯ��
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
    virtual bool init(TMXTiledMap* map, int& stonenum, int& gemnum);
    void setpickaxecheckbox();//���ó�ͷ��ѡ��

    static Pickaxe* create(TMXTiledMap* map,int&stonenum,int&gemnum);
    void pickaxeListenerMouse(TMXTiledMap* map, int& stonenum, int& gemnum);//���ؼ�������

};


#endif

