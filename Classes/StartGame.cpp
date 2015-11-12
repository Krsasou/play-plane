//
//  StartGame.cpp
//  SimpleGame
//
//  Created by cb on 15/11/12.
//
//

#include "StartGame.hpp"

USING_NS_CC;


#include "HelloWorldScene.h"
#define FONT "fonts/Marker Felt.ttf"
Scene * StartGame::createScene() {
    Scene * scene = Scene::create();
    scene->addChild(StartGame::create());
    
    return scene;
}



bool StartGame::init() {
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    winSize = Director::getInstance()->getVisibleSize();
    originSize = Director::getInstance()->getVisibleOrigin();
    
    Vec2 centerSize = Vec2(winSize.width / 2 + originSize.x , winSize.height / 2 + originSize.y);
    auto background = Sprite::create("rank_backgroud.png");
//    background->setAnchorPoint(Vec2(0, 0));
    background->setPosition(centerSize);
    addChild(background);
    
    
    auto label = Label::createWithTTF("Start Game", FONT, 24);
    auto menuLabel = MenuItemLabel::create(label, [](Ref* pSender) {
        auto trans = TransitionFadeBL::create(1, HelloWorld::createScene());
        Director::getInstance()->replaceScene(trans);
    });
    
    auto menu = Menu::create(menuLabel, nullptr);
    menu->setPosition(centerSize);
    
    addChild(menu);
    
    
    
    return true;
}

