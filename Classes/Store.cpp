#include "Store.h"



#include "SimpleAudioEngine.h"
int SeedsBuyPrice = 2;
int SeedsTwoBuyPrice = 3;
int WheatSellPrice = 10;
int CarrotSellPrice = 10;
bool Store::init(TMXTiledMap* map) {

    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    pricechange();
    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setstorescene();
    setopenitem();
   
    return true;
}

Store* Store::create(TMXTiledMap* map) {

    Store* ret = new Store();
    if (ret && ret->init(map)) {
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
void Store::setstorescene() {
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
    


    setsell();
    setbuy();
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
void Store::setsell() {
    //С��ť
    wheatsellItem = MenuItemImage::create(
        "wheat1.png",
        "wheat2.png",
        [this](Ref* pSender) {
            if (wheat_number > 0) {
                money += WheatSellPrice;
                wheat_number--;
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
    this->schedule([this](float dt) {
        wheatsellLabel->setString("SellPrice: " + std::to_string(WheatSellPrice));
        //CCLOG("%d", WheatSellPrice);
        }, "update_label_key3");
    //ţ�̰�ť
    milksellItem = MenuItemImage::create(
        "milk1.png",
        "milk2.png",
        [this](Ref* pSender) {
            if (milk_number > 0) {
                money += MilkSellPrice;
                milk_number--;
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
        [this](Ref* pSender) {
            if (wool_number > 0) {
                money += WoolSellPrice;
                wool_number--;
            }
            else {
                sellfail();

            }
        });

    woolsellItem->setPosition(Vec2(visibleSize.width * 20 / 40,
        visibleSize.height * 21 / 40));
    ////wool��ǩ
    woolsellLabel = Label::createWithTTF("SellPrice: " + std::to_string(WoolSellPrice), "fonts/Marker Felt.ttf", 18);
    woolsellLabel->setPosition(Vec2(visibleSize.width * 20 / 40, visibleSize.height * 19 / 40)); // ���ñ�ǩ��ʾ��λ��
    woolsellLabel->setColor(Color3B::BLACK);
    StoreScene->addChild(woolsellLabel, 4);
    //egg��ť
    eggsellItem = MenuItemImage::create(
        "egg1.png",
        "egg2.png",
        [this](Ref* pSender) {
            if (egg_number > 0) {
                money += EggSellPrice;
                egg_number--;
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
        [this](Ref* pSender) {
            if (carrot_number > 0) {
                money += CarrotSellPrice;
                carrot_number--;
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
    this->schedule([this](float dt) {
        carrotsellLabel->setString("SellPrice: " + std::to_string(CarrotSellPrice));
        }, "update_label_key4");
    // ����һ���˵�
    auto menu = Menu::create(wheatsellItem, milksellItem, woolsellItem, eggsellItem, carrotsellItem, NULL);
    menu->setPosition(Vec2::ZERO);
    StoreScene->addChild(menu, 3);
}
void Store::setbuy()
{
    //��ť
    seedstwobuyItem = MenuItemImage::create(
        "seedstwo1.png",
        "seedstwo2.png",
        [this](Ref* pSender) {
            if (money >= SeedsTwoBuyPrice) {
                money -= SeedsTwoBuyPrice;
                seedstwo_number++;
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
    this->schedule([this](float dt) {
        seedstwobuyLabel->setString("BuyPrice: " + std::to_string(SeedsTwoBuyPrice));
        }, "update_label_key1");
    //��ť
    seedsbuyItem = MenuItemImage::create(
        "seeds1.png",
        "seeds2.png",
        [this](Ref* pSender) {
            if (money >= SeedsBuyPrice) {
                money -= SeedsBuyPrice;
                seeds_number++;
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
    this->schedule([this](float dt) {
        seedsbuyLabel->setString("BuyPrice: " + std::to_string(SeedsBuyPrice));
        }, "update_label_key2");
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
void Store::pricechange()
{
    this->schedule([this](float dt) {
        
        if (weather == 1) {
            SeedsBuyPrice = 4;
            SeedsTwoBuyPrice = 6;
            WheatSellPrice = 8;
            CarrotSellPrice = 8;
        }
        else if (weather == 2) {
            SeedsBuyPrice = 2;
            SeedsTwoBuyPrice = 3;
            WheatSellPrice = 9;
            CarrotSellPrice = 9;
        }
        else {
             SeedsBuyPrice = 2;
             SeedsTwoBuyPrice = 3;
             WheatSellPrice = 12;
             CarrotSellPrice = 12;
        }
        //CCLOG("%d", WheatSellPrice);
        }, 0.2, "lambda_key_price"); // ����ÿ1��ִ��һ�Σ�ʹ��һ��Ψһ�ļ���lambda_key����ʶ����
}