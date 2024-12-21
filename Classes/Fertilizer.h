#ifndef __FERTILIZER_H__
#define __FERTILIZER_H__
#include "global.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
#define RawPlantWaterID 5535//��ѿͼ��id��ˮ
#define MaturePlantID 5548//����ͼ��id
#define RawPlantWaterTwoID 5537//��ѿͼ��id��ˮ
#define MaturePlantTwoID 5552//����ͼ��id
#define MatureTimeFertilizer 1.0f //����ʱ���з���
// ������
class Fertilizer : public cocos2d::Scene {
public:
    bool isfertilizer;//�Ƿ��÷���

    ui::CheckBox* fertilizercheckbox;//���ϸ�ѡ��
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
    void setfertilizercheckbox();//���ó�ͷ��ѡ�� 
    static Fertilizer* create(TMXTiledMap* map);
    void fertilizerListenerMouse(TMXTiledMap* map);//���ؼ�������
    void showfertilizernum();//��Ļ��ʾ��������
};
#endif

