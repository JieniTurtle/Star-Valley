#include "animals.h"
#include"MainCharacter.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define PHYSICS 999

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//·����ʼ��
void Animal::setPath(const std::vector<Vec2>& newPath)
{
    Animalpath = newPath;
    currentPathIndex = 0;  // ����·������
    setPosition(Animalpath[currentPathIndex]);  // ���� Animal ����ʼλ��

    auto physics_body = PhysicsBody::createCircle(12, PhysicsMaterial(0.00001f, 0.0f, 0.1f));
    // this->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    physics_body->setRotationEnable(false);
    physics_body->setVelocityLimit(50.0f);
    this->addComponent(physics_body);
    this->setVisible(false);
}

void Animal::updatemove(float dt)
{
    if (Animalpath.empty()) return;

    // ��ȡĿ��λ��
    Vec2 targetPosition = Animalpath[currentPathIndex];
    Vec2 currentPosition = this->getPosition();

    // ���㵱ǰλ�ú�Ŀ��λ�õľ���
    Vec2 direction = targetPosition - currentPosition;
    float distance = direction.length();

    // �������Ŀ�꣬�л�����һ��·����
    if (distance < 10.0f) {
        currentPathIndex = (currentPathIndex + 1) % Animalpath.size();  // ѭ��·��
    }

    // �ƶ� Animal
    Vec2 moveDirection = direction.getNormalized();
    getPhysicsBody()->applyForce(0.1f * moveDirection * speed);

    // ���ݷ��򲥷Ŷ���
    if (fabs(moveDirection.x) > fabs(moveDirection.y)) { // ˮƽ�ƶ�
        if (moveDirection.x > 0) {
            playAnimation("right");
        }
        else {
            playAnimation("left");
        }
    }
    else { // ��ֱ�ƶ�
        if (moveDirection.y > 0) {
            playAnimation("up");
        }
        else {
            playAnimation("down");
        }
    }

    animate_sprite->setPosition(getPosition());
}

void Animal::playAnimation(const std::string& direction)
{
    //!getActionByTag(1) 
    // �����ǰ������Ŀ�귽����ͬ��ֱ�ӷ���
    if (direction == "up" && 1) {
        animate_sprite->runAction(RepeatForever::create(moveup));
    }
    else if (direction == "down" && 1) {
        animate_sprite->runAction(RepeatForever::create(movedown));
    }
    else if (direction == "left" && 1) {
        animate_sprite->runAction(RepeatForever::create(moveleft));
    }
    else if (direction == "right" && 1) {
        animate_sprite->runAction(RepeatForever::create(moveright));
    }
}

int Cow::Animalsize_x = 125;
int Cow::Animalsize_y = 125;

int Cow::Animalorder_up = 2;
int Cow::Animalorder_left = 3;
int Cow::Animalorder_right = 1;
int Cow::Animalorder_down = 0;

Cow* Cow::create(const std::string& filename, TMXTiledMap* map)
{
    Cow* cow = new Cow();
    if (cow) {
        cow->animalName = filename;
        
        cow->animate_sprite = Sprite::create("HelloWorld.png");
        cow->animate_sprite->setScale(0.5);
        map->addChild(cow->animate_sprite, 10);

        if (cow->init()) {
            cow->autorelease(); // �Զ��ͷ��ڴ�
            return cow;
        }
    }
    CC_SAFE_DELETE(cow); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

void Cow::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (isNearSprite && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_E)
    {
        cow_feed_label->setVisible(true); // ��ʾ����

        // ������ʱ����3�����������
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(Cow::hideLabel), 3.0f);
    }
}

