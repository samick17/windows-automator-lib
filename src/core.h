#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include "color.h"
#include "size.h"
#include "rect.h"
#include "procInfo.h"

class Core {
public:
    std::vector<ProcInfo> GetAllWindows();
    void SendCharByScanCode(int scanCode);
    void SendKeyByVkValue(int vk);
    void SendKey(std::string vkKey);
    void KeyDownByVKValue(int vk);
    void KeyDown(std::string vkKey);
    void KeyUpByVKValue(int vk);
    void KeyUp(std::string vkKey);
    void SendChar(char ch);
    void CombinationKeyByVKValue(std::vector<int> vks);
    void CombinationKey(std::vector<std::string> vkKeys);

    void MouseMove(int x, int y);//mouse move by screen coord
    void MouseMoveRelative(int x, int y);//mouse move by active window coord
    void MouseMoveOffset(int x, int y);//mouse move by cursor position
    int GetScreenX();
    int GetScreenY();
    Size Core::GetWinSize(HWND hwnd);
    Size Core::GetWinSize();
    Rect Core::GetWinRect(HWND hwnd);
    Rect Core::GetWinRect();
    void SetActiveWindow(HWND hwnd);
    void SetActiveWindow(std::string name);
    Point GetMousePosition();
    boolean RegisterHotKeyWithId(int id, unsigned int modifierKey, unsigned int key);
    WPARAM GetMessageReceived();
    long GetPixelAtCursorPosition();
    long GetPixelAt(int x, int y);
    Color PixelToColor(long pixelValue);
    void AppendProcInfo(ProcInfo procInfo);
    ProcInfo GetProcInfoByName(std::string name);
    void SwitchToWindow(HWND hwnd);
    void SwitchToWindow(std::string name);
    void MouseLeftDown();
    void MouseLeftUp();
    void MouseMiddleDown();
    void MouseMiddleUp();
    void MouseRightDown();
    void MouseRightUp();
    void MouseWheel(int value);
    void HideWindow(HWND hwnd);
    void HideWindow(std::string name);
    void DestroyWindow(HWND hwnd);
    void DestroyWindow(std::string name);
    void CaptureScreen(HWND hwnd);
    static void Recycle();
    static Core* GetInstance();
    Size DesktopSize;
    Rect ActiveWindowRect;
private:
    Core();
    void Init();
    void SendKeyInput(KEYBDINPUT ki);
    void SendMouseInput(MOUSEINPUT mi);
    int ToScreenPosX(int x);
    int ToScreenPosY(int y);
    int ToAbsoluteScreenPosX(int x);
    int ToAbsoluteScreenPosY(int y);
    int ToOffsetPosX(int x, Point pt);
    int ToOffsetPosY(int y, Point pt);
    std::vector<ProcInfo> _procInfos;
};