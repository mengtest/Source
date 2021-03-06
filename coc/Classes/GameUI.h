#pragma once

class DebugInfoLayer;
class GameWorld;
class MapManager;
class GameWorldCallBackFunctionsManager;
class ForceManager;

const float UPGRADE_TIME = 30.0f;

class GameUI : public Node
{
public:
    ~GameUI();

    CREATE_FUNC(GameUI);

    void onMouseMove(EventCustom* eventCustom);

    bool isCursorInGameMainUI();
    void disableAllReinforcementButtons();
    void enableAllReinforcementButtons();

    void onUpdateReinforcePresent();

    bool isShowDebugLayer();
    void setDebugLayerShowStatus(bool isShow);

    void showGameWinTips();
    void showGameLostTips();
private:
    bool init() override;
    void initReinforcePresent();
    void initMiniMapPresent();
    void initReinforcementSelectPanel();
    void initSelectReinforcementButton(Button* button, const string& reinforcementTemplateName, GameObjectType gameObjectType, int reinforcmentCount);
    void onSelectReinforcementButtonTouched(Ref* sender, Widget::TouchEventType touchType);
    void onCreateReinforcement(const string& reinforcementTempalteName, GameObjectType gameObjectType, int reinforcementCount);
    void onTurnToUpgradePanel(Ref* sender, Widget::TouchEventType touchType);
    map<Ref*, std::function<void()>> _onSelectReinforcementButtonTouchEventMap;
    map<string, Button*> _reinforceTemplateNameToButtonMap;

    void initUpgradePanel();
    void initUpgradeButton(Button* button, const string& gameObjectTemplateName);
    void onTurnToSelectReinforcePanel(Ref* sender, Widget::TouchEventType touchType);
    void onUpgradeButtonTouched(Ref* sender, Widget::TouchEventType touchType);
    void onUpgradeSuccess(Button* sender, int newLevel);
    void updateUpgradePanelTips();
    void showNeedTechnologyPoint(int needTechnologyPoint, const Color3B& color);
    void updateUpgradeButtonStatus();
    bool isUpgrading(Button* button);
    Layout* _upgradeTipsPanel = nullptr;
    map<Ref*, string> _upgradeButtonToTemplateNameMap;

    void initGameEndTips();
    Text* _winTips = nullptr;
    Text* _lostTips = nullptr;

    void initOptionPanel();
    void onOpenOptionPanel(Ref* sender, Widget::TouchEventType type);
    void onGameContinue(Ref* sender, Widget::TouchEventType type);
    void onGotoSelectStageScene(Ref* sender, Widget::TouchEventType type);
    void onGotoMenuScene(Ref* sender, Widget::TouchEventType type);
    void onBackToWindows(Ref* sender, Widget::TouchEventType type);
    Layout* _optionPanel = nullptr;

    void update(float deltaTime) override;
    void onReinforceButtonSparkMove();
    void updateMinimap();
    void onMinimapTouched(Ref* sender, Widget::TouchEventType touchType);

    void updateTechnologyPoint();
    void updateGamePassTime();

    void syncCursorPoint(const Vec2& cursorPoint);

    Sprite* createNextRankAt(Button* button, const string& childName);

    void clear();

    GameWorldCallBackFunctionsManager* _gameWorld = nullptr;
    ForceManager* _forceManager = nullptr;
    DebugInfoLayer* _debugInfoLayer = nullptr;
    Node* _gameMainUI = nullptr;
    Button* _askReinforceButton = nullptr;
    Sprite* _reinforceButtonSpark = nullptr;

    DrawNode* _minimapDrawNode = nullptr;
    ImageView* _minimapImage = nullptr;
    MapManager* _mapManager = nullptr;
    float _tileMapWidth = 0.0f;
    float _tileMapHeight = 0.0f;
    float _minimapWidth = 0.0f;
    float _minimapHeight = 0.0f;

    Vec2 _cursorPoint;

    vector<Button*> _reinforcementButtonList;
    vector<Button*> _upgradeButtonList;
};