// ��Ӽ����¼�����
void Cow::addKeyboardListener() {
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Cow::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

//��ǩ����
void Cow::hideLabel(float dt)
{
    cow_feed_label->setVisible(false); // ��������
}

void Cow::isMainCharNear(float delta)
{
    Vec2 sprite1Position = mainChar->getPosition(); // ��ȡ���ǵ�λ��(��Ե�ͼ���½�)
    Vec2 sprite2Position = this->getPosition(); // ��ȡ��ͼ��λ��(��Ե�ͼ���½�)

    float distance = sprite1Position.distance(sprite2Position);
    
    // �������С��ĳ��ֵ�����ñ�־λ
    if (distance < 50) {
        isNearSprite = true;
    }
    else {
        isNearSprite = false;
    }
}

//��ʼ��
bool Cow::init()
{
    //��������
    Texture2D* Move = Director::getInstance()->getTextureCache()->addImage("Animal/" + animalName + "/texture.png");

    if (!Sprite::initWithFile("Animal/" + animalName + "/static.png")) { return false; }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    speed = 50.0f;//�����ٶ�
    currentPathIndex = 0;//��ʼ·��
    ifSelected = false;//���Animalδ��ѡ��

    // ����λ�ø��º���
    schedule([=](float dt) {updatemove(dt); }, 0.0f, "animal_updatemove_key");

    Vector<SpriteFrame*> Animalup;
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(Move, Rect(i * Animalsize_x, Animalorder_up * Animalsize_y, Animalsize_x, Animalsize_y));
        Animalup.pushBack(frame);
    }
    Animation* uup = Animation::createWithSpriteFrames(Animalup, 0.3f);
    moveup = Animate::create(uup);
    moveup->setTag(1);

    Vector<SpriteFrame*>Animalleft;
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(Move, Rect(i * Animalsize_x, Animalorder_left * Animalsize_y, Animalsize_x, Animalsize_y));
        Animalleft.pushBack(frame);
    }
    Animation* lleft = Animation::createWithSpriteFrames(Animalleft, 0.3f);
    moveleft = Animate::create(lleft);
    moveleft->setTag(2);

    Vector<SpriteFrame*>Animalright;
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(Move, Rect(i * Animalsize_x, Animalorder_right * Animalsize_y, Animalsize_x, Animalsize_y));
        Animalright.pushBack(frame);
    }
    Animation* rright = Animation::createWithSpriteFrames(Animalright, 0.3f);
    moveright = Animate::create(rright);
    moveright->setTag(3);

    Vector<SpriteFrame*>Animaldown;
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(Move, Rect(i * Animalsize_x, Animalorder_down * Animalsize_y, Animalsize_x, Animalsize_y));
        Animaldown.pushBack(frame);
    }
    Animation* ddown = Animation::createWithSpriteFrames(Animaldown, 0.3f);
    movedown = Animate::create(ddown);
    movedown->setTag(4);

    // �������ֱ�ǩ
    cow_feed_label = cocos2d::Label::createWithSystemFont("The cow has been fed.Obtain Milk x1", "Arial", 25);
    cow_feed_label->setVisible(false); // ��ʼʱ����
    this->addChild(cow_feed_label);
    cow_feed_label->setPosition(cocos2d::Vec2(40, 120));

    Cow::addKeyboardListener();
    this->schedule(CC_SCHEDULE_SELECTOR(Cow::isMainCharNear), 0.1f);

    return true;
}

void Cow::move(Cow* cow, TMXTiledMap* map) {
    map->addChild(cow);
    cow->setScale(2.0f);
    cow->setPosition(Vec2(950, 765 ));
    Sequence* move_cow = Sequence::create(cow->moveup, cow->moveright, cow->moveleft, cow->movedown, NULL);
    std::vector<Vec2> path_cow = { Vec2(950, 765), Vec2(950, 720), Vec2(1070, 720),Vec2(1070, 765) };
    cow->setPath(path_cow);
    cow->animate_sprite->runAction(RepeatForever::create(move_cow));
}

int Sheep::Animalsize_x = 32;
int Sheep::Animalsize_y = 33;

int Sheep::Animalorder_up = 2;
int Sheep::Animalorder_left = 3;
int Sheep::Animalorder_right = 1;
int Sheep::Animalorder_down = 0;

Sheep* Sheep::create(const std::string& filename)
{
    Sheep* sheep = new Sheep();
    if (sheep) {
        sheep->animalName = filename;
        if (sheep->init()) {
            sheep->autorelease(); // �Զ��ͷ��ڴ�
            return sheep;
        }
    }
    CC_SAFE_DELETE(sheep); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

void Sheep::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (isNearSprite && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_E)
    {
        sheep_feed_label->setVisible(true); // ��ʾ����

        // ������ʱ����3�����������
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(Cow::hideLabel), 3.0f);
    }
}

