#include <node.h>
#include <v8.h>
#include <vector>
#include <iostream>
#include "core.h"

class V8Wrapper {
public:
    V8Wrapper(const v8::FunctionCallbackInfo<v8::Value>& args) : _args(args) {
        //this->args = args;
        this->_isolate = args.GetIsolate();
        v8::HandleScope scope(this->_isolate);
    }
    virtual ~V8Wrapper() {
    }
    void returnVal(char* data) {
        this->_args.GetReturnValue().Set(this->toV8(data));
    }
    void returnVal(std::string data) {
        this->_args.GetReturnValue().Set(this->toV8(data));
    }
    void returnVal(int data) {
        this->_args.GetReturnValue().Set(this->toV8(data));
    }
    void returnVal(boolean data) {
        this->_args.GetReturnValue().Set(this->toV8(data));
    }
    void returnVal(std::vector<int> data) {
        this->_args.GetReturnValue().Set(this->toV8(data));
    }
    void returnVal(std::vector<std::string> data) {
        this->_args.GetReturnValue().Set(this->toV8(data));
    }
    void returnVal(Point data) {
        this->_args.GetReturnValue().Set(this->toV8(data));
    }
    void returnVal(Size data) {
        this->_args.GetReturnValue().Set(this->toV8(data));
    }
    void returnVal(Rect data) {
        this->_args.GetReturnValue().Set(this->toV8(data));
    }
    void returnVal(Color data) {
        this->_args.GetReturnValue().Set(this->toV8(data));
    }
    void returnVal(std::vector<ProcInfo> data) {
        this->_args.GetReturnValue().Set(this->toV8(data));
    }
    int getInt(int argIndex) {
        if (this->_args.Length() > argIndex) {
            return (int)this->_args[argIndex]->ToInteger()->Value();
        }
        else {
            return 0;
        }
    }
    std::vector<int> getIntegerArray(int argIndex) {
        std::vector<int> intArray;
        if (this->_args.Length() > argIndex) {
            v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(this->_args[argIndex]);
            int length = (int)array->Length();
            for (int i = 0; i < length; i++) {
                int foo = array->Get(i)->Int32Value();
                intArray.push_back(foo);
            }
            return intArray;
        }
        else {
            return intArray;
        }
    }
    std::vector<std::string> getStringArray(int argIndex) {
        std::vector<std::string> strArray;
        if (this->_args.Length() > argIndex) {
            v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(this->_args[argIndex]);
            int length = (int)array->Length();
            for (int i = 0; i < length; i++) {
                std::string foo = V8StrToString(array->Get(i)->ToString());
                strArray.push_back(foo);
            }
            return strArray;
        }
        else {
            return strArray;
        }
    }
    std::string getString(int argIndex) {
        if (this->_args.Length() > argIndex) {
            return V8StrToString(this->_args[argIndex]->ToString());
        }
        else {
            return 0;
        }
    }
    std::wstring getWString(int argIndex) {
        if (this->_args.Length() > argIndex) {
            std::string foo = V8StrToString(this->_args[argIndex]->ToString());
            std::wstring ws;
            ws.assign(foo.begin(), foo.end());
            return ws;
        }
        else {
            return 0;
        }
    }
private:
    const v8::FunctionCallbackInfo<v8::Value>& _args;
    v8::Isolate* _isolate;
    v8::Local<v8::String> toV8(char* data) {
        return v8::String::NewFromUtf8(this->_isolate, data);
    }
    v8::Local<v8::String> toV8(std::string data) {
        return v8::String::NewFromUtf8(this->_isolate, data.c_str());
    }
    v8::Local<v8::Integer> toV8(int data) {
        return v8::Int32::New(this->_isolate, data);
    }
    v8::Local<v8::Boolean> toV8(boolean data) {
        return v8::Boolean::New(this->_isolate, data);
    }
    v8::Local<v8::Array> toV8(std::vector<int> arr) {
        int length = (int)arr.size();
        v8::Local<v8::Array> array = v8::Array::New(this->_isolate, length);
        for (int i = 0; i < length; i++) {
            array->Set(i, toV8(arr[i]));
        }
        return array;
    }
    v8::Local<v8::Array> toV8(std::vector<std::string> arr) {
        int length = (int)arr.size();
        v8::Local<v8::Array> array = v8::Array::New(this->_isolate, length);
        for (int i = 0; i < length; i++) {
            array->Set(i, toV8(arr[i]));
        }
        return array;
    }
    v8::Local<v8::Object> toV8(Point obj) {
        v8::Local<v8::Object> v8Obj = v8::Object::New(this->_isolate);
        v8Obj->Set(toV8("x"), toV8(obj.x));
        v8Obj->Set(toV8("y"), toV8(obj.y));
        return v8Obj;
    }
    v8::Local<v8::Object> toV8(Size obj) {
        v8::Local<v8::Object> v8Obj = v8::Object::New(this->_isolate);
        v8Obj->Set(toV8("w"), toV8(obj.w));
        v8Obj->Set(toV8("h"), toV8(obj.h));
        return v8Obj;
    }
    v8::Local<v8::Object> toV8(Rect obj) {
        v8::Local<v8::Object> v8Obj = v8::Object::New(this->_isolate);
        v8Obj->Set(toV8("x"), toV8(obj.position.x));
        v8Obj->Set(toV8("y"), toV8(obj.position.y));
        v8Obj->Set(toV8("w"), toV8(obj.size.w));
        v8Obj->Set(toV8("h"), toV8(obj.size.h));
        return v8Obj;
    }
    v8::Local<v8::Object> toV8(Color obj) {
        v8::Local<v8::Object> v8Obj = v8::Object::New(this->_isolate);
        v8Obj->Set(toV8("r"), toV8(obj.r));
        v8Obj->Set(toV8("g"), toV8(obj.g));
        v8Obj->Set(toV8("b"), toV8(obj.b));
        return v8Obj;
    }
    v8::Local<v8::Array> toV8(std::vector<ProcInfo> arr) {
        int length = (int)arr.size();
        v8::Local<v8::Array> array = v8::Array::New(this->_isolate, length);
        for (int i = 0; i < length; i++) {
            ProcInfo pi = arr[i];
            v8::Local<v8::Object> v8Obj = v8::Object::New(this->_isolate);
            v8Obj->Set(toV8("name"), toV8(pi.name));
            v8Obj->Set(toV8("hwnd"), toV8(pi.hwnd));
            array->Set(i, v8Obj);
        }
        return array;
    }
    static std::string V8StrToString(v8::Local<v8::String> str) {
        v8::String::Utf8Value param1(str);
        std::string resultStr = std::string(*param1);
        return resultStr;
    }
};

