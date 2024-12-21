#include "Mineral.h"

#include "SimpleAudioEngine.h"

bool Mineral::init(TMXTiledMap* map) {
   

    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setcheckbox();//���ø�ѡ��
    showstonenum();//��ʾ����
    showgemnum();

    return true;
}

void  Mineral::setcheckbox() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //����ͼ��
    stonecheckbox = ui::CheckBox::create("stone.png", "stone.png");
    stonecheckbox->setPosition(Vec2(visibleSize.width * 9.7 / 10, visibleSize.height * 4 / 10)); // ����λ��

    this->addChild(stonecheckbox);
    //����ͼ��
   gemcheckbox = ui::CheckBox::create("gem.png", "gem.png");
   gemcheckbox->setPosition(Vec2(visibleSize.width * 9.7 / 10, visibleSize.height * 3 / 10)); // ����λ��

    this->addChild(gemcheckbox);
 
}

Mineral* Mineral::create(TMXTiledMap* map) {

    Mineral* ret = new Mineral();
    if (ret && ret->init(map)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

void Mineral::showstonenum() {
    // ������ǩ����ӵ�������
    auto label = Label::createWithTTF(std::to_string(stone_number), "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleSize.width * 9.7 / 10, visibleSize.height * 3.5 / 10)); // ���ñ�ǩ��ʾ��λ��
    this->addChild(label, 1);

    // ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    this->schedule([this, label](float dt) {
        label->setString(std::to_string(stone_number));
        }, "update_label_key");
}

void Mineral::showgemnum() {
    // ������ǩ����ӵ�������
    auto label = Label::createWithTTF(std::to_string(mineral_number), "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleSize.width * 9.7 / 10, visibleSize.height * 2.5 / 10)); // ���ñ�ǩ��ʾ��λ��
    this->addChild(label, 1);

    // ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    this->schedule([this, label](float dt) {
        label->setString(std::to_string(mineral_number));
        }, "update_label_key1");
}