// ��Ӽ����¼�����
void Sheep::addKeyboardListener() {
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Sheep::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

//��ǩ����
void Sheep::hideLabel(float dt)
{
    sheep_feed_label->setVisible(false); // ��������
}

//��ʼ��
bool Sheep::init()
{
    //��������
    Texture2D* Move = Director::getInstance()->getTextureCache()->addImage("Animal/" + animalName + "/texture.png");

    if (!Sprite::initWithFile("Animal/" + animalName + "/static.png")) { return false; }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    speed = 50.0f;//�����ٶ�
    currentPathIndex = 0;//��ʼ·��
    ifSelected = false;//���Animalδ��ѡ��

    // ����λ�ø��º���
    schedule([=](float dt) {updatemove(dt); }, 0.0f, "animal_updatemove_key");

    Vector<SpriteFrame*> Animalup;
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(Move, Rect(i * Animalsize_x, Animalorder_up * Animalsize_y, Animalsize_x, Animalsize_y));
        Animalup.pushBack(frame);
    }
    Animation* uup = Animation::createWithSpriteFrames(Animalup, 0.3f);
    moveup = Animate::create(uup);
    moveup->setTag(1);

    Vector<SpriteFrame*>Animalleft;
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(Move, Rect(i * Animalsize_x, Animalorder_left * Animalsize_y, Animalsize_x, Animalsize_y));
        Animalleft.pushBack(frame);
    }
    Animation* lleft = Animation::createWithSpriteFrames(Animalleft, 0.3f);
    moveleft = Animate::create(lleft);
    moveleft->setTag(2);

    Vector<SpriteFrame*>Animalright;
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(Move, Rect(i * Animalsize_x, Animalorder_right * Animalsize_y, Animalsize_x, Animalsize_y));
        Animalright.pushBack(frame);
    }
    Animation* rright = Animation::createWithSpriteFrames(Animalright, 0.3f);
    moveright = Animate::create(rright);
    moveright->setTag(3);

    Vector<SpriteFrame*>Animaldown;
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(Move, Rect(i * Animalsize_x, Animalorder_down * Animalsize_y, Animalsize_x, Animalsize_y));
        Animaldown.pushBack(frame);
    }
    Animation* ddown = Animation::createWithSpriteFrames(Animaldown, 0.3f);
    movedown = Animate::create(ddown);
    movedown->setTag(4);

    // �������ֱ�ǩ
    sheep_feed_label = cocos2d::Label::createWithSystemFont("The sheep has been fed.Obtain Wool x1", "Arial", 10);
    sheep_feed_label->setVisible(false); // ��ʼʱ����
    this->addChild(sheep_feed_label);
    sheep_feed_label->setPosition(cocos2d::Vec2(20, 40));

    Sheep::addKeyboardListener();
    this->schedule(CC_SCHEDULE_SELECTOR(Sheep::isMainCharNear), 0.1f);

    return true;
}

void Sheep::isMainCharNear(float delta)
{
    Vec2 sprite1Position = mainChar->getPosition(); // ��ȡ���ǵ�λ��(��Ե�ͼ���½�)
    Vec2 sprite2Position = this->getPosition(); // ��ȡ��ͼ��λ��(��Ե�ͼ���½�)

    float distance = sprite1Position.distance(sprite2Position);

    // �������С��ĳ��ֵ�����ñ�־λ
    if (distance < 50)
    {
        isNearSprite = true;
    }
    else
    {
        isNearSprite = false;
    }
}

void Sheep::move(Sheep* sheep, TMXTiledMap* map) {
    map->addChild(sheep);
    sheep->setScale(1.5f);
    sheep->setPosition(Vec2(950, 500));
    Sequence* move_cow = Sequence::create(sheep->moveup, sheep->moveright, sheep->moveleft, sheep->movedown, NULL);
    sheep->runAction(RepeatForever::create(move_cow));
    std::vector<Vec2> path_cow = { Vec2(950, 500), Vec2(950, 545), Vec2(1070, 500),Vec2(1070, 545) };
    sheep->setPath(path_cow);
}

int Chicken::Animalsize_x = 16;
int Chicken::Animalsize_y = 20;

int Chicken::Animalorder_up = 2;
int Chicken::Animalorder_left = 3;
int Chicken::Animalorder_right = 1;
int Chicken::Animalorder_down = 0;

Chicken* Chicken::create(const std::string& filename)
{
    Chicken* chicken = new Chicken();
    if (chicken) {
        chicken->animalName = filename;
        if (chicken->init()) {
            chicken->autorelease(); // �Զ��ͷ��ڴ�
            return chicken;
        }
    }
    CC_SAFE_DELETE(chicken); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

void Chicken::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (isNearSprite && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_E)
    {
        chicken_feed_label->setVisible(true); // ��ʾ����

        // ������ʱ����3�����������
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(Cow::hideLabel), 3.0f);
    }
}