/**/
/*example */
/*
void Method(const v8::FunctionCallbackInfo<v8::Value>& args) {
    V8Wrapper wrapper = V8Wrapper(args);
    //TODO do something
    //TODO get arg here
    v8::Local<v8::String> str = args[0]->ToString();
    //TODO return value here
    std::vector<int> arr = { 2, 2, 2, 34, 4, 5, 6, 6 };
    wrapper.returnVal(arr);
}*/

void GetWindowSize(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        HWND hwnd = (HWND)wrapper.getInt(0);
        Size size = core->GetWinSize(hwnd);
        wrapper.returnVal(size);
    }
    else {
        Size size = core->GetWinSize();
        wrapper.returnVal(size);
    }
}

void GetWindowRect(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        HWND hwnd = (HWND)wrapper.getInt(0);
        Rect rect = core->GetWinRect(hwnd);
        wrapper.returnVal(rect);
    }
    else {
        Rect rect = core->GetWinRect();
        wrapper.returnVal(rect);
    }
}

void GetActiveWindowRect(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    wrapper.returnVal(core->ActiveWindowRect);
}

void MouseMove(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 2 && args[0]->IsInt32() && args[1]->IsInt32()) {
        core->MouseMove(wrapper.getInt(0), wrapper.getInt(1));
    }
}

