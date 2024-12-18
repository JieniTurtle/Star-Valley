#include "animals.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Task.h"
#include "global.h"
#include "explore.h"

USING_NS_CC;

#define MIDDLE -1
#define LEFT 1
#define UP 0
#define RIGHT 3
#define DOWN 2

int GameScene::mapscale = 2;

Scene* GameScene::createScene(std::string s, int direction)
{
    return GameScene::create(s, direction);
}

GameScene* GameScene::create(std::string s, int direction)
{
    GameScene* scene = new GameScene;
    if (scene) {
        scene->scene_name_ = s;
        if (scene->init(direction)) {
            return scene;
        }
    }
    return nullptr;
}


void GameScene::set_physical_map(TMXTiledMap* map) {
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


                // for going to the mine
                if (layer->getTileGIDAt(Vec2(x, y)) == 959 && scene_name_ == "Town") {
                    physics_body->setContactTestBitmask(0xFFFFFFFF);
                    tile->setTag(999);
                }
                if (layer->getTileGIDAt(Vec2(x, y)) == 289 && scene_name_ == "Mine") {
                    physics_body->setContactTestBitmask(0xFFFFFFFF);
                    tile->setTag(999);
                }
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
bool GameScene::init(int direction)
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
    map->setScale(mapscale);//��ͼ��������
    set_physical_map(map);
    map->getLayer("Back")->setLocalZOrder(-3);
    map->getLayer("Buildings")->setLocalZOrder(-2);

    auto task_layer = TaskLayer::create(task_manager);
    this->addChild(task_layer);

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

    mineral = Mineral::create(map);//�����ʯ
    this->addChild(mineral, 1);

    //��������
    character = MainCharacter::create("MainCharacter/transparent.png");    // this HelloWorld.png is set invisible, don't care
    character->setMap(map);//�����ͼ
    map->addChild(character, 1);
    int x = 0, y = 0;
    switch (direction)
    {
    case MIDDLE:   // the first time you enter this game
        x = mapWidth / 2, y = mapHeight / 2;
        break;
    case LEFT:
        x = 1;
        if (scene_name_ == "Town")
            y = 56;
        else if (scene_name_ == "Mine")
            x = 14, y = 9;
        else if (scene_name_ == "Mountain")
            y = 27;
        break;
    case RIGHT:
        x = map->getMapSize().width - 1;
        if (scene_name_ == "newnewFarm")
            y = 48;
        else if (scene_name_ == "Town")
            x = 107, y = 33;
        else if (scene_name_ == "Woods")
            y = 15;
        break;
    case UP:
        y = map->getMapSize().height - 1;
        if (scene_name_ == "Town")
            x = 81;
        break;
    case DOWN:
        y = 2;
        if (scene_name_ == "Mountain")
            x = 15;
        break;
    default:
        break;
    }
    character->setPosition(x * tileWidth, y * tileWidth); // ��ʼλ��

    // bridge
    if (scene_name_ == "Mountain" && !bridge_repaired) {
        auto borken_bridge = Bridge::create(map);
        map->addChild(borken_bridge, 10);
    }

    // treasure chest
    if (scene_name_ == "Mountain" && !chest_opened[0]) {
        auto chest = Chest::create(map, 0);
        map->addChild(chest, 5);
    }
    if (scene_name_ == "Woods" && !chest_opened[1]) {
        auto chest = Chest::create(map, 1);
        map->addChild(chest, 5);
    }

    /*/ please copy this to your aninals sprite
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
        }, "update_key");*/

    MouseStatus = notTaken;//�������״̬

    //��ͼΪ���򣬴���NPC
    if (scene_name_ == "Town") {
        //����NPC Willy ���Ի� �ڵ�ͼ���·�
        std::vector<Vec2> path_Willy = { Vec2(28, 51), Vec2(29, 19), Vec2(-10, 19), Vec2(-10, 55), Vec2(26, 55), Vec2(28, 55)};
        NPC_Willy = initNPC("Willy", path_Willy, map);
        NPC_Willy->retain();

        //����NPC Gus ���Ի� �ڵ�ͼ���Ϸ�
        std::vector<Vec2> path_Gus = { Vec2(700, 700),Vec2(700, 500), Vec2(1000, 500), Vec2(1000, 700) };
        NPC_Gus = initNPC("Gus", path_Gus, map);
        NPC_Gus->retain();

        //����NPC Jodi ���Ի� �ڵ�ͼ���Ϸ�
        std::vector<Vec2> path_Jodi = { Vec2(1000, 700), Vec2(700, 700),Vec2(700, 500) ,Vec2(1000, 500) };
        NPC_Jodi = initNPC("Jodi", path_Jodi, map);
        NPC_Jodi->retain();

        //����NPC Harvey ���Ի� �ڵ�ͼ���·�
        std::vector<Vec2> path_Harvey = { Vec2(1000, 500), Vec2(1000, 700), Vec2(700, 700),Vec2(700, 500) };
        NPC_Harvey = initNPC("Harvey", path_Harvey, map);
        NPC_Harvey->retain();

        //����������¼�
        addMouseListener();
        //this->schedule(CC_SCHEDULE_SELECTOR(GameScene::Mouseupdate), 0.1f); // ���¼��Ϊ0.1��
    }
    //��ͼΪũ��������newnew
    else {
        tools = Tools::create(map);//���빤��
        this->addChild(tools, 1);

        seeds = Seeds::create(map);//��������
        this->addChild(seeds, 1);
        wheat = Wheat::create(map);//����С��
        this->addChild(wheat, 1);
        seedstwo = Seedstwo::create(map);//��������2
        this->addChild(seedstwo, 1);
        carrot = Carrot::create(map);//����carrot
        this->addChild(carrot, 1);
        gloves = Gloves::create(map, (wheat->wheatnum), (carrot->carrotnum));//��������
        this->addChild(gloves, 1);
        wood = Wood::create(map);//����wood
        this->addChild(wood, 1);
        axe = Axe::create(map, (wood->woodnum));//���븫��
        this->addChild(axe, 1);
        kettle = Kettle::create(map);//����kettle
        this->addChild(kettle, 1);
        fertilizer = Fertilizer::create(map);//����fertilizer
        this->addChild(fertilizer, 1);
        farmproduct = FarmProduct::create(map);//����
        this->addChild(farmproduct, 1);
        pickaxe = Pickaxe::create(map, mineral->stonenum, mineral->gemnum);//����gaozi
        this->addChild(pickaxe, 1);
        fishing = Fishing::create(map, character, farmproduct->fishnum);//����
        this->addChild(fishing, 1);
        //

        store = Store::create(map, wheat->wheatnum, farmproduct->milknum, farmproduct->woolnum, farmproduct->eggnum, seeds->seedsnum, fertilizer->fertilizernum, seedstwo->seedstwonum, carrot->carrotnum);
        this->addChild(store, 1);

        auto cow = Cow::create("cow", map);
        cow->setMaincharacter(character);
        Cow::move(cow, map);

        CheckboxOnlyone();
        showmoneynum();
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
                CloseOtherCheckbox(tools->hoecheckbox);
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                tools->ishoe = 0;
                break;
            default:
                break;
        }
        });
    // ����¼�������
    pickaxe->pickaxecheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                pickaxe->ispickaxe = 1;
                CloseOtherCheckbox(pickaxe->pickaxecheckbox);
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                pickaxe->ispickaxe = 0;
                break;
            default:
                break;
        }
        });
    // ����¼�������
    fishing->fishingcheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                fishing->isfishing = 1;
                CloseOtherCheckbox(fishing->fishingcheckbox);
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                fishing->isfishing = 0;
                fishing->fishingcondition = 0;//����״̬Ϊ0

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
                CloseOtherCheckbox(seeds->seedscheckbox);
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                seeds->isseeds = 0;
                break;
            default:
                break;
        }
        });
    // ����¼�������
    seedstwo->seedstwocheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                seedstwo->isseedstwo = 1;
                CloseOtherCheckbox(seedstwo->seedstwocheckbox);
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                seedstwo->isseedstwo = 0;
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
                CloseOtherCheckbox(gloves->glovescheckbox);
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
                CloseOtherCheckbox(wheat->wheatcheckbox);
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                wheat->iswheat = 0;
                break;
            default:
                break;
        }
        });
    // ����¼�������
    carrot->carrotcheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                carrot->iscarrot = 1;
                CloseOtherCheckbox(carrot->carrotcheckbox);
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                carrot->iscarrot = 0;
                break;
            default:
                break;
        }
        });
    // ����¼�������
    axe->axecheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                axe->isaxe = 1;
                CloseOtherCheckbox(axe->axecheckbox);
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                axe->isaxe = 0;
                break;
            default:
                break;
        }
        });
    // ����¼�������
    wood->woodcheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                wood->iswood = 1;
                CloseOtherCheckbox(wood->woodcheckbox);
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                wood->iswood = 0;
                break;
            default:
                break;
        }
        });
    // ����¼�������
    kettle->kettlecheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                kettle->iskettle = 1;
                CloseOtherCheckbox(kettle->kettlecheckbox);
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                kettle->iskettle = 0;
                break;
            default:
                break;
        }
        });
    // ����¼�������
    fertilizer->fertilizercheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                fertilizer->isfertilizer = 1;
                CloseOtherCheckbox(fertilizer->fertilizercheckbox);
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                fertilizer->isfertilizer = 0;
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
        if (NPC_Willy->JudgeClickNPC(clickPos, mapscale)) {
            MouseClickNPC(NPC_Willy);
            MouseStatus = TakenByNPC;
            return;
        }
        if (NPC_Gus->JudgeClickNPC(clickPos, mapscale)) {
            MouseClickNPC(NPC_Gus);
            MouseStatus = TakenByNPC;
            return;
        }
        if (NPC_Jodi->JudgeClickNPC(clickPos, mapscale)) {
            MouseClickNPC(NPC_Jodi);
            MouseStatus = TakenByNPC;
            return;
        }
        if (NPC_Harvey->JudgeClickNPC(clickPos, mapscale)) {
            MouseClickNPC(NPC_Harvey);
            MouseStatus = TakenByNPC;
            return;
        }
    }
    else if (MouseStatus == TakenByNPC) {//��걻NPCռ��
        /*int c = clickNPCButtons();
        if (c == 1) {
        }
        else if (c == 2) {

        }*/
        if (NPC_Willy->ifSelected) {
            if (NPC_Willy->Dialog_NPC->clickEndButton == true) {
                MouseStatus = notTaken;
                NPC_Willy->startMovement();
                NPC_Willy->Dialog_NPC->clickEndButton = false;
            }
        }
        if (NPC_Gus->ifSelected) {
            if (NPC_Gus->Dialog_NPC->clickEndButton == true) {
                MouseStatus = notTaken;
                NPC_Gus->startMovement();
                NPC_Gus->Dialog_NPC->clickEndButton = false;
            }
        }
        if (NPC_Jodi->ifSelected) {
            if (NPC_Jodi->Dialog_NPC->clickEndButton == true) {
                MouseStatus = notTaken;
                NPC_Jodi->startMovement();
                NPC_Jodi->Dialog_NPC->clickEndButton = false;
            }
        }
        if (NPC_Harvey->ifSelected) {
            if (NPC_Harvey->Dialog_NPC->clickEndButton == true) {
                MouseStatus = notTaken;
                NPC_Harvey->startMovement();
                NPC_Harvey->Dialog_NPC->clickEndButton = false;
            }
        }
    }
}