// ��Ӽ����¼�����
void Chicken::addKeyboardListener() {
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Chicken::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

//��ǩ����
void Chicken::hideLabel(float dt)
{
    chicken_feed_label->setVisible(false); // ��������
}

//��ʼ��
bool Chicken::init()
{
    //��������
    Texture2D* Move = Director::getInstance()->getTextureCache()->addImage("Animal/" + animalName + "/texture.png");

    if (!Sprite::initWithFile("Animal/" + animalName + "/static.png")) { return false; }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    speed = 50.0f;//�����ٶ�
    currentPathIndex = 0;//��ʼ·��
    ifSelected = false;//���Animalδ��ѡ��

    // ����λ�ø��º���
    schedule([=](float dt) {updatemove(dt); }, 0.0f, "animal_updatemove_key");

    Vector<SpriteFrame*> Animalup;
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(Move, Rect(i * Animalsize_x, Animalorder_up * Animalsize_y, Animalsize_x, Animalsize_y));
        Animalup.pushBack(frame);
    }
    Animation* uup = Animation::createWithSpriteFrames(Animalup, 0.3f);
    moveup = Animate::create(uup);
    moveup->setTag(1);

    Vector<SpriteFrame*>Animalleft;
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(Move, Rect(i * Animalsize_x, Animalorder_left * Animalsize_y, Animalsize_x, Animalsize_y));
        Animalleft.pushBack(frame);
    }
    Animation* lleft = Animation::createWithSpriteFrames(Animalleft, 0.3f);
    moveleft = Animate::create(lleft);
    moveleft->setTag(2);

    Vector<SpriteFrame*>Animalright;
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(Move, Rect(i * Animalsize_x, Animalorder_right * Animalsize_y, Animalsize_x, Animalsize_y));
        Animalright.pushBack(frame);
    }
    Animation* rright = Animation::createWithSpriteFrames(Animalright, 0.3f);
    moveright = Animate::create(rright);
    moveright->setTag(3);

    Vector<SpriteFrame*>Animaldown;
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(Move, Rect(i * Animalsize_x, Animalorder_down * Animalsize_y, Animalsize_x, Animalsize_y));
        Animaldown.pushBack(frame);
    }
    Animation* ddown = Animation::createWithSpriteFrames(Animaldown, 0.3f);
    movedown = Animate::create(ddown);
    movedown->setTag(4);

    // �������ֱ�ǩ
    chicken_feed_label = cocos2d::Label::createWithSystemFont("The chicken has been fed.Obtain Egg x1", "Arial", 10);
    chicken_feed_label->setVisible(false); // ��ʼʱ����
    this->addChild(chicken_feed_label);
    chicken_feed_label->setPosition(cocos2d::Vec2(20, 40));

    Chicken::addKeyboardListener();
    this->schedule(CC_SCHEDULE_SELECTOR(Chicken::isMainCharNear), 0.1f);

    return true;
}

void Chicken::isMainCharNear(float delta)
{
    Vec2 sprite1Position = mainChar->getPosition(); // ��ȡ���ǵ�λ��(��Ե�ͼ���½�)
    Vec2 sprite2Position = this->getPosition(); // ��ȡ��ͼ��λ��(��Ե�ͼ���½�)

    float distance = sprite1Position.distance(sprite2Position);

    log("distance: %f", distance);
    log("sprite1Position: %f", sprite1Position.y);
    log("sprite2Position: %f", sprite2Position.y);
    // �������С��ĳ��ֵ�����ñ�־λ
    if (distance < 100)
    {
        isNearSprite = true;
    }
    else
    {
        isNearSprite = false;
    }
}

void Chicken::move(Chicken* chicken, TMXTiledMap* map) {
    map->addChild(chicken);
    chicken->setScale(1.5f);
    chicken->setPosition(Vec2(1070, 325));
    Sequence* move_cow = Sequence::create(chicken->moveup, chicken->moveright, chicken->moveleft, chicken->movedown, NULL);
    chicken->runAction(RepeatForever::create(move_cow));
    std::vector<Vec2> path_cow = { Vec2(1070, 325), Vec2(950, 325), Vec2(1070, 260),Vec2(950, 260) };
    chicken->setPath(path_cow);
}

