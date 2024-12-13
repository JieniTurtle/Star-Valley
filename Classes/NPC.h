#ifndef __NPC_SCENE_H__
#define __NPC_SCENE_H__
#include "cocos2d.h"

USING_NS_CC;

class NPC : public cocos2d::Sprite
{
public:
    //NPC����
    std::string NPCname;

    TMXTiledMap* NPCmap;//��ͼָ��
    //�����ͼָ��
    void setMap(TMXTiledMap* map) { NPCmap = map; }

    //NPC�����С
    static int NPCsize_x;
    static int NPCsize_y;

    //NPC����Ķ���˳��
    static int NPCorder_up;
    static int NPCorder_left;
    static int NPCorder_right;
    static int NPCorder_down;

    //NPC���� ����·��ʾ����NPC/filename/moveup1.png
    Animate* movestatic;
    Animate* moveup;
    Animate* moveleft;
    Animate* moveright;
    Animate* movedown;

    //���NPC�Ƿ�ѡ��
    bool ifSelected;

    //·�����
    int currentPathIndex;//·������
    float speed;//�ٶ�
    std::vector<Vec2> NPCpath;//·������

    // �����ƶ�·��
    void setPath(const std::vector<Vec2>& path);

    //NPC��ֹͼƬ·��Ϊ NPC/filename/static.png
    static NPC* create(const std::string& filename);

    //��ʼ��
    virtual bool init();

    //NPC�ƶ��ĸ���
    void updatemove(float dt);

    //NPC��ֹ�ĸ���
    void updatestatic(float dt);

    // ���Ŷ���
    void playAnimation(const std::string& direction);

    // ֹͣNPC�Ķ������ƶ�
    void stopMovement();

    // �ָ�NPC�Ķ������ƶ�
    void startMovement();

    //��������¼�
    bool NPC::onMouseDown(cocos2d::Event* event,int mapscale);

    //�ж����λ���Ƿ���NPC��
    bool JudgeClickNPC(Vec2 NPCp, Vec2 clickp);
};
#endif // __NPC_SCENE_H__;