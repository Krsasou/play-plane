//
//  StartGame.hpp
//  SimpleGame
//
//  Created by cb on 15/11/12.
//
//

#ifndef StartGame_hpp
#define StartGame_hpp
#include <cocos2d.h>
#include <stdio.h>


using namespace cocos2d;

class StartGame: public Layer {
    
    
    
public:
    static Scene * createScene();
    virtual bool init();
    CREATE_FUNC(StartGame);
private:
    Size winSize;
    Vec2 originSize;
    
    
};



#endif /* StartGame_hpp */
