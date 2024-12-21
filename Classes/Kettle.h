#ifndef __KETTLE_H__
#define __KETTLE_H__

#include "cocos2d.h"
#include"global.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
#define HoeOverID 1753  //�������ͼ��id
#define AbleHoeID 809  //�ɸ�����ͼ��id
#define RawPlantNoWaterID 5529//��ѿͼ��idû��ˮ
#define RawPlantNoWaterTwoID 5531//��ѿͼ��idû��ˮ
#define RawPlantWaterID 5535//��ѿͼ��id��ˮ
#define RawPlantWaterTwoID 5537//��ѿͼ��id��ˮ
#define MaturePlantID 5548//����ͼ��id
#define MaturePlantTwoID 5552//����ͼ��id
//extern int MatureTime; //����ʱ��ֻ��ˮ
// ������
class Kettle : public cocos2d::Layer {
public:
    bool iskettle;//�Ƿ��ó�ͷ
    ui::CheckBox* kettlecheckbox;//��ͷ��ѡ��
    Vec2 mapPosition;//��ͼλ��
    int maplength;//��ͼ����
    int mapwidth;//��ͼ���
    Size visibleSize;//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    int mapWidth;  // �����ש����
    int mapHeight; // �����ש����
    int tileWidth; // ������ש�����ؿ��
    int tileHeight; // ������ש�����ظ߶�
    virtual bool init(TMXTiledMap* map);
    void setkettlecheckbox();//���ó�ͷ��ѡ��
    int scheduleCounter;//��ʱ��

    static Kettle* create(TMXTiledMap* map);
    void kettleListenerMouse(TMXTiledMap* map);//���ؼ�������
    //��ʱȡ��ͼ��仯
    void myUpdateFunction(Action* rebackaction, TMXLayer* tileLayer, int tileX, int tileY, std::string updateKey);
};


#endif
