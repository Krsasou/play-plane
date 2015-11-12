#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <string>
using namespace cocos2d;


#define FONT "fonts/Marker Felt.ttf"

class HelloWorld : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();
    virtual void update(float delta);
    void createPlane();
    void createLabel();
    void createBackground();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onStartPlane(Touch * touch, Event *event);
    bool onMovePlane(Touch * touch, Event *event);
    bool onEndPlane(Touch * touch, Event *event);
    
    bool onContactBegan(PhysicsContact &contact);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    
    void upDateScore();
    void gameOver(); 
    
    void addMonster(float dt);
    void addBullet(float dt);
    
    
    
    
    
    
protected:
    Size winSize;
    Point originSize;
    float centerX;
    float centerY;
    Sprite* _plane;
    int score = 0;
    Label *scoreLabel;
    
    
    Sprite *backgroundA;
    Sprite *backgroundB;
};

#endif // __HELLOWORLD_SCENE_H__
