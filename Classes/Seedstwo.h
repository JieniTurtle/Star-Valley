#ifndef __SEEDSTWO_H__
#define __SEEDSTWO_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
#define HoeOverID 1753  //�������ͼ��id
#define RawPlantID 5531//��ѿͼ��idû��ˮ����1not same

#define MaturePlantID 5548//����ͼ��id
#define MatureTime 2.0f //����ʱ��
#define NoWaterDieTime 10.0f //û�н�ˮ�����ʱ��
#define AbleHoeID 809  //�ɸ�����ͼ��id
// ������
class Seedstwo : public cocos2d::Scene {
public:
    bool isseedstwo;//�Ƿ�������
    int seedstwonum;//��������
    ui::CheckBox* seedstwocheckbox;//���Ӹ�ѡ��
    Vec2 mapPosition;//��ͼλ��
    int maplength;//��ͼ����
    int mapwidth;//��ͼ���
    Size visibleSize;//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    int mapWidth;  // �����ש����
    int mapHeight; // �����ש����
    int tileWidth; // ������ש�����ؿ��
    int tileHeight; // ������ש�����ظ߶�
    int scheduleCounter;
    //
    virtual bool init(TMXTiledMap* map);
    void setseedstwocheckbox();//���ó�ͷ��ѡ�� 
    static Seedstwo* create(TMXTiledMap* map);
    void seedstwoListenerMouse(TMXTiledMap* map);//���ؼ�������
    void showseedstwonum();//��Ļ��ʾ��������
    //���Ⱥ������ж��Ƿ�ԭ���أ��н�ˮ����ʱȡ���ö���
    void Seedstwo::myUpdateFunction(Action* rebackaction, TMXLayer* tileLayer, int tileX, int tileY, std::string updateKey);
};
#endif

