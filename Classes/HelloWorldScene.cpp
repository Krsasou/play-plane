#include "HelloWorldScene.h"
#include "UserPlane.hpp"
USING_NS_CC;


enum class PhysicsCategory {
    None = 0,
    Monset = ( 1 << 0),
    Bullet = ( 1 << 1),
    Plane  = ( 1 << 2),
    PlaneModel    = ( PhysicsCategory::Bullet | PhysicsCategory::Plane)
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    winSize = Director::getInstance()->getVisibleSize();
    originSize = Director::getInstance()->getVisibleOrigin();
    centerX = winSize.width / 2 + originSize.x;
    centerY = winSize.height / 2 + originSize.y;
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    this->createBackground();
    
    
    scheduleUpdate();
    
    this->createLabel();
    
    this->createPlane();
    
    srand((unsigned) time(nullptr));
    schedule(schedule_selector(HelloWorld::addMonster), 1);
    schedule(schedule_selector(HelloWorld::addBullet),0.1);
    
    
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2( HelloWorld::onStartPlane, this);
    eventListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onMovePlane, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onEndPlane, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _plane);
    
    auto contactEvent = EventListenerPhysicsContact::create();
    contactEvent->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactEvent, this);
    
    return true;
}







//MAKR:  创建背景

void HelloWorld::createBackground() {
    backgroundA = Sprite::create("backgroud.png");
    backgroundA->setPosition(Vec2(centerX, centerY));
    
    backgroundB = Sprite::create("backgroud.png");
    backgroundB->setPosition(Vec2(centerX , centerY * 3));
    
    
    addChild(backgroundA);
    addChild(backgroundB);
}



void HelloWorld::update(float delta) {
    backgroundA->setPositionY(backgroundA->getPositionY() - 1);
    backgroundB->setPositionY(backgroundB->getPositionY() - 1);
    
    
    Rect boundA = backgroundA->getBoundingBox();
    if (boundA.getMaxY() <= 0 ) {
        backgroundA->setPositionY(centerY * 3);
    }
    Rect boundB = backgroundB->getBoundingBox();
    if (boundB.getMaxY() <= 0) {
        backgroundB->setPositionY(centerY * 3);
    }
    
}


void HelloWorld::createLabel() {
    
    char scoreStr[15];
    sprintf(scoreStr, "SCORE: %d", 0);
    scoreLabel = Label::createWithTTF( scoreStr , "fonts/Marker Felt.ttf", 15);

    auto size = scoreLabel->getContentSize();
    scoreLabel->setPosition(Vec2(winSize.width + originSize.x - size.width / 2 , winSize.height + originSize.y - size.height / 2));
    
    addChild(scoreLabel);
}


void HelloWorld::upDateScore() {
    char scoreStr[15];
    sprintf(scoreStr, "SCORE: %d", score);
    
    scoreLabel->setString(scoreStr);
    auto size = scoreLabel->getContentSize();
    
    scoreLabel->setPosition(Vec2(winSize.width + originSize.x - size.width / 2 , winSize.height + originSize.y - size.height / 2));
}



//MARK: 创建主角飞机
void HelloWorld::createPlane() {
//    _plane = Sprite::create("enemyplane.png");
    _plane = UserPlane::create();
    auto planeContentSize = _plane->getContentSize();
    
    auto body = PhysicsBody::createBox(planeContentSize);
    
    body->setDynamic(true);
    body->setCategoryBitmask((int) PhysicsCategory::Plane);
    body->setCollisionBitmask((int) PhysicsCategory::None);
    body->setContactTestBitmask((int) PhysicsCategory::Monset);
    
    _plane->setPhysicsBody(body);
    
    
    _plane->setPosition(Vec2(centerX , planeContentSize.height / 2 + originSize.y ));
    addChild(_plane);
}



