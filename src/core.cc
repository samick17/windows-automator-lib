#include "core.h"
#include "vk.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <codecvt>
#include <math.h>
#include <codecvt>
#include <map>

#if defined(WIN32) || defined(_WIN32)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

Core *_instance = NULL;

const std::string KEY_MouseLeftDown = "left";
const std::string KEY_MouseLeftUp = "leftUp";
const std::string KEY_MouseMiddleDown = "middle";
const std::string KEY_MouseMiddleUp = "middleUp";
const std::string KEY_MouseRightDown = "right";
const std::string KEY_MouseRightUp = "rightUp";

MOUSEINPUT CreateMouseInput(int x, int y, int flag = 0, int data = 0) {
    MOUSEINPUT mi;
    mi.dx = x;
    mi.dy = y;
    mi.mouseData = data;
    mi.dwFlags = flag != 0 ? flag : 0x0001;
    mi.dwExtraInfo = 0;
    return mi;
}

std::map<std::string, MOUSEINPUT> MouseInputDict = std::map<std::string, MOUSEINPUT>
{
    { KEY_MouseLeftDown, CreateMouseInput(0, 0, 0x0002) },
    { KEY_MouseLeftUp, CreateMouseInput(0, 0, 0x0004) },
    { KEY_MouseMiddleDown, CreateMouseInput(0, 0, 0x0020) },
    { KEY_MouseMiddleUp, CreateMouseInput(0, 0, 0x0040) },
    { KEY_MouseRightDown, CreateMouseInput(0, 0, 0x0008) },
    { KEY_MouseRightUp, CreateMouseInput(0, 0, 0x0010) },
};

std::string toUpper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

int ToUint16(char* ch) {
    unsigned short n;
    memcpy(&n, ch, sizeof(unsigned short));
    int i = 0, arrToInt = 0;
    for (i = 0; i <= 2; i++)
        arrToInt = (arrToInt << 8) | ch[i];
    return arrToInt;
}

int VkToScanCode(int vk) {
    return MapVirtualKey(vk, MAPVK_VK_TO_VSC);
}

KEYBDINPUT CreateKeyInputByScan(int scanCode) {
    KEYBDINPUT ki;
    ki.wVk = 0;
    ki.wScan = scanCode;
    ki.dwFlags = 0x0004;
    ki.time = 0;
    ki.dwExtraInfo = 0;
    return ki;
}

KEYBDINPUT CreateKeyInputByVk(int vk) {
    KEYBDINPUT ki;
    ki.wVk = 0;
    ki.wScan = VkToScanCode(vk);
    ki.dwFlags = 0x0008;
    ki.time = 0;
    ki.dwExtraInfo = 0;
    return ki;
}

typedef struct KeyInfo
{
    int vk, scanCode;
} KeyInfo;

KeyInfo VkToKeyInfo(int vk)
{
    int scanCode = VkToScanCode(vk);
    return KeyInfo{ vk = vk, scanCode = scanCode };
}

KeyInfo ConvertToKeyInfo(char ch)
{
    int vk = VkKeyScan(ch);
    return VkToKeyInfo(vk);
}

KEYBDINPUT CreateKeyInputByChar(char ch)
{
    KeyInfo ki = ConvertToKeyInfo(ch);
    KEYBDINPUT kii;
    kii.wVk = ki.vk;
    kii.wScan = ki.scanCode;
    kii.dwFlags = 0x0004;
    kii.time = 0;
    kii.dwExtraInfo = 0;
    return kii;
}

KEYBDINPUT Clone(KEYBDINPUT ki) {
    return KEYBDINPUT(ki);
}

Core::Core() {
}

/*private*/
void Core::Init() {
    Size size = _instance->GetWinSize();
    _instance->DesktopSize = size;
}

void Core::SendKeyInput(KEYBDINPUT ki) {
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki = ki;
    SendInput(1, &ip, sizeof(INPUT));
}

void Core::SendMouseInput(MOUSEINPUT mi) {
    INPUT ip;
    ip.type = INPUT_MOUSE;
    ip.mi = mi;
    SendInput(1, &ip, sizeof(INPUT));
}

int Core::ToScreenPosX(int x) {
    return((x * 0xFFFF) / this->DesktopSize.w);
}

int Core::ToScreenPosY(int y) {
    return((y * 0xFFFF) / this->DesktopSize.h);
}