void GameScene::MouseClickNPC(NPC* npc)
{
    npc->stopMovement();
    npc->ifSelected = true;
    //enum TaskStatus npcTS = npc->NPCtask.GetTaskStatus();
    this->addChild(npc->Dialog_NPC);
}

int GameScene::clickNPCButtons()
{
    return 0;
}
//�ر�������ѡ��
void GameScene::CloseOtherCheckbox(ui::CheckBox* selectedCheckbox) {
    if (selectedCheckbox != tools->hoecheckbox) {
        tools->hoecheckbox->setSelected(false); // ȡ��ѡ����һ����ѡ��
        tools->ishoe = 0;
    }
    if (selectedCheckbox != pickaxe->pickaxecheckbox) {
        pickaxe->pickaxecheckbox->setSelected(false); // ȡ��ѡ����һ����ѡ��
        pickaxe->ispickaxe = 0;
    }
    if (selectedCheckbox != fishing->fishingcheckbox) {
        fishing->fishingcheckbox->setSelected(false); // ȡ��ѡ����һ����ѡ��
        fishing->isfishing = 0;
        fishing->fishingcondition = 0;
    }
    if (selectedCheckbox != seeds->seedscheckbox) {
        seeds->seedscheckbox->setSelected(false); // ȡ��ѡ����һ����ѡ��
        seeds->isseeds = 0;
    }
    if (selectedCheckbox != seedstwo->seedstwocheckbox) {
        seedstwo->seedstwocheckbox->setSelected(false); // ȡ��ѡ����һ����ѡ��
        seedstwo->isseedstwo = 0;
    }
    if (selectedCheckbox != gloves->glovescheckbox) {

        gloves->glovescheckbox->setSelected(false);
        gloves->isgloves = 0;
    }
    if (selectedCheckbox != wheat->wheatcheckbox) {

        wheat->wheatcheckbox->setSelected(false);
        wheat->iswheat = 0;
    }
    if (selectedCheckbox != carrot->carrotcheckbox) {

        carrot->carrotcheckbox->setSelected(false);
        carrot->iscarrot = 0;
    }
    if (selectedCheckbox != axe->axecheckbox) {

        axe->axecheckbox->setSelected(false);
        axe->isaxe = 0;
    }
    if (selectedCheckbox != wood->woodcheckbox) {
        wood->iswood = 0;
        wood->woodcheckbox->setSelected(false);
    }
    if (selectedCheckbox != kettle->kettlecheckbox) {
        kettle->iskettle = 0;
        kettle->kettlecheckbox->setSelected(false);
    }
    if (selectedCheckbox != fertilizer->fertilizercheckbox) {
        fertilizer->isfertilizer = 0;
        fertilizer->fertilizercheckbox->setSelected(false);
    }
}
void GameScene::showmoneynum() {
    //// ������ǩ����ӵ�������
    //auto label = Label::createWithTTF(std::to_string(money), "fonts/Marker Felt.ttf", 24);
    //label->setPosition(Vec2(visibleSize.width * 8 / 10, visibleSize.height * 9 / 10)); // ���ñ�ǩ��ʾ��λ��
    //this->addChild(label, 1);

    //// ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    //this->schedule([this, label](float dt) {
    //    label->setString(std::to_string(money));
    //    }, "update_label_key");
    std::string moneyString = "Money: " + std::to_string(money);
    auto label = Label::createWithTTF(moneyString, "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleSize.width * 8 / 10, visibleSize.height * 9 / 10)); // ���ñ�ǩ��ʾ��λ��
    label->setColor(Color3B::BLACK);
    this->addChild(label, 1);

    // ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    this->schedule([this, label](float dt) {
        label->setString("Money: " + std::to_string(money));
        }, "update_label_key");
}