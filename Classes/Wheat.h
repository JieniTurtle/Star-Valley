#ifndef __WHEAT_H__
#define __WHEAT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
// С����
class Wheat : public cocos2d::Scene {
public:
    bool iswheat;//�Ƿ���С��
    int wheatnum;//С������
    ui::CheckBox* wheatcheckbox;//���Ӹ�ѡ��
    Vec2 mapPosition;//��ͼλ��
    int maplength;//��ͼ����
    int mapwidth;//��ͼ���
    Size visibleSize;//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    int tempotileX, tempotileY;
    TMXLayer* tempotileLayer;
    int mapWidth;  // �����ש����
    int mapHeight; // �����ש����
    int tileWidth; // ������ש�����ؿ��
    int tileHeight; // ������ש�����ظ߶�
    //
    virtual bool init(TMXTiledMap* map);
    void setwheatcheckbox();//���ó�ͷ��ѡ�� 
    static Wheat* create(TMXTiledMap* map);
   //void wheatListenerMouse(TMXTiledMap* map);//���ؼ�������
    void showwheatnum();//��Ļ��ʾ��������
};
#endif
