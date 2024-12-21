#include "ingredient.h"
USING_NS_CC;

bool CookLayer::init() {
    // ������Ʒ
    
    createItems();

    // ����UI����
    createMenu();
    this->retain();
    // ��ʼ�������¼�������
    initKeyboardListener();
    toggleMenuVisibility();//һ��ʼ�ȹرս���
    listener->setEnabled(false); // ���ð�������
    updateUI();
    return true;
}

void CookLayer::createItems() {
    ingredients.push_back(Iingredients("Milk", &milk_number, "milk.png"));
    ingredients.push_back(Iingredients("Egg", &egg_number, "egg.png"));
    ingredients.push_back(Iingredients("Cake", &cake_number, "cake.png"));
    ingredients.push_back(Iingredients("Carrot", &carrot_number, "carrot.png"));
    ingredients.push_back(Iingredients("Wheat", &wheat_number, "wheat.png"));
    ingredients.push_back(Iingredients("Soup", &soup_number, "soup.png"));
}

void CookLayer::createMenu() {
    // ��ȡ��Ļ�Ŀɼ��ߴ��ԭ��
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // ����λ�õ�X��Y����
    float centerX = origin.x + visibleSize.width / 2;
    float centerY = origin.y + visibleSize.height / 2;

    // ��ʼ����������ʼλ��
    float startX = centerX - 150;  // �õ�һ����Ʒ��ƫ���Ծ�������
    float yPos = centerY+100;  // ������Ʒ��Y���걣��һ��

    // ������Ʒ
    for (int i = 0; i < ingredients.size(); ++i) {
        auto& item = ingredients[i];

        // ������Ʒͼ��
        auto itemSprite = cocos2d::Sprite::create(item.imageFile);
        itemSprite->setPosition(cocos2d::Vec2(startX + (i % 3) * 150, yPos));  // ��������
        this->addChild(itemSprite);
        if (i == 0)
        {
            itemSprite->setScale(0.5f);  // ��Сͼ��
            itemSprite->setTag(i + 8);
        }
        else if (i == 1)
        {
            itemSprite->setScale(0.625f);  // ��Сͼ��
            itemSprite->setTag(i + 8);
        }
        else if (i == 2)
        {
            itemSprite->setScale(0.533f);  // ��Сͼ��
            itemSprite->setTag(i + 8);
        }
        else if (i == 3)
        {
            itemSprite->setScale(0.3125f);  // ��Сͼ��
            itemSprite->setTag(i + 8);
        }
        else if (i == 4)
        {
            itemSprite->setScale(0.8f);  // ��Сͼ��
            itemSprite->setTag(i + 8);
        }
        else if (i == 5)
        {
            itemSprite->setScale(0.4f);  // ��Сͼ��
            itemSprite->setTag(i + 8);
        }
        // ������Ʒ��������ʾ
        auto quantityLabel = cocos2d::Label::createWithTTF(std::to_string(*item.quantity), "fonts/Marker Felt.ttf", 24);
        quantityLabel->setPosition(cocos2d::Vec2(startX + (i % 3) * 150, yPos - 50));  // ����ͼ���·�
        quantityLabel->setTag(i);  // ���ñ�ǩ�Ա��ڰ�ť����¼��л�ȡ
        this->addChild(quantityLabel);

        // �����ϳɰ�ť
        if (i == 2) {
            auto combineButton = cocos2d::ui::Button::create("combine_button.jpg", "combine_button.jpg");  // ���ð�ť�ı���ͼƬ
            combineButton->setTitleText("Combine");
            combineButton->setTitleFontSize(15);  // ���ð�ť�ı������С
            combineButton->setTitleColor(cocos2d::Color3B::BLACK);  // ���ð�ť�ı���ɫ
            combineButton->setPosition(cocos2d::Vec2(startX + (i % 3) * 150, yPos - 80));  // �ϳɰ�ť����������ǩ�·�
            combineButton->addClickEventListener([this, &item](cocos2d::Ref* sender) {
                onCombineButtonClicked1(item);  // ��ť����¼�
                });
            this->addChild(combineButton);
            if(i==2)
                combineButton->setTag(6);// ���ñ�ǩ�Ա��ڰ�ť����¼��л�ȡ
            else if(i==5)
                combineButton->setTag(7);// ���ñ�ǩ�Ա��ڰ�ť����¼��л�ȡ
        }
        // �����ϳɰ�ť
        if (i == 5) {
            auto combineButton = cocos2d::ui::Button::create("combine_button.jpg", "combine_button.jpg");  // ���ð�ť�ı���ͼƬ
            combineButton->setTitleText("Combine");
            combineButton->setTitleFontSize(15);  // ���ð�ť�ı������С
            combineButton->setTitleColor(cocos2d::Color3B::BLACK);  // ���ð�ť�ı���ɫ
            combineButton->setPosition(cocos2d::Vec2(startX + (i % 3) * 150, yPos - 80));  // �ϳɰ�ť����������ǩ�·�
            combineButton->addClickEventListener([this, &item](cocos2d::Ref* sender) {
                onCombineButtonClicked2(item);  // ��ť����¼�
                });
            this->addChild(combineButton);
            if (i == 2)
                combineButton->setTag(6);// ���ñ�ǩ�Ա��ڰ�ť����¼��л�ȡ
            else if (i == 5)
                combineButton->setTag(7);// ���ñ�ǩ�Ա��ڰ�ť����¼��л�ȡ
        }

        if (i == 2) {
            yPos -= 150;  // ����
        }
    }
}