void MouseMoveRelative(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 2 && args[0]->IsInt32() && args[1]->IsInt32()) {
        core->MouseMoveRelative(wrapper.getInt(0), wrapper.getInt(1));
    }
}

void MouseMoveOffset(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 2 && args[0]->IsInt32() && args[1]->IsInt32()) {
        core->MouseMoveOffset(wrapper.getInt(0), wrapper.getInt(1));
    }
}

void SendKey(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsString()) {
        core->SendKey(wrapper.getString(0));
    }
}

void SendCharByScanCode(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        core->SendCharByScanCode(wrapper.getInt(0));
    }
}

void KeyDownByVKValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        core->KeyDownByVKValue(wrapper.getInt(0));
    }
}

void KeyDown(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsString()) {
        core->KeyDown(wrapper.getString(0));
    }
}

void KeyUpByVKValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        core->KeyUpByVKValue(wrapper.getInt(0));
    }
}

void KeyUp(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsString()) {
        core->KeyUp(wrapper.getString(0));
    }
}

void CombinationKey(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsArray()) {
        core->CombinationKey(wrapper.getStringArray(0));
    }
}

void CombinationKeyByVKValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsArray()) {
        core->CombinationKeyByVKValue(wrapper.getIntegerArray(0));
    }
}

void GetAllWindows(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    wrapper.returnVal(core->GetAllWindows());
}

void GetChildWindowsById(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        HWND hwnd = (HWND)wrapper.getInt(0);
        wrapper.returnVal(core->GetChildWindowsById(hwnd));
    }
}

void SwitchToWindow(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        core->SwitchToWindow((HWND)wrapper.getInt(0));
    }
}

void SwitchToWindowByName(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsString()) {
        core->SwitchToWindow(wrapper.getString(0));
    }
}

void SetActiveWindow(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        core->SetActiveWindow((HWND)wrapper.getInt(0));
    }
}

void SetActiveWindowByName(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsString()) {
        core->SetActiveWindow(wrapper.getString(0));
    }
}

void GetMousePosition(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    wrapper.returnVal(core->GetMousePosition());
}

void RegHotKey(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 3 && args[0]->IsInt32() && args[1]->IsInt32() && args[2]->IsInt32()) {
        boolean success = core->RegisterHotKeyWithId(wrapper.getInt(0), wrapper.getInt(1), wrapper.getInt(2));
        wrapper.returnVal(success);
    }
}

void GetHotKeyMsg(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    wrapper.returnVal((int)core->GetMessageReceived());
}

void MouseLeftDown(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    core->MouseLeftDown();
}

void MouseLeftUp(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    core->MouseLeftUp();
}

void MouseLeftClick(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    core->MouseLeftDown();
    core->MouseLeftUp();
}

void MouseMiddleDown(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    core->MouseMiddleDown();
}

void MouseMiddleUp(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    core->MouseMiddleUp();
}

void MouseMiddleClick(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    core->MouseMiddleDown();
    core->MouseMiddleUp();
}

void MouseRightDown(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    core->MouseRightDown();
}

void MouseRightUp(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    core->MouseRightUp();
}

void MouseRightClick(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    core->MouseRightDown();
    core->MouseRightUp();
}

void MouseWheel(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        core->MouseWheel(wrapper.getInt(0));
    }
}

void HideWindow(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        core->HideWindow((HWND)wrapper.getInt(0));
    }
}

void HideWindowByName(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsString()) {
        core->HideWindow(wrapper.getString(0));
    }
}

void DestroyWindow(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        core->DestroyWindow((HWND)wrapper.getInt(0));
    }
}

