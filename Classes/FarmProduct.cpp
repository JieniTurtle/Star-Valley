#include "FarmProduct.h"



#include "SimpleAudioEngine.h"

bool FarmProduct::init(TMXTiledMap* map) {

    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setcheckbox();//���ø�ѡ��
    showmilknum();//��ʾ����
    showeggnum();
    showwoolnum();
    showfishnum();
    return true;
}

void  FarmProduct::setcheckbox() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //����ͼ��
    milkcheckbox = ui::CheckBox::create("milk1.png", "milk1.png");
    milkcheckbox->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height*4 / 10)); // ����λ��

    this->addChild(milkcheckbox);
    //����ͼ��
    woolcheckbox = ui::CheckBox::create("wool1.png", "wool1.png");
    woolcheckbox->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height*3 / 10)); // ����λ��

    this->addChild(woolcheckbox);
    //����ͼ��
    eggcheckbox = ui::CheckBox::create("egg1.png", "egg1.png");
    eggcheckbox->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height*2 / 10)); // ����λ��

    this->addChild(eggcheckbox);
    //����ͼ��
    fishcheckbox = ui::CheckBox::create("fish1.png", "fish1.png");
    fishcheckbox->setPosition(Vec2(visibleSize.width * 9/ 10, visibleSize.height * 1 / 10)); // ����λ��

    this->addChild(fishcheckbox);
}

FarmProduct* FarmProduct::create(TMXTiledMap* map) {

    FarmProduct* ret = new FarmProduct();
    if (ret && ret->init(map)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

void FarmProduct::showmilknum() {
    // ������ǩ����ӵ�������
    auto label = Label::createWithTTF(std::to_string(milk_number), "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height * 3.5 / 10)); // ���ñ�ǩ��ʾ��λ��
    this->addChild(label, 1);

    // ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    this->schedule([this, label](float dt) {
        label->setString(std::to_string(milk_number));
        }, "update_label_key");
}

void FarmProduct::showeggnum() {
    // ������ǩ����ӵ�������
    auto label = Label::createWithTTF(std::to_string(egg_number), "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height * 1.5 / 10)); // ���ñ�ǩ��ʾ��λ��
    this->addChild(label, 1);

    // ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    this->schedule([this, label](float dt) {
        label->setString(std::to_string(egg_number));
        }, "update_label_key1");
}

void FarmProduct::showwoolnum() {
    // ������ǩ����ӵ�������
    auto label = Label::createWithTTF(std::to_string(wool_number), "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height * 2.5 / 10)); // ���ñ�ǩ��ʾ��λ��
    this->addChild(label, 1);

    // ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    this->schedule([this, label](float dt) {
        label->setString(std::to_string(wool_number));
        }, "update_label_key2");
}

void FarmProduct::showfishnum() {
    // ������ǩ����ӵ�������
    auto label = Label::createWithTTF(std::to_string(fish_number), "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height * 0.5 / 10)); // ���ñ�ǩ��ʾ��λ��
    this->addChild(label, 1);

    // ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    this->schedule([this, label](float dt) {
        label->setString(std::to_string(fish_number));
        }, "update_label_key3");
}