int Core::ToAbsoluteScreenPosX(int x) {
    return ((x + this->ActiveWindowRect.position.x) * 0xFFFF / this->DesktopSize.w);
}

int Core::ToAbsoluteScreenPosY(int y) {
    return ((y + this->ActiveWindowRect.position.y) * 0xFFFF / this->DesktopSize.h);
}

/*public*/
void Core::Recycle() {
    if (_instance) {
        delete _instance;
        _instance = NULL;
    }
}

Core* Core::GetInstance() {
    if (!_instance) {
        _instance = new Core();
        _instance->Init();
    }
    return _instance;
}

std::string wcharToString(wchar_t* buffer) {
    std::wstring str(buffer);
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string utf8_string = converter.to_bytes(str);
    delete[] buffer;
    return utf8_string;
}

BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam) {
    if (!IsWindowVisible(hwnd)) {
        return true;
    }
    else {
        int length = GetWindowTextLengthW(hwnd);
        ///if (0 == length) return TRUE;
        Core* core = Core::GetInstance();
        wchar_t* buffer = new wchar_t[length + 1];
        GetWindowTextW(hwnd, buffer, length);
        std::string name = wcharToString(buffer);
        /*std::wstring str(buffer);
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string utf8_string = converter.to_bytes(str);*/
        //delete[] buffer;

        //delete[] buffer;
        ProcInfo procInfo;
        procInfo.name = name;
        procInfo.hwnd = (int)hwnd;
        core->AppendProcInfo(procInfo);
    }
    return true;
};

std::vector<ProcInfo> Core::GetAllWindows() {
    this->_procInfos = std::vector<ProcInfo>();
    EnumWindows(enumWindowsProc, 0);
    return this->_procInfos;
}

void Core::SendCharByScanCode(int scanCode) {
    KEYBDINPUT kiDown = CreateKeyInputByScan(scanCode);
    KEYBDINPUT kiUp = Clone(kiDown);
    kiUp.dwFlags = 0x0008 | 0x0002;
    SendKeyInput(kiDown);
    SendKeyInput(kiUp);
}

void Core::SendKeyByVkValue(int vk) {
    KEYBDINPUT kiDown = CreateKeyInputByVk(vk);
    KEYBDINPUT kiUp = Clone(kiDown);
    kiUp.dwFlags = 0x0008 | 0x0002;
    SendKeyInput(kiDown);
    SendKeyInput(kiUp);
}

void Core::SendKey(std::string str) {
    int vk = VK::GetVK(toUpper(str));
    SendKeyByVkValue(vk);
}

/**/

void Core::KeyDownByVKValue(int vk)
{
    KEYBDINPUT kiDown = CreateKeyInputByVk(vk);
    SendKeyInput(kiDown);
}

void Core::KeyDown(std::string vkKey) {
    int vk = VK::GetVK(toUpper(vkKey));
    KeyDownByVKValue(vk);
}

void Core::KeyUpByVKValue(int vk) {
    KEYBDINPUT kiUp = CreateKeyInputByVk(vk);
    kiUp.dwFlags = 0x0008 | 0x0002;
    SendKeyInput(kiUp);
}

void Core::KeyUp(std::string vkKey) {
    int vk = VK::GetVK(toUpper(vkKey));
    KeyUpByVKValue(vk);
}

void Core::SendChar(char ch) {
    KEYBDINPUT kiDown = CreateKeyInputByChar(ch);
    KEYBDINPUT kiUp = Clone(kiDown);
    kiUp.dwFlags = 0x0002;
    SendKeyInput(kiDown);
    SendKeyInput(kiUp);
}

void Core::CombinationKeyByVKValue(std::vector<int> vks) {
    for (int vk : vks)
        KeyDownByVKValue(vk);
    for (int vk : vks)
        KeyUpByVKValue(vk);
}

void Core::CombinationKey(std::vector<std::string> vkKeys) {
    for (std::string vkKey : vkKeys) {
        KeyDown(vkKey);
    }
    std::reverse(vkKeys.begin(), vkKeys.end());
    for (std::string vkKey : vkKeys)
        KeyUp(vkKey);
}

void Core::MouseMove(int x, int y) {
    SendMouseInput(CreateMouseInput(ToScreenPosX(x), ToScreenPosY(y), 0X8000 | 0X0001));
}

void Core::MouseMoveR(int x, int y) {
    SendMouseInput(CreateMouseInput(ToAbsoluteScreenPosX(x), ToAbsoluteScreenPosY(y), 0X8000 | 0X0001));
}

