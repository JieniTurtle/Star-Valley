#include "Store.h"



#include "SimpleAudioEngine.h"

bool Store::init(TMXTiledMap* map, int& wheatnum, int& milknum, int& woolnum, int& eggnum, int& seedsnum, int& fertilzernum, int& seedstwonum, int& carrotnum) {

    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setstorescene(wheatnum, milknum, woolnum, eggnum, seedsnum, fertilzernum,  seedstwonum,carrotnum);
    setopenitem();
    
    return true;
}

Store* Store::create(TMXTiledMap* map, int& wheatnum, int& milknum, int& woolnum, int& eggnum, int& seedsnum, int& fertilzernum, int& seedstwonum, int& carrotnum) {

    Store* ret = new Store();
    if (ret && ret->init(map, wheatnum,  milknum,  woolnum, eggnum,  seedsnum,  fertilzernum,  seedstwonum, carrotnum)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}
void Store::setopenitem() {
    // ����һ����ť
     openItem = MenuItemImage::create(
        "storeopen.png",
        "storeopen.png",
        CC_CALLBACK_0(Store::menuOpenCallback, this));

    openItem->setPosition(Vec2( visibleSize.width*7/10,
        visibleSize.height* 9 / 10));

    // ����һ���˵�
    auto menu = Menu::create(openItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}
//�����̵갴ť
void Store::menuOpenCallback() {
    //����������Ϊ�ɼ�
    for (auto& child : StoreScene->getChildren())
    {
        child->setVisible(true);
    }
}
//�����̵����
void Store::setstorescene(int& wheatnum,  int& milknum, int& woolnum, int& eggnum, int& seedsnum, int& fertilzernum, int& seedstwonum, int& carrotnum) {
    StoreScene =Layer::create();
    emptystoragesprite = Sprite::create("emptystorage.png");
    emptystoragesprite->setPosition(Vec2(visibleSize.width / 2,
        visibleSize.height / 2));
    emptystoragesprite->setScale(0.8);
    StoreScene -> addChild(emptystoragesprite, 0);
    //
    closeItem = MenuItemImage::create(
        "closeitem.png",
        "closeitem.png",
        CC_CALLBACK_0(Store::CloseCallback, this));

    closeItem->setPosition(Vec2(visibleSize.width * 7 / 10,
        visibleSize.height * 9 / 10));

    // ����һ���˵�
    closemenu = Menu::create(closeItem, NULL);
    closemenu->setPosition(Vec2::ZERO);
    StoreScene->addChild(closemenu, 4);
    


    setsell(wheatnum, milknum, woolnum, eggnum, seedsnum, fertilzernum,  seedstwonum, carrotnum);
    setbuy(wheatnum, milknum, woolnum, eggnum, seedsnum, fertilzernum, seedstwonum, carrotnum);
    this->addChild(StoreScene, 2);
    //��ʼΪ���ɼ�
    for (auto& child : StoreScene->getChildren())
    {
        child->setVisible(false);
    }
}
void Store::CloseCallback() {
    for (auto& child : StoreScene->getChildren())
    {
        child->setVisible(false);
    }
}
void Store::setsell(int& wheatnum, int& milknum, int& woolnum, int& eggnum, int& seedsnum, int& fertilzernum, int& seedstwonum, int& carrotnum) {
    //С��ť
    wheatsellItem = MenuItemImage::create(
        "wheat1.png",
        "wheat2.png",
        [this,&wheatnum](Ref* pSender) {
            if (wheatnum > 0) {
                money += WheatSellPrice;
                wheatnum--;
            }
            else {
                sellfail();
            }
        });

    wheatsellItem->setPosition(Vec2(visibleSize.width * 13/ 40,
        visibleSize.height * 21 / 40));
    //С���ǩ
    wheatsellLabel = Label::createWithTTF("SellPrice: " + std::to_string(WheatSellPrice), "fonts/Marker Felt.ttf", 18);
    wheatsellLabel->setPosition(Vec2(visibleSize.width * 13 / 40, visibleSize.height * 19 / 40)); // ���ñ�ǩ��ʾ��λ��
    wheatsellLabel->setColor(Color3B::BLACK);
    StoreScene->addChild(wheatsellLabel, 4);
    //ţ�̰�ť
    milksellItem = MenuItemImage::create(
        "milk1.png",
        "milk2.png",
        [this, &milknum](Ref* pSender) {
            if (milknum > 0) {
                money += MilkSellPrice;
                milknum--;
            }
            else {
                sellfail();
  
            }
        });

    milksellItem->setPosition(Vec2(visibleSize.width * 16.5 / 40,
        visibleSize.height * 21 / 40));
    //ţ�̱�ǩ
    milksellLabel = Label::createWithTTF("SellPrice: " + std::to_string(MilkSellPrice), "fonts/Marker Felt.ttf", 18);
    milksellLabel->setPosition(Vec2(visibleSize.width * 16.5 / 40, visibleSize.height * 19 / 40)); // ���ñ�ǩ��ʾ��λ��
    milksellLabel->setColor(Color3B::BLACK);
    StoreScene->addChild(milksellLabel, 4);
    //wool��ť
    woolsellItem = MenuItemImage::create(
        "wool1.png",
        "wool2.png",
        [this, &woolnum](Ref* pSender) {
            if (woolnum > 0) {
                money += WoolSellPrice;
                woolnum--;
            }
            else {
                sellfail();

            }
        });

    woolsellItem->setPosition(Vec2(visibleSize.width * 20 / 40,
        visibleSize.height * 21 / 40));
    ////wool��ǩ
    //woolsellLabel = Label::createWithTTF("SellPrice: " + std::to_string(WoolSellPrice), "fonts/Marker Felt.ttf", 18);
    //woolsellLabel->setPosition(Vec2(visibleSize.width * 20 / 40, visibleSize.height * 19 / 40)); // ���ñ�ǩ��ʾ��λ��
    //woolsellLabel->setColor(Color3B::BLACK);
    //StoreScene->addChild(woolsellLabel, 4);
    //egg��ť
    eggsellItem = MenuItemImage::create(
        "egg1.png",
        "egg2.png",
        [this, &eggnum](Ref* pSender) {
            if (eggnum > 0) {
                money += EggSellPrice;
                eggnum--;
            }
            else {
                sellfail();

            }
        });

    eggsellItem->setPosition(Vec2(visibleSize.width * 23.5 / 40,
        visibleSize.height * 21 / 40));
    //egg��ǩ
    eggsellLabel = Label::createWithTTF("SellPrice: " + std::to_string(EggSellPrice), "fonts/Marker Felt.ttf", 18);
    eggsellLabel->setPosition(Vec2(visibleSize.width * 23.5 / 40, visibleSize.height * 19 / 40)); // ���ñ�ǩ��ʾ��λ��
    eggsellLabel->setColor(Color3B::BLACK);
    StoreScene->addChild(eggsellLabel, 4);
    //carrot��ť
    carrotsellItem = MenuItemImage::create(
        "carrot1.png",
        "carrot2.png",
        [this, &carrotnum](Ref* pSender) {
            if (carrotnum > 0) {
                money += CarrotSellPrice;
                carrotnum--;
            }
            else {
                sellfail();
            }
        });

    carrotsellItem->setPosition(Vec2(visibleSize.width *27 / 40,
        visibleSize.height * 21 / 40));
    //carrot��ǩ
    carrotsellLabel = Label::createWithTTF("SellPrice: " + std::to_string(CarrotSellPrice), "fonts/Marker Felt.ttf", 18);
    carrotsellLabel->setPosition(Vec2(visibleSize.width * 27 / 40, visibleSize.height * 19 / 40)); // ���ñ�ǩ��ʾ��λ��
    carrotsellLabel->setColor(Color3B::BLACK);
    StoreScene->addChild(carrotsellLabel, 4);
    // ����һ���˵�
    auto menu = Menu::create(wheatsellItem, milksellItem, woolsellItem, eggsellItem, carrotsellItem, NULL);
    menu->setPosition(Vec2::ZERO);
    StoreScene->addChild(menu, 3);
}
void Store::setbuy(int& wheatnum, int& milknum, int& woolnum, int& eggnum, int& seedsnum, int& fertilzernum, int& seedstwonum, int& carrotnum)
{
    //��ť
    seedstwobuyItem = MenuItemImage::create(
        "seedstwo1.png",
        "seedstwo2.png",
        [this, &seedstwonum](Ref* pSender) {
            if (money >= SeedsTwoBuyPrice) {
                money -= SeedsTwoBuyPrice;
                seedstwonum++;
            }
            else {
                buyfail();
            }
        });

    seedstwobuyItem->setPosition(Vec2(visibleSize.width * 16.5 / 40,
        visibleSize.height * 16 / 40));
    //��ǩ
    seedstwobuyLabel = Label::createWithTTF("BuyPrice: " + std::to_string(SeedsTwoBuyPrice), "fonts/Marker Felt.ttf", 18);
    seedstwobuyLabel->setPosition(Vec2(visibleSize.width * 16.5 / 40, visibleSize.height * 14 / 40)); // ���ñ�ǩ��ʾ��λ��
    seedstwobuyLabel->setColor(Color3B::BLACK);
    StoreScene->addChild(seedstwobuyLabel, 4);
    //��ť
    seedsbuyItem = MenuItemImage::create(
        "seeds1.png",
        "seeds2.png",
        [this, &seedsnum](Ref* pSender) {
            if (money >= SeedsBuyPrice) {
                money -= SeedsBuyPrice;
                seedsnum++;
            }
            else {
                buyfail();
            }
        });

    seedsbuyItem->setPosition(Vec2(visibleSize.width * 13 / 40,
        visibleSize.height * 16 / 40));
    //��ǩ
    seedsbuyLabel = Label::createWithTTF("BuyPrice: " + std::to_string(SeedsBuyPrice), "fonts/Marker Felt.ttf", 18);
    seedsbuyLabel->setPosition(Vec2(visibleSize.width * 13 / 40, visibleSize.height * 14 / 40)); // ���ñ�ǩ��ʾ��λ��
    seedsbuyLabel->setColor(Color3B::BLACK);
    StoreScene->addChild(seedsbuyLabel, 4);
    // ����һ���˵�
    auto menu = Menu::create(seedsbuyItem, seedstwobuyItem, NULL);
    menu->setPosition(Vec2::ZERO);
    StoreScene->addChild(menu, 3);
}
void Store::sellfail() {
    auto label = Label::createWithSystemFont("You don't have enough product", "Arial", 24);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/ 2));
    auto sprite = Sprite::create("buysellfailscene.png");//����
    sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    sprite->setScale(1.2);
    StoreScene->addChild(label,6);
    StoreScene->addChild(sprite, 5);
    label->setVisible(true);

    label->setColor(Color3B::BLUE);

    auto callback = [=]() {
        StoreScene->removeChild(label);
        StoreScene->removeChild(sprite);
        };
    Action* rebackaction = Sequence::create(DelayTime::create(FailSellDisplayTime), CallFunc::create(callback), nullptr);
    this->runAction(rebackaction);
    // �������ӳ�ִ�У�n�볤����

 
}
void Store::buyfail() {
    auto label = Label::createWithSystemFont("You don't have enough money", "Arial", 24);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    auto sprite = Sprite::create("buysellfailscene.png");//����
    sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    sprite->setScale(1.2);
    StoreScene->addChild(label, 6);
    StoreScene->addChild(sprite, 5);
    
    label->setVisible(true);

    label->setColor(Color3B::BLUE);

    auto callback = [=]() {
        StoreScene->removeChild(label);
        StoreScene->removeChild(sprite);
        };
    Action* rebackaction = Sequence::create(DelayTime::create(FailSellDisplayTime), CallFunc::create(callback), nullptr);
    this->runAction(rebackaction);
    // �������ӳ�ִ�У�n�볤����


}
