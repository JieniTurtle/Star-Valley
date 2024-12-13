#include "animals.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

int GameScene::mapscale = 2;

Scene* GameScene::createScene(std::string s)
{
    return GameScene::create(s);
}

GameScene* GameScene::create(std::string s)
{
    GameScene* scene = new GameScene;
    if (scene) {
        scene->scene_name_ = s;
        if (scene->init()) {
            return scene;
        }
    }
    return nullptr;
}


void set_physical_map(TMXTiledMap* map) {
    auto layer = map->getLayer("Buildings");
    const int tile_width = 16, tile_height = 16;
    const int scale = 2;

    for (int x = 0; x < map->getMapSize().width; x++) {
        for (int y = 0; y < map->getMapSize().height; y++) {
            if (layer->getTileGIDAt(Vec2(x, y)) != 0) {
                if (x > 0 && x < map->getMapSize().width - 1 && y > 0 && y < map->getMapSize().height - 1) {
                    if (layer->getTileGIDAt(Vec2(x + 1, y)) != 0 && layer->getTileGIDAt(Vec2(x - 1, y)) != 0 && layer->getTileGIDAt(Vec2(x, y + 1)) != 0 && layer->getTileGIDAt(Vec2(x, y - 1)) != 0) {
                        continue;
                    }
                }
                
                auto physics_body = PhysicsBody::createBox(Size(tile_width, tile_height), PhysicsMaterial(1.0f, 0.0f, 0.01f));
                physics_body->setDynamic(false);
                auto tile = layer->getTileAt(Vec2(x, y));
                tile->addComponent(physics_body);
            }
        }
    }
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//���д����ȡ��ǰ��Ϸ��ͼ���ڵ�ԭ������

    Scene::initWithPhysics();
    this->getPhysicsWorld()->setGravity(Vec2(0, 0));
    this->getPhysicsWorld()->setUpdateRate(1);
    // ���õ��Ի���
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // ��ӳ�ʼ����ͼ
    auto map = TMXTiledMap::create("maps/" + scene_name_ + ".tmx");
    if (!map) {
        problemLoading("'newnewFarm.tmx'");
        return false;
    }
    if (!map) {
        CCLOG("map fail");
        return false;
    }
    this->addChild(map, 0);
    map->setScale(2);//��ͼ��������
    set_physical_map(map);

    map->getLayer("Back")->setLocalZOrder(-3);
    map->getLayer("Buildings")->setLocalZOrder(-2);


    // ��ȡ��ͼ�Ĵ�С
    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height; // ������ש�����ظ߶�
    map->setAnchorPoint(Vec2(0.5, 0.5));
    map->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    auto tileLayer = map->getLayer("soil"); // �滻Ϊ����ͼ������
    Vec2 tilePosition(1, 64); // ����������Ҫ��ѯ��ͼ��λ�ã���������Ͻ�
    if (scene_name_ == "newnewFarm") {
        int tileGID = tileLayer->getTileGIDAt(tilePosition, nullptr);
        CCLOG("Tile GID at: %d", tileGID);
    }
    
    // create the physical body of map's edge
    auto edge = PhysicsBody::createEdgeBox(Size(mapWidth * tileWidth, mapHeight * tileHeight));
    edge->setDynamic(false);
    map->setTag(114);
    edge->setContactTestBitmask(0xFFFFFFFF);
    map->addComponent(edge);

    //��������
    character = MainCharacter::create("HelloWorld.png");    // this HelloWorld.png is set invisible, don't care
    character->setScale(2); // 0.5
    character->setMap(map);//�����ͼ
    map->addChild(character, 20);
    character->setPosition(mapWidth / 2 * tileWidth, mapHeight / 2 * tileWidth); // ��ʼλ��


    // please copy this to your aninals sprite
    auto test = Sprite::create("HelloWorld.png");
    // add physical property
    auto physics_body = PhysicsBody::createCircle(test->getContentSize().width / 2, PhysicsMaterial(0.00001f, 0.0f, 0.1f));
    // this->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    physics_body->setRotationEnable(false);
    physics_body->setVelocityLimit(200);
    test->setScale(0.5);
    test->addComponent(physics_body);
    map->addChild(test, 10);
    test->setPosition(mapWidth / 2 * tileWidth, mapHeight / 2 * tileWidth + 100);
    test->schedule([test](float dt) {
        test->getPhysicsBody()->setVelocity(test->getPhysicsBody()->getVelocity() * 0.9);
        }, "update_key");

    tools = Tools::create(map);//���빤��
    this->addChild(tools, 1);

    seeds = Seeds::create(map);//��������
    this->addChild(seeds, 1);

    wheat = Wheat::create(map);//����С��
    this->addChild(wheat, 1);
    gloves = Gloves::create(map,(wheat->wheatnum));//��������
    this->addChild(gloves, 1);

    

    MouseStatus = notTaken;//�������״̬

    //��ͼΪ���򣬴���NPC
    if (scene_name_ == "Town") {
        //����NPC Willy ���Ի� �ڵ�ͼ���·�
        std::vector<Vec2> path_Willy = { Vec2(700, 500), Vec2(1000, 500), Vec2(1000, 700), Vec2(700, 700) };
        NPC_Willy = initNPC("Willy", path_Willy, map);
        Dialog_Willy = Dialog::create(NPC_Willy->NPCname);

        //����NPC Gus ���Ի� �ڵ�ͼ���Ϸ�
        std::vector<Vec2> path_Gus = { Vec2(700, 700),Vec2(700, 500), Vec2(1000, 500), Vec2(1000, 700) };
        NPC_Gus = initNPC("Gus", path_Gus, map);
        Dialog_Gus = Dialog::create(NPC_Gus->NPCname);

        //����NPC Jodi ���Ի� �ڵ�ͼ���Ϸ�
        std::vector<Vec2> path_Jodi = { Vec2(1000, 700), Vec2(700, 700),Vec2(700, 500) ,Vec2(1000, 500) };
        NPC_Jodi = initNPC("Jodi", path_Jodi, map);
        Dialog_Jodi = Dialog::create(NPC_Jodi->NPCname);

        //����NPC Harvey ���Ի� �ڵ�ͼ���·�
        std::vector<Vec2> path_Harvey = { Vec2(1000, 500), Vec2(1000, 700), Vec2(700, 700),Vec2(700, 500) };
        NPC_Harvey = initNPC("Harvey", path_Harvey, map);
        Dialog_Harvey = Dialog::create(NPC_Harvey->NPCname);

        Dialog_Willy->retain();
        Dialog_Gus->retain();
        Dialog_Jodi->retain();
        Dialog_Harvey->retain();

        //����������¼�
        addMouseListener();
        this->schedule(CC_SCHEDULE_SELECTOR(GameScene::Mouseupdate), 0.1f); // ���¼��Ϊ0.1��
    }
    //��ͼΪũ��������newnew
    else {
        auto cow = Cow::create("cow");
        cow->setMaincharacter(character);
        cow->setMap(map);
        Cow::move(cow, map);


        auto sheep = Sheep::create("sheep");
        sheep->setMaincharacter(character);
        sheep->setMap(map);
        Sheep::move(sheep, map);

        auto chicken = Chicken::create("chicken");
        chicken->setMaincharacter(character);
        chicken->setMap(map);
        Chicken::move(chicken, map);

        CheckboxOnlyone();
    }
    return true;
}