//MARK: 当发生碰撞时
bool HelloWorld::onContactBegan(PhysicsContact &contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    if (nodeB == _plane || nodeA == _plane) {
        this->gameOver();
        return false;
    }
    
    
    
    if (nodeA != NULL ) {
        nodeA->removeFromParent();
    }
    if (nodeB != NULL) {
        nodeB->removeFromParent();
    }
    
    score++;
    this->upDateScore();
    
    return true;
    
}

//MARK: 游戏结束
void HelloWorld::gameOver() {
    //TODO 游戏结束
}

bool HelloWorld::onStartPlane(Touch *touch, Event *event) {
    
    if (!event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
        return false;
    }
    return true;
}


//MARK: 移动飞机
bool HelloWorld::onMovePlane(Touch *touch, Event *event) {
    auto postion = touch->getLocation();
    auto planeContentSize = _plane->getContentSize();
    postion.x = postion.x <= originSize.x + planeContentSize.width / 2  ? originSize.x + planeContentSize.width / 2 : (postion.x > winSize.width + originSize.x - planeContentSize.width / 2 ? winSize.width + originSize.x - planeContentSize.width / 2 : postion.x);
    
    
    
    postion.y  =  postion.y < planeContentSize.height / 2 + originSize.y ? planeContentSize.height / 2 + originSize.y : ( postion.y > winSize.height + originSize.y - planeContentSize.height / 2 ? winSize.height + originSize.y - planeContentSize.height / 2 : postion.y );
    _plane->setPosition(postion);
    return true;
}


bool HelloWorld::onEndPlane(Touch *touch, Event *event){
    return true;
}

void HelloWorld::addBullet(float dt) {
    auto bullet = Sprite::create("planebullet.png");
    
    auto planePosition = _plane->getPosition();
    auto planeContentSize = _plane->getContentSize();
    auto bulletContent = bullet->getContentSize();
    
    auto body = PhysicsBody::createBox(bulletContent);
    
    body->setDynamic(true);
    body->setCategoryBitmask((int) PhysicsCategory::Bullet);
    body->setCollisionBitmask((int) PhysicsCategory::None);
    body->setContactTestBitmask((int) PhysicsCategory::Monset);
    
    
    bullet->setPhysicsBody(body);
    
    bullet->setPosition(Vec2(planePosition.x , planePosition.y + planeContentSize.height / 2));
    auto moveActin = MoveTo::create(1, Vec2(planePosition.x, winSize.height));
    auto removeAction = RemoveSelf::create();
    bullet->runAction(Sequence::create(moveActin, removeAction, nullptr));
    addChild(bullet);
    
}


void HelloWorld::addMonster(float dt) {
    auto pinfo = AutoPolygon::generatePolygon("enemyplanee2.png");
    auto monster = Sprite::create(pinfo);
    auto monsterContentSize = monster->getContentSize();
    
    auto physicsBody = PhysicsBody::createBox(monsterContentSize);
    physicsBody->setDynamic(true);
    
    physicsBody->setCategoryBitmask((int) PhysicsCategory::Monset);
    physicsBody->setCollisionBitmask((int) PhysicsCategory::None);
    physicsBody->setContactTestBitmask((int) PhysicsCategory::PlaneModel);
    monster->setPhysicsBody(physicsBody);
    int minX = monsterContentSize.width /2 + originSize.x;
    int maxX = winSize.width + originSize.x - monsterContentSize.width / 2;
    int rangeX = maxX - minX;
    int randX = (rand() % rangeX) + minX;
    Vec2 position = Vec2(randX, winSize.height + originSize.y - monsterContentSize.height / 2);
    monster->setPosition(position);
//    monster->setAnchorPoint(Vec2(0, 0));
    int minDuration = 2.0;
    int maxDuration = 4.0;
    int rangDuration = maxDuration - minDuration;
    int randDuration = (rand() % rangDuration) + minDuration;
    
    
    auto moveAction = MoveTo::create(randDuration, Vec2(position.x, 0));
    auto removeAction = RemoveSelf::create();
    
    monster->runAction(Sequence::create(moveAction, removeAction ,nullptr));
    
    addChild(monster);
    
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
