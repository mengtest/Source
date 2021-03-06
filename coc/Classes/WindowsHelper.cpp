#include "Base.h"
#include "WindowsHelper.h"

#define SYSTEM_NORMAL_CURSOR 32512

static WindowsHelper* s_windowsHelper = nullptr;

WindowsHelper::~WindowsHelper()
{
    uninitInstane();
}

WindowsHelper* WindowsHelper::getInstance()
{
    if (s_windowsHelper == nullptr)
    {
        s_windowsHelper = new WindowsHelper();
        s_windowsHelper->init();
    }

    return s_windowsHelper;
}

bool WindowsHelper::init()
{
    _systemDefaultCursor = CopyCursor(LoadCursor(nullptr, IDC_ARROW));
    _attackCursorHandle = LoadCursorFromFile(L"../Resources/publish/cursor/cursor_attack.cur");
    _normalCursorHandle = LoadCursorFromFile(L"../Resources/publish/cursor/cursor_normal.cur");

    return true;
}

void WindowsHelper::uninitInstane()
{
    DestroyCursor(_attackCursorHandle);
    DestroyCursor(_normalCursorHandle);

    SetSystemCursor(_systemDefaultCursor, SYSTEM_NORMAL_CURSOR);
}

void WindowsHelper::switchToDefaultCursor()
{
    auto defaultCursorHandle = CopyCursor(_systemDefaultCursor);
    SetSystemCursor(defaultCursorHandle, SYSTEM_NORMAL_CURSOR);

    _cursorType = CursorType::Default;
}

void WindowsHelper::switchToAttackCursor()
{
    auto attackCursorHandle = CopyCursor(_attackCursorHandle);
    SetSystemCursor(attackCursorHandle, SYSTEM_NORMAL_CURSOR);

    _cursorType = CursorType::Attack;
}

void WindowsHelper::switchToNormalCursor()
{
    auto normalCursorHandle = CopyCursor(_normalCursorHandle);
    SetSystemCursor(normalCursorHandle, SYSTEM_NORMAL_CURSOR);

    _cursorType = CursorType::Normal;
}

CursorType WindowsHelper::getCursorType()
{
    return _cursorType;
}
