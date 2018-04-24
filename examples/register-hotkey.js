const Core = require('../core');
const VK = require('../vk');
const HotkeyModifiers = require('../hotkey-modifiers');
const Utils = require('util');
//if installed by package, using:
//const Lib = require('windows-automator-lib');
//const Core = Lib.Core;
//const VK = Lib.VK;
//const HotkeyModifiers = Lib.HotkeyModifiers;

/*
example of register hotkey
*/

function registerHotkey(id, keyEventConfig) {
  var keyId = parseInt(id);
  var success = Core.regHotKey(keyId, keyEventConfig.modKey, keyEventConfig.key);
  if(!success) {
    throw Utils.format('register key :%s failed', keyId);
  }
}

var keyEventMap = {
  1: {
    modKey: HotkeyModifiers.CONTROL|HotkeyModifiers.SHIFT,
    key: VK.H,
    handler: function() {
      console.log('handle event 1');
    }
  },
  2: {
    modKey: HotkeyModifiers.CONTROL,
    key: VK.G,
    handler: function() {
      console.log('handle event 2');
    }
  }
};

function onKey() {
  var keyId = Core.getHotKeyMsg();
  if(keyId in keyEventMap) {
    keyEventMap[keyId].handler();
  }
}

try {
  for(var key in keyEventMap) {
    registerHotkey(key, keyEventMap[key]);
  }
  onKey();
}
catch(e) {
  console.log(e);
}