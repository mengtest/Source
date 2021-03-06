#pragma once

class MapManager;
class Npc;
class GameObjectManager;
class GameObjectSelectBox;
class BulletManager;
class SpecialEffectManager;
class ForceManager;
class GameUICallbackFunctionsManager;
class SoundManager;

struct DebugInfo
{
    MapDebugInfo mapDebugInfo;

    int gameObjectCount = 0;
};

class GameWorld : public Node
{
public:
    ~GameWorld();
	CREATE_FUNC(GameWorld);

    GameObject* createGameObject(GameObjectType gameObjectType, ForceType forceType, const string& jobName, const Vec2& position);
    void removeGameObjectBy(int uniqueID);

    void createBullet(BulletType bulletType, int attackerID, int attackTargetID);
    void createSpecialEffect(const string& templateName, const Vec2& inMapPosition, bool isRepeat);

    void onMouseLeftButtonDown();
    void onMouseLeftButtonUp();
    void onMouseRightButtonDown();
    void onMouseRightButtonUp();
    void onMouseMove(EventCustom* eventCustom);
    void onClearDebugDraw();

    void syncCursorPoint(const Vec2& cursorPoint);

    list<Vec2>  computePathList(const Vec2& inMapStartPosition, const Vec2& inMapEndPosition, bool isAllowEndTileNodeToMoveIn = false);
    MapManager* getMapManager();
    const DebugInfo& getDebugInfo();
    void createReinforcement(ForceType forceType, const string& npcTemplateName, int npcCount);    

    int getEnemyBaseCampUniqueID();
    int getPlayerBaseCampUniqueID();

    void setShiftKeyStatus(bool isPressed);
    void setCtrlKeyStatus(bool isPressed);
    void sendMopUpCommandForPlayerForce();

    bool isMouseClick();

    void onPlayerManipulateTeamBy(int teamID);
    void onJumpToPlayerBaseCamp();

    bool isPlayerHoldingBuilding();

    void onSelectGameObjectEvent();

    void pauseGame();
private:
    bool init() override;
    void initEditedGameObjects();
    void initMapGIDTable();

    void update(float deltaTime) override;
    void onMouseScroll(Event* event);
    void constructBuilding();
    void cancelConstructBuilding();

    vector<Vec2> computeNpcCreatePointList(int buildingUniqueID, int readyToCreateNpcCount, bool shouldRefreshMap);

    bool isLeftButtonMultyClick();
    bool isTeamContinuousCalledInAFlash(int teamID);

    void updateCursor();

    bool isPlayerBaseCampDestroy();
    bool isAIBaseCampDestroy();

    void onWin();
    void onLost();

    void clear();

    void delayAjustScreen();

    GameObjectManager* _gameObjectManager = nullptr;
    GameObjectSelectBox* _gameObjectSelectBox = nullptr;
    BulletManager* _bulletManager = nullptr;
    SpecialEffectManager* _specialEffectManager = nullptr;
    MapManager* _mapManager = nullptr;
    ForceManager* _forceManager = nullptr;
    GameUICallbackFunctionsManager* _gameUI = nullptr;
    SoundManager* _soundManager = nullptr;

    Vec2 _cursorPoint;
    Vec2 _previousClickedCursorPoint;

    bool _isLeftMouseButtonDown = false;
    bool _isShiftKeyPressed = false;
    bool _isCtrlKeyPressed = false;
    bool _hasSendMopUpCommandForPlayerForce = false;

    int _holdingBuildingID = GAME_OBJECT_UNIQUE_ID_INVALID;

    DebugInfo _debugInfo;

    int _playerBaseCampUniqueID = GAME_OBJECT_UNIQUE_ID_INVALID;
    int _aiBaseCampUniqueID = GAME_OBJECT_UNIQUE_ID_INVALID;
    vector<vector<int>> _mapGIDTable;   // 这个表用于寻找npc出兵点位置，如果场景中有npc，那么此npc所占用的格子算作障碍格

    vector<GameObject*> _pillboxList;   // 可相互争夺的建筑物列表
};