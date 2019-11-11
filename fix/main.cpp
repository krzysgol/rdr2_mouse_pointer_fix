#include "windows.h"

namespace {

static const UINT TIMER_INTERVAL_MS = 1000;
static constexpr const char* GAME_WINDOW_NAME = "Red Dead Redemption 2";
static constexpr const char* APP_MUTEX_NAME = "RDR2_MOUSE_POINTER_FIX_MTX";
static constexpr const char* APP_CAPTION = "RDR2 Mouse Fix";
static constexpr const char* ACTIVATE_TEXT = "Activating RDR2 Mouse Fix";
static constexpr const char* ALREADY_ACTIVATED_TEXT = "RDR2 Mouse Fix already activated";
static constexpr const char* DEACTIVATE_TEXT = "Deactivated RDR2 Mouse Fix";
static UINT_PTR Timer = NULL;
static HANDLE Mutex = NULL;
static bool WasGameRunning = false;
static bool ExitScheduled = false;


inline bool IsGameRunning()
{
    auto isRunning = ::FindWindow(NULL, GAME_WINDOW_NAME) != NULL;
    if (!isRunning && WasGameRunning)
        ExitScheduled = true;

    WasGameRunning = isRunning;
    return isRunning;   
}

boolean IsAnotherInstanceRunning()
{
    Mutex = ::CreateMutex(NULL, false, APP_MUTEX_NAME);
    if (Mutex == NULL)
        return true;

    return ::GetLastError() == ERROR_ALREADY_EXISTS;
}

void CALLBACK TimerProc(HWND, UINT, UINT_PTR timerId, DWORD)
{
    if (timerId != Timer || !IsGameRunning())
        return;

    POINT point = {};
    ::GetCursorPos(&point);

    // Right edge of rightmost display
    auto rightEdgePos = ::GetSystemMetrics(SM_CXVIRTUALSCREEN) - 1;
    if (point.x < rightEdgePos)
        ::SetCursorPos(rightEdgePos, point.y);
}

} // namespace


int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    if (IsAnotherInstanceRunning())
    {
        ::MessageBox(NULL, ALREADY_ACTIVATED_TEXT, APP_CAPTION, MB_OK);
        return 1;
    }
        
    ::MessageBox(NULL, ACTIVATE_TEXT, APP_CAPTION, MB_OK);

    Timer = ::SetTimer(NULL, 0, TIMER_INTERVAL_MS, &TimerProc);

    MSG msg = {};
    while (::GetMessage(&msg, NULL, 0, 0))
    {
        ::DispatchMessage(&msg);
        if (ExitScheduled)
            break;
    }
    
    ::KillTimer(NULL, Timer);
    ::CloseHandle(Mutex);

    ::MessageBox(NULL, DEACTIVATE_TEXT, APP_CAPTION, MB_OK);
    return 0;
}
