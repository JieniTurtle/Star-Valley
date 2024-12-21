#include "Date.h"

Date* Date::create()
{
    Date* date = new Date;
    if (date) {
        if (date->init()) {
            date->autorelease(); // �Զ��ͷ��ڴ�
            return date;
        }
    }
    CC_SAFE_DELETE(date); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

bool Date::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    // date and day & night
    color_layer_ = LayerColor::create(Color4B(0, 0, 255, 0), visibleSize.width, visibleSize.height);
    if (hour > 21 || hour < 3) {
        color_layer_->setOpacity(128);
    }
    this->addChild(color_layer_, 6);

    // time
    auto time_background = Sprite::create("Menu/unpressed_buttom.png");
    float x = time_background->getContentSize().width * 0.6;
    float y = visibleSize.height - time_background->getContentSize().height * 0.6;
    time_background->setPosition(Vec2(x, y));
    this->addChild(time_background);

    time_label_ = Label::createWithTTF("", "Fonts/Marker Felt.ttf", 24);
    schedule(schedule_selector(Date::update), 1.0f); // ÿ�����һ��
    time_label_->setPosition(time_background->getContentSize() / 2);
    time_label_->setTextColor(Color4B(0, 0, 0, 255));
    time_background->addChild(time_label_, 2);

    return true;
}

void Date::update(float delta = 1.0f)
{
    std::string time_string = std::to_string(hour) + " : 00";
    time_label_->setString(time_string);
    if (hour == 15) {
        auto fade_back = FadeTo::create(seconds_a_day_ / 4, 128);
        color_layer_->runAction(fade_back);
    }
    else if (hour == 3) {
        auto fade = FadeTo::create(seconds_a_day_ / 4, 0);
        color_layer_->runAction(fade);
    }
    hour = (hour + 1) % 24;
    if (hour == 0)
        date++;
}