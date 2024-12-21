#ifndef __FARMPRODUCT_H__
#define __FARMPRODUCT_H__

#include "cocos2d.h"
#include "global.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
#define HoeOverID 1753  //�������ͼ��id
#define AbleHoeID 809  //�ɸ�����ͼ��id
#define RawPlantNoWaterID 5529//��ѿͼ��idû��ˮ
#define RawPlantWaterID 5535//��ѿͼ��id��ˮ
#define MaturePlantID 5548//����ͼ��id
#define MatureTime 8.0f //����ʱ��ֻ��ˮ
// ������
class FarmProduct : public cocos2d::Layer {
public:
  
    ui::CheckBox* milkcheckbox;//ţ�̸�ѡ��
    ui::CheckBox* eggcheckbox;//������ѡ��
    ui::CheckBox* woolcheckbox;//��ë��ѡ��
    ui::CheckBox* fishcheckbox;//yu��ѡ��

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

    void showmilknum();//��ʾ����
    void showwoolnum();
    void showeggnum();
    void showfishnum();
    static FarmProduct* create(TMXTiledMap* map);
   
};


#endif