
#ifndef __CARROT_H__
#define __CARROT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
// ��
class Carrot : public cocos2d::Scene {
public:
    bool iscarrot;//�Ƿ���С��
    int carrotnum;//С������
    ui::CheckBox* carrotcheckbox;//���Ӹ�ѡ��
    Vec2 mapPosition;//��ͼλ��
    int maplength;//��ͼ����
    int mapwidth;//��ͼ���
    Size visibleSize;//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    int mapWidth;  // �����ש����
    int mapHeight; // �����ש����
    int tileWidth; // ������ש�����ؿ��
    int tileHeight; // ������ש�����ظ߶�
    //
    virtual bool init(TMXTiledMap* map);
    void setcarrotcheckbox();//���ó�ͷ��ѡ�� 
    static Carrot* create(TMXTiledMap* map);
    //void wheatListenerMouse(TMXTiledMap* map);//���ؼ�������
    void showcarrotnum();//��Ļ��ʾ��������
};
#endif
