var Core = require('../core');

var wheelValue = -20;
Core.mouseWheel(wheelValue);
Core.mouseLeftClick();
Core.mouseRightClick();
Core.mouseMiddleClick();

Core.mouseMove(1440,900);
console.log(Core.getMousePosition());

//move to relative position within active window
/*we should set active window first*/
var rect = Core.getActiveWindowRect();
console.log(rect);
//capture window which title contains specified name
Core.setActiveWindowByName("Desktop");
/*
or by hwnd
Core.setActiveWindow(hwnd);
*/
var rect = Core.getActiveWindowRect();
console.log(rect);
Core.mouseMoveRelative(25,25);
