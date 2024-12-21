#include "Wood.h"
#include "SimpleAudioEngine.h"

bool Wood::init(TMXTiledMap* map) {
    iswood = 0;
   
    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setwoodcheckbox();//���ó�ͷ��ѡ��
    showwoodnum();//��ʾ��������
    //wheatListenerMouse(map);
    return true;
}

void  Wood::setwoodcheckbox() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //������ͷͼ��
    woodcheckbox = ui::CheckBox::create("wood1.png", "wood2.png");
    woodcheckbox->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height * 6 / 10)); // ����λ��

    this->addChild(woodcheckbox);


}

Wood* Wood::create(TMXTiledMap* map) {

    Wood* ret = new Wood();
    if (ret && ret->init(map)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}



void Wood::showwoodnum() {
    // ������ǩ����ӵ�������
    auto label = Label::createWithTTF(std::to_string(wood_number), "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height * 5.5 / 10)); // ���ñ�ǩ��ʾ��λ��
    this->addChild(label, 1);

    // ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    this->schedule([this, label](float dt) {
        label->setString(std::to_string(wood_number));
        }, "update_label_key");
}