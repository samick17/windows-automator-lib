#include "vk.h"
#include <string>
#include <map>

int VK::GetVK(std::string str) {
    std::map<std::string, int> vkMap;

    vkMap["TAB"] = 0x09;
    vkMap["RETURN"] = 0x0D;
    vkMap["SHIFT"] = 0x10;
    vkMap["CONTROL"] = 0x11;
    vkMap["ALT"] = 0x12;
    vkMap["SPACE"] = 0x20;
    vkMap["ESCAPE"] = 0x1B;
    vkMap["HOME"] = 0x24;
    vkMap["END"] = 0x23;
    vkMap["PAGE_UP"] = 0x21;
    vkMap["PAGE_DOWN"] = 0x22;
    vkMap["LEFT"] = 0x25;
    vkMap["UP"] = 0x26;
    vkMap["RIGHT"] = 0x27;
    vkMap["DOWN"] = 0x28;
    vkMap["INSERT"] = 0x2D;
    vkMap["DELETE"] = 0x2E;
    vkMap["LWIN"] = 0x5B;
    vkMap["RWIN"] = 0x5C;
    vkMap["F1"] = 0x70;
    vkMap["F2"] = 0x71;
    vkMap["F3"] = 0x72;
    vkMap["F4"] = 0x73;
    vkMap["F5"] = 0x74;
    vkMap["F6"] = 0x75;
    vkMap["F7"] = 0x76;
    vkMap["F8"] = 0x77;
    vkMap["F9"] = 0x78;
    vkMap["F10"] = 0x79;
    vkMap["F11"] = 0x7A;
    vkMap["F12"] = 0x7B;
    vkMap["F13"] = 0x7C;
    vkMap["F14"] = 0x7D;
    vkMap["F15"] = 0x7E;
    vkMap["F16"] = 0x7F;
    vkMap["F17"] = 0x80;
    vkMap["F18"] = 0x81;
    vkMap["F19"] = 0x82;
    vkMap["F20"] = 0x83;
    vkMap["F21"] = 0x84;
    vkMap["F22"] = 0x85;
    vkMap["F23"] = 0x86;
    vkMap["F24"] = 0x87;
    vkMap["CAPS_LOCK"] = 0x14;
    vkMap["NUM_LOCK"] = 0x90;
    vkMap["SCROLL_LOCK"] = 0x91;
    vkMap["L_SHIFT"] = 0xA0;
    vkMap["R_SHIFT"] = 0xA1;
    vkMap["L_CONTROL"] = 0xA2;
    vkMap["R_CONTROL"] = 0xA3;
    vkMap["L_ALT"] = 0xA4;
    vkMap["R_ALT"] = 0xA5;
    vkMap["L_WIN"] = 0x5B;
    vkMap["R_WIN"] = 0x6C;
    vkMap["MULTIPLY"] = 0x6A;
    vkMap["ADD"] = 0x6B;
    vkMap["SEPARATOR"] = 0x6C;
    vkMap["SUBTRACT"] = 0x6D;
    vkMap["DECIMAL"] = 0x6E;
    vkMap["DEVICE"] = 0x6F;
    vkMap["SNAPSHOT"] = 0x2C;
    vkMap["0"] = 0x30;
    vkMap["1"] = 0x31;
    vkMap["2"] = 0x32;
    vkMap["3"] = 0x33;
    vkMap["4"] = 0x34;
    vkMap["5"] = 0x35;
    vkMap["6"] = 0x36;
    vkMap["7"] = 0x37;
    vkMap["8"] = 0x38;
    vkMap["9"] = 0x39;
    vkMap["A"] = 0x41;
    vkMap["B"] = 0x42;
    vkMap["C"] = 0x43;
    vkMap["D"] = 0x44;
    vkMap["E"] = 0x45;
    vkMap["F"] = 0x46;
    vkMap["G"] = 0x47;
    vkMap["H"] = 0x48;
    vkMap["I"] = 0x49;
    vkMap["J"] = 0x4A;
    vkMap["K"] = 0x4B;
    vkMap["L"] = 0x4C;
    vkMap["M"] = 0x4D;
    vkMap["N"] = 0x4E;
    vkMap["O"] = 0x4F;
    vkMap["P"] = 0x50;
    vkMap["Q"] = 0x51;
    vkMap["R"] = 0x52;
    vkMap["S"] = 0x53;
    vkMap["T"] = 0x54;
    vkMap["U"] = 0x55;
    vkMap["V"] = 0x56;
    vkMap["W"] = 0x57;
    vkMap["X"] = 0x58;
    vkMap["Y"] = 0x59;
    vkMap["Z"] = 0x5A;
    vkMap["NUM_0"] = 0x60;
    vkMap["NUM_1"] = 0x61;
    vkMap["NUM_2"] = 0x62;
    vkMap["NUM_3"] = 0x63;
    vkMap["NUM_4"] = 0x64;
    vkMap["NUM_5"] = 0x65;
    vkMap["NUM_6"] = 0x66;
    vkMap["NUM_7"] = 0x67;
    vkMap["NUM_8"] = 0x68;
    vkMap["NUM_9"] = 0x69;
    vkMap["OEM_1"] = 0xBA;//the "; =" key
    vkMap["OEM_2"] = 0xBF;//the "/?" key
    vkMap["OEM_3"] = 0xC0;//the "~" key
    vkMap["OEM_COMMA"] = 0xBC;//the ";" key
    vkMap["OEM_MINUS"] = 0xBD;//the "-" key
    vkMap["OEM_PERIOD"] = 0xBE;//the "." key
    vkMap["OEM_PLUS"] = 0xBB;//the "+" key


    return vkMap[str];
}