//����ÿһ����ѡ��ÿ��ֻ��ѡһ��
void GameScene::CheckboxOnlyone() {
    // ����¼�������
    tools->hoecheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                tools->ishoe = 1;
                seeds->seedscheckbox->setSelected(false); // ȡ��ѡ����һ����ѡ��
                gloves->glovescheckbox->setSelected(false);
                wheat->wheatcheckbox->setSelected(false);
                wheat->iswheat = 0;
                gloves->isgloves = 0;
                seeds->isseeds = 0;
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                tools->ishoe = 0;
                break;
            default:
                break;
        }
        });

    // ����¼�������
    seeds->seedscheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                seeds->isseeds = 1;
                tools->hoecheckbox->setSelected(false); // ȡ��ѡ����һ����ѡ��
                gloves->glovescheckbox->setSelected(false);
                wheat->wheatcheckbox->setSelected(false);
                wheat->iswheat = 0;
                tools->ishoe = 0;
                gloves->isgloves = 0;
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                seeds->isseeds = 0;
                break;
            default:
                break;
        }
        });
    // ����¼�������
    gloves->glovescheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                gloves->isgloves = 1;
                seeds->seedscheckbox->setSelected(false); // ȡ��ѡ����һ����ѡ��
                tools->hoecheckbox->setSelected(false);
                wheat->wheatcheckbox->setSelected(false);
                wheat->iswheat = 0;
                tools->ishoe = 0;
                seeds->isseeds = 0;
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                gloves->isgloves = 0;
                break;
            default:
                break;
        }
        });
    // ����¼�������
    wheat->wheatcheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                wheat->iswheat = 1;
                seeds->seedscheckbox->setSelected(false); // ȡ��ѡ����һ����ѡ��
                gloves->glovescheckbox->setSelected(false);
                tools->hoecheckbox->setSelected(false);
                tools->ishoe = 0;
                gloves->isgloves = 0;
                seeds->isseeds = 0;
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                wheat->iswheat = 0;
                break;
            default:
                break;
        }
        });
  
}

