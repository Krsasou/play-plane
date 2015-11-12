//
//  GameOver.cpp
//  SimpleGame
//
//  Created by cb on 15/11/12.
//
//

#include "GameOver.hpp"



Scene* GameOver::createScene() {
    
    Scene * scene = Scene::create();
    scene->addChild(GameOver::create());
    
    return scene;
    
}


bool GameOver::init() {
    
    return true;
}








