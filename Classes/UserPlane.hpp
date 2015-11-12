//
//  UserPlane.hpp
//  SimpleGame
//
//  Created by cb on 15/11/12.
//
//

#ifndef UserPlane_hpp
#define UserPlane_hpp

#include <stdio.h>
#include <cocos2d.h>
using namespace cocos2d;
class UserPlane: public Sprite {
    
public:
    static Sprite * createSprite();
    virtual bool init();
    CREATE_FUNC(UserPlane);
    
};

#endif /* UserPlane_hpp */