void CookLayer::onCombineButtonClicked1(Iingredients& ingredient) {
    if (ingredient.ingredientsName == "Cake") {
        bool canCombine = true;

        for (auto& material : ingredients) {
            if (material.ingredientsName == "Milk" && !material.consumeQuantity(5)) {
                canCombine = false;
            }
            if (material.ingredientsName == "Egg" && !material.consumeQuantity(5)) {
                canCombine = false;
            }
        }

        if (canCombine) {
            ingredient.addQuantity(1);
            CCLOG("Successfully created a Potion!");
        }
        else {
            CCLOG("Not enough materials.");
        }
    }

    //updateUI();
}
void CookLayer::onCombineButtonClicked2(Iingredients& ingredient) {
    if (ingredient.ingredientsName == "Soup") {
        bool canCombine = true;

        for (auto& material : ingredients) {
            if (material.ingredientsName == "Carrot" && !material.consumeQuantity(5)) {
                canCombine = false;
            }
            if (material.ingredientsName == "Wheat" && !material.consumeQuantity(5)) {
                canCombine = false;
            }
        }

        if (canCombine) {
            ingredient.addQuantity(1);
            CCLOG("Successfully created a Potion!");
        }
        else {
            CCLOG("Not enough materials.");
        }
    }

    updateUI();
}
void CookLayer::updateUI() {

    this->schedule([this](float dt) {
        // �����д��Ҫִ�е��߼�
        for (int i = 0; i < ingredients.size(); i++) {
            auto label = (cocos2d::Label*)this->getChildByTag(i);
            label->setString(std::to_string(*(ingredients[i].quantity)));
        }
        }, 0.2f, "lambda_key_cook"); // ʹ��һ��������ʶ�������
}

CookLayer* CookLayer::create() {
    CookLayer* ret = new CookLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

void CookLayer::initKeyboardListener() {
     listener = cocos2d::EventListenerKeyboard::create();

    // ���ð����¼�������
    listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
        if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_I) {
            toggleMenuVisibility();  // �л��ϳɲ˵�����ʾ��ر�
        }
        };

    // ��ȡ�¼��ַ�������Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// �л��˵���ʾ������
void CookLayer::toggleMenuVisibility() {
    menuVisible = !menuVisible;  // �л�״̬
    for (int i = 0; i < ingredients.size()+8; i++) {
        this->getChildByTag(i)->setVisible(menuVisible);  // ���úϳɰ�ť�Ŀɼ���
    }
}
