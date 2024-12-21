#ifndef __SEEDTOOLS_H__
#define __SEEDTOOLS_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "global.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
#define HoeOverID 1753  //�������ͼ��id
#define RawPlantID 5529//��ѿͼ��idû��ˮ
#define MaturePlantID 5548//����ͼ��id
#define MatureTime 2.0f //����ʱ��
extern int NoWaterDieTime; //û�н�ˮ�����ʱ��
#define AbleHoeID 809  //�ɸ�����ͼ��id
// ������
class Seeds : public cocos2d::Scene {
public:
    bool isseeds;//�Ƿ�������

    ui::CheckBox* seedscheckbox;//���Ӹ�ѡ��
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
    int scheduleCounter;
    //
    virtual bool init(TMXTiledMap* map);
    void setseedscheckbox();//���ó�ͷ��ѡ�� 
    static Seeds* create(TMXTiledMap* map);
    void seedsListenerMouse(TMXTiledMap* map);//���ؼ�������
    void showseedsnum();//��Ļ��ʾ��������
    //���Ⱥ������ж��Ƿ�ԭ���أ��н�ˮ����ʱȡ���ö���
    void Seeds::myUpdateFunction(Action* rebackaction, TMXLayer* tileLayer, int tileX, int tileY, std::string updateKey);
}; 
#endif