void DestroyWindowByName(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsString()) {
        core->DestroyWindow(wrapper.getString(0));
    }
}

void CaptureScreen(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        core->CaptureScreen((HWND)wrapper.getInt(0));
    }
}

void GetTextById(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Core* core = Core::GetInstance();
    V8Wrapper wrapper = V8Wrapper(args);
    if (args.Length() == 1 && args[0]->IsInt32()) {
        wrapper.returnVal(core->GetTextById((HWND)wrapper.getInt(0)));
    }
}

void init(v8::Local<v8::Object> target) {
    NODE_SET_METHOD(target, "getWindowSize", GetWindowSize);
    NODE_SET_METHOD(target, "getWindowRect", GetWindowRect);
    NODE_SET_METHOD(target, "getActiveWindowRect", GetActiveWindowRect);
    NODE_SET_METHOD(target, "mouseMove", MouseMove);
    NODE_SET_METHOD(target, "mouseMoveRelative", MouseMoveRelative);
    NODE_SET_METHOD(target, "mouseMoveOffset", MouseMoveOffset);
    NODE_SET_METHOD(target, "sendKey", SendKey);
    NODE_SET_METHOD(target, "sendCharByScanCode", SendCharByScanCode);
    NODE_SET_METHOD(target, "keyDownByVKValue", KeyDownByVKValue);
    NODE_SET_METHOD(target, "keyDown", KeyDown);
    NODE_SET_METHOD(target, "keyUpByVKValue", KeyUpByVKValue);
    NODE_SET_METHOD(target, "keyUp", KeyUp);
    NODE_SET_METHOD(target, "combinationKey", CombinationKey);
    NODE_SET_METHOD(target, "combinationKeyByVKValue", CombinationKeyByVKValue);
    NODE_SET_METHOD(target, "getAllWindows", GetAllWindows);
    NODE_SET_METHOD(target, "getChildWindowsById", GetChildWindowsById);
    NODE_SET_METHOD(target, "switchToWindow", SwitchToWindow);
    NODE_SET_METHOD(target, "switchToWindowByName", SwitchToWindowByName);
    NODE_SET_METHOD(target, "setActiveWindow", SetActiveWindow);
    NODE_SET_METHOD(target, "setActiveWindowByName", SetActiveWindowByName);
    NODE_SET_METHOD(target, "getMousePosition", GetMousePosition);
    NODE_SET_METHOD(target, "regHotKey", RegHotKey);
    NODE_SET_METHOD(target, "getHotKeyMsg", GetHotKeyMsg);
    NODE_SET_METHOD(target, "mouseLeftDown", MouseLeftDown);
    NODE_SET_METHOD(target, "mouseLeftUp", MouseLeftUp);
    NODE_SET_METHOD(target, "mouseLeftClick", MouseLeftClick);
    NODE_SET_METHOD(target, "mouseMiddleDown", MouseMiddleDown);
    NODE_SET_METHOD(target, "mouseMiddleUp", MouseMiddleUp);
    NODE_SET_METHOD(target, "mouseMiddleClick", MouseMiddleClick);
    NODE_SET_METHOD(target, "mouseRightDown", MouseRightDown);
    NODE_SET_METHOD(target, "mouseRightClick", MouseRightClick);
    NODE_SET_METHOD(target, "mouseRightUp", MouseRightUp);
    NODE_SET_METHOD(target, "mouseWheel", MouseWheel);
    NODE_SET_METHOD(target, "hideWindow", HideWindow);
    NODE_SET_METHOD(target, "hideWindowByName", HideWindowByName);
    NODE_SET_METHOD(target, "closeWindow", DestroyWindow);
    NODE_SET_METHOD(target, "closeWindowByName", DestroyWindowByName);
    NODE_SET_METHOD(target, "captureScreen", CaptureScreen);
    NODE_SET_METHOD(target, "getTextById", GetTextById);
}

NODE_MODULE(Automator, init);