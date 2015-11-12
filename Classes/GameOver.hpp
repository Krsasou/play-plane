//
//  GameOver.hpp
//  SimpleGame
//
//  Created by cb on 15/11/12.
//
//

#ifndef GameOver_hpp
#define GameOver_hpp
#include "cocos2d.h"
#include <stdio.h>


using namespace cocos2d;

class GameOver: public Layer {

    public :
    
    static Scene * createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameOver);

    
};



#endif /* GameOver_hpp */