NPC* GameScene::initNPC(std::string NPC_Name, std::vector<Vec2>& NPC_Path, TMXTiledMap* NPC_Map)
{
    NPC* npc = NPC::create(NPC_Name);
    if (npc == nullptr) { return NULL; }
    npc->setPath(NPC_Path);
    NPC_Map->addChild(npc);
    npc->setMap(NPC_Map);
    npc->startMovement();
    return npc;
}

void GameScene::addMouseListener()
{
    auto MouseListener = EventListenerMouse::create();
    MouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(MouseListener, this);
}

void GameScene::Mouseupdate(float delta)
{

}

void GameScene::onMouseDown(cocos2d::Event* event)
{
    //��ȡ���ӷ�Χ
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ�������λ�ã���ʼԭ��Ϊ���Ͻǣ�
    EventMouse* e = static_cast<EventMouse*>(event);
    Vec2 clickPos = e->getLocation() / mapscale;
    //���������λ��ת��Ϊ����Ļ���½�Ϊԭ��
    clickPos.y = visibleSize.height / mapscale - clickPos.y;

    if (MouseStatus == notTaken) {//���δ��ռ��
        //�������� NPC ���¼�
        if (NPC_Willy->onMouseDown(event, mapscale)) { addChild(Dialog_Willy); }
        if (NPC_Gus->onMouseDown(event, mapscale)) { addChild(Dialog_Gus); }
        if (NPC_Jodi->onMouseDown(event, mapscale)) { addChild(Dialog_Jodi); }
        if (NPC_Harvey->onMouseDown(event, mapscale)) { addChild(Dialog_Harvey); }
        if (NPC_Willy->ifSelected || NPC_Gus->ifSelected || NPC_Jodi->ifSelected || NPC_Harvey->ifSelected) {
            MouseStatus = TakenByNPC;
            return;
        }
    }
    else if (MouseStatus == TakenByNPC) {//��걻NPCռ��
        if (NPC_Willy->ifSelected) {
            if (Dialog_Willy->JudgeClickButton(clickPos, mapscale)) {
                Dialog_Willy->removeFromParent();
                NPC_Willy->onMouseDown(event, mapscale);
                MouseStatus = notTaken;
            }
        }
        if (NPC_Gus->ifSelected) {
            if (Dialog_Gus->JudgeClickButton(clickPos, mapscale)) {
                Dialog_Gus->removeFromParent();
                NPC_Gus->onMouseDown(event, mapscale);
                MouseStatus = notTaken;
            }
        }
        if (NPC_Jodi->ifSelected) {
            if (Dialog_Jodi->JudgeClickButton(clickPos, mapscale)) {
                Dialog_Jodi->removeFromParent();
                NPC_Jodi->onMouseDown(event, mapscale);
                MouseStatus = notTaken;
            }
        }
        if (NPC_Harvey->ifSelected) {
            if (Dialog_Harvey->JudgeClickButton(clickPos, mapscale)) {
                Dialog_Harvey->removeFromParent();
                NPC_Harvey->onMouseDown(event, mapscale);
                MouseStatus = notTaken;
            }
        }
    }
}
