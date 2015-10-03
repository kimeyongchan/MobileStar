#include "GameWorld.h"
#include "AStarAlgorithm.h"

Scene* GameWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameWorld::create();
    
    scene->addChild(layer);
    
    return scene;
}

GameWorld::GameWorld(){
    //카메라 레이어 초기화
    m_pCameraLayer = Layer::create();
    addChild(m_pCameraLayer, 0);
    
    //UI 레이어 초기화
    m_pUILayer = Layer::create();
    addChild(m_pUILayer, 1);
    
    //맵 생성
    m_pMap = new GameMap();
    //m_pMap->LoadMap(TILE_WIDTH_NUM * TILE_SIZE / NODE_SIZE, TILE_HEIGHT_NUM * TILE_SIZE / NODE_SIZE);
    m_pMap->LoadMap(10,5);
    m_pCameraLayer->addChild(m_pMap);
    
    //마린 생성
    auto pMarine = new Marine(this,5);
    m_pCameraLayer->addChild(pMarine);
    m_Units.pushBack(pMarine);
    
    //카메라 설정 : 맵 크기 (64*256, 64*256)
    CameraMgr->SetScreen(TILE_WIDTH_SIZE*TILE_WIDTH_NUM, TILE_HEIGHT_SIZE*TILE_HEIGHT_NUM);
    CameraMgr->SetMovePos(0,100);
    
    //네트워크 매니저 초기화
    NetMgr->SetGameWorld(this);

}

GameWorld::~GameWorld(){
}

void GameWorld::onEnter(){
    Layer::onEnter();
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameWorld::TouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameWorld::TouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameWorld::TouchCancelled, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameWorld::TouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    scheduleUpdate();
    
    schedule(schedule_selector(GameWorld::updateNetwork),0.083);
}

void GameWorld::update(float eTime){
    //카메라 업데이트
    CameraMgr->Update(eTime);
    m_pCameraLayer->setPosition(-CameraMgr->GetPos());
    
    //유닛 업데이트
    for(auto pUnit : m_Units){
        pUnit->update(eTime);
    }
}

//1초에 4번 실행된다.
void GameWorld::updateNetwork(float eTime){
    //DispatchTask에 쌓인 메시지를 서버로 보낸다.
    NetMgr->DispatchToServer();
    
    //Task에 쌓인 메시지를 처리한다.
    NetMgr->CarryOutMessages();
}
bool GameWorld::TouchBegan(Touch* touch, Event* _event){
    for(auto pUnit : m_Units){
        pUnit->TouchBegan(touch, _event);
    }
    
    return true;
}
void GameWorld::TouchMoved(Touch* touch, Event* _event){
    for(auto pUnit : m_Units){
        pUnit->TouchMoved(touch, _event);
    }
}
void GameWorld::TouchCancelled(Touch* touch, Event* _event){
    for(auto pUnit : m_Units){
        pUnit->TouchCancelled(touch, _event);
    }
    
    TouchEnded(touch, _event);
}
void GameWorld::TouchEnded(Touch* touch, Event* _event){
    for(auto pUnit : m_Units){
        pUnit->TouchEnded(touch, _event);
    }
}