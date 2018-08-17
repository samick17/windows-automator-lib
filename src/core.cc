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
    mi.time = 0;
    mi.dwExtraInfo = 0;
    mi.mouseData = data;
    mi.dwFlags = flag != 0 ? flag : 0x0001;
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

int Core::ToOffsetPosX(int x, Point pt) {
    return ((x + pt.x) * 0xFFFF / this->DesktopSize.w);
}

int Core::ToOffsetPosY(int y, Point pt) {
    return ((y + pt.y) * 0xFFFF / this->DesktopSize.h);
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
        Core* core = Core::GetInstance();
        wchar_t* buffer = new wchar_t[length + 1];
        GetWindowTextW(hwnd, buffer, length + 1);
        std::string name = wcharToString(buffer);
        ProcInfo procInfo;
        procInfo.name = name;
        procInfo.hwnd = (int)hwnd;
        core->AppendProcInfo(procInfo);
    }
    return true;
};

BOOL CALLBACK enumWindowsProp(HWND hwnd, LPTSTR lpszString, HANDLE hData, ULONG_PTR dwData) {
    //printf("asdasd");
    if (!IsWindowVisible(hwnd)) {
        return true;
    }
    else {
        Core* core = Core::GetInstance();
        PropInfo propInfo;

        UINT rc;
        ATOM atmText;
        atmText=GlobalFindAtom(lpszString);
        std::string strText;

        #if defined(_UNICODE)
        {
            wchar_t szBuf[MAX_PATH] = { 0 };
            GlobalGetAtomNameW(atmText, szBuf, _countof(szBuf));
            rc=GetAtomName(atmText,szBuf,_countof(szBuf));
            wstring ws(txt);
            strText(ws.begin(), ws.end());
        }
        #else
        {
            char szBuf[MAX_PATH] = { 0 };
            rc=GlobalGetAtomNameA(atmText, szBuf, _countof(szBuf));
            strText=szBuf;
        }
        #endif
        
        propInfo.name = strText;

        propInfo.hwnd = (int)hwnd;
        core->AppendPropInfo(propInfo);
    }
    return true;
};

std::vector<ProcInfo> Core::GetAllWindows() {
    this->_procInfos = std::vector<ProcInfo>();
    EnumWindows(enumWindowsProc, 0);
    return this->_procInfos;
}

std::vector<ProcInfo> Core::GetChildWindowsById(HWND hwnd) {
    this->_procInfos = std::vector<ProcInfo>();
    EnumChildWindows(hwnd, enumWindowsProc, 0);
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

void Core::MouseMoveRelative(int x, int y) {
    SendMouseInput(CreateMouseInput(ToAbsoluteScreenPosX(x), ToAbsoluteScreenPosY(y), 0X8000 | 0X0001));
}

void Core::MouseMoveOffset(int x, int y) {
    Point pt = GetMousePosition();
    SendMouseInput(CreateMouseInput(ToOffsetPosX(x, pt), ToOffsetPosY(y, pt), 0X8000 | 0X0001));
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
    SendMouseInput(CreateMouseInput(0, 0, MOUSEEVENTF_WHEEL, value));
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

void Core::AppendPropInfo(PropInfo propInfo) {
    this->_propInfos.push_back(propInfo);
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

void Core::HideWindow(HWND hwnd) {
    CloseWindow(hwnd);
}

void Core::HideWindow(std::string name) {
    ProcInfo pi = GetProcInfoByName(name);
    HideWindow((HWND)pi.hwnd);
}

void Core::DestroyWindow(HWND hwnd) {
    PostMessage(hwnd, WM_CLOSE, 0, 0);
}

void Core::DestroyWindow(std::string name) {
    ProcInfo pi = GetProcInfoByName(name);
    this->DestroyWindow((HWND)pi.hwnd);
}

void Core::CaptureScreenToClipBoard(HWND hwnd) {
    int x1, y1, x2, y2, w, h;
    RECT rect;
    GetWindowRect(hwnd, &rect);

    // get screen dimensions
    x1  = rect.left;
    y1  = rect.top;
    x2  = rect.right;
    y2  = rect.bottom;
    w   = x2 - x1;
    h   = y2 - y1;

    // copy screen to bitmap
    HDC     hScreen = GetDC(hwnd);
    HDC     hDC     = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL    bRet    = BitBlt(hDC, 0, 0, w, h, hScreen, 0, 0, SRCCOPY);

    // save bitmap to clipboard
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hBitmap);
    CloseClipboard();

    // clean up
    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    DeleteObject(hBitmap);
}

ImageData Core::CaptureScreen(HWND hwnd) {
    int x1, y1, x2, y2, w, h;
    RECT rect;
    GetWindowRect(hwnd, &rect);

    // get screen dimensions
    x1  = rect.left;
    y1  = rect.top;
    x2  = rect.right;
    y2  = rect.bottom;
    w   = x2 - x1;
    h   = y2 - y1;

    // copy screen to bitmap
    HDC     hScreen = GetDC(hwnd);
    HDC     hDC     = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL    bRet    = BitBlt(hDC, 0, 0, w, h, hScreen, 0, 0, SRCCOPY);

    BITMAP bmp;
    GetObject(hBitmap, sizeof(bmp), &bmp);

    BITMAPINFO info { };
    info.bmiHeader.biSize = sizeof(info.bmiHeader);
    info.bmiHeader.biWidth = bmp.bmWidth;
    // pay attention to the sign, you most likely want a 
    // top-down pixel array as it's easier to use
    info.bmiHeader.biHeight = -bmp.bmHeight;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 24;
    info.bmiHeader.biCompression = BI_RGB;

    // the following calculations work for 16/24/32 bits bitmaps 
    // but assume a byte pixel array
    size_t pixelSize = info.bmiHeader.biBitCount / 8;
    // the + 3 ) & ~3 part is there to ensure that each
    // scan line is 4 byte aligned
    size_t scanlineSize = (pixelSize * info.bmiHeader.biWidth + 3) & ~3;
    size_t bitmapSize = bmp.bmHeight * scanlineSize;

    std::vector<BYTE> pixels(bitmapSize);
    GetDIBits(hDC, hBitmap, 0, bmp.bmHeight, &pixels[0], &info, DIB_RGB_COLORS);

    for (LONG y = 0; y < bmp.bmHeight; y++)
    {
        for (LONG x = 0; x < bmp.bmWidth; x++)
        {
                    size_t pixelOffset = y * scanlineSize + x * pixelSize;
            COLORREF color = RGB(
                pixels[pixelOffset + 2],
                pixels[pixelOffset + 1],
                pixels[pixelOffset + 0]);
            SetPixel(hDC, x, y, color);
        }
    }

    // clean up
    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    DeleteObject(hBitmap);
    ImageData imgData;
    imgData.width = bmp.bmWidth;
    imgData.height = bmp.bmHeight;
    imgData.data = pixels;
    return imgData;
}

std::string Core::GetTextById(HWND hwnd) {
    int length = GetWindowTextLengthW(hwnd);
    wchar_t* buffer = new wchar_t[length + 1];
    GetWindowTextW(hwnd, buffer, length + 1);
    std::string name = wcharToString(buffer);
    return name;
}

std::vector<PropInfo> Core::GetWindowProperties(HWND hwnd) {
    this->_propInfos = std::vector<PropInfo>();
    PropInfo propInfo;
    this->AppendPropInfo(propInfo);
    EnumPropsEx(hwnd, enumWindowsProp, NULL);
    return this->_propInfos;
}
