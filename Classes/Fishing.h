#ifndef __FISHING_H__
#define __FISHING_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"Maincharacter.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
#define AbleFishing 1403
// �������
class Fishing : public cocos2d::Layer {
public:
    bool isfishing;//�Ƿ��fishing
    bool fishingcondition;//�Ƿ�Ϊ����״̬
    ui::CheckBox* fishingcheckbox;//fishing��ѡ��
    Vec2 mapPosition;//��ͼλ��
    int maplength;//��ͼ����
    int mapwidth;//��ͼ���
    Size visibleSize;//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    int mapWidth;  // �����ש����
    int mapHeight; // �����ש����
    int tileWidth; // ������ש�����ؿ��
    int tileHeight; // ������ש�����ظ߶�
    Label* isfishingnow;//���ڵ����ǩ
    Sprite* isfishingnowtext;//ǰһ������
    int scheduleCounter;
   
    //
    virtual bool init(TMXTiledMap* map, MainCharacter* maincharacter,int& fishnum);
    void setfishingcheckbox();//����fishing��ѡ��
    void ifgainfish(int& fishnum);
    static Fishing* create(TMXTiledMap* map, MainCharacter* maincharacter, int& fishnum);
    void fishingListenerMouse(TMXTiledMap* map, MainCharacter* maincharacter, int& fishnum);//fishing��������
    void fishingprocess(TMXTiledMap* map, MainCharacter* maincharacter, int& fishnum);//ִ�е���״̬�Ķ���
    void myUpdateFunction(std::string updateKey);
    void myUpdateFunction3(int& fishnum, std::string updateKey3);
    void myUpdateFunction2(TMXTiledMap* map, MainCharacter* maincharacter, std::string updateKey);
};


#endif