int Core::GetScreenX() {
    return GetWinSize(GetDesktopWindow()).w;
}

int Core::GetScreenY() {
    return GetWinSize(GetDesktopWindow()).h;
}

Size Core::GetWinSize() {
    return GetWinSize(GetDesktopWindow());
}

Size Core::GetWinSize(HWND hwnd) {
    RECT rect;
    GetWindowRect(hwnd, &rect);
    return Size(rect.right - rect.left, rect.bottom - rect.top);
}

Rect Core::GetWinRect(HWND hwnd) {
    RECT rect;
    GetWindowRect(hwnd, &rect);
    return Rect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
}

Rect Core::GetWinRect() {
    return GetWinRect(GetDesktopWindow());
}

void Core::SetActiveWindow(HWND hwnd) {
    if (IsWindow(hwnd)) {
        Rect r = this->GetWinRect(hwnd);
        this->ActiveWindowRect = r;
    }
}

void Core::SetActiveWindow(std::string name) {
    ProcInfo pi = GetProcInfoByName(name);
    SetActiveWindow((HWND)pi.hwnd);
}

Point Core::GetMousePosition() {
    CURSORINFO cursorInfo;
    cursorInfo.cbSize = sizeof(CURSORINFO);
    cursorInfo.hCursor = GetCursor();
    cursorInfo.flags = 0x00000001;
    GetCursorInfo(&cursorInfo);
    return Point(cursorInfo.ptScreenPos.x, cursorInfo.ptScreenPos.y);
}

boolean Core::RegisterHotKeyWithId(int id, unsigned int modifierKey, unsigned int key) {
    return RegisterHotKey(NULL, id, modifierKey, key);
}

WPARAM Core::GetMessageReceived() {
    MSG msg = { 0 };
    if (GetMessage(&msg, NULL, 0, 0) != 0 && msg.message == WM_HOTKEY)
        return  msg.wParam;
    return 0;
}

void Core::MouseLeftDown()
{
    SendMouseInput(MouseInputDict[KEY_MouseLeftDown]);
}

void Core::MouseLeftUp()
{
    SendMouseInput(MouseInputDict[KEY_MouseLeftUp]);
}

void Core::MouseMiddleDown() {
    SendMouseInput(MouseInputDict[KEY_MouseMiddleDown]);
}

void Core::MouseMiddleUp() {
    SendMouseInput(MouseInputDict[KEY_MouseMiddleUp]);
}

void Core::MouseRightDown() {
    SendMouseInput(MouseInputDict[KEY_MouseRightDown]);
}

void Core::MouseRightUp() {
    SendMouseInput(MouseInputDict[KEY_MouseRightUp]);
}

void Core::MouseWheel(int value) {
    SendMouseInput(CreateMouseInput(0, 0, 0x0800, value));
}

long Core::GetPixelAtCursorPosition() {
    POINT _cursor;
    GetCursorPos(&_cursor);
    return GetPixelAt(_cursor.x, _cursor.y);
}

long Core::GetPixelAt(int x, int y) {
    HINSTANCE _hGDI = LoadLibrary("gdi32.dll");
    if (_hGDI)
    {
        HDC _hdc = GetDC(NULL);
        if (_hdc)
        {
            COLORREF _color = GetPixel(_hdc, x, y);
            return _color;
        }
        FreeLibrary(_hGDI);
    }
    return 0;
}

Color Core::PixelToColor(long pixelValue) {
    Color c;
    c.r = GetRValue(pixelValue);
    c.g = GetGValue(pixelValue);
    c.g = GetBValue(pixelValue);
    return c;
}

void Core::AppendProcInfo(ProcInfo procInfo) {
    this->_procInfos.push_back(procInfo);
}

ProcInfo Core::GetProcInfoByName(std::string name) {
    std::vector<ProcInfo> procInfos = GetAllWindows();
    for (ProcInfo pi : procInfos) {
        if (strstr(pi.name.c_str(), name.c_str())) {
            return pi;
        }
    }
    return ProcInfo();
}

void Core::SwitchToWindow(HWND hwnd) {
    SwitchToThisWindow(hwnd, true);
}

void Core::SwitchToWindow(std::string name) {
    ProcInfo pi = GetProcInfoByName(name);
    SwitchToWindow((HWND)pi.hwnd);
}